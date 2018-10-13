#ifndef BONUS_H
#define BONUS_H

#include "drawable.h"
#include "spatiable.h"

namespace app {

class bonus:
	public drawable,
	public spatiable {

	public:

			bonus(const defs::tpoint, const defs::tvector);
	void		step(float);


	//Spatiable implementation
	defs::tpoly		get_poly(const shape_manager&) const;
	defs::tshape_index	get_shape() const {return defs::square;}

	//Drawable implementation ----------------
	void		transform_draw_struct(draw_struct&) const;

	
	private:

};

}

#endif
