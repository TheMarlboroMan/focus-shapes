#include "bonus.h"

#include <tools/converters/converters.h>

using namespace app;

bonus::bonus(const defs::tpoint _p, const defs::tvector _v):
	collisionable(_p, _v) {

}

void bonus::step(float _delta) {

	do_motion(_delta);
}

void bonus::transform_draw_struct(draw_struct& _ds) const {

	const auto poly=get_poly(_ds.shape_man);
	auto points=ldt::vector_of_representation_points_from_vertices(get_poly(_ds.shape_man).get_vertices());
	_ds.set_type(draw_struct::types::polygon);
	_ds.set_polygon_points(points, true);
	_ds.set_blend(ldv::representation::blends::alpha);
	_ds.set_color(ldv::rgba8(0, 255, 0, 128));
}

defs::tpoly bonus::get_poly(const shape_manager& _shape_man) const {

	auto poly=_shape_man.get(get_shape());
	poly.rotation_center_in(get_point());

	return poly;
}

void bonus::confirm_collision(collision_data& _cd, size_t /*_index*/) {

	if(!erase_me) {
		_cd.score+=100;
		erase_me=true;
	}
}
