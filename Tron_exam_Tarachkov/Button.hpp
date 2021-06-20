#pragma once
#include<SFML/Graphics.hpp>

namespace Tron
{
	enum class ButtonType
	{
		NONE,
		NEWGAME,
		SETTINGS,
		C_RED, C_YELLOW, C_BLUE, C_GREEN, C_ORANGE, C_WHITE, C_MAGENTA, C_PURPLE,
		EXIT,
		BACKTOMENU,
		CHOOSECOLORP1,
		CHOOSECOLORP2
	};

	class Button
	{
	public:
		Button(int x, int y, ButtonType buttonType);

		bool Setup();

		#pragma region GETTERS
		sf::Sprite GetSprite();
		int X();
		int Y();
		ButtonType Type();
		#pragma endregion

		bool isPressed(sf::Vector2i mousePos); //функция нажатия на кнопки	

		bool GetActivity(); //функция, определяющая активна ли кнопка (только для кнопок "Выбор цвета ...")		
		void Activate();   //функция для активации кнопки (только для кнопок "Выбор цвета ...")		
		void Deactivate(); //функция для деактивации кнопки (только для кнопок "Выбор цвета ...")
		

	private:
		int m_x, m_y;
		int m_width, m_height;
		bool m_active = 0;
		
		sf::Texture m_texture1, m_texture2; // 1 тектура- основная, 2- для системных кнопок в настройках
		sf::Sprite m_spriteButton;		
		ButtonType m_buttonType;

	};


}
