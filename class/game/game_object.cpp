#include "game_object.h"

using namespace app;

game_object::game_object(const defs::tpoint _p, const defs::tvector _v, defs::tshape_index _si):
	point(_p), vector(_v), shape(_si) {

}

void game_object::do_motion(float _delta) {

	point.x+=vector.x * _delta;
	point.y+=vector.y * _delta;
}
