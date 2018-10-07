#include "player.h"

using namespace app;

player::player():
	game_object(defs::tpoint(200, 200), defs::tvector(0,0), defs::square),
	life{255}, invulnerability_time{0.f} {

}

void player::hit() {

	if(!invulnerability_time) {
		invulnerability_time=1.0f;

		life-=20;
		if(life < 0) {
			life=0;
		}
	}
}

void player::set_input(const player_input _pi) {

	set_vector_x(_pi.x * 100.f);
	set_vector_y(_pi.y * 100.f);
}

void player::step(float _delta) {

	do_motion(_delta);

	if(invulnerability_time > 0.f) {
		invulnerability_time-=_delta;
		invulnerability_time=invulnerability_time > 0.f ? invulnerability_time : 0.f;
	}
}

void player::transform_draw_struct(draw_struct& _ds) const {

/*
	auto poly=shape_man.get(_type);
	poly.rotation_center_in(_pt);
	if(_angle) {
		poly.rotate(_angle);
	}

	return poly;

	const auto poly=poly_from_points(_p.get_point(), _p.get_shape());

	auto color=_p.is_invulnerable() 
		? ldv::rgba8(255, 255, 255, _p.get_life()) 
		: ldv::rgba8(0, 0, 255, _p.get_life());

	auto drawable_poly=ldt::representation_from_primitive(poly, color);
	drawable_poly.set_blend(ldv::representation::blends::alpha);
	drawable_poly.draw(_screen);
*/

	//TODO: Just so we can compile.
	_ds.rep;
}
