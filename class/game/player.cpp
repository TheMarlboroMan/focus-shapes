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
