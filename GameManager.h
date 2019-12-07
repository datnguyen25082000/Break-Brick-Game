#pragma once
#include <vector>
#include "Ball.h"
#include "Paddle.h"
#include "Score.h"
#include "BackGround.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "Items.h"
#include "Barrier.h"
#include <string>
#include "GameConstants.h"
#include "Edit.h"
#include <stdlib.h>

class GameManager
{
private:

	Ball _ball; //tạo 1 Ball
	std::vector<Items> _items;
	std::vector<Barrier> _barriers;

	//Tạo hai điểm cho trái - phải
	Score _leftScore; 
	Score _rightScore;

	//Tạo thanh trái với hai phím di chuyển lên và xuống
	Paddle _leftPaddle;
	sf::Keyboard::Key _leftUp; 
	sf::Keyboard::Key _leftDown;
	
	//Tạo thanh phải với hai phím di chuyển lên và xuống
	Paddle _rightPaddle;
	sf::Keyboard::Key _rightUp;
	sf::Keyboard::Key _rightDown;

	//cửa sổ window 
	sf::RenderWindow* _window;

	float _deltaTime;
	bool _isPlaying;
	bool _isPause;
	bool _is1phayer;
	int _item_Score = ITEM_SCORE;
	int _level;
	
	std::vector<std::string> rankList;
	std::vector<int> rankScore;
private:
	void Update();

	void AskReStart();

	void EventHandler();


public: // Properties
	float DeltaTime();
	void SetIs1Player(bool a)
	{
		_is1phayer = a;
	}
	bool IsPLaying();

public:
	//Hàm khởi tạo Ball
	void InitBall(float radius = 0.0f, sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2f velocity = sf::Vector2f(0, 0), 
				  sf::Color fillColor = sf::Color::Blue, float border = 0, sf::Color borderColor = sf::Color::White);

	//Hàm khởi tạo Paddle
	void InitPaddle(int paddle, sf::Vector2f size=sf::Vector2f(0,0), sf::Vector2f position = sf::Vector2f(0, 0), float baseSpeed = .0f,
					sf::Color fillColor = sf::Color::Green, float border = 0, sf::Color borderColor = sf::Color::Green);

	void InitItemLv1( sf::Vector2f size = sf::Vector2f(0, 0), sf::Color fillColor = sf::Color::Green);

	void InitItemLv2(sf::Vector2f size = sf::Vector2f(0, 0), sf::Color fillColor = sf::Color::Green);

	void InitBarrier(sf::Vector2f size = sf::Vector2f(0, 0));


	//khởi tạo các phím điều khiển thanh trái và phải
	void InitKeyControl(int paddle, sf::Keyboard::Key , sf::Keyboard::Key );

	//khởi tạo các thông số cho Score
	void InitScore(int paddle, sf::Font font, int size = 0, sf::Vector2f position = sf::Vector2f(0, 0), sf::Color color=sf::Color::White, int basescore = 0);

	void Start();
	void PostProcess();
	void About();
	void Setting();
	void HowToPlay();
	void SetBackground1Player();
public: // ctor and dtor
	GameManager(sf::RenderWindow* window);
	~GameManager();
};

