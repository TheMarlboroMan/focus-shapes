#ifndef SPATIABLE_H
#define SPATIABLE_H

#include "defs.h"
#include "shape_manager.h"

namespace app {

class spatiable {

	public:

	virtual defs::tpoly		get_poly(const shape_manager&) const=0;
	virtual defs::tshape_index	get_shape() const=0;

				spatiable(const defs::tpoint _p={0.0, 0.0}, const defs::tvector _v=defs::tvector{0.,0.});
	defs::tpoint		get_point() const {return point;}
	defs::tvector		get_vector() const {return vector;}

	void			set_point(defs::tpoint _v) {point=_v;}
	void			set_vector(defs::tvector _v) {vector=_v;}
	void			set_vector_x(defs::tunit _v) {vector.x=_v;}
	void			set_vector_y(defs::tunit _v) {vector.y=_v;}
	void			do_motion(float _delta);

	private:

	defs::tpoint				point;
	defs::tvector				vector;

};

}

#endif
