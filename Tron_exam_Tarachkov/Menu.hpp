#pragma once
#include "Button.hpp"
const int mainW = 300; //
const int mainH = 100; //Размеры основных кнопок
const int clrSize = 100; //Размеры цветов

namespace Tron
{
	class Menu
	{
	public:
		Menu(std::shared_ptr<sf::RenderWindow> window) //создает векторы с пустыми(!) кнопками для меню и для настроек
		{
			int btwButMain = (window.get()->getSize().y - 3 * mainH) / 4; //дистанция между кнопками в главном меню (4-количество пустых пространств между кнопками)
			int btwClrSetW = (window.get()->getSize().x - 4 * clrSize) / 5;//дистанция по ширине между цветами в настройках (5-количество пустых пространств между кнопками)
			int btwButSet = (window.get()->getSize().y - 4 * mainH) / 5;//дистанция по высоте между кнопками в настройках (5-количество пустых пространств между кнопками)
			m_window = window;
			//-----------------------------КНОПКИ МЕНЮ------------------------------------
			std::shared_ptr<Button> newGameBut = std::make_shared<Button>((window.get()->getSize().x - mainW) / 2, btwButMain * 1 + mainH * 0, ButtonType::NEWGAME);
			m_buttonsM.push_back(newGameBut);
			std::shared_ptr<Button> settingsBut = std::make_shared<Button>((window.get()->getSize().x - mainW) / 2, btwButMain * 2 + mainH * 1, ButtonType::SETTINGS);
			m_buttonsM.push_back(settingsBut);
			std::shared_ptr<Button> exitBut = std::make_shared<Button>((window.get()->getSize().x - mainW) / 2, btwButMain * 3 + mainH * 2, ButtonType::EXIT);
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
			std::shared_ptr<Button> Choose2But = std::make_shared<Button>((window.get()->getSize().x * 2 - mainW) / 3 , btwButSet * 2 + 1 * mainH, ButtonType::CHOOSECOLORP2);
			m_buttonsS.push_back(Choose2But);

		}

		bool Setup() //настройка кнопок (загружаем текстуры)
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
			
			m_spriteP1.setTexture(m_textureP1);
			m_spriteP2.setTexture(m_textureP2);
			m_spriteP1.setPosition(m_buttonsS[2]->X(), m_buttonsS[2]->Y());
			m_spriteP2.setPosition(m_buttonsS[0]->X(), m_buttonsS[0]->Y());

			return true;
		}

		void DisplayMenu() //функция вывода меню
		{
			m_window->clear();
			for (const auto& button : m_buttonsM)
				m_window->draw(button->Get());
			m_window->display();
		}

		void DisplaySettings() //функция вывода настроек
		{
			m_window->clear();
			for (const auto& button : m_buttonsS)
				m_window->draw(button->Get());
			m_window->draw(m_spriteP1);
			m_window->draw(m_spriteP2);
			m_window->display();
		}

		ButtonType PressedButtonM() //проверка нажатия на кнопки из меню
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

		ButtonType PressedButtonS() //провекра нажатия на кнопки из настроек
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

		void loopSettings(sf::Color& colorP1, sf::Color& colorP2) //функция для работы с окном настроек (такая же функция для меню реализована в мейне)
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
					//---------------КНОПКИ ЦВЕТА----------------------------
				case ButtonType::C_RED:
					std::cerr << "RED" << std::endl; //для дебага, потом убрать!
					PressColorBut(colorP1, colorP2, 0);
					break;
				case ButtonType::C_BLUE:
					std::cerr << "BLUE" << std::endl;
					PressColorBut(colorP1, colorP2, 1);
					break;
				case ButtonType::C_GREEN:
					std::cerr << "Green" << std::endl;
					PressColorBut(colorP1, colorP2, 2);
					break;
				case ButtonType::C_YELLOW:
					std::cerr << "Yellow" << std::endl;
					PressColorBut(colorP1, colorP2, 3);
					break;
				case ButtonType::C_ORANGE:
					std::cerr << "Orange" << std::endl;
					PressColorBut(colorP1, colorP2, 4);
					break;
				case ButtonType::C_WHITE:
					std::cerr << "White" << std::endl;
					PressColorBut(colorP1, colorP2, 5);
					break;
				case ButtonType::C_MAGENTA:
					std::cerr << "Magenta" << std::endl;
					PressColorBut(colorP1, colorP2, 6);
					break;
				case ButtonType::C_PURPLE:
					std::cerr << "Purple" << std::endl;
					PressColorBut(colorP1, colorP2, 7);
					break;
					//------------------СИСТЕМНЫЕ КНОПКИ----------------------------
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
				} //ДОДЕЛАТЬ АНИМАЦИЮ ПРИ НАЖАТИИ

				DisplaySettings(); // Вывод на экран

				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}

	private:
		std::shared_ptr<sf::RenderWindow> m_window;
		std::vector<std::shared_ptr<Button>> m_buttonsM; //вектор кнопок для МЕНЮ
		std::vector<std::shared_ptr<Button>> m_buttonsS; //вектор кнопок для НАСТРОЕК

		sf::Texture m_textureP1, m_textureP2;
		sf::Sprite m_spriteP1, m_spriteP2;

		void PressColorBut(sf::Color& colorP1, sf::Color& colorP2, int numberBut)
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
				m_spriteP1.setPosition(m_buttonsS[numberBut]->X(), m_buttonsS[numberBut]->Y());
			}
			if (m_buttonsS[10]->GetActivity() && colorP1 != ColorNow)
			{
				colorP2 = ColorNow;
				m_spriteP2.setPosition(m_buttonsS[numberBut]->X(), m_buttonsS[numberBut]->Y());
			}

		}
	};


}