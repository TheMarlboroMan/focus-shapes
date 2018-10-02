#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "game_object.h"
#include "player_input.h"

namespace app {

class player:
	public game_object {

	public:

			player():
		game_object(defs::tpoint(200, 200), defs::tvector(0,0)),
		life{255}, invulnerability_time{0.f} {

	}

	int		get_life() const {return life;}
	bool		has_life() const {return life > 0;}
	bool		is_invulnerable() const {return invulnerability_time > 0.;}

	//TODO: Separate implementation.
	void		hit() {

		if(!invulnerability_time) {
			invulnerability_time=1.0f;

			life-=20;
			if(life < 0) {
				life=0;
			}
		}
	}

	void		get_input(const player_input _pi) {

		set_vector_x(_pi.x * 100.f);
		set_vector_y(_pi.y * 100.f);
	}

	void		step(float _delta) {

		do_motion(_delta);

		if(invulnerability_time > 0.f) {
			invulnerability_time-=_delta;
			invulnerability_time=invulnerability_time > 0.f ? invulnerability_time : 0.f;
		}
	}

	private:

	int		life;
	float		invulnerability_time;
};

}

#endif
