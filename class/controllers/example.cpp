#include "example.h"

#include <algorithm>

#include <tools/converters/converters.h>

//local
#include "../input.h"

//app
#include "../game/player_input.h"
#include "../game/shape_manager.h"



using namespace app;

controller_example::controller_example(tools::log& plog)
	:log(plog) {

	//TODO: This should be injected somewhere else...
	ttf_man.insert("main_font", 10, "data/fonts/ConsolaMono.ttf");

	//TODO: This should be injected somewhere else too...
	shape_manager sm("data/app/shapes.dnot");
}

void controller_example::loop(dfw::input& input, const dfw::loop_iteration_data& lid) {

	if(input().is_exit_signal() || input.is_input_down(input_app::escape)) {
		set_leave(true);
		return;
	}

	skeeper.angle+=lid.delta * 90.f;
	skeeper.angle=fmod(skeeper.angle, 360.f);

	if(input().is_event_input()) {

		defs::tvector v=vector_from_angle_and_magnitude<defs::tunit>(skeeper.angle, 50);
		projectiles.push_back(projectile(defs::tpoint(350, 200), v));
	}

	const auto pi=get_player_input(input);
	player_instance.get_input(pi);

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

	const auto poly=poly_from_points(_p.get_point(), _p.get_angle());

	//Now, this poly is convertible to a drawable type-
	auto drawable_poly=ldt::representation_from_primitive(poly, ldv::rgba8(255, 0, 0, 128));
	drawable_poly.set_blend(ldv::representation::blends::alpha);

	//I'd like to draw the bounding box now...
//	auto drawable_box=ldt::representation_from_primitive(ldt::box_from_poly(poly), ldv::rgba8(255, 255, 255, 64));
//	drawable_box.set_blend(ldv::representation::blends::alpha);

	//And draw the whole shit.
//	drawable_box.draw(_screen);
	drawable_poly.draw(_screen);
}

void	controller_example::draw_player_instance(ldv::screen& _screen, const player& _p) {

	const auto poly=poly_from_points(_p.get_point());

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
		const auto poly=poly_from_points(_p.get_point(), _p.get_angle());
		return !ldt::box_from_poly(poly).collides_with(screen_bound);
	});

	projectiles.erase(it, std::end(projectiles));
}


void controller_example::do_player_collision_check(player& _pl, const std::vector<projectile>& _vp) {

	const auto player_poly=poly_from_points(_pl.get_point());

	for(const auto& p: _vp) {
		//TODO :Use bounding boxes, check if we can go faster that way!.
		const auto poly=poly_from_points(p.get_point(), p.get_angle());
		if(ldt::SAT_collision_check(player_poly, poly)) {
			_pl.hit();
		}
	}
}

//TODO: This is so wasteful.
//TODO: Incorporate dictionaries of shapes and such, instead 
//TODO: Again, use the center as the handle...
app::defs::tpoly	controller_example::poly_from_points(defs::tpoint _pt, defs::tangle _angle) {

	//TODO: We should be able to use the shape manager to get a shape and
	//then center it in the center, so to say... 
	//There's a "poly.rotation_center_in", which we can use and be happy.

	defs::tbox box{_pt.x, _pt.y, 20., 20.};
	auto poly=ldt::poly_from_box(box);
	poly.set_rotation_center(poly.get_centroid());
	if(_angle) {
		poly.rotate(_angle);
	}

	return poly;
}
