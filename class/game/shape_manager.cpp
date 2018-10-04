#include "shape_manager.h"

#include <class/dnot_parser.h>

using namespace app;

shape_manager::shape_manager() {

}

shape_manager::shape_manager(const std::string& _filename) {

	load(_filename);
}

defs::tpoly shape_manager::get(defs::tshape_index _t) const {

	if(!container.count(_t)) {
		throw std::runtime_error("shape_manager could not get shape");
	}

	return container.at(_t);
}

void shape_manager::load(const std::string& _filename) {

	container.clear();
	auto root=tools::dnot_parse_file(_filename);

	if(!root.is_map()) {
		throw std::runtime_error("malformed shape_manager file: root node must be a map");
	}

	if(!root.key_exists("shapes")) {
		throw std::runtime_error("malformed shape_manager file: root node must contain a 'shapes' node");
	}

	if(!root["shapes"].is_vector()) {
		throw std::runtime_error("malformed shape_manager file: shapes node must be of type vector");
	}

	for(const auto& _token : root["shapes"].get_vector()) {
		parse_shape(_token);
	}

}

//!Validates and parses a shape node. Allows for extra nodes, but each of the
//!compulsory nodes must be in place.
void shape_manager::parse_shape(const tools::dnot_token& _token) {

	//Validate format....

	if(!_token.is_map()) {
		throw std::runtime_error("malformed shape_manager file: found a non-map type into shapes vector");
	}

	if(!_token.key_exists("name") || !_token["name"].is_string_value()) {
		throw std::runtime_error("malformed shape_manager file: found a shape node with no name or with a node that is not a string value");
	}

	const std::string& name=_token["name"];

	if(!_token.key_exists("id") || !_token["id"].is_int_value()) {
		throw std::runtime_error("malformed shape_manager file: shape "+name+" does not have an id or it is not an integer value");
	}

	if(!_token.key_exists("vertices") || !_token["vertices"].is_vector()) {
		throw std::runtime_error("malformed shape_manager file: shape "+name+" does not have vertices or it is not of vector type");
	}

	if(!_token.key_exists("center") || !_token["center"].is_map()) {
		throw std::runtime_error("malformed shape_manager file: shape "+name+" does not have center or it is not of map type");
	}

	//Extract and parse information.

	std::vector<defs::tpoint> points;
	size_t iteration=0;
	for(const auto& tok : _token["vertices"].get_vector()) {
		try {
			points.push_back(parse_point(tok));
			++iteration;
		}
		catch(std::exception& e) {
			throw std::runtime_error("malformed shape_manager file: shape "+name+" vertices failed in vertex "+std::to_string(iteration)+" with "+e.what());
		}
	}

	defs::tpoint center(0,0);
	try {
		center=parse_point(_token["center"]);
	}
	catch(std::exception& e) {
		throw std::runtime_error("malformed shape_manager file: shape "+name+" center failed with "+e.what());
	}

	//Insert the node...
	int id=_token["id"];

	if(container.count(id)) {
		throw std::runtime_error("shape_manager could not insert shape with repeated id "+name);
	}

	container[id]=defs::tpoly(points, center);
}

defs::tpoint shape_manager::parse_point(const tools::dnot_token& _token) {

	if(!_token.is_map() || !_token.key_exists("x") || !_token.key_exists("y")) {
		throw std::runtime_error("malformed point node: not a map or missing x|y nodes");
	}

	if(!_token["x"].is_int_value() || !_token["y"].is_int_value()) {
		throw std::runtime_error("malformed point node: x and y nodes must be integer values");
	}

	//The parser complains that _token["x"] is not a double type when trying to
	//coerce types.
	return defs::tpoint(_token["x"].get_int(), _token["y"].get_int());
}
