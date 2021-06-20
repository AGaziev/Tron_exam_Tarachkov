#include "Menu.hpp"

namespace Tron
{

	Menu::Menu(std::shared_ptr<sf::RenderWindow> window) //создает векторы с пустыми(!) кнопками для меню и для настроек
	{
		int btwButMain = (window.get()->getSize().y / 2 - 3 * mainH) / 2; //дистанция между кнопками в главном меню (4-количество пустых пространств между кнопками)
		int btwClrSetW = (window.get()->getSize().x - 4 * clrSize) / 5;//дистанция по ширине между цветами в настройках (5-количество пустых пространств между кнопками)
		int btwButSet = (window.get()->getSize().y - 4 * mainH) / 5;//дистанция по высоте между кнопками в настройках (5-количество пустых пространств между кнопками)
		m_window = window;
		//-----------------------------КНОПКИ МЕНЮ------------------------------------
		std::shared_ptr<Button> newGameBut = std::make_shared<Button>((window.get()->getSize().x - mainW) / 2, window.get()->getSize().y / 4 + btwButMain * 1 + mainH * 0, ButtonType::NEWGAME);
		m_buttonsM.push_back(newGameBut);
		std::shared_ptr<Button> settingsBut = std::make_shared<Button>((window.get()->getSize().x - mainW) / 2, window.get()->getSize().y / 4 + btwButMain * 2 + mainH * 1, ButtonType::SETTINGS);
		m_buttonsM.push_back(settingsBut);
		std::shared_ptr<Button> exitBut = std::make_shared<Button>((window.get()->getSize().x - mainW) / 2, window.get()->getSize().y / 4 + btwButMain * 3 + mainH * 2, ButtonType::EXIT);
		m_buttonsM.push_back(exitBut);
		//------------------------КНОПКИ ЦВЕТОВ В НАСТРОЙКАХ----------------------------------------
		std::shared_ptr<Button> redBut = std::make_shared<Button>(btwClrSetW * 1 + clrSize * 0, 3 * btwButSet + 2 * mainH, ButtonType::C_RED);
		m_buttonsS.push_back(redBut);
		std::shared_ptr<Button> blueBut = std::make_shared<Button>(btwClrSetW * 2 + clrSize * 1, 3 * btwButSet + 2 * mainH, ButtonType::C_BLUE);
		m_buttonsS.push_back(blueBut);
		std::shared_ptr<Button> greenBut = std::make_shared<Button>(btwClrSetW * 3 + clrSize * 2, 3 * btwButSet + 2 * mainH, ButtonType::C_GREEN);
		m_buttonsS.push_back(greenBut);
		std::shared_ptr<Button> YellowBut = std::make_shared<Button>(btwClrSetW * 4 + clrSize * 3, 3 * btwButSet + 2 * mainH, ButtonType::C_YELLOW);
		m_buttonsS.push_back(YellowBut);
		std::shared_ptr<Button> OrangeBut = std::make_shared<Button>(btwClrSetW * 1 + clrSize * 0, 4 * btwButSet + 3 * mainH, ButtonType::C_ORANGE);
		m_buttonsS.push_back(OrangeBut);
		std::shared_ptr<Button> WhiteBut = std::make_shared<Button>(btwClrSetW * 2 + clrSize * 1, 4 * btwButSet + 3 * mainH, ButtonType::C_WHITE);
		m_buttonsS.push_back(WhiteBut);
		std::shared_ptr<Button> MagentaBut = std::make_shared<Button>(btwClrSetW * 3 + clrSize * 2, 4 * btwButSet + 3 * mainH, ButtonType::C_MAGENTA);
		m_buttonsS.push_back(MagentaBut);
		std::shared_ptr<Button> PurpleBut = std::make_shared<Button>(btwClrSetW * 4 + clrSize * 3, 4 * btwButSet + 3 * mainH, ButtonType::C_PURPLE);
		m_buttonsS.push_back(PurpleBut);
		//--------------------------СИСТЕМНЫЕ КНОПКИ В НАСТРОЙКАХ--------------------------------
		std::shared_ptr<Button> BackBut = std::make_shared<Button>((window.get()->getSize().x - mainW) / 2, btwButSet * 1 + 0 * mainH, ButtonType::BACKTOMENU);
		m_buttonsS.push_back(BackBut);
		std::shared_ptr<Button> Choose1But = std::make_shared<Button>((window.get()->getSize().x - 2 * mainW) / 3, btwButSet * 2 + 1 * mainH, ButtonType::CHOOSECOLORP1);
		m_buttonsS.push_back(Choose1But);
		std::shared_ptr<Button> Choose2But = std::make_shared<Button>((window.get()->getSize().x * 2 - mainW) / 3, btwButSet * 2 + 1 * mainH, ButtonType::CHOOSECOLORP2);
		m_buttonsS.push_back(Choose2But);
	}

	#pragma region Setup
	bool Menu::SetTextures()
	{
		for (const auto& button : m_buttonsM)
			if (!button->Setup())
				return false;
		for (const auto& button : m_buttonsS)
			if (!button->Setup())
				return false;

		if (!m_textureP1.loadFromFile("..\\assets\\ChoosedP1.png"))
			return false;
		if (!m_textureP2.loadFromFile("..\\assets\\ChoosedP2.png"))
			return false;
		if (!m_LeftT.loadFromFile("..\\assets\\LeftPerson.png"))
			return false;
		if (!m_RightT.loadFromFile("..\\assets\\RightPerson.png"))
			return false;
		if (!m_LogoT.loadFromFile("..\\assets\\Logo.png"))
			return false;
		if (!m_BackgroundT.loadFromFile("..\\assets\\BackgroundMenu.png"))
			return false;
		if (!m_iconP1T.loadFromFile("..\\assets\\FirstPlayer.png"))
			return false;
		if (!m_iconP2T.loadFromFile("..\\assets\\SecondPlayer.png"))
			return false;
		if (!m_FrameT.loadFromFile("..\\assets\\Frame.png"))
			return false;

		m_Background.setTexture(m_BackgroundT);
		m_Frame.setTexture(m_FrameT);
		m_Frame.setScale(2, 2);
		m_LeftMainPerson.setTexture(m_LeftT);
		m_RightMainPerson.setTexture(m_RightT);
		m_Logo.setTexture(m_LogoT);
		//Настройка иконки первого персонажа
		m_iconP1.setTexture(m_iconP1T);
		m_iconP1.setPosition(0, 0);
		m_iconP1.setScale(2, 2);
		m_iconP1.setColor(sf::Color::White);
		//Настройка иконки второго персонажа
		m_iconP2.setTexture(m_iconP2T);
		m_iconP2.setOrigin(m_iconP2.getGlobalBounds().width, 0);
		m_iconP2.setPosition(m_window->getSize().x, 0);
		m_iconP2.setScale(2, 2);
		m_iconP2.setColor(sf::Color::Yellow);


		m_spriteP1.setTexture(m_textureP1);
		m_spriteP2.setTexture(m_textureP2);
		m_spriteP1.setPosition(m_buttonsS[5]->X(), m_buttonsS[5]->Y());
		m_spriteP2.setPosition(m_buttonsS[3]->X(), m_buttonsS[3]->Y());

		return true;
	}

	bool Menu::SetMusic()
	{
		if (!m_music.openFromFile("..\\music\\TRON Legacy.ogg"))
			return false;
		m_music.setVolume(30);
		return true;
	}

	bool Menu::Setup() //настройка кнопок (загружаем текстуры)
	{
		if (!SetTextures())
			return false;
		if (!SetMusic())
			return false;
		return true;
	}
	#pragma endregion
	

	#pragma region Main Menu
	void Menu::DisplayMenu() //функция вывода меню
	{
		m_window->clear();
		m_window->draw(m_Background);
		m_window->draw(m_LeftMainPerson);
		m_window->draw(m_RightMainPerson);
		m_window->draw(m_Logo);
		for (const auto& button : m_buttonsM)
			m_window->draw(button->GetSprite());
		m_window->display();
	}
	
	ButtonType Menu::PressedButtonM() //проверка нажатия на кнопки из меню
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);

			for (const auto& button : m_buttonsM)
				if (button->isPressed(mousePos))
					return button->Type();
		}
		return ButtonType::NONE;
	}

	void Menu::Animation(int& i, bool Up)
	{

		sf::Color tmpcolor(0, 0, 0, 50);
		if (Up == true)
		{
			m_Logo.setColor(m_Logo.getColor() + tmpcolor);
			/*m_RightMainPerson.setColor(m_RightMainPerson.getColor() + tmpcolor);
			m_LeftMainPerson.setColor(m_LeftMainPerson.getColor() + tmpcolor);*/
		}
		else
		{
			m_Logo.setColor(m_Logo.getColor() - tmpcolor);
			/*m_RightMainPerson.setColor(m_RightMainPerson.getColor() - tmpcolor);
			m_LeftMainPerson.setColor(m_LeftMainPerson.getColor() - tmpcolor);*/
		}
		i++;

	}
	#pragma endregion	
	
	#pragma region Settings
	void Menu::DisplaySettings() //функция вывода настроек
	{
		m_window->clear();
		m_window->draw(m_Background);
		for (const auto& button : m_buttonsS)
			m_window->draw(button->GetSprite());
		m_Frame.setPosition(0, 0);
		m_window->draw(m_Frame);
		m_window->draw(m_iconP1);
		m_Frame.setPosition(m_window->getSize().x - m_iconP1.getGlobalBounds().width, 0);
		m_window->draw(m_Frame);
		m_window->draw(m_iconP2);
		m_window->draw(m_spriteP1);
		m_window->draw(m_spriteP2);
		m_window->display();
	}	

	ButtonType Menu::PressedButtonS() //провекра нажатия на кнопки из настроек
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);

			for (const auto& button : m_buttonsS)
				if (button->isPressed(mousePos))
					return button->Type();
		}
		return ButtonType::NONE;
	}

	sf::Texture Menu::getTexture(int tmp)
	{
		switch (tmp)
		{
		case 1:
			return m_iconP1T;
		case 2:
			return m_iconP2T;
		}
	}	

	void Menu::loopSettings(sf::Color& colorP1, sf::Color& colorP2) //функция для работы с окном настроек 
	{
		while (m_window->isOpen())
		{
			sf::Event event;
			while (m_window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					m_window->close();
			}

			ButtonType button = PressedButtonS(); //переменной button присваиваем тип нажатой кнопки

			switch (button) //согласно типу по разному отрабатываем для каждой из кнопок
			{
				//----------------------КНОПКИ ЦВЕТА----------------------------
			case ButtonType::C_RED:
				PressColorBut(colorP1, colorP2, 0);
				break;
			case ButtonType::C_BLUE:
				PressColorBut(colorP1, colorP2, 1);
				break;
			case ButtonType::C_GREEN:
				PressColorBut(colorP1, colorP2, 2);
				break;
			case ButtonType::C_YELLOW:
				PressColorBut(colorP1, colorP2, 3);
				break;
			case ButtonType::C_ORANGE:
				PressColorBut(colorP1, colorP2, 4);
				break;
			case ButtonType::C_WHITE:
				PressColorBut(colorP1, colorP2, 5);
				break;
			case ButtonType::C_MAGENTA:
				PressColorBut(colorP1, colorP2, 6);
				break;
			case ButtonType::C_PURPLE:
				PressColorBut(colorP1, colorP2, 7);
				break;
				//---------------------СИСТЕМНЫЕ КНОПКИ----------------------------
			case ButtonType::CHOOSECOLORP1:
				m_buttonsS[9]->Activate();
				m_buttonsS[10]->Deactivate();
				break;
			case ButtonType::CHOOSECOLORP2:
				m_buttonsS[9]->Deactivate();
				m_buttonsS[10]->Activate();
				break;
			case ButtonType::BACKTOMENU:
				return;
			}

			DisplaySettings();

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
	#pragma endregion

	void Menu::turnOnOff(bool tmp)
	{
		if (tmp == true)	m_music.play();
		else m_music.stop();
	}

	void Menu::PressColorBut(sf::Color& colorP1, sf::Color& colorP2, int numberBut)
	{
		sf::Color ColorNow;

		switch (numberBut)
		{
		case 0:
			ColorNow = sf::Color::Red;
			break;
		case 1:
			ColorNow = sf::Color::Cyan;
			break;
		case 2:
			ColorNow = sf::Color::Green;
			break;
		case 3:
			ColorNow = sf::Color::Yellow;
			break;
		case 4:
			ColorNow = sf::Color(255, 127, 39);//Orange
			break;
		case 5:
			ColorNow = sf::Color::White;
			break;
		case 6:
			ColorNow = sf::Color::Magenta;
			break;
		case 7:
			ColorNow = sf::Color(128, 0, 255); //Purple
			break;
		}

		if (m_buttonsS[9]->GetActivity() && colorP2 != ColorNow)
		{
			colorP1 = ColorNow;
			m_iconP1.setColor(colorP1);
			m_spriteP1.setPosition(m_buttonsS[numberBut]->X(), m_buttonsS[numberBut]->Y());
		}
		if (m_buttonsS[10]->GetActivity() && colorP1 != ColorNow)
		{
			colorP2 = ColorNow;
			m_iconP2.setColor(colorP2);
			m_spriteP2.setPosition(m_buttonsS[numberBut]->X(), m_buttonsS[numberBut]->Y());
		}
	}

}
