#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "game_object.h"

namespace app {

class projectile:
	public game_object {

	public:

	//TODO: Separate implementation.
			projectile(const defs::tpoint _p, const defs::tvector _v):
		game_object(_p, _v),  angle(0.f) {

	}

	defs::tangle	get_angle() const {return angle;}

	//TODO: Separate implementation.
	void		step(float _delta) {

		do_motion(_delta);
		angle=angle + (90.f * _delta);
	}
	
	private:

	defs::tangle				angle;
};

}

#endif
