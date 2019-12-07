#include "Paddle.h"
#include "GameConstants.h"


const sf::Vector2f BASE_VELOCITY(.0f, 1.0f);

//Hàm trả về vector vị trí
sf::Vector2f Paddle::Position()
{
	return _gameObject.getPosition();
}
//Hàm thiết lập vị trị paddle
void Paddle::SetPosition(sf::Vector2f value)
{
	_gameObject.setPosition(value);
}
void Paddle::SetPosition(float valuex, float valuey)
{
	_gameObject.setPosition(valuex, valuey);
}

//vector vận tốc
sf::Vector2f Paddle::Velocity()
{
	return BASE_VELOCITY * _speed;
}

float Paddle::Speed()
{
	return _speed;
}

void Paddle::SetSpeed(float value)
{
	_speed = value;
}

float Paddle::BaseSpeed()
{
	return _baseSpeed;
}

void Paddle::SetBaseSpeed(float value)
{
	_baseSpeed = value;
}


//Kích thước 
sf::Vector2f Paddle::Size()
{
	return _gameObject.getSize();
}

void Paddle:: SetSize(sf::Vector2f value)
{
	_gameObject.setSize(value);
}

void Paddle::SetSize(float valueWidth, float valueHeight)
{
	_gameObject.setSize(sf::Vector2f(valueWidth, valueHeight));
}


//Màu sắc
sf::Color Paddle::FillColor()
{
	return _gameObject.getFillColor();
}

void Paddle::SetFillColor(sf::Color value)
{
	_gameObject.setFillColor(value);
}

//Độ dày viền thanh trượt
float Paddle::BorderThickness()
{
	return _gameObject.getOutlineThickness();
}

void Paddle::SetBorderThickness(float value)
{
	_gameObject.setOutlineThickness(value);
}

// Màu viền
sf::Color Paddle::BorderColor()
{
	return _gameObject.getOutlineColor();
}

void Paddle::SetBorderColor(sf::Color value)
{
	_gameObject.setOutlineColor(value);
}

//Hàm dùng để di chuyển 
//Input: 2 phím di chuyển lên và xuống
void Paddle::KeyCheck(sf::Keyboard::Key up, sf::Keyboard::Key down)
{
	_speed = 0.0f;
	if (sf::Keyboard::isKeyPressed(up))
	{
		_speed = - _baseSpeed;//di chuyển lên
	}

	if (sf::Keyboard::isKeyPressed(down))
	{
		_speed = _baseSpeed; // di chuyển xuống
	}
}


void Paddle::Render(sf::RenderWindow* window)
{
	window->draw(_gameObject); // vẽ _gameObject
}