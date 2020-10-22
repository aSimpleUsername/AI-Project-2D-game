#pragma once

#include <GL/glut.h>
#include <string>

#include "gameEntity2D.h"

class UserInterface
{
public:
	void playerHealth(int playerHealth);		//displays player health
	void level(int level);						//displays what level it is
	void remainingEnemies(int numEnemies);		//displays remaining enemies
	void info();								//displays useful info
	void deathScreen();							//displays text on death

private:
	void renderText(float x, float y, void* font, std::string string);

};

