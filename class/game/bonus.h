#ifndef BONUS_H
#define BONUS_H

#include "drawable.h"
#include "collisionable.h"

namespace app {

class bonus:
	public drawable,
	public collisionable {

	public:

			bonus(const defs::tpoint, const defs::tvector);
	void		step(float);
	bool		must_be_erased() const {return erase_me;}


	//Collisionable+Spatiable implementation
	void	 		confirm_collision(collision_data& _cd);
	defs::tpoly		get_poly(const shape_manager&) const;
	defs::tshape_index	get_shape() const {return defs::square;}

	//Drawable implementation ----------------
	void			transform_draw_struct(draw_struct&) const;

	
	private:

	bool			erase_me=false;
};

}

#endif
