#ifndef GAME_SHAPE_MANAGER_H
#define GAME_SHAPE_MANAGER_H

#include <map>

#include "defs.h"

namespace app {


class shape_manager {

	public:

	enum class ptype {square, triangle};

	const defs::tpoly&	get(ptype);
	void			insert(ptype, const defs::tpoly&);

	private:

	std::map<ptype, defs::tpoly>	container;

};

}

#endif
