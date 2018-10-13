#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>

#include <tools/converters/converters.h>

#include "defs.h"
#include "shape_manager.h"
#include "projectile.h"
#include "bonus.h"

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
	typedef				std::unique_ptr<bonus>		tptr_bonus;

					world();
	void				step(float, const shape_manager&);
	void				add_drawables(std::vector<const drawable *>&) const;
	size_t				get_object_count() const;
	std::vector<collisionable*>	get_collisionables();


	private:

	void				purge_actors(const shape_manager&);

	static const size_t		max_projectiles=500;
	static const size_t		max_bonuses=50;

	defs::tbox 			world_bounds;
	status_keeper			skeeper;
	std::vector<tptr_projectile>	projectiles;
	std::vector<tptr_bonus>		bonuses;
	float				crap;

	template <typename T>
	void step_list(T& _l, float _delta) { 
		for(auto &i : _l) {
			i->step(_delta);
		}
	}

	template <typename T>
	void to_drawable_vector(T& _l, std::vector<const drawable *>& _v) const {
		for(auto &i : _l) {
			_v.push_back(i.get());
		}
	}

	template <typename T>
	void to_collisionable_vector(T& _l, std::vector<collisionable *>& _v){
		for(auto &i : _l) {
			_v.push_back(i.get());
		}
	}

	template <typename T>
	void erase_out_of_bounds(std::vector<T>& _l, const shape_manager& _shape_man) {

		auto check_bound=[this, &_shape_man](const spatiable* _go) {

			//TODO: This is a bit absurd... We could just check a center and some margin against the box.
			const auto poly=_go->get_poly(_shape_man);
			return !ldt::box_from_poly(poly).collides_with(world_bounds);
		};

		_l.erase(
			std::remove_if(std::begin(_l), std::end(_l), [check_bound](const T& _p) {
				return check_bound(_p.get());
			})
		, std::end(_l));
	}

};

}

#endif
