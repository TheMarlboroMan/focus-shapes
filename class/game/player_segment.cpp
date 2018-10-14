#include "player_segment.h"
#include <tools/converters/converters.h> 


using namespace app;

player_segment::player_segment(float& _it, defs::tpoint _pt):
	spatiable(_pt, defs::tvector(0,0)), invulnerable{&_it} {

}

void player_segment::transform_draw_struct(draw_struct& _ds) const {

	auto color=*invulnerable
		? ldv::rgba8(255, 255, 255, 255) 
		: ldv::rgba8(0, 0, 255, 128);

	auto points=ldt::vector_of_representation_points_from_vertices(get_poly(_ds.shape_man).get_vertices());
	_ds.set_type(draw_struct::types::polygon);
	_ds.set_polygon_points(points, true);
	_ds.set_blend(ldv::representation::blends::alpha);
	_ds.set_color(color);
}

defs::tpoly player_segment::get_poly(const shape_manager& _shape_man) const {

	auto poly=_shape_man.get(get_shape());
	poly.rotation_center_in(get_point());

	return poly;
}
