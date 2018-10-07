#ifndef BONUS_H
#define BONUS_H

#include "game_object.h"
#include "drawable.h"

namespace app {

class bonus:
	public game_object,
	public drawable {

	public:

			bonus(const defs::tpoint, const defs::tvector, defs::tshape_index=defs::square);

	//Drawable implementation ----------------
	void		transform_draw_struct(draw_struct&) const;

	//Game object implementation -------------
	void		step(float);
	
	private:

};

}

#endif
