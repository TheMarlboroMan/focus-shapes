#include "player.h"

using namespace app;

player::player():
	invulnerability_time{0.f} {

	segments.push_back({invulnerability_time, {0.,0.}});
}

void player::hit() {

	if(!invulnerability_time) {
		invulnerability_time=1.0f;
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
