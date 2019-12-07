#include "Score.h"
#include "GameConstants.h"

//Thiết lập điểm 
void Score::SetScore(int value)
{
	_score = value;
	_textScore.setString(std::to_string(_score));
}

int Score::GetScore()
{
	return _score;
}
//Kích thước 
void Score::SetSize(int value)
{
	_textScore.setCharacterSize(value);
}

//Vị trí
void Score::SetPosition(sf::Vector2f value)
{
	_textScore.setPosition(sf::Vector2f(value));
}
sf::Vector2f Score::Position()
{
	return sf::Vector2f(_textScore.getPosition());
}

//Màu sắc
void Score::SetFillColor(sf::Color value)
{
	_textScore.setFillColor(value);

}

sf::Color Score::FillColor()
{
	return sf::Color(_textScore.getFillColor());
}

// Định dạng font chữ
void Score::SetFont(sf::Font font)
{
	*_pfont = font;
	_textScore.setFont(*_pfont);
}

sf::Font Score::Font()
{
	return *_textScore.getFont();
}

//Kích cỡ
int Score::Size()
{
	return _textScore.getCharacterSize();
}

//Kích thước : gồm dài và rộng
sf::FloatRect Score::GlobalBounds()
{

	return _textScore.getGlobalBounds();
}

//Vẽ score
void Score::Render(sf::RenderWindow* window)
{
	window->draw(_textScore); //vẽ score ở dạng text
}

//Khởi tạo score
Score::Score()
{
	_score = BASE_SCORE;
	_pfont = new sf::Font;
	_textScore.setFont(*_pfont);
}

//Hàm hủy
Score::~Score()
{
	delete _pfont;
}

