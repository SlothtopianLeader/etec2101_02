#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <random>
#include "clean_arraylist.h"
#include "WordReader.h"
#include "RandomMacros.h"

class TextCircle
{
private:
	sf::Text my_text;		// This MUST have a font when created.
	sf::CircleShape my_circle;
	sf::CircleShape my_bullet;
	sf::RectangleShape my_retangle;
	sf::Vector2f my_position;
	float spawnTime = 1.0f;
	float circleYVelocity = 0.015625;
public:
	TextCircle(sf::Font& the_font) : my_text(the_font),   // <- this : syntax passes the value to
		my_circle(getRandomSize()), my_bullet(20.0f), my_retangle({600.0f, 50.0f})
	{													// the c'tor.
		my_position = sf::Vector2f(100.0f, 100.0f);
		my_circle.setFillColor(RAND_COLOR);
		// my_circle.setRotation(sf::degrees(110.f));

	}

	void set_text(std::string s)
	{
		my_text.setString(s);
		sf::FloatRect fr = my_text.getLocalBounds();
		sf::Vector2f size = fr.size;
		float width = size.x;
		float height = size.y;
		float x = my_circle.getPosition().x;
		float y = my_circle.getPosition().y;
		my_text.setOrigin(sf::Vector2f(width / 2, height / 2));
		my_text.setPosition(sf::Vector2f(x + my_circle.getRadius(), y + my_circle.getRadius()));
	}

	void set_position(float x, float y)
	{
		my_text.setPosition(sf::Vector2f(x, y));
		my_circle.setPosition(sf::Vector2f(x, y));
		my_text.setPosition(sf::Vector2f(x + my_circle.getRadius(), y + my_circle.getRadius()));

		my_bullet.setPosition(sf::Vector2f(x, y));
	}

	sf::Text get_text()
	{
		return my_text;
	}

	sf::CircleShape get_circle()
	{
		return my_circle;
	}

	sf::CircleShape get_bullet()
	{
		return my_bullet;
	}

	sf::Color getRandomColor()
	{
		return sf::Color(rand() % 256, rand() % 256, rand() % 256);
	}

	sf::CircleShape getRandomSize()
	{
		float radius = RAND_RADIUS(MIN, MAX);
		sf::CircleShape circle(radius);
		circle.setFillColor(RAND_COLOR);
		return circle;
	}
	
	sf::RectangleShape getRectangle()
	{
		return my_retangle;
	}
};


int main(int argc, char** argv)
{
	WordReader WR("..\\..\\media\\scowl.txt");

	// This code is run before the game starts.  Note how SFML is very object-oriented (creating
	// objects and calling methods) rather than SDL, which is very C based (mostly calling functions
	// and passing around structs)
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "AudriannaS Lab4 Solution");
	std::srand(static_cast<unsigned int>(std::time(0)));

	sf::Texture my_space_image("..\\..\\media\\space.jpg");
	sf::Sprite my_space_sprite(my_space_image);

	sf::CircleShape test_circle(100.0f);
	test_circle.setFillColor(sf::Color(255, 200, 100, 255));
	test_circle.setPosition(sf::Vector2f(10.0f, 10.0f));
	test_circle.setOrigin(sf::Vector2f(100.0f, 100.0f));

	sf::Texture my_hand_image("..\\..\\media\\hand.png");
	sf::Sprite my_hand_sprite(my_hand_image);
	my_hand_sprite.setOrigin(sf::Vector2f({100.f, 100.f}));		// X = 100 is top left of hand
	my_hand_sprite.setPosition(sf::Vector2f(375.0f, 500.0f));


	sf::Font my_font("..\\..\\media\\Oswald\\static\\Oswald-Regular.ttf");
	sf::Text test_text(my_font);

	// Suggestion: make a collection of "parallel" arrays to hold all 
	// data about falling circles.  When you spawn a circle, add a data item to
	// each list
	ssuds::ArrayList<float> circle_xvalues;
	ssuds::ArrayList<float> circle_yvalues;
	ssuds::ArrayList<float> circle_speeds;
	ssuds::ArrayList<std::string> circle_text;
	ssuds::ArrayList<float> bullet_xvalues;
	ssuds::ArrayList<float> bullet_yvalues;
	TextCircle only_text_circle(my_font);
	//TextCircle only_bullet(my_font);

	sf::Clock spawnClock;

	// This is the "GAME LOOP" -- it runs as long as the window is open.  The two main
	// parts of a game loop are input-handling and drawing.  You might want to add a third
	// section that does other (non-input-related) updates.
	while (window.isOpen())
	{
		if (spawnClock.getElapsedTime().asSeconds() >= 1.0f)
		{
			sf::CircleShape circle(RAND_RADIUS(MIN, MAX));
			circle.setFillColor(RAND_COLOR);

			circle_xvalues.append(rand() % 800);
			circle_yvalues.append(-100);
			circle_text.append(WR.getRandomWord());
			circle_speeds.append(RAND_SPEED);

			spawnClock.restart();
		}
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ UPDATES                                 @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		for (unsigned int i = 0; i < circle_xvalues.size(); i++)
		{
			circle_yvalues[i] += circle_speeds[i];
			if (circle_yvalues[i] >= 600)
			{
				circle_xvalues.remove(i);
				circle_yvalues.remove(i);
				circle_speeds.remove(i);
				circle_text.remove(i);
			}
		}

		for (int i = circle_xvalues.size() - 1; i >= 0; i--)
		{
			for (int j = bullet_xvalues.size() - 1; j >= 0; j--)
			{
				float dx = circle_xvalues[i] - bullet_xvalues[j];
				float dy = circle_yvalues[i] - bullet_yvalues[j];
				float distance = sqrtf(dx * dx + dy * dy);

				float circle_radius = only_text_circle.get_circle().getRadius();
				float bullet_radius = only_text_circle.get_bullet().getRadius();

				if (distance <= (circle_radius + bullet_radius))
				{
					circle_xvalues.remove(i);
					circle_yvalues.remove(i);
					circle_speeds.remove(i);
					circle_text.remove(i);

					bullet_xvalues.remove(j);
					bullet_yvalues.remove(j);
				}
			}
		}

		for (unsigned int i = 0; i < bullet_xvalues.size(); i++)
		{
			bullet_yvalues[i] -= 0.2f;
		}


		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ Input-handling (keyboard and mouse)     @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// std::optional is a new C++-17+ thing -- it's kind of like
		// in python, if a function doesn't return anything useful, None is
		// returned.
		// Normally you would use == like this in a while loop -- this is assigning a result to event
		// AND THEN using that value as the "truth-test" for the while condition
		while (const std::optional event = window.pollEvent())
		{
			// We use event to see if it's something we care about
			if (event->is<sf::Event::Closed>())
			{
				// The quit button was pressed.
				window.close();
			}

			else if (const sf::Event::KeyPressed* keyEvt = event->getIf<sf::Event::KeyPressed>())
			{
				// We get here if a key is pressed.  Now see if it's a key we care about
				if (keyEvt->code == sf::Keyboard::Key::Escape)
				{
					window.close();
				}
			}
			else if (const sf::Event::MouseButtonPressed* buttonEvt =
				event->getIf<sf::Event::MouseButtonPressed>())
			{
				// We get here if any mouse button is pressed.  Now see if it's
				// a button press that we care about
				if (buttonEvt->button == sf::Mouse::Button::Left)
				{
					float x = buttonEvt->position.x;
					float y = buttonEvt->position.y;

					bullet_xvalues.append(x);
					bullet_yvalues.append(y);
;				}
			}
			else if (const sf::Event::MouseMoved* mouseEvt =
				event->getIf<sf::Event::MouseMoved>())
			{
				sf::Vector2f mousePos(mouseEvt->position.x, mouseEvt->position.y);
				sf::Vector2f handPos = my_hand_sprite.getPosition();
				float dx = mousePos.x - handPos.x;
				float dy = mousePos.y - handPos.y;
				float angle = atan2(dy, dx) * 180.0f / 3.14159f + 180.0f;
				my_hand_sprite.setRotation(sf::degrees(angle));
			}
		}



		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ Drawing (to the window)     @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		window.clear();
		window.draw(my_space_sprite);
		window.draw(my_hand_sprite);
		for (int i = 0; i < circle_xvalues.size(); i++)		// Drawing our text circles
		{
			only_text_circle.set_position(circle_xvalues[i], circle_yvalues[i]);
			only_text_circle.set_text(circle_text[i]);
			window.draw(only_text_circle.get_circle());
			window.draw(only_text_circle.get_text());
		}

		for (int i = 0; i < bullet_xvalues.size(); i++)		// Drawing the bullets
		{
			TextCircle temp_bullet(my_font);
			temp_bullet.set_position(bullet_xvalues[i], bullet_yvalues[i]);
			temp_bullet.get_bullet().setFillColor(sf::Color::White);
			window.draw(temp_bullet.get_bullet());
		}

		window.display();// Shows our drawings
	}
	return 0;
}