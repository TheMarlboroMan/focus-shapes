#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>

#include "defs.h"
#include "shape_manager.h"
#include "projectile.h"

namespace app {

struct status_keeper {

	defs::tangle	angle;

			status_keeper():
				angle(0) {
	
	}
};

class world {

	public:

	typedef				std::unique_ptr<projectile>	tptr_projectile;

					world();
	void				step(float, const shape_manager&);
	void				add_drawables(std::vector<const drawable *>&);
	size_t				get_object_count() const;
	std::vector<const spatiable*>	get_collisionables() const;


	private:

	void				purge_actors(const shape_manager&);

	static const size_t		max_projectiles=500;

	defs::tbox 			world_bounds;
	status_keeper			skeeper;
	std::vector<tptr_projectile>	projectiles;
	float				crap;
};

}

#endif
