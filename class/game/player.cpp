#include "player.h"

#include <tools/converters/converters.h> 

using namespace app;

player_segment::player_segment(float& _it, defs::tpoint _pt):
	spatiable(_pt, defs::tvector(0,0)), invulnerable{_it} {

}

void player_segment::transform_draw_struct(draw_struct& _ds) const {

	auto color=invulnerable
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

////////////

player::player():
	life{255}, invulnerability_time{0.f} {

	segments.push_back({invulnerability_time, {0.,0.}});
}

void player::hit() {

	if(!invulnerability_time) {
		invulnerability_time=1.0f;

		life-=20;
		if(life < 0) {
			life=0;
		}

		segments.pop_back();
	}
}

void player::set_input(const player_input _pi) {

	player_segment * prev=nullptr;
	for(auto& s : segments) {

		defs::tvector v={0., 0.};

		//The first one sets the vector.
		if(nullptr==prev) {
			v={(double)_pi.x, (double)_pi.y};

		}
		//The others set their vector relative to the previous...
		else {
			if(prev->get_point().distance_to(s.get_point()) >= 8) {
				v=ldt::vector_from_points(s.get_point(), prev->get_point());
			}
		}

		if(v.x || v.y) {
			v.normalize();
			s.set_vector(v*100.);
		}

		prev=&s;
	}
}

void player::step(float _delta) {

	for(auto& i : segments) {
		i.do_motion(_delta);
	}

	if(invulnerability_time > 0.f) {
		invulnerability_time-=_delta;
		invulnerability_time=invulnerability_time > 0.f ? invulnerability_time : 0.f;
	}
}

void player::add_drawables(std::vector<drawable const *>& _v) {

	for(const auto& i : segments) {
		_v.push_back(&i);
	}
}

std::vector<spatiable const *> player::get_spatiables() const {

	std::vector<spatiable const *> result;
	for(const auto& i : segments) {
		result.push_back(&i);
	}
	return result;
}

void player::add_segment() {

	player_segment s{invulnerability_time, segments.back().get_point()};
	segments.push_back(s);
	invulnerability_time=1.f;
}
