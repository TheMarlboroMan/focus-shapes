#include "world.h"

#include <class/number_generator.h>

using namespace app;

world::world():
	//TODO: Should actually come from somewhere...
	world_bounds{0,0,700,500},
	crap(0.f) {

	projectiles.reserve(max_projectiles);
	bonuses.reserve(max_bonuses);
}

void world::step(float _delta, const shape_manager& _shape_man) {

	//TODO: Ratio of malus:bonus, fixed 4:1, make it compulsory!

	skeeper.angle+=_delta * 90.f;
	skeeper.angle=fmod(skeeper.angle, 360.f);

	crap+=_delta;

	if(crap > 0.2f) {
		crap=0.f;


		tools::int_generator gen(1, 5);
		defs::tvector v=vector_from_angle_and_magnitude<defs::tunit>(skeeper.angle, 50);
		
		if(1!=gen()) {
			//TODO: Keep a maximum size of shit!!!!
			projectiles.push_back(
				tptr_projectile(
					new projectile(defs::tpoint(350, 200), v)
				)
			);
		}
		else {
			//TODO: Keep a maximum size of shit!!!!
			bonuses.push_back(
				tptr_bonus(
					new bonus(defs::tpoint(350, 200), v)
				)
			);
		}
	}

	step_list(projectiles, _delta);
	step_list(bonuses, _delta);

	purge_actors(_shape_man);
}


void world::add_drawables(std::vector<const drawable *>& _v) const {

	to_drawable_vector(projectiles, _v);
	to_drawable_vector(bonuses, _v);
}

size_t world::get_object_count() const {

	return projectiles.size()+bonuses.size();
}

std::vector<collisionable *> world::get_collisionables() {

	std::vector<collisionable  *> result;
	to_collisionable_vector(projectiles, result);
	to_collisionable_vector(bonuses, result);
	return result;
}

void world::purge_actors(const shape_manager& _shape_man) {

	//Erase the erasables...
	projectiles.erase(
		std::remove_if(std::begin(projectiles), std::end(projectiles), [](const tptr_projectile& _p) {
			return _p->must_be_erased();}
		), std::end(projectiles));

	bonuses.erase(
		std::remove_if(std::begin(bonuses), std::end(bonuses), [](const tptr_bonus& _b) {
			return _b->must_be_erased();}
		), std::end(bonuses));

	//Erase whatever is out of bounds...
	erase_out_of_bounds(projectiles, _shape_man);
	erase_out_of_bounds(bonuses, _shape_man);
}
