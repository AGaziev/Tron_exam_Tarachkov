#include "Player.hpp"

namespace Tron
{
	
	Player::Player() {}

	void Player::Setinfo(sf::Color color, int w, int h, int p) 
	{
		m_num = p;
		m_clr = color;
		m_w = w; m_h = h;
		if (p == 1) // 1 игрок будет в середине левой половины экрана и двигается вправо
		{
			m_x = w / 4;
			m_y = h / 2;
			m_dx = 1;
			m_dy = 0;
		}
		else { // 2 игрок в правой середине и двигается влево
			m_x = 3 * w / 4;
			m_y = h / 2;
			m_dx = -1;
			m_dy = 0;
		}
	}

	#pragma region Изменение движения
	void Player::Left()
	{
		if (m_dy != 0)
		{
			m_dy = 0;
			m_dx = -1;
		}
	}
	void Player::Right()
	{
		if (m_dy != 0)
		{
			m_dy = 0;
			m_dx = 1;
		}
	}
	void Player::Up()
	{
		if (m_dx != 0)
		{
			m_dx = 0;
			m_dy = -1;
		}
	}
	void Player::Down()
	{
		if (m_dx != 0)
		{
			m_dx = 0;
			m_dy = 1;
		}
	}
	#pragma endregion Функции с изменением движения игрока

	#pragma region GETTERS
	int Player::X() { return m_x; }
	int Player::Y() { return m_y; }
	sf::Color Player::Color() { return m_clr; }
	#pragma endregion

	bool Player::move(bool map[80][80])
	{
		if (checkAlive(map)) //проверка на столкновение
		{
			m_x += m_dx;//изменение координат
			m_y += m_dy;
			return true;
		}
		return false;
	}

	void Player::Reset()
	{
		//std::cout << m_num;
		if (m_num == 1)
		{
			m_x = m_w / 4;
			m_y = m_h / 2;
			m_dx = 1;
			m_dy = 0;
		}
		if (m_num == 2)
		{
			m_x = 3 * m_w / 4;
			m_y = m_h / 2;
			m_dx = -1;
			m_dy = 0;
		}
	}

	//private
	bool Player::checkAlive(bool map[80][80])
	{
		if (m_x + m_dx > 79 || m_y + m_dy > 79 || m_y + m_dy < 0 || m_x + m_dx < 0)
			return false;
		return !map[m_x + m_dx][m_y + m_dy];
	}

}