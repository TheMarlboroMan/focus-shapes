#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "game_object.h"
#include "player_input.h"

namespace app {

class player:
	public game_object {

	public:

			player();

	int		get_life() const {return life;}
	bool		has_life() const {return life > 0;}
	bool		is_invulnerable() const {return invulnerability_time > 0.;}

	void		hit();
	void		set_input(const player_input _pi);
	void		step(float _delta);

	private:

	int		life;
	float		invulnerability_time;
};

}

#endif
