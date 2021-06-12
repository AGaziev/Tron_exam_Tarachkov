#pragma once
#include "Button.hpp"
namespace Tron
{
	class Menu
	{
	public:
		Menu(std::shared_ptr<sf::RenderWindow> window) //создает векторы с пустыми(!) кнопками для меню и для настроек
		{
			m_window = window;
			//-----------------------------КНОПКИ МЕНЮ------------------------------------
			std::shared_ptr<Button> newGameBut = std::make_shared<Button>(350, 200, ButtonType::NEWGAME);
			m_buttonsM.push_back(newGameBut);
			std::shared_ptr<Button> settingsBut = std::make_shared<Button>(350, 350, ButtonType::SETTINGS);
			m_buttonsM.push_back(settingsBut);
			std::shared_ptr<Button> exitBut = std::make_shared<Button>(350, 500, ButtonType::EXIT);
			m_buttonsM.push_back(exitBut);
			//------------------------КНОПКИ ЦВЕТОВ В НАСТРОЙКАХ----------------------------------------
			std::shared_ptr<Button> redBut = std::make_shared<Button>(310, 400, ButtonType::C_RED);
			m_buttonsS.push_back(redBut);
			std::shared_ptr<Button> blueBut = std::make_shared<Button>(410, 400, ButtonType::C_BLUE);
			m_buttonsS.push_back(blueBut);
			std::shared_ptr<Button> greenBut = std::make_shared<Button>(510, 400, ButtonType::C_GREEN);
			m_buttonsS.push_back(greenBut);
			std::shared_ptr<Button> YellowBut = std::make_shared<Button>(610, 400, ButtonType::C_YELLOW);
			m_buttonsS.push_back(YellowBut);
			std::shared_ptr<Button> OrangeBut = std::make_shared<Button>(310, 500, ButtonType::C_ORANGE);
			m_buttonsS.push_back(OrangeBut);
			std::shared_ptr<Button> WhiteBut = std::make_shared<Button>(410, 500, ButtonType::C_WHITE);
			m_buttonsS.push_back(WhiteBut);
			std::shared_ptr<Button> MagentaBut = std::make_shared<Button>(510, 500, ButtonType::C_MAGENTA);
			m_buttonsS.push_back(MagentaBut);
			std::shared_ptr<Button> PurpleBut = std::make_shared<Button>(610, 500, ButtonType::C_PURPLE);
			m_buttonsS.push_back(PurpleBut);
			//--------------------------СИСТЕМНЫЕ КНОПКИ В НАСТРОЙКАХ--------------------------------
			std::shared_ptr<Button> BackBut = std::make_shared<Button>(1, 1, ButtonType::BACKTOMENU);
			m_buttonsS.push_back(BackBut);
			std::shared_ptr<Button> Choose1But = std::make_shared<Button>(50, 200, ButtonType::CHOOSECOLORP1);
			m_buttonsS.push_back(Choose1But);
			std::shared_ptr<Button> Choose2But = std::make_shared<Button>(540, 200, ButtonType::CHOOSECOLORP2);
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
					if (m_buttonsS[9]->GetActivity())	colorP1 = sf::Color::Red;	//если нажата кнопка "выбрать цвет для 1 игрока" цвет присваиваем 1 игроку
					if (m_buttonsS[10]->GetActivity()) colorP2 = sf::Color::Red;	//аналогично для 2 игрока (в противном случае ничего не делаем)				
					break;
				case ButtonType::C_BLUE:
					std::cerr << "BLUE" << std::endl;
					if (m_buttonsS[9]->GetActivity())	colorP1 = sf::Color::Cyan;
					if (m_buttonsS[10]->GetActivity()) colorP2 = sf::Color::Cyan;
					break;
				case ButtonType::C_GREEN:
					std::cerr << "Green" << std::endl;
					if (m_buttonsS[9]->GetActivity())	colorP1 = sf::Color::Green;
					if (m_buttonsS[10]->GetActivity()) colorP2 = sf::Color::Green;
					break;
				case ButtonType::C_YELLOW:
					std::cerr << "Yellow" << std::endl;
					if (m_buttonsS[9]->GetActivity())	colorP1 = sf::Color::Yellow;
					if (m_buttonsS[10]->GetActivity()) colorP2 = sf::Color::Yellow;
					break;
				case ButtonType::C_ORANGE:
					std::cerr << "Orange" << std::endl;
					if (m_buttonsS[9]->GetActivity())	colorP1 = sf::Color(255, 127, 39);
					if (m_buttonsS[10]->GetActivity()) colorP2 = sf::Color(255, 127, 39);
					break;
				case ButtonType::C_WHITE:
					std::cerr << "White" << std::endl;
					if (m_buttonsS[9]->GetActivity())	colorP1 = sf::Color::White;
					if (m_buttonsS[10]->GetActivity()) colorP2 = sf::Color::White;
					break;
				case ButtonType::C_MAGENTA:
					std::cerr << "Magenta" << std::endl;
					if (m_buttonsS[9]->GetActivity())	colorP1 = sf::Color::Magenta;
					if (m_buttonsS[10]->GetActivity()) colorP2 = sf::Color::Magenta;
					break;
				case ButtonType::C_PURPLE:
					std::cerr << "Purple" << std::endl;
					if (m_buttonsS[9]->GetActivity())	colorP1 = sf::Color(128, 0, 255);
					if (m_buttonsS[10]->GetActivity()) colorP2 = sf::Color(128, 0, 255);
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
				/*
				m_window->clear();

				sf::RectangleShape CLR1(sf::Vector2f(205, 80));
				CLR1.setFillColor(colorP1);
				CLR1.setPosition(50, 320);
				m_window->draw(CLR1);

				sf::RectangleShape CLR2(sf::Vector2f(205, 80));
				CLR2.setFillColor(colorP2);
				CLR2.setPosition(745, 320);
				m_window->draw(CLR2);

				for (const auto& button : m_buttonsS)
					m_window->draw(button->Get());
				m_window->display();*/


				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}

	private:
		std::shared_ptr<sf::RenderWindow> m_window;
		std::vector<std::shared_ptr<Button>> m_buttonsM; //вектор кнопок для МЕНЮ
		std::vector<std::shared_ptr<Button>> m_buttonsS; //вектор кнопок для НАСТРОЕК
	};


}