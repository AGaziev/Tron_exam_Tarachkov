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
		}

		bool SetBackground()
		{
			sf::Texture t;
			if (!t.loadFromFile("..\\assets\\Background.png"))
				return false;
			sf::Sprite s;
			m_map.create(m_width, m_height);
			m_map.setSmooth(true);
			m_back.setTexture(m_map.getTexture());
			m_map.clear(); m_map.draw(s);
			return true;
		}

		bool SetPlayers()
		{
			m_P1.Setinfo(m_colorP1, 80, 80, 1);
			m_P1.Setinfo(m_colorP1, 80, 80, 1);
			
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
		}

		bool Settup()
		{
			if (!SetMusic())
				return false;
			if (!SetBackground())
				return false;
			if (!SetInfo())
				return false;
			return true;
		}
		#pragma endregion

		void LifeCycle()
		{
		}


	private:
		std::shared_ptr<sf::RenderWindow> m_window;
		int m_width, m_height;
		sf::Color m_colorP1, m_colorP2;
		sf::Sprite m_back;
		sf::RenderTexture m_map;
		bool map[80][80] = { 0 };

		Player m_P1, m_P2;
	};

}