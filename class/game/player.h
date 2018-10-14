#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <vector>

#include "player_input.h"
#include "player_segment.h"


namespace app {

class player {

	public:

			player();

	bool		is_invulnerable() const {return invulnerability_time > 0.;}
	std::vector<spatiable const *>	get_spatiables() const;
	size_t		get_length() const {return segments.size();}

	void		add_drawables(std::vector<drawable const *>&);
	void		hit(size_t);
	void		set_input(const player_input _pi);
	void		step(float _delta);
	void		add_segment();

	private:

	static const float		inv_time;
	static const double		speed;
	static const int		max_segment_radius=8;
	static const size_t		max_length=10;

	std::vector<player_segment>	segments;

	float		invulnerability_time;
};

}

#endif
