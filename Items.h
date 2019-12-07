#pragma once
#include <SFML/Graphics.hpp>

class Items
{
public:
	Items();
	~Items();

private: // Fields
	sf::RectangleShape item; // tạo 1 object với hình dạng tròn
public: // Properties
	sf::Vector2f Position(); // vector vị trí
	void SetPosition(float valuex, float valuey);

	sf::Vector2f Size();
	void SetSize(sf::Vector2f value);
	void SetSize(float valueWidth, float valueHeight);

	//màu sắc cho Ball
	sf::Color FillColor();
	void SetFillColor(sf::Color Fillcolor);

public:
	void Render(sf::RenderWindow *window); // Hàm vẽ ball
};

