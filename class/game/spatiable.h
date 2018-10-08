#ifndef SPATIABLE_H
#define SPATIABLE_H

#include "defs.h"
#include "shape_manager.h"

namespace app {

class spatiable {

	public:

	virtual defs::tpoly	get_poly(const shape_manager&) const=0;

};

}

#endif
