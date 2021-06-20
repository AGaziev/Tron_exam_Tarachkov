#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Tron
{

	class Player
	{
	public:
		
		Player();

		void Setinfo(sf::Color color, int w, int h, int p); // Цвет игрока, размер поля, номер игрока

		#pragma region Изменение движения
		void Left();
		void Right();
		void Up();
		void Down();
		#pragma endregion Функции с изменением движения игрока

		#pragma region GETTERS
		int X();
		int Y();
		sf::Color Color();
		int dX();
		int dY();
		#pragma endregion

		bool move(bool map[80][80]);
		void Reset();

	private:
		sf::Color m_clr;	//Player's clr
		int m_num;			//Номер игрока
		int m_x, m_y;		//Players' coords
		int	m_dx, m_dy;		//Directional vectors
		int m_w, m_h;		//Screen sizes		
		
		bool checkAlive(bool map[80][80]);

	};

}