#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "player_input.h"
#include "drawable.h"
#include "spatiable.h"

namespace app {


class player:
	public drawable,
	public spatiable {

	public:

			player();

	int		get_life() const {return life;}
	bool		has_life() const {return life > 0;}
	bool		is_invulnerable() const {return invulnerability_time > 0.;}

	void		hit();
	void		set_input(const player_input _pi);
	void		step(float _delta);

	//Spatiable implementation
	defs::tpoly		get_poly(const shape_manager&) const;
	defs::tshape_index	get_shape() const {return defs::square;}

	//Drawable implementation
	void		transform_draw_struct(draw_struct&) const;

	private:

	int		life;
	float		invulnerability_time;
};

}

#endif
