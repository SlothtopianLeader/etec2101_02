#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

enum class Day
{
	Monday, Tuesday, Wednesday
};

int main(int argc, char** argv)
{
	Day today = Day::Monday;
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "AudriannaS Lab4 Solution");
	sf::CircleShape test_circle(100.0f);
	test_circle.setFillColor(sf::Color::Green);
	test_circle.setPosition(sf::Vector2f(10.0f, 10.0f));
	test_circle.setOrigin(sf::Vector2f(100.0f, 100.0f));

	/*
	sf::Texture my_hand_image("hand.png");
	sf::Sprite my_hand_sprite(my_hand_image);
	my_hand_sprite.setRotation(sf::degrees(45.0f));
	my_hand_sprite.setOrigin(sf::Vector2f());
	*/

	while (window.isOpen())
	{
		Day today = Day::Monday;

		// Input-handling (keyboard and mouse)
		// std::optional is a new C++-17+ thing -- it's kind of like
		// in python, if a function doesn't return anything useful, None is
		// returned.
		// Normally you would use == like this in a while loop.

		while (const std::optional event = window.pollEvent())
		{
			// We use event to see if it's something we care about
			if (event->is<sf::Event::Closed>())
			{
				// The quit button was pressed.
				window.close();
			}
			else if(const sf::Event::KeyPressed * keyEvt = event->getIf<sf::Event::KeyPressed>())
			{
				// We get here if a key is pressed.	Now see if it's a key we care about
				if (keyEvt->code == sf::Keyboard::Key::Escape)
				{
					window.close();
				}
			}
			else if (const sf::Event::MouseButtonPressed* buttonEvt =
				event->getIf<sf::Event::MouseButtonPressed>())
				{
					// We get here if any mouse button is pressed.	Now see if it's
					// a button press that we care about
					if (buttonEvt->button == sf::Mouse::Button::Left)
					{
						// We get here if it's a left-mouse button pressed. Move green circle here
						sf::Vector2f temp_pos(buttonEvt->position.x, buttonEvt->position.y);
						test_circle.setPosition(temp_pos);
					}
				};
		}

		// Drawing (to the window)
		window.clear();
		window.draw(test_circle);
		window.display();			// Shows our drawings
	}
	return 0;
}