/*
 * entity.hpp
 *
 *  Created on: 19 de jun. de 2023
 *      Author: hayde
 */

#ifndef ENTITIES_ENTITY_HPP_
#define ENTITIES_ENTITY_HPP_

class Entity{
public:
	virtual ~Entity(){};
	virtual void init(){};
	virtual void update(){};
	virtual void draw(){};
};



#endif /* ENTITIES_ENTITY_HPP_ */
