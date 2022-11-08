#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include <list>

#include "Snake.h"

using namespace std;
using namespace sf;



class Food
{
public:
	const Color color = Color::Color(159, 2, 30);
	int x = 0;
	int y = 0;
	bool newFoodPosFound = true;


	Food(Snake snake, int width, int height) {
		newFoodPosFound = false;
		newPos(snake, width, height);

	}

	void newPos(Snake snake, int width, int height) {

		while (!newFoodPosFound)
				{
					x = (rand() % (width / 50)) * 50;
					y = (rand() % (height / 50)) * 50;
					
					for (Snake::Segment s : snake.body)
					{
						if (s.x != x && s.y != y) {
							newFoodPosFound = true;
						}
						else
						{
							newFoodPosFound = false;
						}
					}
				}

	}


};

