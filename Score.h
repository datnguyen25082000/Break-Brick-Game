#pragma once
#include <SFML/Graphics.hpp>

class Score
{
private:
	int _score; 
	sf::Text _textScore; // _score ở dạng text
	sf::Font* _pfont;   // font chữ dùng cho score
public:
	void SetScore(int value);
	int GetScore();

	//Kích cỡ Score
	void SetSize(int value);
	int Size();

	//vị trí
	void SetPosition(sf::Vector2f value );
	sf::Vector2f Position();

	//Màu sắc
	void SetFillColor(sf::Color value);

	void SetFont(sf::Font);
	
	//Hàm lấy kích thước của score gồm dài và rộng
	sf::FloatRect GlobalBounds();


	sf::Color FillColor();//màu sắc
	sf::Font Font();//font chữ

public:
	//Vẽ score
	void Render(sf::RenderWindow* window);

public:
	Score();
	~Score();
};

