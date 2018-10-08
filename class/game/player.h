#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "game_object.h"
#include "player_input.h"
#include "drawable.h"

namespace app {

class player:
	public game_object,
	public drawable,
	public spatiable {

	public:

			player();

	int		get_life() const {return life;}
	bool		has_life() const {return life > 0;}
	bool		is_invulnerable() const {return invulnerability_time > 0.;}

	void		hit();
	void		set_input(const player_input _pi);

	//Spatiable implementation
	defs::tpoly	get_poly(const shape_manager&) const;

	//Drawable implementation --------------------
	void		transform_draw_struct(draw_struct&) const;

	//Game object implementation -----------------
	void		step(float _delta);

	private:

	int		life;
	float		invulnerability_time;
};

}

#endif
