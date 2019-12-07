#include "GameManager.h"
#include "GameConstants.h"
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>



//Tính khoảng thời gian giữa hai thời điểm
float GameManager::DeltaTime()
{
	return _deltaTime;
}

bool GameManager::IsPLaying()
{

	return _isPlaying;
}


//-------------------------------------------- in game function --------------------------------------------//


//hàm xử lí khi bóng chạm biên trái-phải hay người chơi được cộng điểm
void GameManager::AskReStart()
{
	Score* selectedScore;
	//Nếu bóng chạm vào biên trái thì cộng 1 điểm cho thanh phải,và ngược lại
	selectedScore = _ball.Position().x < LEFT_BOUNDARY ? &_rightScore : &_leftScore;
	selectedScore->SetScore(selectedScore->GetScore() + 1);

	if (_is1phayer)
		_isPlaying = false;

	if (selectedScore->GetScore() >= NUMBER_OF_GAME)// 1 thanh đạt điểm tối đa
	{
		// dừng game và hiển thị người chiến thắng
		_isPlaying = false;
	}
	else // nếu chơi đạt điểm tối đa
	{
		_ball.SetPosition(INITIAL_BALL_POSITION); // tạo lại vị trí bóng ban đầu
		// cho bóng di chuyển với vector vận tốc bất kì
		_ball.SetVelocity(Ball::GenerateRandomVelocity(BALL_BASE_SPEED, BALL_BASE_X_MIN_SPEED, BALL_BASE_Y_MIN_SPEED));
	}
}

//Hàm cập nhập các vị trí mới , vận tốc mới cho thanh trái - phải , bóng
void GameManager::Update()
{
	// thiết lập các vị trí mới của bóng , thanh trái, thanh phải sau mỗi lần update
	_ball.SetPosition(_ball.Position() + _ball.Velocity() * _deltaTime);
	_leftPaddle.SetPosition(_leftPaddle.Position() + _leftPaddle.Velocity() * _deltaTime);
	_rightPaddle.SetPosition(_rightPaddle.Position() + _rightPaddle.Velocity() * _deltaTime);

	//Update Paddle
	if (_leftPaddle.Position().y < TOP_BOUNDARY) //nếu vị trí thanh trái di chuyển quá biên trên
	{
		_leftPaddle.SetPosition(_leftPaddle.Position().x, TOP_BOUNDARY); // không cho vị trí thanh trái vượt quá biên
		if (_leftPaddle.Speed() < 0) //nếu thanh trái vẫn di chuyển lên
		{
			_leftPaddle.SetSpeed(.0f); // set tốc độ bằng không 
		}
	}

	if (_leftPaddle.Position().y + _leftPaddle.Size().y > BOTTOM_BOUNDARY) //nếu vị trí thanh trái di chuyển quá biên dưới
	{
		_leftPaddle.SetPosition(_leftPaddle.Position().x, BOTTOM_BOUNDARY - _leftPaddle.Size().y);
		if (_leftPaddle.Speed() > 0) //nếu thanh trái vẫn di chuyển xuống
		{
			_leftPaddle.SetSpeed(.0f); // set tốc độ bằng không
		}
	}

	//Update Ball
	if (_ball.Position().y < TOP_BOUNDARY) // nếu bóng di chuyển quá biên trên
	{
		_ball.SetPosition(_ball.Position().x, TOP_BOUNDARY); // không cho vị trí của bóng vượt quá biên trên
		_ball.SetVelocity(_ball.Velocity().x, -_ball.Velocity().y); // đổi hướng bóng
	}
	if (_ball.Position().y + 2 * _ball.Radius() > BOTTOM_BOUNDARY) // nếu bóng di chuyển quá biên dưới 
	{
		_ball.SetPosition(_ball.Position().x, BOTTOM_BOUNDARY - 2 * _ball.Radius()); // không cho vị trí của bóng vượt quá biên trên
		_ball.SetVelocity(_ball.Velocity().x, -_ball.Velocity().y); // đổi hướng bóng
	}

	if (_ball.Position().x < LEFT_BOUNDARY) // khi bóng chạm biên trái
	{
		AskReStart();
	}

	//bóng chạm vào thanh trái
	if (_ball.Position().x >= _leftPaddle.Position().x && _ball.Position().x <= _leftPaddle.Position().x + _leftPaddle.Size().x
		&& _ball.Position().y + _ball.Radius() > _leftPaddle.Position().y
		&& _ball.Position().y + _ball.Radius() < _leftPaddle.Position().y + _leftPaddle.Size().y)
	{
		_ball.SetPosition(_leftPaddle.Position().x + _leftPaddle.Size().x, _ball.Position().y); //cho bóng không đi tiếp
		// Đổi hướng và đọ lớn của quả bóng
		auto newVel = _ball.Velocity();
		float speed = _ball.Speed();
		float affection = AFFECTION_RATIO * speed / _leftPaddle.BaseSpeed();
		newVel.y += _leftPaddle.Velocity().y * affection;
		newVel.x = -newVel.x;
		float newSpeed = sqrtf(newVel.x * newVel.x + newVel.y * newVel.y);
		float scale = speed / newSpeed;
		newVel *= scale * VELOCITY_INCREASING_PERCENTAGE;
		_ball.SetVelocity(newVel);
	}

	// cham vao item -> mat item
	for (int i = 0; i < _items.size(); i++)
	{
		if ((_ball.Position().y >= _items[i].Position().y && _ball.Position().y <= (_items[i].Position().y + _items[i].Size().y)) ||
			((_ball.Position().y + 2 * _ball.Radius()) >= _items[i].Position().y && (_ball.Position().y + 2 * _ball.Radius()) <= (_items[i].Position().y + _items[i].Size().y))) // nếu bóng di chuyển quá biên trên
		{
			if (_ball.Position().x + _ball.Radius() >= _items[i].Position().x && _ball.Position().x + _ball.Radius() < _items[i].Position().x + _items[i].Size().x)
			{
				sf::Texture texture;
				texture.loadFromFile("image/10.jpg");
				sf::Sprite sprite;
				sprite.setTexture(texture);
				sprite.setPosition(_ball.Position().x, _ball.Position().y);
				_window->draw(sprite);

				_leftScore.SetScore(_leftScore.GetScore() + _item_Score); // score khi an 1 item 
				_ball.SetVelocity(-_ball.Velocity().x, _ball.Velocity().y); // đổi hướng bóng
				_items.erase(_items.begin() + i);
			}
		}
	}

	if (_is1phayer)
	{
		for (int i = 0; i< _barriers.size(); i++)
		{
			if ((_ball.Position().y >= _barriers[i].Position().y && _ball.Position().y <= (_barriers[i].Position().y + _barriers[i].Size().y)) ||
				((_ball.Position().y + 2 * _ball.Radius()) >= _barriers[i].Position().y && (_ball.Position().y + 2 * _ball.Radius()) <= (_barriers[i].Position().y + _barriers[i].Size().y))) // nếu bóng di chuyển quá biên trên
			{
				if (_ball.Position().x + _ball.Radius() >= _barriers[i].Position().x && _ball.Position().x + _ball.Radius() < _barriers[i].Position().x + _barriers[i].Size().x)
				{
					_ball.SetVelocity(-_ball.Velocity().x, _ball.Velocity().y); // đổi hướng bóng
				}
			}
		}
		if (_ball.Position().x + 2 * _ball.Radius() > 4 * WINDOW_WIDTH / 5) // nếu bóng di chuyển quá biên dưới 
		{
			_ball.SetPosition(4 * WINDOW_WIDTH / 5 - 2 * _ball.Radius(), _ball.Position().y); // không cho vị trí của bóng vượt quá biên trên
			_ball.SetVelocity(-_ball.Velocity().x, _ball.Velocity().y); // đổi hướng bóng
		}
	}

	if (!_is1phayer)
	{
		//Tương tự như thành trái
		if (_rightPaddle.Position().y < TOP_BOUNDARY) // //nếu vị trí thanh phải di chuyển quá biên trên
		{
			_rightPaddle.SetPosition(_rightPaddle.Position().x, TOP_BOUNDARY); // không cho vị trí thanh phải vượt quá biên
			if (_rightPaddle.Speed() < 0)
			{
				_rightPaddle.SetSpeed(.0f);
			}
		}

		if (_rightPaddle.Position().y + _rightPaddle.Size().y > BOTTOM_BOUNDARY)
		{
			_rightPaddle.SetPosition(_rightPaddle.Position().x, BOTTOM_BOUNDARY - _rightPaddle.Size().y);
			if (_rightPaddle.Speed() > 0)
			{
				_rightPaddle.SetSpeed(.0f);
			}
		}

		// bóng chạm vào thanh phải
		if (_ball.Position().x + 2 * _ball.Radius() >= _rightPaddle.Position().x && _ball.Position().x + 2*_ball.Radius() <= _rightPaddle.Position().x + _rightPaddle.Size().x
			&& _ball.Position().y + _ball.Radius() > _rightPaddle.Position().y
			&& _ball.Position().y + _ball.Radius() < _rightPaddle.Position().y + _rightPaddle.Size().y)
		{
			_ball.SetPosition(_rightPaddle.Position().x - 2 * _ball.Radius(), _ball.Position().y);//cho bóng không đi tiếp
			//Đổi hướng và độ lớn bóng
			auto newVel = _ball.Velocity();
			float speed = _ball.Speed();
			float affection = AFFECTION_RATIO * speed / _rightPaddle.BaseSpeed();
			newVel.y += _rightPaddle.Velocity().y * affection;
			newVel.x = -newVel.x;
			float newSpeed = sqrtf(newVel.x * newVel.x + newVel.y * newVel.y);
			float scale = speed / newSpeed;
			newVel *= scale * VELOCITY_INCREASING_PERCENTAGE;
			_ball.SetVelocity(newVel);
		}

		if (_ball.Position().x + 2 * _ball.Radius() > RIGHT_BOUNDARY) // bóng chạm biên phải
		{
			AskReStart();
		}
	}
}


//Hàm dùng để bắt các phím người dùng nhấn khi cửa sổ đang chạy
void GameManager::EventHandler()
{
	sf::Event event;
	while (_window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed: //exit 
			_window->close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == EXIT_KEY)//thoát
			{
				_window->close();
			}
			if (event.key.code == PAUSE_KEY)//tạm dừng
			{
				_isPause = !_isPause;
			}
			if (event.key.code == SAVE_GAME)
			{
				// save_game()
			}
			break;
		}
	}

	_leftPaddle.KeyCheck(_leftUp, _leftDown); 
	if (!_is1phayer)
		_rightPaddle.KeyCheck(_rightUp, _rightDown);
}

//Hàm xử lý bắt đầu game, tạm dừng game, vẽ và hiện thị các vật thể ra màn hình
void GameManager::Start()
{
	_isPlaying = true;
	_isPause = false;
	sf::Clock clock;

	sf::Texture texture;
	texture.loadFromFile("image/background.jpg");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(WINDOW_WIDTH / sprite.getGlobalBounds().width, WINDOW_HEIGHT / sprite.getGlobalBounds().height);

	sf::Texture texture2;
	texture2.loadFromFile("image/background2.jpg");
	sf::Sprite sprite2;
	sprite2.setTexture(texture2);
	sprite2.setScale(WINDOW_WIDTH / sprite2.getGlobalBounds().width, WINDOW_HEIGHT / sprite2.getGlobalBounds().height);

	while (_window->isOpen())
	{
		_deltaTime = clock.restart().asSeconds();
		// Event handling
		EventHandler();

		if (_isPause)
		{
			continue;
		}

		// Update
		Update();
		_window->clear();
		// Render
		if (_isPlaying)
		{
			if (_is1phayer) // 1 nguoi choi 
			{
				if (_items.size() == 0)
				{
					InitItemLv2(PADDLE_SIZE, sf::Color::Red);
				}
				/*	 if (...)
					 {
					 Barrier newBarrier;
					 InitBarrier();
					 _barriers.push_back(newBarrier);
					 }*/
				_window->draw(sprite);
				SetBackground1Player();
				_ball.Render(_window); // Vẽ ball
				for (int i = 0; i < _items.size(); i++)
				{
					_items[i].Render(_window);
				}
				for (int i = 0; i < _barriers.size(); i++)
				{
					_barriers[i].Render(_window);
				}

				// Render Barrier
				//vẽ hai thanh trượt
				_leftPaddle.Render(_window);
				_leftScore.Render(_window);
				_window->display();
			}
			else // 2 nguoi choi 
			{
				_window->draw(sprite2);
				_leftScore.Render(_window); // vẽ điểm _leftScore 
				_rightScore.Render(_window); // vẽ điểm _rightScore 
				_ball.Render(_window); // Vẽ ball
				//vẽ hai thanh trượt
				_leftPaddle.Render(_window);
				_rightPaddle.Render(_window);
				_window->display();
			}
		}
		else
		{
			//_window->display();
			PostProcess();
			break;
		}
	}
}

void GameManager::SetBackground1Player()
{ 
	sf::Font font;
	font.loadFromFile(FONT_NAME);

	sf::Text score;
	score.setFont(font);
	score.setString("SCORE: ");
	score.setFillColor(TEXT_COLOR);
	score.setOutlineColor(TEXT_BORDER_COLOR);
	score.setOutlineThickness(TEXT_BORDER_THICKNESS);
	score.setPosition(4 * WINDOW_WIDTH / 5 + 30, WINDOW_HEIGHT / 4);

	sf::Text items;
	items.setFont(font);
	items.setString("ITEMS: ");
	items.setFillColor(TEXT_COLOR);
	items.setOutlineColor(TEXT_BORDER_COLOR);
	items.setOutlineThickness(TEXT_BORDER_THICKNESS);
	items.setPosition(4 * WINDOW_WIDTH / 5 + 30, 2* WINDOW_HEIGHT / 4);

	sf::Text speed;
	speed.setFont(font);
	speed.setString("SPEED: ");
	speed.setFillColor(TEXT_COLOR);
	speed.setOutlineColor(TEXT_BORDER_COLOR);
	speed.setOutlineThickness(TEXT_BORDER_THICKNESS);
	speed.setPosition(4 * WINDOW_WIDTH / 5 + 30, 3 * WINDOW_HEIGHT / 4);

	sf::Text numberItem;
	numberItem.setFont(font);
	std::string number = std::to_string(_items.size());
	numberItem.setString(number);
	numberItem.setOutlineThickness(TEXT_BORDER_THICKNESS);
	numberItem.setPosition(4 * WINDOW_WIDTH / 5 + 160, 2 * WINDOW_HEIGHT / 4);

	sf::Text ball_speed;
	ball_speed.setFont(font);
	std::string sp = std::to_string(int(_ball.Speed()));
	ball_speed.setString(sp);
	ball_speed.setOutlineThickness(TEXT_BORDER_THICKNESS);
	ball_speed.setPosition(4 * WINDOW_WIDTH / 5 + 160, 3 * WINDOW_HEIGHT / 4);

	_window->draw(score);
	_window->draw(speed);
	_window->draw(items);
	_window->draw(numberItem);
	_window->draw(ball_speed);

	_leftScore.SetPosition(sf::Vector2f(4 * WINDOW_WIDTH / 5 + 160, WINDOW_HEIGHT / 4 - 4));
	_leftScore.SetSize(score.getGlobalBounds().height + 10);
}

void GameManager::About()
{
	sf::Texture texture;
	texture.loadFromFile("image/about.jpg");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(WINDOW_WIDTH / sprite.getGlobalBounds().width, WINDOW_HEIGHT / sprite.getGlobalBounds().height);

	while (_window->isOpen())
	{
		sf::Event event;
		while (_window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed: //exit 
				_window->close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == EXIT_KEY)//thoát
				{
					_window->close();
				}
				if (event.key.code == sf::Keyboard::Enter)
				{
					return;
				}
			}
		}
		_window->clear();
		_window->draw(sprite);
		_window->display();
	}
}

void GameManager::Setting()
{
	sf::Texture texture;
	texture.loadFromFile("image/setting.jpg");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(WINDOW_WIDTH / sprite.getGlobalBounds().width, WINDOW_HEIGHT / sprite.getGlobalBounds().height);

	while (_window->isOpen())
	{
		sf::Event event;
		while (_window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed: //exit 
				_window->close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == EXIT_KEY)//thoát
				{
					_window->close();
				}
				if (event.key.code == sf::Keyboard::Enter)
				{
					return;
				}
			}
		}
		_window->clear();
		_window->draw(sprite);
		_window->display();
	}
}

void GameManager::HowToPlay()
{
	sf::Texture texture;
	texture.loadFromFile("image/howtoplay.jpg");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(WINDOW_WIDTH / sprite.getGlobalBounds().width, WINDOW_HEIGHT / sprite.getGlobalBounds().height);

	while (_window->isOpen())
	{
		sf::Event event;
		while (_window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed: //exit 
				_window->close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == EXIT_KEY)//thoát
				{
					_window->close();
				}
				if (event.key.code == sf::Keyboard::Enter)
				{
					return;
				}
			}
		}
		_window->clear();
		_window->draw(sprite);
		_window->display();
	}
}

void GameManager::PostProcess()
{
	for (int i = 0; i < rankScore.size(); i++)
	{
		if (_leftScore.GetScore() > rankScore[i])
		{
			rankScore.insert(rankScore.begin() + i, _leftScore.GetScore());
		//	rankList.insert(rankList.begin() + i, _name);
		}
	}

	Edit congratula;
	congratula.InitText("CONGRATULATIONS ^^", TITLE_SIZE, sf::Color::Blue, TEXT_BORDER_COLOR, TEXT_BORDER_THICKNESS, 0, 3); 
	_window->clear();
	while (_window->isOpen())
	{
		sf::Event event;
		while (_window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed: //exit 
				_window->close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == EXIT_KEY)//thoát
				{
					_window->close();
				}
				if (event.key.code == sf::Keyboard::Enter)
				{
					return;
				}
			}
		}
		_window->clear();
		congratula.Render(_window);
		_window->display();
	}
}

//-----------------------------------------------init function-----------------------------------------------//


// Hàm dùng để khởi tạo các thông số cho Ball
//input: bán kính radius, vị trí position, vận tốc velocity, màu bóng fillcolor , độ dày của đường viền borderthickness, màu của đường viền bordercolor
void GameManager::InitBall(float radius, sf::Vector2f position, sf::Vector2f velocity, sf::Color fillColor, float borderthickness, sf::Color borderColor)
{
	_ball.SetRadius(radius); // khởi tạo giá trị bán kính
	_ball.SetPosition(position); // khởi tạo vector vị trí
	_ball.SetVelocity(velocity); // khởi tạo vector vận tốc
	_ball.SetFillColor(fillColor); // khởi tạo màu sắc quả bóng
	_ball.SetBorderThickness(borderthickness); // độ dày của đường viền
	_ball.SetBorderColor(borderColor); // khởi tạo màu đường viền
}

// Hàm dùng để khởi tạo các thông số cho thanh trái và thanh phải
/* Input: thanh trái or phải paddleside , kích thước sizepaddle, vị trí position, tốc độ basesSpeed , màu sắc fillcolor,
Độ dày của đường viền borderThickness, màu sắc đường viền borderColor */
void GameManager::InitPaddle(int paddleside, sf::Vector2f sizepaddle, sf::Vector2f position, float baseSpeed, sf::Color fillColor, float borderThickness, sf::Color borderColor)
{
	Paddle* selectedPaddle;
	if (paddleside == PADDLE_LEFT)
	{
		selectedPaddle = &_leftPaddle;
	}
	else if (paddleside == PADDLE_RIGHT)
	{
		selectedPaddle = &_rightPaddle;
	}
	else
	{
		return;
	}
	selectedPaddle->SetSize(sizepaddle); //khởi tạo kích thước
	selectedPaddle->SetPosition(position); // khởi tạo vị trí
	selectedPaddle->SetBaseSpeed(baseSpeed); // khởi tạo vận tốc
	selectedPaddle->SetFillColor(fillColor); //khởi tạo màu sắc
	selectedPaddle->SetBorderThickness(borderThickness); //khởi tạo độ dày đường viền
	selectedPaddle->SetBorderColor(borderColor);  // khởi tạo màu của đường viền
}

void GameManager::InitItemLv2(sf::Vector2f size, sf::Color fillColor)
{
	for (int i = 0; i < 40; i++)
	{
		Items ad;
		_items.push_back(ad);
	}

	for (int i = 0; i < 8; i++)
	{
		_items[i].SetPosition(WINDOW_WIDTH / 2 + 200, 30 + i * 100);
		_items[i].SetSize(size.x, size.y/3);
		_items[i].SetFillColor(fillColor);
	}

	for (int i = 8; i < 16; i++)
	{
		_items[i].SetPosition(WINDOW_WIDTH / 2 + 240, 40 + (i-8) * 100);
		_items[i].SetSize(size.x, size.y / 3);
		_items[i].SetFillColor(fillColor);
	}
	for (int i = 16; i < 24; i++)
	{
		_items[i].SetPosition(WINDOW_WIDTH / 2 + 280, 30 + (i-16) * 100);
		_items[i].SetSize(size.x, size.y / 3);
		_items[i].SetFillColor(fillColor);
	}

	for (int i = 24; i < 32; i++)
	{
		_items[i].SetPosition(WINDOW_WIDTH / 2 + 320, 50 + (i-24) * 100);
		_items[i].SetSize(size.x, size.y / 3);
		_items[i].SetFillColor(fillColor);
	}
	for (int i = 32; i < 40; i++)
	{
		_items[i].SetPosition(WINDOW_WIDTH / 2 + 360, 30 + (i-32) * 100);
		_items[i].SetSize(size.x, size.y / 3);
		_items[i].SetFillColor(fillColor);
	}
}

void GameManager::InitItemLv1(sf::Vector2f size, sf::Color fillColor)
{
	for (int i = 0; i < 16; i++)
	{
		Items ad;
		_items.push_back(ad);
	}

	for (int i = 0; i < 8; i++)
	{
		_items[i].SetPosition(WINDOW_WIDTH / 2 + 200, 30 + i * 100);
		_items[i].SetSize(size.x, size.y / 3);
		_items[i].SetFillColor(fillColor);
	}

	for (int i = 8; i < 16; i++)
	{
		_items[i].SetPosition(WINDOW_WIDTH / 2 + 250, 40 + (i - 8) * 100);
		_items[i].SetSize(size.x, size.y / 3);
		_items[i].SetFillColor(fillColor);
	}
}

void GameManager::InitBarrier(sf::Vector2f size)
{
	int a;
	a = rand() % 4 + 2;
	for (int i = 0; i < a; i++)
	{
		Barrier ad;
		_barriers.push_back(ad);
	}

	for (int i = 0; i < a; i++)
	{
		_barriers[i].SetPosition(WINDOW_WIDTH / 2 + 60, 30 + i * 100);
		_barriers[i].SetSize(size.x, size.y / 3);
		_barriers[i].SetFillColor(sf::Color::Yellow);
	}
}

// Hàm khởi tạo hai phím di chuyển lên - xuống cho thanh trái và thanh phải
// Input: chọn thanh paddleside , phím di chuyển lên: up , phím di chuyển xuống: down 
void GameManager::InitKeyControl(int paddleside, sf::Keyboard::Key up, sf::Keyboard::Key down)
{
	if (paddleside == PADDLE_LEFT)
	{
		_leftUp = up;
		_leftDown = down;
	}
	else if (paddleside == PADDLE_RIGHT)
	{
		_rightUp = up;
		_rightDown = down;
	}

}

// Khởi tạo các thông số cho Score của người chơi trái và phải
// Input: chọn bên paddle, định dạng chữ font, kích cỡ Score size , vị trí position, màu chữ color , điểm ban đầu: basescore 
void GameManager::InitScore(int paddle, sf::Font font, int size, sf::Vector2f position, sf::Color color, int basescore)
{
	Score* selectedScore;
	//Chọn _leftScore or _rightScore
	if (paddle == SCORE_LEFT)
	{
		selectedScore = &_leftScore;
	}
	else if (paddle == SCORE_RIGHT)
	{
		selectedScore = &_rightScore;
	}
	else
	{
		return;
	}
	selectedScore->SetFont(font); //khởi tạo font chữ
	selectedScore->SetSize(size); // khởi tạo kích cỡ chữ
	selectedScore->SetPosition(position); // khởi tạo vị trí
	selectedScore->SetFillColor(color); // khởi tạo màu chữ
	selectedScore->SetScore(basescore); //khởi tạo giá trị điểm khi mới vào game

}

// Hàm tạo GameManager
// Input : cửa sổ *winodw, BackGround
GameManager::GameManager(sf::RenderWindow* window) 
{
	_window = window;
	_deltaTime = .0f;
	_leftUp = LEFT_PADDLE_UPKEY;
	_leftDown = LEFT_PADDLE_DOWNKEY;
	_rightUp = RIGHT_PADDLE_UPKEY;
	_rightDown = RIGHT_PADDLE_DOWNKEY;
	_isPlaying = false;
	_isPause = false;

	std::fstream rank_file;
	rank_file.open("rank.txt");
	std::string str;
	std::string name;
	int score;
	while (rank_file >> score)
	{
		rank_file >> name;
		rankList.push_back(name);
		rankScore.push_back(score);
	}
	rank_file.close();
}

GameManager::~GameManager()
{
	std::fstream rank_file;
	rank_file.open("rank.txt", std::ios::out);
	for (int i = 0; i < rankScore.size(); i++)
	{
		rank_file << rankScore[i];
		rank_file << " " << rankList[i] << "\n";
	}

	rank_file.close();
}