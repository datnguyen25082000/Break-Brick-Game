#include "GameManager.h"
#include "GameConstants.h"


int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = ANTIALIASING_LEVEL;
	// Tạo 1 cửa sổ mainWindow
	sf::RenderWindow mainWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, WINDOW_STYLE, settings);
	mainWindow.setFramerateLimit(FRAME_RATE_LIMIT);
	sf::Font font;
	font.loadFromFile(FONT_NAME);


	Edit title;
	title.InitText("PING PONG GAME", TITLE_SIZE, TITLE_COLOR, TEXT_BORDER_COLOR,TEXT_BORDER_THICKNESS, 0, 3);
	Edit onePlayer;
	onePlayer.InitText("1 PLAYER", TEXT_SIZE, TEXT_COLOR, TEXT_BORDER_COLOR, TEXT_BORDER_THICKNESS, 0, 20);
	Edit twoPlayer;
	twoPlayer.InitText("2 PLAYERS", TEXT_SIZE, TEXT_COLOR, TEXT_BORDER_COLOR, TEXT_BORDER_THICKNESS, 0, 25);
	Edit guide;
	guide.InitText("HOW TO PLAY", TEXT_SIZE, TEXT_COLOR, TEXT_BORDER_COLOR, TEXT_BORDER_THICKNESS, 0, 30);
	Edit about;
	about.InitText("ABOUT", TEXT_SIZE, TEXT_COLOR, TEXT_BORDER_COLOR, TEXT_BORDER_THICKNESS, 0, 35);
	Edit setting;
	setting.InitText("SETTING", TEXT_SIZE, TEXT_COLOR, TEXT_BORDER_COLOR, TEXT_BORDER_THICKNESS, 0, 40);

	// ESC : EXIT  
	sf::Text exitText;
	exitText.setFont(font);
	exitText.setString(EXIT_MENU_TEXT);
	exitText.setCharacterSize(ESC_SIZE);
	exitText.setFillColor(TEXT_COLOR);
	exitText.setOutlineColor(TEXT_BORDER_COLOR);
	exitText.setOutlineThickness(TEXT_BORDER_THICKNESS);
	exitText.setPosition(WINDOW_WIDTH - exitText.getGlobalBounds().width, WINDOW_HEIGHT - 2*exitText.getGlobalBounds().height);

	// set background image
	sf::Texture texture;
	texture.loadFromFile("image/background1.jpg");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(WINDOW_WIDTH / sprite.getGlobalBounds().width, WINDOW_HEIGHT / sprite.getGlobalBounds().height);

	while (mainWindow.isOpen())
	{
		GameManager gameManager(&mainWindow);
		gameManager.InitPaddle(PADDLE_LEFT, PADDLE_SIZE, INITIAL_LEFT_PADDLE_POSITION, PADDLE_BASE_SPEED, LEFT_PADDLE_COLOR);
		gameManager.InitPaddle(PADDLE_RIGHT, PADDLE_SIZE, INITIAL_RIGHT_PADDLE_POSITION, PADDLE_BASE_SPEED, RIGHT_PADDLE_COLOR);
		gameManager.InitKeyControl(PADDLE_LEFT, LEFT_PADDLE_UPKEY, LEFT_PADDLE_DOWNKEY);
		gameManager.InitKeyControl(PADDLE_RIGHT, RIGHT_PADDLE_UPKEY, RIGHT_PADDLE_DOWNKEY);
		gameManager.InitScore(SCORE_LEFT, font, SCORE_SIZE, LEFT_SCORE_POSITION, sf::Color::White, BASE_SCORE);
		gameManager.InitScore(SCORE_RIGHT, font, SCORE_SIZE, RIGHT_SCORE_POSITION, sf::Color::White, BASE_SCORE);
		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				mainWindow.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == EXIT_KEY)
				{
					mainWindow.close();
				}
				if (event.key.code == LOAD_GAME)
				{
					// GameManager.Loadgame()
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (onePlayer.CheckMouseButtonPress(&event))
				{
					gameManager.SetIs1Player(true);
					sf::Vector2f ball_vel = Ball::GenerateRandomVelocity(BALL_BASE_SPEED, BALL_BASE_X_MIN_SPEED, BALL_BASE_Y_MIN_SPEED); // Tạo một vetor vận tốc bất kì
					gameManager.InitBall(BALL_RADIUS, INITIAL_BALL_POSITION, ball_vel, BALL_COLOR, BALL_BORDER, BALL_BORDER_COLOR); // Khởi tạo một bóng mới
					//khởi tạo lại hai điểm số ban đầu
					gameManager.InitItemLv2(PADDLE_SIZE, ITEM_COLOR);
					gameManager.InitBarrier(PADDLE_SIZE);
					gameManager.InitScore(SCORE_LEFT, font, SCORE_SIZE, LEFT_SCORE_POSITION, sf::Color::White, BASE_SCORE);
					gameManager.Start();
				}
				if (twoPlayer.CheckMouseButtonPress(&event))
				{
					gameManager.SetIs1Player(false);
					sf::Vector2f ball_vel = Ball::GenerateRandomVelocity(BALL_BASE_SPEED, BALL_BASE_X_MIN_SPEED, BALL_BASE_Y_MIN_SPEED); // Tạo một vetor vận tốc bất kì
					gameManager.InitBall(BALL_RADIUS, INITIAL_BALL_POSITION, ball_vel, BALL_COLOR, BALL_BORDER, BALL_BORDER_COLOR); // Khởi tạo một bóng mới
					//khởi tạo lại hai điểm số ban đầu
					gameManager.InitScore(SCORE_LEFT, font, SCORE_SIZE, LEFT_SCORE_POSITION, sf::Color::White, BASE_SCORE);
					gameManager.InitScore(SCORE_RIGHT, font, SCORE_SIZE, RIGHT_SCORE_POSITION, sf::Color::White, BASE_SCORE);
					gameManager.Start();
				}
				if (guide.CheckMouseButtonPress(&event))
				{
					gameManager.HowToPlay();
				}
				if (about.CheckMouseButtonPress(&event))
				{
					gameManager.About();
				}
				if (setting.CheckMouseButtonPress(&event))
				{
					gameManager.Setting();
				}
				break;
			}
		}
		mainWindow.clear();
		mainWindow.draw(sprite);
		mainWindow.draw(exitText);
		title.Render(&mainWindow);
		onePlayer.Render(&mainWindow);
		twoPlayer.Render(&mainWindow);
		guide.Render(&mainWindow);
		about.Render(&mainWindow);
		setting.Render(&mainWindow);
		mainWindow.display();
	}
	
	return 0;
}

