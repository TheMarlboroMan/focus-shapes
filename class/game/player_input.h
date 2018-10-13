#ifndef GAME_PLAYER_INPUT_H
#define GAME_PLAYER_INPUT_H

namespace app {

struct player_input {

	int		x, y;
	bool		activate;
	
			player_input():
				x{0}, y{0}, activate{false} {
	}
};


}

#endif
