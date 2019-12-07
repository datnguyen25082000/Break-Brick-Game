#pragma once
#include <SFML/Graphics.hpp>

class Barrier
{
public:
	Barrier();
	~Barrier();
private: // Fields
	sf::RectangleShape barrier; // tạo 1 object với hình dạng tròn

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

