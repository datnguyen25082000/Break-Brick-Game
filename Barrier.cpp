#include "Barrier.h"


Barrier::Barrier()
{
}


Barrier::~Barrier()
{
}

sf::Vector2f Barrier::Position()
{
	return barrier.getPosition();
}

void Barrier::SetPosition(float valuex, float valuey)
{
	barrier.setPosition(valuex, valuey);
}


//Kích thước 
sf::Vector2f Barrier::Size()
{
	return barrier.getSize();
}

void Barrier::SetSize(sf::Vector2f value)
{
	barrier.setSize(value);
}

void Barrier::SetSize(float valueWidth, float valueHeight)
{
	barrier.setSize(sf::Vector2f(valueWidth, valueHeight));
}


//Màu sắc
sf::Color Barrier::FillColor()
{
	return barrier.getFillColor();
}

void Barrier::SetFillColor(sf::Color value)
{
	barrier.setFillColor(value);
}


void Barrier::Render(sf::RenderWindow* window)
{
	window->draw(barrier); // vẽ _gameObject
}