#include "world.h"

#include <tools/converters/converters.h>

using namespace app;

world::world():
	//TODO: Should actually come from somewhere...
	world_bounds{0,0,700,500},
	crap(0.f) {

	projectiles.reserve(max_projectiles);
}

void world::step(float _delta, const shape_manager& _shape_man) {

	//TODO: Ratio of malus:bonus, fixed 4:1, make it compulsory!

	skeeper.angle+=_delta * 90.f;
	skeeper.angle=fmod(skeeper.angle, 360.f);

	crap+=_delta;

	if(crap > 0.2f) {
		crap=0.f;

		//TODO: Keep a maximum size of shit!!!!

		defs::tvector v=vector_from_angle_and_magnitude<defs::tunit>(skeeper.angle, 50);
		projectiles.push_back(
			tptr_projectile(
				new projectile(defs::tpoint(350, 200), v)
			)
		);
	}

	for(auto &p : projectiles) {
		p->step(_delta);
	}

	purge_actors(_shape_man);
}

void world::add_drawables(std::vector<const drawable *>& v) {

	for(auto &p : projectiles) {
		v.push_back(p.get());
	}
}

size_t world::get_object_count() const {

	return projectiles.size();
}

std::vector<const spatiable*> world::get_collisionables() const {

	std::vector<const spatiable *> result;

	for(const auto& p : projectiles) {
		result.push_back( &(*p));
	}
	
	return result;
}

void world::purge_actors(const shape_manager& _shape_man) {

	auto check_bound=[this, &_shape_man](const spatiable* _go) {

		//TODO: This is a bit absurd... We could just check a center and some margin against the box.
		const auto poly=_go->get_poly(_shape_man);
		return !ldt::box_from_poly(poly).collides_with(world_bounds);
	};

	auto it=std::remove_if(std::begin(projectiles), std::end(projectiles), [check_bound](const tptr_projectile& _p) {
		return check_bound(_p.get());
	});

	projectiles.erase(it, std::end(projectiles));
}
