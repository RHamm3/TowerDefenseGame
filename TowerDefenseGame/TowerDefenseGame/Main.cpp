#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.h"

int main() {

	//Initialize Random
	srand(static_cast<unsigned>(time(NULL)));


	//Initialize Game Engine
	Game game;

	//Game Loop
	while (game.running()) {
		/***************Update***************/
		game.update();
		/***************Render***************/
		game.render();
	}


	
	return 0; 

}