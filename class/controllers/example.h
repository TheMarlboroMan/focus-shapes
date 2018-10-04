#ifndef CONTROLLER_TEMPLATE_H
#define CONTROLLER_TEMPLATE_H

//std
#include <cmath>

//libdansdl2
#include <def_video.h>


//tools
#include <class/ttf_manager.h>

//framework
#include <class/controller_interface.h>

//local
#include "states.h"

//app
#include "../game/defs.h"
#include "../game/player_input.h"
#include "../game/projectile.h"
#include "../game/player.h"
#include "../game/shape_manager.h"

namespace app
{

struct status_keeper {

	defs::tangle	angle;

			status_keeper():
				angle(0) {
	
	}
};

class controller_example:
	public dfw::controller_interface {

	public:

						controller_example(tools::log&);
	virtual void 				loop(dfw::input&, const dfw::loop_iteration_data&);
	virtual void 				draw(ldv::screen&, int);
	virtual void 				awake(dfw::input& /*input*/) {}
	virtual void 				slumber(dfw::input& /*input*/) {}
	virtual bool				can_leave_state() const {return true;}

	private:

	void					draw_projectile(ldv::screen&, const projectile&);
	void					draw_player_instance(ldv::screen&, const player&);
	player_input				get_player_input(dfw::input&);
	void					purge_actors();
	void					do_player_collision_check(player&, const std::vector<projectile>&);

	defs::tpoly				poly_from_points(defs::tpoint, defs::tshape_index, defs::tangle=0.f);

	//references...
	tools::log&				log;

	//properties
	tools::ttf_manager			ttf_man;
	status_keeper				skeeper;
	shape_manager				shape_man;
	//TODO: Add multiple players????
	player					player_instance;
	std::vector<projectile>			projectiles;

};

}

#endif
