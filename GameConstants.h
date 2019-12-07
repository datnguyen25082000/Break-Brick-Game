#pragma once
#include <SFML/Graphics.hpp>
#include <string>


const unsigned int SCREEN_WIDTH = sf::VideoMode::getDesktopMode().width;
const unsigned int SCREEN_HEIGHT = sf::VideoMode::getDesktopMode().height;

const std::string WINDOW_TITLE = "Pong Game";
const int WINDOW_STYLE = sf::Style::None;
const unsigned int WINDOW_WIDTH = SCREEN_WIDTH;
const unsigned int WINDOW_HEIGHT = SCREEN_HEIGHT;
const int ANTIALIASING_LEVEL = 8;
const int FRAME_RATE_LIMIT = 120;

const float BACKGROUND_STROKE = 10.0f;
const int CIRCLE_POINT_COUNT = 100;
#define BACKGROUND_BRUSH sf::Color(255, 255, 255)
#define BACKGROUND_COLOR sf::Color(76, 235, 52)
#define BALL_COLOR sf::Color(255, 238, 3) 
#define BALL_BORDER_COLOR sf::Color(255, 3, 20)

#define LEFT_PADDLE_COLOR sf::Color(0,255,255)
#define RIGHT_PADDLE_COLOR sf::Color(131,111,255)
#define ITEM_COLOR sf::Color(118 ,238, 0)
#define BARRIER_COLOR sf::Color(119,52,235)

#define TEXT_COLOR sf::Color(255, 173, 0)
#define TEXT_BORDER_COLOR sf::Color::Black
#define TITLE_COLOR sf::Color(0, 191, 255)

const float TEXT_BORDER_THICKNESS = 1.0f;

const float MENU_GAP = 15.0f;

const float TOP_BOUNDARY = 0;
const float BOTTOM_BOUNDARY = (float) WINDOW_HEIGHT;
const float LEFT_BOUNDARY = 0;
const float RIGHT_BOUNDARY = (float) WINDOW_WIDTH;

const sf::Keyboard::Key START_KEY = sf::Keyboard::Space;
const sf::Keyboard::Key EXIT_KEY = sf::Keyboard::Escape;
const sf::Keyboard::Key PAUSE_KEY = sf::Keyboard::Space;
const sf::Keyboard::Key CONTUNUE = sf::Keyboard::A;
const sf::Keyboard::Key SAVE_GAME = sf::Keyboard::S;
const sf::Keyboard::Key LOAD_GAME = sf::Keyboard::L;

const float BALL_RADIUS = 10.0f;
const sf::Vector2f INITIAL_BALL_POSITION((float)WINDOW_WIDTH / 2.0f - BALL_RADIUS, (float)WINDOW_HEIGHT / 2.0f - BALL_RADIUS);
const float BALL_BASE_SPEED = 600.0f;
const float BALL_BASE_X_MIN_SPEED = BALL_BASE_SPEED / 3.0f;
const float BALL_BASE_Y_MIN_SPEED = BALL_BASE_SPEED / 3.0f;
const float BALL_BORDER = 5.0f;

const float VELOCITY_INCREASING_PERCENTAGE = 1.1f;
const float AFFECTION_RATIO = 0.5f;

const sf::Vector2f PADDLE_SIZE(30, WINDOW_HEIGHT / 4.5f);
const sf::Vector2f ITEM_SIZE(25, WINDOW_HEIGHT / 5.0f);
const sf::Vector2f BA_SIZE(35, WINDOW_HEIGHT / 5.0f);
const float PADDLE_SPEED = 2.0f;
const float PADDLE_BASE_SPEED = 600.0f;

const int PADDLE_LEFT = 0;
const int PADDLE_RIGHT = 1;

const int SCORE_LEFT = 0;
const int SCORE_RIGHT = 1;


const sf::Keyboard::Key LEFT_PADDLE_UPKEY = sf::Keyboard::W;
const sf::Keyboard::Key LEFT_PADDLE_DOWNKEY = sf::Keyboard::S;

const sf::Keyboard::Key RIGHT_PADDLE_UPKEY = sf::Keyboard::Up;
const sf::Keyboard::Key RIGHT_PADDLE_DOWNKEY = sf::Keyboard::Down;

const sf::Vector2f INITIAL_LEFT_PADDLE_POSITION(LEFT_BOUNDARY + 4 * PADDLE_SIZE.x, 
												(BOTTOM_BOUNDARY - TOP_BOUNDARY - PADDLE_SIZE.y) / 2.0f);
const sf::Vector2f INITIAL_RIGHT_PADDLE_POSITION(RIGHT_BOUNDARY -  4 * PADDLE_SIZE.x, 
												 (BOTTOM_BOUNDARY - TOP_BOUNDARY - PADDLE_SIZE.y) / 2.0f);

const sf::Vector2f LEFT_SCORE_POSITION(WINDOW_WIDTH / 2.0f - 75.0f, 15);
const sf::Vector2f RIGHT_SCORE_POSITION(WINDOW_WIDTH /2.0f + 20.0f, 15);

const int SCORE_SIZE = 100;
const int BASE_SCORE = 0;
const int TEXT_SIZE = 70;
const int ESC_SIZE = 40;
const int TITLE_SIZE = 90;
const int ITEM_SCORE = 10;

const int NUMBER_OF_GAME = 10;

const std::string FONT_NAME = "ASMAN.ttf";
const std::string LEFT_WIN_MESSAGE = "Left Win";
const std::string RIGHT_WIN_MESSAGE = "Right Win";
const std::string PLAY_MENU_TEXT = "   SPACE: PLAY";
const std::string EXIT_MENU_TEXT = "  ESC: EXIT  ";
const std::string KEY_MENU_TEXT = "      W-S     Up-Down";

