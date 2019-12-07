#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class BackGround
{
private:
	std::vector<sf::CircleShape> _circleList; //tạo 1 vector chứa các vật thể tròn
	std::vector<sf::RectangleShape> _rectList;//tạo 1 vector chứa các vật thể hình chữ nhật
	sf::Color _backColor; 
public:
	sf::Color Color();
	void SetColor(sf::Color value);
	//Thêm vào
	void Add(sf::RectangleShape object);
	void Add(sf::CircleShape object);
	void Clear(); // Xóa
	///vẽ
	void Render(sf::RenderWindow *window);

public://kHởi tạo

	BackGround();
	BackGround(sf::Color backColor);
};

