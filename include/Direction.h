#ifndef DIRECTION_H_
#define DIRECTION_H_

#include "glimac/glm.hpp"

enum Direction{NORTH, EAST, SOUTH, WEST};

Direction getInverseDirection(Direction d){
	switch(d){
	case NORTH:
		return SOUTH;
	case EAST:
		return WEST;
	case SOUTH:
		return NORTH;
	case WEST:
		return EAST;
	}
}

glm::vec3 getDirection(Direction d){
	switch(d){
	case NORTH:
		return glm::vec3(0,0, 1);
	case EAST:
		return glm::vec3(1,0, 0);
	case SOUTH:
		return glm::vec3(0,0, -1);
	case WEST:
		return glm::vec3(-1,0, 0);
	}
}

#endif /* DIRECTION_H_ */
