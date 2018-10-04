#include "projectile.h"

using namespace app;

projectile::projectile(const defs::tpoint _p, const defs::tvector _v, defs::tshape_index _si):
	game_object(_p, _v, _si), angle(0.f) {

}

void projectile::step(float _delta) {

	do_motion(_delta);
	angle=angle + (90.f * _delta);
}

