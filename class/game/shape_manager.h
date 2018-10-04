#ifndef GAME_SHAPE_MANAGER_H
#define GAME_SHAPE_MANAGER_H

#include <map>
#include <string>

#include <class/dnot_token.h>

#include "defs.h"


namespace app {

//!Manages the shapes. Should be loaded with a different class.

class shape_manager {

	public:


	//!Creates the instance.
				shape_manager();

	//!Creates the class and loads a file.
				shape_manager(const std::string&);

	//!Returns a copy of the indexed shape.
	defs::tpoly		get(defs::tshape_index) const;

	//!Truncates the current map and loads a new one from file.
	void			load(const std::string&);

	private:

	//!Validates and inserts a shape.
	void			parse_shape(const tools::dnot_token&);
	//!Validates and returns a point.
	defs::tpoint		parse_point(const tools::dnot_token&);

	std::map<defs::tshape_index, defs::tpoly>	container;

};

}

#endif
