#include "Items.h"


Items::Items()
{
}


Items::~Items()
{
}

//Hàm trả về vector vị trí
sf::Vector2f Items::Position()
{
	return item.getPosition();
}

void Items::SetPosition(float valuex, float valuey)
{
	item.setPosition(valuex, valuey);
}


//Kích thước 
sf::Vector2f Items::Size() 
{
	return item.getSize();
}

void Items::SetSize(sf::Vector2f value)
{
	item.setSize(value);
}

void Items::SetSize(float valueWidth, float valueHeight)
{
	item.setSize(sf::Vector2f(valueWidth, valueHeight));
}


//Màu sắc
sf::Color Items::FillColor()
{
	return item.getFillColor();
}

void Items::SetFillColor(sf::Color value)
{
	item.setFillColor(value);
}


void Items::Render(sf::RenderWindow* window)
{
	window->draw(item); // vẽ _gameObject
}
