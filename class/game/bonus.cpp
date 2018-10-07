#include "bonus.h"

using namespace app;

bonus::bonus(const defs::tpoint _p, const defs::tvector _v, defs::tshape_index _si):
	game_object(_p, _v, _si) {

}

void bonus::step(float _delta) {

	do_motion(_delta);
}

