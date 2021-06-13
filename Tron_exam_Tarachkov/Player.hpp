#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Tron
{

	class Player
	{
	public:
		
		Player() {}

		void Setinfo(sf::Color color, int w, int h, int p) // ÷вет игрока, размер пол€, номер игрока
		{
			m_lives = 3;
			m_clr = color;
			m_w = w; m_h = h;
			if (p == 1) // 1 игрок будет в середине левой половины экрана и двигаетс€ вправо
			{
				m_x = w / 4;
				m_y = h / 2;
				m_dx = 1;
				m_dy = 0;
			}
			else { // 2 игрок в правой середине и двигаетс€ влево
				m_x = 3 * w / 4;
				m_y = h / 2;
				m_dx = -1;
				m_dy = 0;
			}
		}
		
		#pragma region »зменение движени€
		void Left() {
			if (m_dy != 0)
			{
				m_dy = 0;
				m_dx = -1;
			}
		}
		void Right() {
			if (m_dy != 0)
			{
				m_dy = 0;
				m_dx = 1;
			}
		}
		void Up() {
			if (m_dx != 0)
			{
				m_dx = 0;
				m_dy = -1;
			}
		}
		void Down() {
			if (m_dx != 0)
			{
				m_dx = 0;
				m_dy = 1;
			}
		}
		#pragma endregion ‘ункции с изменением движени€ игрока

		#pragma region GETTERS
		int X() { return m_x; }
		int Y() { return m_y; }
		sf::Color Color() { return m_clr; }
		int lives() { return m_lives; } 
		#pragma endregion

		bool move(bool map[80][80]) {
			if (checkAlive(map)) {//проверка на столкновение
				m_x += m_dx;//изменение координат
				m_y += m_dy;
				return true;
			}
			return false;
		}

		void setColor(sf::Color clr){ m_clr = clr; }
		void setLives(int m) { m_lives -= m; }

	private:
		sf::Color m_clr;	//Player's clr
		int m_x, m_y;		//Players' coords
		int	m_dx, m_dy;		//Directional vectors
		int m_w, m_h;	//Screen sizes
		int m_lives;
		bool checkAlive(bool map[80][80])
		{
			if (m_x + m_dx > 79 || m_y + m_dy > 79 || m_y + m_dy < 0 || m_x + m_dx < 0)
				return false;
			return !map[m_x+m_dx][m_y+m_dy];
		}
	};

}