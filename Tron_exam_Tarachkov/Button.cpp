#include "Button.hpp"

namespace Tron
{

	Button::Button(int x, int y, ButtonType buttonType)
	{
		m_x = x;
		m_y = y;
		m_buttonType = buttonType;
	}

	bool Button::Setup()
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

	#pragma region GETTERS
	sf::Sprite Button::GetSprite() { return m_spriteButton; }
	int Button::X() { return m_x; }
	int Button::Y() { return m_y; }
	ButtonType Button::Type() { return m_buttonType; }
	#pragma endregion

	bool Button::isPressed(sf::Vector2i mousePos) //функция нажатия на кнопки
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

	bool Button::GetActivity() { return m_active; } //функция, определяющая активна ли кнопка (только для кнопок "Выбор цвета ...")

	void Button::Activate() //функция для активации кнопки (только для кнопок "Выбор цвета ...")
	{
		if (m_buttonType == ButtonType::CHOOSECOLORP1 || m_buttonType == ButtonType::CHOOSECOLORP2)
		{
			m_active = 1;
			m_spriteButton.setTexture(m_texture2);
		}
	}
	void Button::Deactivate() //функция для активации кнопки (только для кнопок "Выбор цвета ...")
	{
		if (m_buttonType == ButtonType::CHOOSECOLORP1 || m_buttonType == ButtonType::CHOOSECOLORP2)
		{
			m_active = 0;
			m_spriteButton.setTexture(m_texture1);
		}
	}


}