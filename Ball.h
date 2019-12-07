#pragma once
#include <SFML/Graphics.hpp>


class Ball
{
private: // Fields
	sf::CircleShape _gameObject; // tạo 1 object với hình dạng tròn
	sf::Vector2f _velocity; // vector vận tốc

public: // Properties
	sf::Vector2f Position(); // vector vị trí
	void SetPosition(sf::Vector2f value);
	void SetPosition(float valuex, float valuey);

	sf::Vector2f Velocity(); // vector vận tốc
	void SetVelocity(sf::Vector2f value);
	void SetVelocity(float valuex, float valuey);

	float Speed();

	//bán kính
	float Radius();
	void SetRadius(float value);

	//màu sắc cho Ball
	sf::Color FillColor();
	void SetFillColor(sf::Color Fillcolor);

	//Độ dày của đường viền ball
	float BorderThickness();
	void SetBorderThickness(float value);

	//Màu sắc đường viền
	sf::Color BorderColor();
	void SetBorderColor(sf::Color value);

public: 
	void Render(sf::RenderWindow *window); // Hàm vẽ ball
public:
	static sf::Vector2f GenerateRandomVelocity(float speed, float minX, float minY);//Hàm tạo 1 vector vận tốc bât kì
};

