#include "example.h"

#include <algorithm>

//local
#include "../input.h"

//app
#include "../game/player_input.h"
#include "../game/drawable.h"
#include "../game/draw_struct.h"

using namespace app;

controller_example::controller_example(tools::log& plog)
	:log(plog), 
	//TODO: fuck this
	camera(ldv::rect(0,0,700,500), ldv::point(0,0)),
	shape_man("data/app/shapes.dnot") {

	camera.set_coordinate_system(ldv::camera::tsystem::cartesian);

	//TODO: This should be injected somewhere else...
	ttf_man.insert("main_font", 10, "data/fonts/ConsolaMono.ttf");
	ttf_man.insert("main_font", 20, "data/fonts/ConsolaMono.ttf");
}

void controller_example::loop(dfw::input& input, const dfw::loop_iteration_data& lid) {

	if(input().is_exit_signal() || input.is_input_down(input_app::escape)) {
		set_leave(true);
		return;
	}

	world_instance.step(lid.delta, shape_man);

	//TODO: Allow this...
	//shape_man.load("data/app/shapes.dnot");

	const auto pi=get_player_input(input);
	player_instance.set_input(pi);
	player_instance.step(lid.delta);

	//TODO: Players should have a "tail" or something.
	do_player_collision_check(player_instance, world_instance.get_collisionables());

	if(!player_instance.has_life()) {
		set_leave(true);
		return;
	}
}

void controller_example::draw(ldv::screen& _screen, int _fps) {

	//TODO: Perhaps a funky background?
	_screen.clear(ldv::rgba8(0, 0, 0, 0));

	//Create and fill drawable array...
	std::vector<const drawable *>	drawables;
	drawables.push_back(&player_instance);
	world_instance.add_drawables(drawables);

	draw_struct ds(shape_man);
	for(const auto& d : drawables) {
		d->transform_draw_struct(ds);
		ds.rep->draw(_screen, camera); 
	}

	const auto& font=ttf_man.get("main_font", 10);
	ldv::ttf_representation txt(font, ldv::rgba8(255,255,255,255), std::to_string(world_instance.get_object_count())+" FPS: "+std::to_string(_fps)); 
	txt.draw(_screen);

	//Draw score...
	const auto& score_font=ttf_man.get("main_font", 20);
	ldv::ttf_representation txt_score(score_font, ldv::rgba8(255,255,255,255), std::to_string(gdata.score)); 
	txt_score.align(
		ldv::rect(0,0, _screen.get_w(), _screen.get_h()),
		ldv::representation_alignment{
			ldv::representation_alignment::h::center,
			ldv::representation_alignment::v::inner_top,
			0, 0
		}
	);

	txt_score.draw(_screen);
}

player_input controller_example::get_player_input(dfw::input& _input) {

	player_input result;

	if(_input.is_input_pressed(app::input_app::down)) {
		result.y=-1;
	}
	else if(_input.is_input_pressed(app::input_app::up)) {
		result.y=1;
	}

	if(_input.is_input_pressed(app::input_app::left)) {
		result.x=-1;
	}
	else if(_input.is_input_pressed(app::input_app::right)) {
		result.x=1;
	}

	return result;
}

void controller_example::do_player_collision_check(player& _pl, const std::vector<const spatiable *>& _vs) {

	const auto player_poly=_pl.get_poly(shape_man);
	for(const auto& p: _vs) {

		const auto& go=*p;
		const auto poly=go.get_poly(shape_man);
		if(ldt::SAT_collision_check(player_poly, poly)) {

			//TODO: Will need some more work to separate bonuses and stuff.
			_pl.hit();
		}
	}
}
