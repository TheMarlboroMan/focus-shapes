#include "spatiable.h"

using namespace app;

spatiable::spatiable(const defs::tpoint _p, const defs::tvector _v):
	point(_p), vector(_v) {

}

void spatiable::do_motion(float _delta) {

	point.x+=vector.x * _delta;
	point.y+=vector.y * _delta;
}
