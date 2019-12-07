#include "BackGround.h"
//Màu sắc
sf::Color BackGround::Color()
{
	return _backColor;
}

void BackGround::SetColor(sf::Color value)
{
	_backColor = value;
}

//Thêm vào
void BackGround::Add(sf::RectangleShape object)
{
	_rectList.push_back(object);
}

void BackGround::Add(sf::CircleShape object)
{
	_circleList.push_back(object);
}

//Xóa
void BackGround::Clear()
{
	_rectList.clear();
	_circleList.clear();
}

//Hàm vẽ
void BackGround::Render(sf::RenderWindow *window)
{
	//Vẽ lần lượt các cirle object có trong vector _cỉrcleList
	for (auto circle : _circleList)
	{
		window->draw(circle);
	}

	//Vẽ lần lượt các cirle object có trong vector _cỉrcleList
	for (auto rect : _rectList)
	{
		window->draw(rect);
	}
}

BackGround::BackGround()
{
}

BackGround::BackGround(sf::Color backColor)
{
	_backColor = backColor;
}
