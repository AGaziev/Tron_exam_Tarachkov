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
		}

		bool SetInfo() // настройка счета или времени игры (загрузка шрифтов и тому подобное)
		{
		}

		bool SetPlayers()
		{
			Player p1(m_colorP1, m_width, m_height, 1);
			Player p2(m_colorP2, m_width, m_height, 2);
			/*
			if (!p1.setTexture())
				return false;
			if (!p1.setTexture())
				return false;*/
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
			if (!SetPlayers())
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
	};

}