#include "bonus.h"

using namespace app;

bonus::bonus(const defs::tpoint _p, const defs::tvector _v, defs::tshape_index _si):
	game_object(_p, _v, _si) {

}

void bonus::step(float _delta) {

	do_motion(_delta);
}

void bonus::transform_draw_struct(draw_struct& _ds) const {

	const auto poly=get_poly(_ds.shape_man);
/*
	//TODO: Shit...
	const auto poly=poly_from_points(_p.get_point(), _p.get_shape(), _p.get_angle());

	auto drawable_poly=ldt::representation_from_primitive(poly, ldv::rgba8(0, 255, 0, 128));

	_ds.set_type(x);
	_ds.set_poly(drawable_poly);
	_ds.set_blend(ldv::representation::blends::alpha);
*/
}

defs::tpoly bonus::get_poly(const shape_manager& _shape_man) const {

	auto poly=_shape_man.get(get_shape());
	poly.rotation_center_in(get_point());
	} 

	return poly;
}
