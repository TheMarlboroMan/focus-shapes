#include "projectile.h"

using namespace app;

projectile::projectile(const defs::tpoint _p, const defs::tvector _v, defs::tshape_index _si):
	game_object(_p, _v, _si), angle(0.f) {

}

void projectile::step(float _delta) {

	do_motion(_delta);
	angle=angle + (90.f * _delta);
}

void projectile::transform_draw_struct(draw_struct& _ds) const {

	const auto poly=get_poly(_ds.shape_man);
/*

	//Now, this poly is convertible to a drawable type-
	auto drawable_poly=ldt::representation_from_primitive(poly, ldv::rgba8(255, 0, 0, 128));

	_ds.set_type(x);
	_ds.set_poly(drawable_poly);
	_ds.set_blend(ldv::representation::blends::alpha);
*/
}

defs::tpoly projectile::get_poly(const shape_manager& _shape_man) const {

	auto poly=_shape_man.get(get_shape());
	poly.rotation_center_in(get_point());
	if(angle) {
		poly.rotate(angle);
	} 

	return poly;
}
