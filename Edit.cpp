#include "Edit.h"

void Edit::InitText(std::string text , int size, sf::Color colour, sf::Color border_color, float border_thickness, float x, float y)
{
	_text.setFont(_font);
	_text.setString(text);
	_text.setCharacterSize(size);
	_text.setFillColor(colour);
	_text.setOutlineColor(border_color);
	_text.setOutlineThickness(border_thickness);
	_text.setPosition(x + (WINDOW_WIDTH - _text.getGlobalBounds().width) / 2.0f, _text.getGlobalBounds().height + y*MENU_GAP);
}

bool Edit::CheckMouseButtonPress(sf::Event* event)
{
	if (event->mouseButton.x > _text.getPosition().x && event->mouseButton.x < _text.getPosition().x + _text.getGlobalBounds().width)
	{
		if (event->mouseButton.y > _text.getPosition().y && event->mouseButton.y < _text.getPosition().y + _text.getGlobalBounds().height)
		{
			return true;
		}
	}
	return false;
}

void Edit::Render(sf::RenderWindow* window)
{
	window->draw(_text);
}

Edit::Edit()
{
	_font.loadFromFile("ASMAN.ttf");
}