#ifndef GAME_DEFS_H
#define GAME_DEFS_H

#include <tools/vector_2d/vector_2d.h>
#include <tools/point_2d/point_2d.h>
#include <tools/polygon_2d/polygon_2d.h>
#include <tools/box/box.h>

namespace app {

struct defs {

	typedef		double			tunit;
	typedef		float			tangle;
	typedef 	ldt::vector_2d<tunit> 	tvector;
	typedef		ldt::point_2d<tunit>	tpoint;
	typedef		ldt::polygon_2d<tunit>	tpoly;
	typedef		ldt::box<tunit, tunit>	tbox;

	typedef		int tshape_index;
	enum 		shape_types {square=1, triangle};

};


}

#endif
