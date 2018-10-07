#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "game_object.h"
#include "drawable.h"

namespace app {

class projectile:
	public game_object,
	public drawable {

	public:

			projectile(const defs::tpoint, const defs::tvector, defs::tshape_index=defs::square);
	defs::tangle	get_angle() const {return angle;}

	//Drawable implementation ---------------
	void		transform_draw_struct(draw_struct&) const;

	//Game object implementation ------------
	void		step(float);
	
	private:

	defs::tangle				angle;
};

}

#endif
