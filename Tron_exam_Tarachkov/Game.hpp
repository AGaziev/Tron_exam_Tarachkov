#pragma once
#include"Player.hpp"

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
		#pragma region SETTUP
		void SetColors(sf::Color colorP1, sf::Color colorP2)
		{
			m_colorP1 = colorP1;
			m_colorP2 = colorP2;
		}
		bool SetMusic()
		{
			return true;
		}

		bool SetBackground()
		{
			sf::Texture t;
			if (!t.loadFromFile("..\\assets\\Background.png"))
				return false;
			m_spriteBackground.setTexture(t);
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
			memset(map, 0, 6400);
			/*m_p1.setColor(m_colorP1);
			m_p2.setColor(m_colorP2);*/
			/*
			if (!p1.setTexture())
			return false;
			if (!p1.setTexture())
			return false;*/
			return true;
		}

		bool SetInfo() // настройка счета или времени игры (загрузка шрифтов и тому подобное)
		{
			if (!font.loadFromFile("..\\assets\\Adumu.ttf"))
				return false;					
						
			m_scoreTextP1.setFont(font);
			m_scoreTextP2.setFont(font);			
			
			m_scoreTextP1.setString(std::to_string(m_scoreP1));
			m_scoreTextP2.setString(std::to_string(m_scoreP2));

			// set the character size in pixels, not points!
			m_scoreTextP1.setCharacterSize(36); 
			m_scoreTextP2.setCharacterSize(36);
			
			m_scoreTextP1.setFillColor(sf::Color::Red);
			m_scoreTextP2.setFillColor(sf::Color::Red);
			
			//m_scoreTextP1.setStyle(sf::Text::Bold); //посмотрите как вам жирный шрифт, может лучше
			//m_scoreTextP2.setStyle(sf::Text::Bold);

			m_scoreTextP1.setPosition(100, 40);
			m_scoreTextP2.setPosition(700-36, 40);

			return true;
			
		}

		bool Settup()
		{
			if (!SetMusic())
				return false;
			if (!SetBackground())
				return false;
			if (!SetInfo())
				return false;
			SetPlayers();
			return true;
		}
		#pragma endregion

		void LifeCycle()
		{
			bool Game = true;
			int dead = 0;
			while (m_window->isOpen())
			{
				sf::Event event;
				while (m_window->pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						return;
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
					sf::RectangleShape segment(sf::Vector2f(10, 10));
					segment.setPosition(m_P1.X() * 10, m_P1.Y() * 10); segment.setFillColor(m_P1.Color());    m_map.draw(segment);
					segment.setPosition(m_P2.X() * 10, m_P2.Y() * 10); segment.setFillColor(m_P2.Color());    m_map.draw(segment);
					m_map.display();

					map[m_P1.X()][m_P1.Y()] = true;
					map[m_P2.X()][m_P2.Y()] = true;
					if (!m_P1.move(map))
					{
						m_scoreP2++;
						if (m_scoreP2 < 5)
							Settup();//ѕќћ≈Ќя“№!!!!!
						if (m_scoreP2==5)						
							Game = false;
						dead = 1;
					}
					if (!m_P2.move(map)) 
					{
						m_scoreP1++;
						if (m_scoreP1 < 5)
							Settup(); //ѕќћ≈Ќя“№!!!!!
						if(m_scoreP1==5)
							Game = false;
						dead = 2;
					}
				}else{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
						break;
				}
				
				m_scoreTextP1.setString(std::to_string(m_scoreP1));
				m_scoreTextP2.setString(std::to_string(m_scoreP2));
				m_window->clear();
				m_window->draw(m_scoreTextP1);
				m_window->draw(m_scoreTextP2);
				m_window->draw(m_back);
				m_window->display();
				
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}

	private:
		
		std::shared_ptr<sf::RenderWindow> m_window;
		int m_width, m_height;
		sf::Color m_colorP1, m_colorP2;
		sf::Sprite m_back;
		sf::Sprite m_spriteBackground;
		sf::RenderTexture m_map;
		bool map[80][80] = { 0 };
		Player m_P1, m_P2;

		int m_scoreP1=0, m_scoreP2=0;
		sf::Font font;
		sf::Text m_scoreTextP1, m_scoreTextP2;

	};

}