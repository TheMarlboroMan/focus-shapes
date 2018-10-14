#ifndef PLAYER_SEGMENT_H
#define PLAYER_SEGMENT_H

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

	const float *		invulnerable;
};


}

#endif
