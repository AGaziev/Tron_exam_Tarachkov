#include "Game.hpp"

namespace Tron
{

	Game::Game(std::shared_ptr<sf::RenderWindow> window)
	{
		m_window = window;
		m_width = m_window->getSize().x;
		m_height = m_window->getSize().y;
	}

	#pragma region SETUP
	void Game::SetColors(sf::Color colorP1, sf::Color colorP2, sf::Texture P1, sf::Texture P2)
	{
		m_colorP1 = colorP1;
		m_colorP2 = colorP2;
		m_TexturePlayer1 = P1;
		m_TexturePlayer2 = P2;

		m_Player1.setTexture(m_TexturePlayer1);
		m_Player2.setTexture(m_TexturePlayer2);

		m_Player1.setColor(m_colorP1);
		m_Player2.setColor(m_colorP2);

		m_Player1.setPosition(0, 0);
		m_Player2.setPosition(m_window->getSize().x - m_Player2.getGlobalBounds().width, 0);
	}

	bool Game::SetMusic()
	{
		if (!g_music.openFromFile("..\\music\\Hotline.ogg"))
			return false;

		if (!buffer.loadFromFile("..\\music\\crash7.wav"))
			return false;

		m_crashSound.setBuffer(buffer);

		return true;
	}

	bool Game::SetBackground()
	{
		if (!m_textureBack.loadFromFile("..\\assets\\Background.png"))
			return false;
		if (!m_textureHUD.loadFromFile("..\\assets\\HUD.png"))
			return false;
		m_HUD.setTexture(m_textureHUD);
		m_spriteBackground.setTexture(m_textureBack);
		m_map.create(m_width, m_height);
		m_map.setSmooth(true);
		m_back.setPosition(0, 100);
		m_back.setTexture(m_map.getTexture());
		m_map.clear(); m_map.draw(m_spriteBackground);

		return true;
	}

	bool Game::SetPlayers()
	{
		m_P1.Setinfo(m_colorP1, 80, 80, 1);
		m_P2.Setinfo(m_colorP2, 80, 80, 2);
		//std::cout << m_P1.X() << "-p1-" << m_P1.Y() << std::endl;
		//std::cout << m_P2.X() << "-p2-" << m_P2.Y() << std::endl;			
		return true;
	}

	bool Game::SetInfo()
	{
		if (!font.loadFromFile("..\\assets\\Adumu.ttf"))
			return false;

		m_scoreTextP1.setFont(font);
		m_scoreTextP2.setFont(font);
		m_PrSpace.setFont(font);

		m_scoreTextP1.setString("Player 1 \nScore: " + std::to_string(m_scoreP1));
		m_scoreTextP2.setString("Player 2 \nScore: " + std::to_string(m_scoreP2));
		m_PrSpace.setString("Press Space to start game");

		m_scoreTextP1.setCharacterSize(44);
		m_scoreTextP2.setCharacterSize(44);
		m_PrSpace.setCharacterSize(44);


		m_scoreTextP1.setFillColor(m_colorP1);
		m_scoreTextP2.setFillColor(m_colorP2);
		sf::Color tmpclr(135, 135, 135);
		m_PrSpace.setFillColor(tmpclr);

		m_scoreTextP1.setPosition(120, -5);
		m_scoreTextP2.setPosition(m_width - 210, -5);
		m_PrSpace.setPosition(m_width / 2 - m_PrSpace.getGlobalBounds().width / 2, 40);

		if (!m_textureCrash.loadFromFile("..\\assets\\Crash.png"))
			return false;
		m_Crash.setTexture(m_textureCrash);
		m_Crash.setOrigin(10, 10);

		return true;
	}

	bool Game::Setup()
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
		g_music.play();
		return true;
	}
	#pragma endregion

	void Game::LifeCycle()
	{
		int dead = 0, i = 0, j = 0;
		sf::RectangleShape segment(sf::Vector2f(10, 10));
		bool Game = true;
		bool Round = false;
		segment.setPosition(m_P1.X() * 10, m_P1.Y() * 10); segment.setFillColor(m_P1.Color());    m_map.draw(segment);
		segment.setPosition(m_P2.X() * 10, m_P2.Y() * 10); segment.setFillColor(m_P2.Color());    m_map.draw(segment);
		m_map.display();
		while (m_window->isOpen())
		{
			sf::Event event;
			while (m_window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					m_window->close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))//¬ыход из игры с обнулением счета
			{
				g_music.stop();
				m_scoreP1 = 0; m_scoreP2 = 0;
				Restart();
				break;
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
						//¬ыполнитс€ один раз после столкновени€
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
						//¬ыполнитс€ один раз после столкновени€
						m_crashSound.play();
						m_scoreP1++;
						Round = false;
						m_PrSpace.setString("Press Space to restart round");
						if (m_scoreP1 == 3) {
							Game = false;
							m_PrSpace.setString("Press Space to return to menu");
						}
					}
					if (m_P1.X() == m_P2.X() && m_P1.Y() == m_P2.Y())
					{
						m_crashSound.play();
						segment.setPosition(m_P1.X() * 10, m_P1.Y() * 10); segment.setFillColor(m_P1.Color());    m_map.draw(segment);
						segment.setPosition(m_P2.X() * 10, m_P2.Y() * 10); segment.setFillColor(m_P2.Color());    m_map.draw(segment);
						dead = 3;
						m_map.display();
						Round = false;
						m_PrSpace.setString("Press Space to restart round");
					}
				}
				else {//≈сли закончилс€ раунд
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					{
						dead = 0;
						Round = true;
						Restart();
					}

				}
			}
			else {//≈сли есть победитель
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					g_music.stop();
					break;
				}
			}
			m_PrSpace.setPosition(m_width / 2 - m_PrSpace.getGlobalBounds().width / 2, 40);
			m_scoreTextP1.setString("Player 1 \nScore:" + std::to_string(m_scoreP1));
			m_scoreTextP2.setString("Player 2 \nScore:" + std::to_string(m_scoreP2));
			m_window->clear();

			m_window->draw(m_HUD);
			m_window->draw(m_scoreTextP1);
			m_window->draw(m_scoreTextP2);
			if (!Round || !Game)
				m_window->draw(m_PrSpace);
			m_window->draw(m_back);
			if (dead == 1)
			{
				m_Crash.setColor(m_colorP1);
				m_Crash.setPosition(m_P1.X() * 10, m_P1.Y() * 10 + 100);
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
				m_Crash.setPosition(m_P2.X() * 10, m_P2.Y() * 10 + 100);
				m_Crash.setTextureRect(sf::IntRect(30 * i, 0, 30, 30));
				m_window->draw(m_Crash);
				i++;
				if (i == 4) {
					dead = 0;
					i = 0;
				}
			}
			if (dead == 3)
			{
				m_Crash.setColor(m_colorP1);
				m_Crash.setPosition(m_P1.X() * 10, m_P1.Y() * 10 + 100);
				m_Crash.setTextureRect(sf::IntRect(30 * i, 0, 30, 30));
				m_window->draw(m_Crash);
				i++;
				if (i == 4) {
					dead = 0;
					i = 0;
				}
				m_Crash.setColor(m_colorP2);
				m_Crash.setPosition((m_P2.X()-m_P2.dX()) * 10, (m_P2.Y()-m_P2.dY()) * 10 + 100);
				m_Crash.setTextureRect(sf::IntRect(30 * j, 0, 30, 30));
				m_window->draw(m_Crash);
				j++;
				if (j == 4) {
					dead = 0;
					j = 0;
				}
			}
			m_window->draw(m_Player1);
			m_window->draw(m_Player2);
			m_window->display();
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
	}

	void Game::Restart() {
		memset(map, 0, 6400);
		m_map.clear(); m_map.draw(m_spriteBackground);
		m_P1.Reset();
		m_P2.Reset();
	}


}