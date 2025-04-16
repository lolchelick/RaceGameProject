#include <SFML/Graphics.hpp>
#include "include/Background.h"
#include "include/Player.h" 
#include "include/TextureHolder.h"
#include "include/Biker.h"
#include "include/Button.h"

#include <iostream>
#include <sstream>
#include <vector>

#define PATH_TO_CONTENT_IMG "C:/RaceGameProject/cnt/img/"
#define PATH_TO_CONTENT_AUDIO "C:/RaceGameProject/cnt/audio/"
#define PATH_TO_CONTENT_FONT "C:/RaceGameProject/cnt/fonts/"
#define BACKGROUND_SHEET_SIZE Vector2f(375, 1500)
#define BACKGROUND_MOVE_SPEED 500.0f
#define WIN_SIZE Vector2f(BACKGROUND_SHEET_SIZE.x, BACKGROUND_SHEET_SIZE.y / 3)
#define NULL_POS Vector2f(0.0f, 0.0f)
#define POS_OF_FIRST_HEART Vector2f(40.0f, 10.0f)

using namespace sf;

void bikerDeath(Biker& b, std::string pathToTexture);
void bikerReborn(Biker& b, std::string pathToTexture);

bool dead = false;
bool intersects = false;

enum gameState { MAIN_MENU, PLAYING, GAME_OVER };
gameState gameStateNow = MAIN_MENU;

int score = 0;
int lives = 3;

int main()
{
	RenderWindow win(VideoMode(WIN_SIZE.x, WIN_SIZE.y), "RaceGame!!!");

	win.setMouseCursorVisible(true);

#pragma region Adding Score
	std::stringstream ss;
	ss << "SCORE: ";
	Font scoreFont;
	scoreFont.loadFromFile(PATH_TO_CONTENT_FONT"game_interface_font.ttf");
	Text scoreText;
	scoreText.setFont(scoreFont);
	scoreText.setCharacterSize(20);
	scoreText.setString(ss.str());
	scoreText.setPosition(Vector2f(260.0f, 10.0f));
	scoreText.setFillColor(Color::Yellow);
#pragma endregion Adding Score

#pragma region Adding Lives
	std::vector<Sprite> vectorHearts;
	for (int i = 0; i < lives; i++)
	{
		vectorHearts.push_back(Sprite(TextureHolder::GetTexture(PATH_TO_CONTENT_IMG"LiveHeartTexture.png")));
	}
	int i = 1;
	for (auto it = vectorHearts.begin(); it != vectorHearts.end(); it++)
	{
		it->setPosition(Vector2f(POS_OF_FIRST_HEART.x * i, POS_OF_FIRST_HEART.y));
		i++;
	}
#pragma endregion Adding Lives



	Button bPlay(Vector2f(WIN_SIZE.x / 2.0f, WIN_SIZE.y / 4.0f * 3.0f), PATH_TO_CONTENT_IMG"PlayButtonTexture.png");
	Font fontPlay;
	if (!fontPlay.loadFromFile(PATH_TO_CONTENT_FONT"main_menu_font.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}
	Text textPlay;
	textPlay.setFont(fontPlay);
	textPlay.setCharacterSize(40);
	textPlay.setPosition(Vector2f(70.0f, 50.0f));
	textPlay.setString("RACE GAME");
	textPlay.setFillColor(Color::Black);


	
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
	



	Clock clock;

	while (win.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();


#pragma region Polling Event

		Event ev;
		while (win.pollEvent(ev))
		{
			if (ev.type == Event::Closed)
			{
				win.close();
				std::cout << "Type : Event::Closed" << std::endl;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			win.close();
		}
#pragma endregion Polling Event


		if (gameStateNow == MAIN_MENU)
		{
			if (bPlay.update(win))
			{
				gameStateNow = PLAYING;
			}
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

#pragma endregion Player Control Logic

#pragma region Biker Control
			biker.update(deltaTime);
#pragma endregion Biker Control Logic

#pragma region Collision Detection

			if (biker.getPosition().x >= 0.0f && biker.getPosition().x <= WIN_SIZE.x && biker.getPosition().y >= 0.0f
				&& biker.getPosition().y <= WIN_SIZE.y && !intersects)
			{
				if (player.getRect().intersects(biker.getRect()))
				{
					std::cout << "Collision Detected in \t X: " << biker.getPosition().x << "  Y: " << biker.getPosition().y << std::endl;
					bikerDeath(biker, PATH_TO_CONTENT_IMG"BloodTexture.png");
					intersects = true;
					score++;
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

			
			scoreText.setString((ss).str() + std::to_string(score));
		}



		win.clear();
		
		if (gameStateNow == MAIN_MENU)
		{
			win.draw(rectMainMenuBack); 
			win.draw(bPlay.getShape());
			win.draw(textPlay);
		}

		else if (gameStateNow == PLAYING)
		{
			win.draw(backSheet_2.getShape());
			win.draw(backSheet_1.getShape());
			win.draw(biker.getSprite());
			win.draw(player.getSprite()); 
			win.draw(scoreText);
			for (int i = 0; i < lives; i++)
			{
				win.draw(vectorHearts.at(i));
			}
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
