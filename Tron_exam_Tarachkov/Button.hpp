#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>

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
		Button(int x, int y, ButtonType buttonType)
		{
			m_x = x;
			m_y = y;
			m_buttonType = buttonType;
		}

		bool Setup()
		{
			switch (m_buttonType)
			{//-----------------ЗАГРУЗКА ТЕКСТУР ДЛЯ СИСТЕМНЫХ КНОПОК-----------------------------
			case ButtonType::NEWGAME:
				if (!m_texture1.loadFromFile("..\\assets\\Newgame.png"))
					return false;
				break;
			case ButtonType::SETTINGS:
				if (!m_texture1.loadFromFile("..\\assets\\Settings.png"))
					return false;
				break;
			case ButtonType::EXIT:
				if (!m_texture1.loadFromFile("..\\assets\\Exit.png"))
					return false;
				break;
			case ButtonType::BACKTOMENU:
				if (!m_texture1.loadFromFile("..\\assets\\Backtomenu.png"))
					return false;
				break;
			case ButtonType::CHOOSECOLORP1:
				if (!m_texture1.loadFromFile("..\\assets\\ChooseColP1.png"))
					return false;
				if (!m_texture2.loadFromFile("..\\assets\\ChooseColP1_2.png"))
					return false;
				break;
			case ButtonType::CHOOSECOLORP2:
				if (!m_texture1.loadFromFile("..\\assets\\ChooseColP2.png"))
					return false;
				if (!m_texture2.loadFromFile("..\\assets\\ChooseColP2_2.png"))
					return false;
				break;
				//---------------------ЗАГРУЗКА ТЕКСТУР ДЛЯ КНОПОК ЦВЕТА----------------------------------
			case ButtonType::C_RED:
				if (!m_texture1.loadFromFile("..\\assets\\Red.png"))
					return false;
				break;
			case ButtonType::C_BLUE:
				if (!m_texture1.loadFromFile("..\\assets\\Cyan.png"))
					return false;
				break;
			case ButtonType::C_GREEN:
				if (!m_texture1.loadFromFile("..\\assets\\Green.png"))
					return false;
				break;
			case ButtonType::C_YELLOW:
				if (!m_texture1.loadFromFile("..\\assets\\Yellow.png"))
					return false;
				break;
			case ButtonType::C_ORANGE:
				if (!m_texture1.loadFromFile("..\\assets\\Orange.png"))
					return false;
				break;
			case ButtonType::C_WHITE:
				if (!m_texture1.loadFromFile("..\\assets\\White.png"))
					return false;
				break;
			case ButtonType::C_MAGENTA:
				if (!m_texture1.loadFromFile("..\\assets\\Magenta.png"))
					return false;
				break;
			case ButtonType::C_PURPLE:
				if (!m_texture1.loadFromFile("..\\assets\\Purple.png"))
					return false;
				break;
			}

			m_spriteButton.setTexture(m_texture1);
			m_spriteButton.setPosition(m_x, m_y);
			m_width = m_spriteButton.getGlobalBounds().width;
			m_height = m_spriteButton.getGlobalBounds().height;
			return true;
		}

		sf::Sprite Get()
		{
			return m_spriteButton;
		}
		int X() { return m_x; }
		int Y() { return m_y; }

		bool isPressed(sf::Vector2i mousePos) //функция нажатия на кнопки
		{
			int x1 = m_x;
			int y1 = m_y;
			int x2 = m_x + m_width;
			int y2 = m_y + m_height;
			int x = mousePos.x;
			int y = mousePos.y;

			if (x1 <= x && x <= x2 && y1 <= y && y <= y2)
				return true;
			return false;
		}

		ButtonType Type() { return m_buttonType; }
		bool GetActivity() { return m_active; } //функция, определяющая активна ли кнопка (только для кнопок "Выбор цвета ...")
		void Activate() //функция для активации кнопки (только для кнопок "Выбор цвета ...")
		{
			if (m_buttonType == ButtonType::CHOOSECOLORP1 || m_buttonType == ButtonType::CHOOSECOLORP2)
			{
				m_active = 1;
				m_spriteButton.setTexture(m_texture2);
			}
		}
		void Deactivate() //функция для активации кнопки (только для кнопок "Выбор цвета ...")
		{
			if (m_buttonType == ButtonType::CHOOSECOLORP1 || m_buttonType == ButtonType::CHOOSECOLORP2)
			{
				m_active = 0;
				m_spriteButton.setTexture(m_texture1);
			}
		}
	private:
		int m_x, m_y;
		int m_width, m_height;
		bool m_active = 0;
		sf::Sprite m_spriteButton;
		sf::Texture m_texture1, m_texture2;
		ButtonType m_buttonType;

	};


}
