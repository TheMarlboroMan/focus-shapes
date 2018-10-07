#include "bonus.h"

using namespace app;

bonus::bonus(const defs::tpoint _p, const defs::tvector _v, defs::tshape_index _si):
	game_object(_p, _v, _si) {

}

void bonus::step(float _delta) {

	do_motion(_delta);
}

void bonus::transform_draw_struct(draw_struct& _ds) const {

/*
	//TODO: Shit...
	const auto poly=poly_from_points(_p.get_point(), _p.get_shape(), _p.get_angle());

	//Now, this poly is convertible to a drawable type-
	//TODO: What about the color????
	auto drawable_poly=ldt::representation_from_primitive(poly, ldv::rgba8(255, 0, 0, 128));
	drawable_poly.set_blend(ldv::representation::blends::alpha);
	drawable_poly.draw(_screen);
*/

	//TODO: Just so we can compile.
	_ds.rep;
}
