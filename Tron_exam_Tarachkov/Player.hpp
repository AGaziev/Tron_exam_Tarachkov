#pragma once
#include <SFML/Graphics.hpp>

namespace Tron
{

	class Player
	{
	public:
		Player(int w, int h, int p) // ������ ����, ����� ������
		{
			m_w = w; m_h = h;
			if (p = 1) // 1 ����� ����� � �������� ����� �������� ������ � ��������� ������
			{
				m_x = w / 4;
				m_y = h / 2;
				dx = 1;
				dy = 0;
			}
			else { // 2 ����� � ������ �������� � ��������� �����
				m_x = 3 * w / 4;
				m_y = h / 2;
				dx = -1;
				dy = 0;
			}
		}
		#pragma region ��������� ��������
		void Left() {
			if (m_y != 0)
			{
				m_y = 0;
				m_x = -1;
			}
		}
		void Right() {
			if (m_y != 0)
			{
				m_y = 0;
				m_x = -1;
			}
		}
		void Up() {
			if (m_x != 0)
			{
				m_x = 0;
				m_y = -1;
			}
		}
		void Down() {
			if (m_x != 0)
			{
				m_x = 0;
				m_y = 1;
			}
		}
		#pragma endregion ������� � ���������� �������� ������

		#pragma region GETTERS
		int X() { return m_x; }
		int Y() { return m_y; }
		sf::Color Color() { return p_clr; }
		#pragma endregion

		bool move(bool* map[80][80]) {
			if (isAlive(map)) {//�������� �� ������������
				m_x += dx * speed;//��������� ���������
				m_y += dy * speed;
				return true;
			}
			else return false;
		}

		void setColor(sf::Color clr)
		{
			p_clr = clr;
		}

	private:
		sf::Color p_clr;	//Player's clr
		int m_x, m_y;		//Players' coords
		int	dx, dy;			//Directional vectors
		int m_w, m_h;		//Screen sizes
		int speed = 1;		//��� ���� � �����, ���� ����� ����������
		bool isAlive(bool* map[80][80])
		{
			if (m_x + dx > 79 || m_y + dy > 79 || m_y + dy < 0 || m_x + dx < 0)
				return false;
			return !map[m_x+dx][m_y+dy];
		}
	};

}