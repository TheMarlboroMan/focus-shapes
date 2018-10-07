#ifndef CONTROLLER_TEMPLATE_H
#define CONTROLLER_TEMPLATE_H

//std
#include <cmath>
#include <memory>
#include <vector>

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

struct game_data {

	unsigned int		score;

	game_data():score(0) {

	}

	void			reset() {

		score=0;
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

	typedef	std::unique_ptr<game_object>	tptr_game_object;

	player_input				get_player_input(dfw::input&);
	void					purge_actors();
	void					do_player_collision_check(player&, const std::vector<tptr_game_object>&);

	//references...
	tools::log&				log;

	//properties
	tools::ttf_manager			ttf_man;
	status_keeper				skeeper;
	game_data				gdata;
	shape_manager				shape_man;
	//TODO: Add multiple players????
	player					player_instance;
	std::vector<tptr_game_object>		game_objects;

};

}

#endif
