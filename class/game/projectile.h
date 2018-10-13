#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "drawable.h"
#include "spatiable.h"

namespace app {

class projectile:
	public drawable,
	public spatiable {

	public:

			projectile(const defs::tpoint, const defs::tvector);
	void		step(float);

	//Spatiable implementation
	defs::tpoly		get_poly(const shape_manager&) const;
	defs::tshape_index	get_shape() const {return defs::triangle;}

	//Drawable implementation ---------------
	void		transform_draw_struct(draw_struct&) const;
	
	private:

	defs::tangle				angle;
};

}

#endif
