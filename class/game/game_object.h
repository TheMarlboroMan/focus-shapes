#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "defs.h"

namespace app {

class game_object {

	public:

				game_object(const defs::tpoint _p, const defs::tvector _v=defs::tvector{0.,0.}, defs::tshape_index=defs::square);
	defs::tpoint		get_point() const {return point;}
	defs::tvector		get_vector() const {return vector;}
	defs::tshape_index	get_shape() const {return shape;}

	void			set_vector_x(defs::tunit _v) {vector.x=_v;}
	void			set_vector_y(defs::tunit _v) {vector.y=_v;}

	protected:

	void		do_motion(float _delta);

	private:

	defs::tpoint				point;
	defs::tvector				vector;
	defs::tshape_index			shape;

};


}

#endif
