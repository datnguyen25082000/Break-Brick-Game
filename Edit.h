#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include"GameConstants.h"
class Edit
{
private:
	sf::Text _text;
	sf::Font _font;
public:
	void InitText(std::string text , int size, sf::Color colour, sf::Color border_color, float border_thickness, float x, float y);
	bool CheckMouseButtonPress(sf::Event* event);

public:
	void Render(sf::RenderWindow* window);
	Edit();
};

