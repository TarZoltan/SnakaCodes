#include <iostream>
#include "SFML/Graphics.hpp"
#include <list>

#include "Snake.h"
#include "Food.h"

#include <opencv2/opencv.hpp>
#include <ostream>

using namespace std;
using namespace sf;
using namespace cv;






int main()
{
	//tábla beállítások:

	const int width = 1200;
	const int height = 800;
	const int loop_pause = 100;
	const Color BG_color = Color::Color(49, 79, 64);


	bool Dead = false;
	int Score = 0;

	//képfeldolgozás:

	Mat webcam;


	RenderWindow window(VideoMode(width, height), "Snake");


	Snake snake;
	Food food(snake, width, height);


	VideoCapture cam(0);
	//cam.read(webcam);
	//imshow("cam", webcam);


	//---------------------------------------------------------------game loop

	while (window.isOpen())
	{

		// idõzítés



		sleep(Time(milliseconds(loop_pause)));

		Event event;

		cam.read(webcam);
		

		while (window.pollEvent(event))
		{


			if (event.type == Event::Closed)
			{
				window.close();
			}
			else if (event.type == Event::KeyPressed) {

				if (Dead && event.key.code == Keyboard::Space)
				{
					Score = 0;
					snake.direction = 1;
					snake.body = { {700, 600}, {750, 600}, {800, 600}, {850, 600}, {900, 600} };
					food.newPos(snake, width, height);
					Dead = false;

				}

				switch (event.key.code)
				{
				case Keyboard::W:
					snake.direction = 0;
					break;
				case Keyboard::A:
					snake.direction = 1;
					break;
				case Keyboard::S:
					snake.direction = 2;
					break;
				case Keyboard::D:
					snake.direction = 3;
					break;

				}

			}

		}

		window.clear(BG_color);

		

		//------------------------------------------------------------logika

		if (!Dead) {


			//snake pozíciója

			switch (snake.direction)
			{
			case 0:
				snake.moveUp();
				break;
			case 1:
				snake.moveLeft();
				break;
			case 2:
				snake.moveDown();
				break;
			case 3:
				snake.moveRight();
				break;
			}

			//ütközés:

			if (snake.body.front().x < 0 || snake.body.front().x + snake.size > width)
				Dead = true;
			if (snake.body.front().y < 0 || snake.body.front().y + snake.size > height)
				Dead = true;


			if (snake.body.front().x == food.x && snake.body.front().y == food.y)
			{

				Score++;

				//out << "Megvan!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! pont: " << Score << endl;

				imwrite(to_string(Score) + " eves.png", webcam);
			



				food.newFoodPosFound = false;

				food.newPos(snake, width, height);

				snake.snakeEats();

			}

			for (list<Snake::Segment>::iterator i = snake.body.begin(); i != snake.body.end(); i++) {
				if (i != snake.body.begin() && i->x == snake.body.front().x && i->y == snake.body.front().y)
					Dead = true;
			}
			//-------------------------------------------------------------megjelenítés

			float size = snake.size;

			//kígyó:
			for (auto s : snake.body) {
				RectangleShape part;
				part.setPosition(s.x, s.y);
				part.setSize(Vector2f{ size, size });
				part.setFillColor(snake.color);
				window.draw(part);
			}

			//snake.drawn_snake(window());

			RectangleShape food_shape;
			food_shape.setPosition(food.x, food.y);
			food_shape.setSize(Vector2f{ size, size });
			food_shape.setFillColor(food.color);
			window.draw(food_shape);

		}
		else
		{
			Font font;
			font.loadFromFile("Lato-Light.ttf");
			Text txt;
			txt.setFont(font);
			txt.setString("A pontod: " + to_string(Score));
			txt.setCharacterSize(90);
			txt.setFillColor(snake.color);
			txt.setOrigin(txt.getGlobalBounds().width / 2, txt.getGlobalBounds().height / 2);
			txt.setPosition(width / 2, height / 2);
			window.draw(txt);

			Text restart_txt;
			restart_txt.setFont(font);
			restart_txt.setString("Újrakezéskez üss spacet-t");
			restart_txt.setCharacterSize(30);
			restart_txt.setFillColor(snake.color);
			restart_txt.setOrigin(txt.getGlobalBounds().width / 2, txt.getGlobalBounds().height / 2);
			restart_txt.setPosition(300, height);
			window.draw(restart_txt);

		}

 
		window.display();
	}

	return 0;
}
