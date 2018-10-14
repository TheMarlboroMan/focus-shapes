#ifndef MOVEMENT_ENGINE_H
#define MOVEMENT_ENGINE_H

#include "defs.h"

namespace app;

struct movement_data {

	defs::tvector		vector;
	defs::tpoint		rotation_center;
};

class movement_engine {

	public:

	virtual void	step(defs::tpoint& _pos, float _delta, movement_data&)=0;
};

#endif
