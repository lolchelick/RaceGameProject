#include <SFML/Graphics.hpp>
#include "include/Background.h"
#include "include/Player.h" 
#include "include/TextureHolder.h"
#include "include/Biker.h"

#include <iostream>

#define PATH_TO_CONTENT_IMG "C:/RaceGameProject/cnt/img/"
#define PATH_TO_CONTENT_AUDIO "C:/RaceGameProject/cnt/audio/"
#define PATH_TO_CONTENT_FONT "C:/RaceGameProject/cnt/fonts/"
#define BACKGROUND_SHEET_SIZE Vector2f(375, 1500)
#define BACKGROUND_MOVE_SPEED 500.0f
#define WIN_SIZE Vector2f(BACKGROUND_SHEET_SIZE.x, BACKGROUND_SHEET_SIZE.y / 3)
#define NULL_POS Vector2f(0.0f, 0.0f)
#define POS_OF_FIRST_HEART Vector2f(10.0f, 10.0f)

using namespace sf;

void bikerDeath(Biker& b, std::string pathToTexture);
void bikerReborn(Biker& b, std::string pathToTexture);

bool dead = false;
bool intersects = false;

enum gameState { MAIN_MENU, PLAYING, GAME_OVER };
gameState gameStateNow = MAIN_MENU;

int score = 0;
int lives = 5;

int main()
{
	RenderWindow win(VideoMode(WIN_SIZE.x, WIN_SIZE.y), "RaceGame!!!");
	
	//TextureHolder th;

#pragma region Set Icon
	Image icon;
	if(!icon.loadFromFile(PATH_TO_CONTENT_IMG"icon.png"))
	{
		std::cout << std::endl << "Error loading ICON" << std::endl;
		return 1;
	}
	win.setIcon(32, 32, icon.getPixelsPtr());
#pragma endregion Set Icon

#pragma region BackgroundCreation
	Background backSheet_1(&TextureHolder::GetTexture(PATH_TO_CONTENT_IMG"RoadTexture.png"), BACKGROUND_SHEET_SIZE, true, Vector2f(0.0f, (WIN_SIZE.y - BACKGROUND_SHEET_SIZE.y)), BACKGROUND_MOVE_SPEED);
	Background backSheet_2(&TextureHolder::GetTexture(PATH_TO_CONTENT_IMG"RoadTexture.png"), BACKGROUND_SHEET_SIZE, false, Vector2f(0.0f, backSheet_1.getPosition().y - BACKGROUND_SHEET_SIZE.y), BACKGROUND_MOVE_SPEED);
	bool movedBack_1 = false;
	bool movedBack_2 = false;

	std::cout << "backSheet_1 POSITION: " << "X: " << backSheet_1.getPosition().x << "\tY: " << backSheet_1.getPosition().y << std::endl;
	std::cout << "backSheet_2 POSITION: " << "X: " << backSheet_2.getPosition().x << "\tY: " << backSheet_2.getPosition().y << std::endl;
#pragma endregion BackgroundCreation

#pragma region PlayerCreation
	Player player(TextureHolder::GetTexture(PATH_TO_CONTENT_IMG"CarTexture.png"), Vector2f(280, 430), 170.0f);
#pragma endregion PlayerCreation

#pragma region BikerCreation
	Biker biker(PATH_TO_CONTENT_IMG"BikeTexture.png", 1.5f, BACKGROUND_MOVE_SPEED, win);
#pragma endregion BikerCreation

#pragma region MainManuContentCreation
	Sprite rectMainMenuBack;
	rectMainMenuBack.setTexture(TextureHolder::GetTexture(PATH_TO_CONTENT_IMG"MainMenuBackTexture.png"));
	rectMainMenuBack.setPosition(NULL_POS);
#pragma endregion MainManuContentCreation
	
#pragma region Text
	Font mainMenuFont;
	Font gameInterFaceFont;
	mainMenuFont.loadFromFile(PATH_TO_CONTENT_FONT"main_menu_font.ttf");
	gameInterFaceFont.loadFromFile(PATH_TO_CONTENT_FONT"game_interface_font.ttf");

	Text playButton;
	Text scoreText;
	playButton.setFont(mainMenuFont);
	playButton.setCharacterSize(60);
	playButton.setFillColor(Color::Black);
	playButton.setString(String("PLAY"));
	playButton.setPosition(Vector2f(100.0f, 340.0f));
#pragma endregion Text


	Clock clock;

	while (win.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		Event ev;
		while (win.pollEvent(ev))
		{
			if (ev.type == Event::Closed)
			{
				win.close();
				std::cout << "Type : Event::Closed" << std::endl;
			}
			if (ev.key.code == Keyboard::Escape)
			{
				win.close();
			}

		}

		if (gameStateNow == MAIN_MENU)
		{

		}

		if (gameStateNow == PLAYING)
		{
#pragma region Background Swap Logic
			if (backSheet_1.getPosition().y >= NULL_POS.y && !movedBack_1)
			{
				backSheet_2.setPosition(Vector2f(0.0f, NULL_POS.y - BACKGROUND_SHEET_SIZE.y));
				std::cout << "backSheet_2 WAS MOVED TO THE:\t\tX: " << backSheet_2.getPosition().x << "\tY: " << backSheet_2.getPosition().y << std::endl;
				movedBack_1 = true;
				movedBack_2 = false;
			}
			else if (backSheet_2.getPosition().y >= NULL_POS.y && !movedBack_2)
			{
				backSheet_1.setPosition(Vector2f(0.0f, NULL_POS.y - BACKGROUND_SHEET_SIZE.y));
				std::cout << "backSheet_1 WAS MOVED TO THE:\t\tX: " << backSheet_1.getPosition().x << "\tY: " << backSheet_1.getPosition().y << std::endl;
				movedBack_2 = true;
				movedBack_1 = false;
			}
			if (backSheet_1.getPosition().y < win.getSize().y)
			{
				backSheet_1.update(deltaTime, win);
			}
			if (backSheet_2.getPosition().y < win.getSize().y)
			{
				backSheet_2.update(deltaTime, win);
			}
#pragma endregion Background Swap Logic

#pragma region Player Control

			player.update(deltaTime, win);

#pragma endregion Player Control

#pragma region Biker Control
			biker.update(deltaTime);
#pragma endregion Biker Control

#pragma region Collision Detection

			if (biker.getPosition().x >= 0.0f && biker.getPosition().x <= WIN_SIZE.x && biker.getPosition().y >= 0.0f
				&& biker.getPosition().y <= WIN_SIZE.y && !intersects)
			{
				if (player.getRect().intersects(biker.getRect()))
				{
					std::cout << "Collision Detected in \t X: " << biker.getPosition().x << "  Y: " << biker.getPosition().y << std::endl;
					bikerDeath(biker, PATH_TO_CONTENT_IMG"BloodTexture.png");
					intersects = true;
				}
				else
				{
					intersects = false;
				}
			}
			if (biker.isSpawnedUpward() && dead)
			{
				intersects = false;
				std::cout << "Spawned Upward and ready to set Textures" << std::endl;
				bikerReborn(biker, PATH_TO_CONTENT_IMG"BikeTexture.png");

			}
#pragma endregion Collision Detection

#pragma region Setting Live Hearts
#pragma endregion Setting Live Hearts

		}

		
		

		win.clear();
		
		if (gameStateNow == MAIN_MENU)
		{
			win.draw(rectMainMenuBack); 
			win.draw(playButton);
			//win.draw(text of button play);
		}

		if (gameStateNow == PLAYING)
		{
			win.draw(backSheet_2.getShape());
			win.draw(backSheet_1.getShape());
			win.draw(biker.getSprite());
			win.draw(player.getSprite()); 
		}

		win.display();
	}

	std::cout << std::endl <<"SESSION ENDED!" << std::endl;
	return 0;
}

 

void bikerDeath(Biker& b, std::string pathToTexture)
{
	Texture &t = TextureHolder::GetTexture(pathToTexture);
	Sprite s(t);
	s.setOrigin(t.getSize().x / 2.0f, t.getSize().y / 2.0f);
	b.setSprite(s);
	b.setUnoSpeedCoeff();
	dead = true;
}
void bikerReborn(Biker &b, std::string pathToTexture)
{
	Texture &t = TextureHolder::GetTexture(pathToTexture);
	Sprite s(t);
	s.setOrigin(t.getSize().x / 2.0f, t.getSize().y / 2.0f);
	s.setPosition(- 15, -15);
	b.setSprite(s);
	dead = false;
}

