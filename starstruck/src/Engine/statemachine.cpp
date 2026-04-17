/*
 * statemachine.cpp
 *
 *  Created on: 3 de jun. de 2023
 *      Author: hayde
 */
#include <Engine/statemachine.hpp>

void StateMachine::addState(StateRef newState, bool replace){
	add = true;
	/*###REPLACE STATE
	- useful in cases which previous states will not be reentered
	- Ex: end level 1, replace with level 2, level 1 is unaccessable now */
	this-> replace = replace;
	this-> newState = std::move(newState); //possible queue state or actual state replacer
}

void StateMachine::removeState(){
	/*###REMOVE LAST STATE: kill top state, return to the previous
	- useful for queue states with reaccessable states.
	- Ex: menu and options, kill options and return to menu*/
	remove = true;
}

void StateMachine::doChanges(){

	//###REMOVE1
	if(remove && !&states.empty){ //remove == true && states stack not empty
		states.pop(); //kill actual state
		remove = false;
		states.top()-> resume(); //resume previous state
	}

	//###ADD
	if(add){
		if(!&states.empty){ //if not empty

			//###REPLACE
			if(replace){ //if is replacing
				states.pop(); //kill actual state
				replace = false;

			}else{ //if not replacing (queue)
				states.top()->pause(); //freeze previous state
			}
		}
		states.push(std::move(newState)); //add new state, empty or not
		states.top() -> init(); //start the latest state
		add = false;
	}
}

StateRef &StateMachine::getActualState(){ //returns actual state;
	return states.top();
}
