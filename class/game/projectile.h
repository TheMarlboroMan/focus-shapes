#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "drawable.h"
#include "collisionable.h"

namespace app {

class projectile:
	public drawable,
	public collisionable {

	public:

			projectile(const defs::tpoint, const defs::tvector);
	void		step(float);
	bool		must_be_erased() const {return erase_me;}

	//collisionable+spatiable implementation
	void	 		confirm_collision(collision_data& _cd);
	defs::tpoly		get_poly(const shape_manager&) const;
	defs::tshape_index	get_shape() const {return defs::triangle;}

	//Drawable implementation ---------------
	void		transform_draw_struct(draw_struct&) const;
	
	private:

	defs::tangle				angle;
	bool					erase_me=false;
};

}

#endif
