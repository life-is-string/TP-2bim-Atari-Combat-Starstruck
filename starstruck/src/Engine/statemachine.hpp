/*
 * statemachine.hpp
 *
 *  Created on: 3 de jun. de 2023
 *      Author: hayde
 */
#pragma once
#ifndef ENGINE_STATEMACHINE_HPP_
#define ENGINE_STATEMACHINE_HPP_
#include "stdafx.hpp"
#include <Engine/state.hpp>

typedef std::unique_ptr<State> StateRef;
class StateMachine{
public:

	void addState(StateRef newState, bool replace = true);
	void removeState();
	void doChanges();
	StateRef &getActualState();
private:
	std::stack<StateRef> states;
	StateRef newState;
	bool remove, replace, add;
};

#endif /* ENGINE_STATEMACHINE_HPP_ */
