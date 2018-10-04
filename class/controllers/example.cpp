#include "example.h"

#include <algorithm>

#include <tools/converters/converters.h>

//local
#include "../input.h"

//app
#include "../game/player_input.h"



using namespace app;

controller_example::controller_example(tools::log& plog)
	:log(plog), shape_man("data/app/shapes.dnot") {

	//TODO: This should be injected somewhere else...
	ttf_man.insert("main_font", 10, "data/fonts/ConsolaMono.ttf");
}

void controller_example::loop(dfw::input& input, const dfw::loop_iteration_data& lid) {

	if(input().is_exit_signal() || input.is_input_down(input_app::escape)) {
		set_leave(true);
		return;
	}

	skeeper.angle+=lid.delta * 90.f;
	skeeper.angle=fmod(skeeper.angle, 360.f);

	//TODO: Ratio of malus:bonus, fixed 4:1, make it compulsory!
	//TODO: Change the rules...
	if(input().is_event_input()) {

		defs::tvector v=vector_from_angle_and_magnitude<defs::tunit>(skeeper.angle, 50);

		//TODO: Should push some other things...
		projectiles.push_back(projectile(defs::tpoint(350, 200), v, defs::triangle));
	}

	//TODO: Allow this...
	//shape_man.load("data/app/shapes.dnot");

	const auto pi=get_player_input(input);
	player_instance.set_input(pi);

	for(auto &p : projectiles) {
 		p.step(lid.delta);
	}

	player_instance.step(lid.delta);

	purge_actors();

	//TODO: Players should have a "tail" or something.

	do_player_collision_check(player_instance, projectiles);

	if(!player_instance.has_life()) {
		set_leave(true);
		return;
	}
}

void controller_example::draw(ldv::screen& _screen, int _fps) {

	_screen.clear(ldv::rgba8(0, 0, 0, 0));

	for(auto &p : projectiles) {
		draw_projectile(_screen, p);
	}

	draw_player_instance(_screen, player_instance);

	const auto& font=ttf_man.get("main_font", 10);
	ldv::ttf_representation txt(font, ldv::rgba8(255,255,255,255), std::to_string(projectiles.size())+" FPS: "+std::to_string(_fps)); 
	txt.draw(_screen);
}

void controller_example::draw_projectile(ldv::screen& _screen, const projectile& _p) {

	const auto poly=poly_from_points(_p.get_point(), _p.get_shape(), _p.get_angle());

	//Now, this poly is convertible to a drawable type-
	auto drawable_poly=ldt::representation_from_primitive(poly, ldv::rgba8(255, 0, 0, 128));
	drawable_poly.set_blend(ldv::representation::blends::alpha);
	drawable_poly.draw(_screen);
}

void	controller_example::draw_player_instance(ldv::screen& _screen, const player& _p) {

	const auto poly=poly_from_points(_p.get_point(), _p.get_shape());

	auto color=_p.is_invulnerable() 
		? ldv::rgba8(255, 255, 255, _p.get_life()) 
		: ldv::rgba8(0, 0, 255, _p.get_life());

	auto drawable_poly=ldt::representation_from_primitive(poly, color);
	drawable_poly.set_blend(ldv::representation::blends::alpha);
	drawable_poly.draw(_screen);
}

player_input controller_example::get_player_input(dfw::input& _input) {

	player_input result;

	if(_input.is_input_pressed(app::input_app::down)) {
		result.y=1;
	}
	else if(_input.is_input_pressed(app::input_app::up)) {
		result.y=-1;
	}

	if(_input.is_input_pressed(app::input_app::left)) {
		result.x=-1;
	}
	else if(_input.is_input_pressed(app::input_app::right)) {
		result.x=1;
	}

	return result;
}

void controller_example::purge_actors() {

	//TODO: This should not be... And you know it. Use the app config data.
	defs::tbox screen_bound={0,0,700,500};

	auto it=std::remove_if(std::begin(projectiles), std::end(projectiles), [screen_bound, this](const projectile& _p) {

		//TODO: This is a bit absurd... 
		//We could just check a center and some margin against the box.
		const auto poly=poly_from_points(_p.get_point(), _p.get_shape(), _p.get_angle());
		return !ldt::box_from_poly(poly).collides_with(screen_bound);
	});

	projectiles.erase(it, std::end(projectiles));
}


void controller_example::do_player_collision_check(player& _pl, const std::vector<projectile>& _vp) {

	//TODO: The poly from points is starting to get boring.... The class should know.
	const auto player_poly=poly_from_points(_pl.get_point(), _pl.get_shape());

	for(const auto& p: _vp) {
		//TODO :Use bounding boxes, check if we can go faster that way!.
		const auto poly=poly_from_points(p.get_point(), p.get_shape(), p.get_angle());
		if(ldt::SAT_collision_check(player_poly, poly)) {
			_pl.hit();
		}
	}
}

app::defs::tpoly controller_example::poly_from_points(defs::tpoint _pt, defs::tshape_index _type, defs::tangle _angle) {

	auto poly=shape_man.get(_type);
	poly.rotation_center_in(_pt);
	if(_angle) {
		poly.rotate(_angle);
	}

	return poly;
}
