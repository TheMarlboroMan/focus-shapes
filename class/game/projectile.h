#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "game_object.h"
#include "drawable.h"

namespace app {

class projectile:
	public game_object,
	public drawable,
	public spatiable {

	public:

			projectile(const defs::tpoint, const defs::tvector, defs::tshape_index=defs::square);
	defs::tangle	get_angle() const {return angle;}

	//Spatiable implementation
	defs::tpoly	get_poly(const shape_manager&) const;

	//Drawable implementation ---------------
	void		transform_draw_struct(draw_struct&) const;

	//Game object implementation ------------
	void		step(float);
	
	private:

	defs::tangle				angle;
};

}

#endif
