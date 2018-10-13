#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <vector>

#include "player_input.h"
#include "drawable.h"
#include "spatiable.h"

namespace app {

class player_segment:
	public drawable,
	public spatiable {

	public: 
				player_segment(float&, defs::tpoint);

	//Spatiable implementation
	defs::tpoly		get_poly(const shape_manager&) const;
	defs::tshape_index	get_shape() const {return defs::square;}

	//Drawable implementation
	void			transform_draw_struct(draw_struct&) const;

	private:

	const float&		invulnerable;
	

};

class player {

	public:

			player();

	int		get_life() const {return life;}
	bool		has_life() const {return life > 0;}
	bool		is_invulnerable() const {return invulnerability_time > 0.;}

	void		add_drawables(std::vector<drawable const *>&);
	std::vector<spatiable const *>	get_spatiables() const;
	void		hit();
	void		set_input(const player_input _pi);
	void		step(float _delta);
	void		add_segment();

	private:

	std::vector<player_segment>	segments;

	int		life;
	float		invulnerability_time;
};

}

#endif
