#include "Ball.h"
#include <random>
#include "GameConstants.h"

//Hàm trả về giá trị vector vị trí
sf::Vector2f Ball::Position()
{
	float border = _gameObject.getOutlineThickness();//Lấy độ dày đường viền ball
	return sf::Vector2f(_gameObject.getPosition().x - border, _gameObject.getPosition().y - border);
}

//Thiết lập vị trí
void Ball::SetPosition(sf::Vector2f value)
{
	SetPosition(value.x, value.y);
}

void Ball::SetPosition(float valuex, float valuey)
{
	float border = _gameObject.getOutlineThickness();
	_gameObject.setPosition(valuex + border, valuey + border);
}

// Hàm trả về giá trị vector vận tốc
sf::Vector2f Ball:: Velocity()
{
	return _velocity;
}
//Hàm thiết lập vector vận tốc
void Ball::SetVelocity(sf::Vector2f value)
{
	_velocity.x = value.x;
	_velocity.y = value.y;
}
void Ball:: SetVelocity(float valuex, float valuey)
{
	_velocity.x = valuex;
	_velocity.y = valuey;
}

//tốc độ Ball
float Ball::Speed()
{
	return sqrtf(_velocity.x * _velocity.x + _velocity.y * _velocity.y);
}

//Bán kính bóng
float Ball:: Radius()
{
	return _gameObject.getRadius() + _gameObject.getOutlineThickness(); //R = r + độ dày viền
}

void Ball::SetRadius(float value) 
{
	_gameObject.setRadius(value);
}

// Hàm trả về màu sắc ball
sf::Color Ball:: FillColor()
{
	return _gameObject.getFillColor();
}

//Thiết lập màu sắc ball
void Ball:: SetFillColor(sf::Color value)
{
	_gameObject.setFillColor(value);
}

//Độ dày đường viền
float Ball:: BorderThickness()
{
	return _gameObject.getOutlineThickness();
}
void Ball::SetBorderThickness(float value)
{
	_gameObject.setOutlineThickness(value);
}

//Màu đường viền
sf::Color Ball:: BorderColor()
{
	return _gameObject.getOutlineColor();
}
void Ball::SetBorderColor(sf::Color value)
{
	_gameObject.setOutlineColor(value);
}

//Hàm vẽ Ball ra window 
void Ball::Render(sf::RenderWindow* window)
{
	window->draw(_gameObject);
}

//Hàm khởi tạo 1 vector vận tốc bất kì
sf::Vector2f Ball::GenerateRandomVelocity(float speed, float minX, float minY)
{
	float maxX = sqrtf(speed * speed - minY * minY);
	if (maxX < minX)
	{
		return sf::Vector2f(0, 0);
	}
	float x = (minX + (rand() / (float) RAND_MAX) * (maxX - minX)) * ((rand() % 2) == 0 ? -1 : 1);
	float y = sqrtf(speed * speed - x * x) * ((rand() % 2) == 0 ? -1 : 1);
	return sf::Vector2f(x, y);
}

