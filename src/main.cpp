#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "include/Background.h"
#include "include/Player.h" 
#include "include/TextureHolder.h"
#include "include/Biker.h"
#include "include/Button.h"
#include "include/Trap.h"

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

std::string setRandomMusic();

bool dead = false;
bool intersects = false;
bool intersectsTrap = false;

enum gameState { MAIN_MENU, PLAYING, GAME_OVER };
gameState gameStateNow = MAIN_MENU;

const int MAX_LIVES = 3;

int score = 0;
int lives = MAX_LIVES;

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

#pragma region Adding Sounds
	SoundBuffer bufferCarCrash;
	SoundBuffer bufferTrap;
	SoundBuffer bufferGameOver;
	

	if (!bufferCarCrash.loadFromFile(PATH_TO_CONTENT_AUDIO"CarCrashSound.wav"))
	{
		std::cout << "Error loading sound CarCrashSound.wav" << std::endl;
		return -1;
	}
	if (!bufferTrap.loadFromFile(PATH_TO_CONTENT_AUDIO"TrapSound.wav"))
	{
		std::cout << "Error loading sound TrapSound.wav" << std::endl;
		return -1;
	}
	if (!bufferGameOver.loadFromFile(PATH_TO_CONTENT_AUDIO"GameOverSound.wav"))
	{
		std::cout << "Error loading sound GameOverSound.wav" << std::endl;
		return -1;
	}

	Sound soundCarCrash(bufferCarCrash);
	Sound soundTrap(bufferTrap);
	Sound soundGameOver(bufferGameOver);


#pragma endregion AddingSounds

#pragma region Back Music
	Music BackMusic;
	std::string musicFile = setRandomMusic();
	if (!BackMusic.openFromFile(PATH_TO_CONTENT_AUDIO + musicFile))
	{
		std::cout << "Error loading background music" << std::endl;
		return -1;
	}
#pragma endregion Back Music


#pragma region Adding Play Button
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
#pragma endregion Adding Play Button

	

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
	
#pragma region Trap Creation
	Trap trap(BACKGROUND_MOVE_SPEED, PATH_TO_CONTENT_IMG"TrapTexture.png", win);

#pragma endregion Trap Creation
	
#pragma region Game Over Screen Creation
	Texture &t = TextureHolder::GetTexture(PATH_TO_CONTENT_IMG"GameOverScreenTexture.png");
	Sprite rectGameOver;

	rectGameOver.setTexture(t);
	rectGameOver.setPosition(Vector2f(0.0f, 0.0f));
#pragma endregion Game Over Screen Creation


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

		else if (gameStateNow == PLAYING)
		{
			if (BackMusic.getStatus() == Music::Stopped)
			{
				BackMusic.play();
				//BackMusic.setPlayingOffset(seconds(8.0f));
			}
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
					soundCarCrash.play();
					biker.setDead();
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

#pragma region Controlling Trap
			trap.update(deltaTime);
			if (player.getCollisionRect().intersects(trap.getRect()) && !intersectsTrap)
			{
				lives--;
				intersectsTrap = true;

				std::cout << std::endl << "OHHHH NOOOOO YOU COLLIDED THIS GIRLLL((((" << std::endl << std::endl;
				soundTrap.play();
			}
			if (trap.getPosition().y < 0 && intersectsTrap)
			{
				intersectsTrap = false;
			}	
#pragma endregion Controlling Trap

			scoreText.setString((ss).str() + std::to_string(score));

			if (lives < 1)
			{
				gameStateNow = GAME_OVER;
				BackMusic.stop();
				soundGameOver.play();
			}
		}

		else if (gameStateNow == GAME_OVER)
		{
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				gameStateNow = PLAYING;
				lives = MAX_LIVES;
				score = 0;
			}
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
			win.draw(trap.getSprite());
			win.draw(biker.getSprite());
			win.draw(player.getSprite()); 
			win.draw(scoreText);
			for (int i = 0; i < lives; i++)
			{
				win.draw(vectorHearts.at(i));
			}
		}
		else if (gameStateNow == GAME_OVER)
		{
			win.draw(rectGameOver);
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

std::string setRandomMusic()
{
	srand(time(nullptr));
	int randN = rand() % 5;
	
	switch (randN)
	{
	case 0:
		return "Kishlachok_Dvinulsya.mp3";
		break;
	case 1:
		return "Kishlachok_Muzika.mp3";
		break;
	case 2:
		return "Kishlachok_PacanskiyEmoRap.mp3";
		break;
	case 3:
		return "Kishlachok_Rostov.mp3";
		break;
	case 4:
		return "Kishlachok_VseOChemMechtal.mp3";
		break;
	default:
		break;
	}
}