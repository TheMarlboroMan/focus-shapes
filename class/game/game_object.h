#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "defs.h"

namespace app {

class game_object {

	public:

			game_object(const defs::tpoint _p, const defs::tvector _v):
		point(_p), vector(_v) {

	}

	defs::tpoint	get_point() const {return point;}
	defs::tvector	get_vector() const {return vector;}

	void		set_vector_x(defs::tunit _v) {vector.x=_v;}
	void		set_vector_y(defs::tunit _v) {vector.y=_v;}

	protected:

	//TODO: Separate implementation
	void		do_motion(float _delta) {

		point.x+=vector.x * _delta;
		point.y+=vector.y * _delta;
	}

	private:

	defs::tpoint				point;
	defs::tvector				vector;

};


}

#endif
