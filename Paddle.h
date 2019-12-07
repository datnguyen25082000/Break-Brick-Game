#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


class Paddle 
{
private: 
	sf::RectangleShape _gameObject;//1 vật thể với hình dạng chữ nhật
	float _speed;
	float _baseSpeed;

public: // Properties

	//vị trí
	sf::Vector2f Position();
	void SetPosition(sf::Vector2f value);
	void SetPosition(float valuex, float valuey);

	//vector vận tốc
	sf::Vector2f Velocity();

	float Speed();
	void SetSpeed(float value);
	float BaseSpeed();
	void SetBaseSpeed(float value);

	//kích thước
	sf::Vector2f Size();
	void SetSize(sf::Vector2f value);
	void SetSize(float valueWidth, float valueHeight);

	//màu sắc
	sf::Color FillColor();
	void SetFillColor(sf::Color Fillcolor);
	//độ dày đường viền
	float BorderThickness();
	void SetBorderThickness(float value);

	sf::Color BorderColor();
	void SetBorderColor(sf::Color value);

	//Hàm để di chuyển thành trượt
	void KeyCheck(sf::Keyboard::Key up, sf::Keyboard::Key down);

	//Vẽ vật thể 
	void Render(sf::RenderWindow *window);

};

