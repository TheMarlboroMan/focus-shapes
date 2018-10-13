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
#include "../game/world.h"
#include "../game/player.h"
#include "../game/shape_manager.h"

namespace app
{

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

	player_input				get_player_input(dfw::input&);
	void					do_player_collision_check(player&, const std::vector<collisionable *>&);

	//references...
	tools::log&				log;

	//properties
	ldv::camera				camera;
	tools::ttf_manager			ttf_man;
	world					world_instance;
	game_data				gdata;
	shape_manager				shape_man;
	//TODO: Add multiple players????
	//TODO: Move player to the world???
	player					player_instance;
	float					stupid;
};

}

#endif
