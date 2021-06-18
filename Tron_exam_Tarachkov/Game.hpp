#pragma once
#include"Player.hpp"
#include <SFML/Audio.hpp>
#include <iostream>  // убрать потом

namespace Tron
{

	class Game
	{
	public:
		Game(std::shared_ptr<sf::RenderWindow> window)
		{
			m_window = window;
			m_width = m_window->getSize().x;
			m_height = m_window->getSize().y;
			m_colorP1 = sf::Color::Green;
			m_colorP2 = sf::Color::Red;			
		}

		//TO DO
		#pragma region SETUP
		void SetColors(sf::Color colorP1, sf::Color colorP2)
		{
			m_colorP1 = colorP1;
			m_colorP2 = colorP2;
		}
		
		bool SetMusic()
		{
			if (!g_music.openFromFile("..\\music\\Hotline.ogg"))
				return false;
			
			if (!buffer.loadFromFile("..\\music\\crash7.wav"))
			{
				std::cerr << "Fail load crash";
				return false;
			}				
			m_crashSound.setBuffer(buffer);			

			return true;
		}

		bool SetBackground()
		{
			if (!m_textureBack.loadFromFile("..\\assets\\Background.png"))
				return false;
			m_spriteBackground.setTexture(m_textureBack);
			m_map.create(m_width, m_height);
			m_map.setSmooth(true);
			m_back.setPosition(0, 100);
			m_back.setTexture(m_map.getTexture());
			m_map.clear(); m_map.draw(m_spriteBackground);
			return true;
		}

		bool SetPlayers()
		{
			m_P1.Setinfo(m_colorP1, 80, 80, 1);
			m_P2.Setinfo(m_colorP2, 80, 80, 2);
			std::cout << m_P1.X() << "-p1-" << m_P1.Y() << std::endl;
			std::cout << m_P2.X() << "-p2-" << m_P2.Y() << std::endl;			
			return true;
		}

		bool SetInfo() // настройка счета или времени игры (загрузка шрифтов и тому подобное)
		{
			if (!font.loadFromFile("..\\assets\\Adumu.ttf"))
				return false;					
						
			m_scoreTextP1.setFont(font);
			m_scoreTextP2.setFont(font);
			m_PrSpace.setFont(font);
			
			m_scoreTextP1.setString(std::to_string(m_scoreP1));
			m_scoreTextP2.setString(std::to_string(m_scoreP2));
			m_PrSpace.setString("Press Space to start game");

			m_scoreTextP1.setCharacterSize(36); 
			m_scoreTextP2.setCharacterSize(36);
			m_PrSpace.setCharacterSize(24);

			
			m_scoreTextP1.setFillColor(sf::Color::Red);
			m_scoreTextP2.setFillColor(sf::Color::Red);
			sf::Color tmpclr(135, 135, 135);
			m_PrSpace.setFillColor(tmpclr);

			m_scoreTextP1.setPosition(100, 40);
			m_scoreTextP2.setPosition(700-36, 40);
			m_PrSpace.setPosition(m_width / 2 - m_PrSpace.getGlobalBounds().width/2, 40);

			if (!m_textureCrash.loadFromFile("..\\assets\\Crash.png"))
				return false;
			m_Crash.setTexture(m_textureCrash);
			m_Crash.setOrigin(10, 10);

			return true;			
		}

		bool Setup()
		{
			if (!SetMusic())
				return false;
			if (!SetBackground())
				return false;
			if (!SetInfo())
				return false;
			SetPlayers();
			m_scoreP1 = 0; m_scoreP2 = 0;			
			Restart();
			turnOnOff(true);
			return true;
		}
		#pragma endregion

		void LifeCycle()
		{
			int dead = 0,i=0;
			sf::RectangleShape segment(sf::Vector2f(10, 10));
			bool Game = true;
			bool Round = false;
			segment.setPosition(m_P1.X() * 10, m_P1.Y() * 10); segment.setFillColor(m_P1.Color());    m_map.draw(segment);
			segment.setPosition(m_P2.X() * 10, m_P2.Y() * 10); segment.setFillColor(m_P2.Color());    m_map.draw(segment);
			m_map.display();
			while (m_window->isOpen())
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))//Выход из игры с обнулением счета
				{
					turnOnOff(false);
					m_scoreP1 = 0; m_scoreP2 = 0;
					Restart();
					break;
				}
				sf::Event event;
				while (m_window->pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						m_window->close();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))		m_P1.Left();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))		m_P1.Right();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))		m_P1.Up();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))		m_P1.Down();

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))		m_P2.Left();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	m_P2.Right();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))		m_P2.Up();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))		m_P2.Down();
				
				if (Game) {
					if (Round) {
						segment.setPosition(m_P1.X() * 10, m_P1.Y() * 10); segment.setFillColor(m_P1.Color());    m_map.draw(segment);
						segment.setPosition(m_P2.X() * 10, m_P2.Y() * 10); segment.setFillColor(m_P2.Color());    m_map.draw(segment);

						map[m_P1.X()][m_P1.Y()] = true;
						map[m_P2.X()][m_P2.Y()] = true;
						if (!m_P1.move(map))//проверка на столкновение первого игрока
						{
							dead = 1;
							//Выполнится один раз после столкновения
							m_crashSound.play();
							m_scoreP2++;
							Round = false;
							m_PrSpace.setString("Press Space to restart round");
							if (m_scoreP2 == 3) { 
								Game = false; 
								m_PrSpace.setString("Press Space to return to the main menu"); 
							}
						}
						if (!m_P2.move(map)) //проверка на столкновение второго игрока
						{
							dead = 2;
							//Выполнится один раз после столкновения
							m_crashSound.play();
							m_scoreP1++;
							Round = false;
							m_PrSpace.setString("Press Space to restart round");
							if (m_scoreP1 == 3) { 
								Game = false; 
								m_PrSpace.setString("Press Space to return to the main menu"); 
							}
						}
						if (m_P1.X() == m_P2.X() && m_P1.Y() == m_P2.Y())
						{
							m_crashSound.play();
							segment.setPosition(m_P1.X() * 10, m_P1.Y() * 10); segment.setFillColor(m_P1.Color());    m_map.draw(segment);
							segment.setPosition(m_P2.X() * 10, m_P2.Y() * 10); segment.setFillColor(m_P2.Color());    m_map.draw(segment);
							m_map.display();
							Round = false;
							m_PrSpace.setString("Press Space to restart round");
						}
					}
					else {//Если закончился раунд
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
						{
							dead = 0;
							Round = true;
							Restart();
						}

					}
				}
				else {//Если есть победитель
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					{
						turnOnOff(false);
						break;
					}
				}
				m_PrSpace.setPosition(m_width / 2 - m_PrSpace.getGlobalBounds().width / 2, 40);
				m_scoreTextP1.setString(std::to_string(m_scoreP1));
				m_scoreTextP2.setString(std::to_string(m_scoreP2));
				m_window->clear();
				m_window->draw(m_scoreTextP1);
				m_window->draw(m_scoreTextP2);
				if (!Round || !Game)
					m_window->draw(m_PrSpace);
				m_window->draw(m_back);
				if (dead == 1)
				{
					m_Crash.setColor(m_colorP1);
					m_Crash.setPosition(m_P1.X() * 10, m_P1.Y() * 10+100);
					m_Crash.setTextureRect(sf::IntRect(30 * i, 0, 30, 30));
					m_window->draw(m_Crash);
					i++;
					if (i == 4) {
						dead = 0;
						i = 0;
					}
				}
				if (dead == 2)
				{
					m_Crash.setColor(m_colorP2);
					m_Crash.setPosition(m_P2.X() * 10, m_P2.Y() * 10+100);
					m_Crash.setTextureRect(sf::IntRect(30 * i, 0, 30, 30));
					m_window->draw(m_Crash);
					i++;
					if (i == 4) {
						dead = 0;
						i = 0;
					}
				}
				m_window->display();
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
			}
		}

		void Restart() {
			memset(map, 0, 6400);
			m_map.clear(); m_map.draw(m_spriteBackground);
			m_P1.Reset();
			m_P2.Reset();
		}

	private:
		
		std::shared_ptr<sf::RenderWindow> m_window;
		int m_width, m_height;
		sf::Texture m_textureBack;
		sf::Texture m_textureCrash;
		sf::Color m_colorP1, m_colorP2;
		sf::Sprite m_back;
		sf::Sprite m_spriteBackground;
		sf::Sprite m_Crash;
		sf::RenderTexture m_map;
		bool map[80][80] = { 0 };
		Player m_P1, m_P2;

		int m_scoreP1=0, m_scoreP2=0;
		sf::Font font;
		sf::Text m_scoreTextP1, m_scoreTextP2;
		sf::Text m_PrSpace;
		sf::Music g_music;
		sf::SoundBuffer buffer;
		sf::Sound m_crashSound;

		void turnOnOff(bool tmp)
		{
			if (tmp == true)
			{
				g_music.play();
				/*for (int i = 0; i < 100; i++) //ЗАТУХАНИЕ (наоборот, хз как назвать)
				{
					g_music.setVolume(i);
					std::this_thread::sleep_for(std::chrono::milliseconds(5));
				}*/
			}
			else
			{
				/*for (int i = 100; i > 0; i--) //ЗАТУХАНИЕ
				{
					g_music.setVolume(i);
					std::this_thread::sleep_for(std::chrono::milliseconds(5));
				}*/
				g_music.stop(); // или .pause() !!!!
			}
		}
				

	};

}