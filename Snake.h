#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include <list>

using namespace std;
using namespace sf;


class Snake
{
public:

	struct Segment
	{
		int x;
		int y;
	};

	const int size = 50;
	const Color color = Color::Color(162, 228, 184);
	list<Segment> body = { {700, 600}, {750, 600}, {800, 600} };
	int direction = 1;
	

	void snakeEats() {
		body.push_back({ body.back().x, body.back().y });

	}

	void moveUp() {
		body.push_front({ body.front().x, body.front().y - size });
		body.pop_back();
	}

	void moveDown() {
		body.push_front({ body.front().x, body.front().y + size });
		body.pop_back();
	}

	void moveRight() {
		body.push_front({ body.front().x + size, body.front().y });
		body.pop_back();
	}

	void moveLeft() {
		body.push_front({ body.front().x - size , body.front().y });
		body.pop_back();
	}

	/*void drawn_snake(RenderWindow window) {
		float fsize = size;
		for (Snake::Segment s : body) {
			RectangleShape part;
			part.setPosition(s.x, s.y);
			part.setSize(Vector2f{ fsize, fsize });
			part.setFillColor(color);
			window.draw(part);
		}
	}*/


};

