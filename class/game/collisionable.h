#ifndef COLLISIONABLE_H
#define COLLISIONABLE_H

#include "spatiable.h"

namespace app {

struct collision_data {

	int		score=0,
			hits=0;
};

class collisionable:
	public spatiable {

	public:

		collisionable(const defs::tpoint _p={0.0, 0.0}, const defs::tvector _v=defs::tvector{0.,0.})
			:spatiable(_p, _v) {}
					

	virtual void 			confirm_collision(collision_data&)=0;

	//Must implement from spatiable...
	virtual defs::tpoly		get_poly(const shape_manager&) const=0;
	virtual defs::tshape_index	get_shape() const=0;
};

}

#endif
