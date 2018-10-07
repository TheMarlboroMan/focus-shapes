#ifndef BONUS_H
#define BONUS_H

#include "game_object.h"

namespace app {

class bonus:
	public game_object {

	public:

			bonus(const defs::tpoint, const defs::tvector, defs::tshape_index=defs::square);
	void		step(float);
	
	private:

};

}

#endif
