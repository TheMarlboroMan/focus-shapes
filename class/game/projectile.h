#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "game_object.h"

namespace app {

class projectile:
	public game_object {

	public:

			projectile(const defs::tpoint, const defs::tvector, defs::tshape_index=defs::square);
	defs::tangle	get_angle() const {return angle;}
	void		step(float);
	
	private:

	defs::tangle				angle;
};

}

#endif
