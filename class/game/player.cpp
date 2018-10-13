#include "player.h"

#include <tools/converters/converters.h> 

using namespace app;

player::player():
	spatiable(defs::tpoint(0, 0), defs::tvector(0,0)),
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

	auto color=is_invulnerable() 
		? ldv::rgba8(255, 255, 255, life) 
		: ldv::rgba8(0, 0, 255, life);


	auto points=ldt::vector_of_representation_points_from_vertices(get_poly(_ds.shape_man).get_vertices());
	_ds.set_type(draw_struct::types::polygon);
	_ds.set_polygon_points(points, true);
	_ds.set_blend(ldv::representation::blends::alpha);
	_ds.set_color(color);
}

defs::tpoly player::get_poly(const shape_manager& _shape_man) const {

	auto poly=_shape_man.get(get_shape());
	poly.rotation_center_in(get_point());

	return poly;
}
