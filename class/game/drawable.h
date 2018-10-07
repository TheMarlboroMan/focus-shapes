#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "draw_struct.h"


namespace app {

class drawable {

	public:

	virtual void	transform_draw_struct(draw_struct&) const=0;
};

}

#endif
