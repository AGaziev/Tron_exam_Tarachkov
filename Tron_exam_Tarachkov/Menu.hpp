#pragma once
#include "Button.hpp"
const int mainW = 300; //
const int mainH = 100; //������� �������� ������
const int clrSize = 100; //������� ������

namespace Tron
{
	class Menu
	{
	public:
		Menu(std::shared_ptr<sf::RenderWindow> window) //������� ������� � �������(!) �������� ��� ���� � ��� ��������
		{
			int btwButMain = (window.get()->getSize().y - 3 * mainH) / 4; //��������� ����� �������� � ������� ���� (4-���������� ������ ����������� ����� ��������)
			int btwClrSetW = (window.get()->getSize().x - 4 * clrSize) / 5;//��������� �� ������ ����� ������� � ���������� (5-���������� ������ ����������� ����� ��������)
			int btwButSet = (window.get()->getSize().y - 4 * mainH) / 5;//��������� �� ������ ����� �������� � ���������� (5-���������� ������ ����������� ����� ��������)
			m_window = window;
			//-----------------------------������ ����------------------------------------
			std::shared_ptr<Button> newGameBut = std::make_shared<Button>((window.get()->getSize().x - mainW) / 2, btwButMain * 1 + mainH * 0, ButtonType::NEWGAME);
			m_buttonsM.push_back(newGameBut);
			std::shared_ptr<Button> settingsBut = std::make_shared<Button>((window.get()->getSize().x - mainW) / 2, btwButMain * 2 + mainH * 1, ButtonType::SETTINGS);
			m_buttonsM.push_back(settingsBut);
			std::shared_ptr<Button> exitBut = std::make_shared<Button>((window.get()->getSize().x - mainW) / 2, btwButMain * 3 + mainH * 2, ButtonType::EXIT);
			m_buttonsM.push_back(exitBut);
			//------------------------������ ������ � ����������----------------------------------------
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
			//--------------------------��������� ������ � ����������--------------------------------
			std::shared_ptr<Button> BackBut = std::make_shared<Button>((window.get()->getSize().x - mainW) / 2, btwButSet * 1 + 0 * btwButSet, ButtonType::BACKTOMENU);
			m_buttonsS.push_back(BackBut);
			std::shared_ptr<Button> Choose1But = std::make_shared<Button>((window.get()->getSize().x - 2 * mainW) / 3, btwButSet * 2 + 1 * btwButSet, ButtonType::CHOOSECOLORP1);
			m_buttonsS.push_back(Choose1But);
			std::shared_ptr<Button> Choose2But = std::make_shared<Button>((window.get()->getSize().x * 2 - mainW) / 3 , btwButSet * 2 + 1 * btwButSet, ButtonType::CHOOSECOLORP2);
			m_buttonsS.push_back(Choose2But);

		}

		bool Setup() //��������� ������ (��������� ��������)
		{
			for (const auto& button : m_buttonsM)
				if (!button->Setup())
					return false;
			for (const auto& button : m_buttonsS)
				if (!button->Setup())
					return false;
			return true;
		}

		void DisplayMenu() //������� ������ ����
		{
			m_window->clear();
			for (const auto& button : m_buttonsM)
				m_window->draw(button->Get());
			m_window->display();
		}

		void DisplaySettings() //������� ������ ��������
		{
			m_window->clear();
			for (const auto& button : m_buttonsS)
				m_window->draw(button->Get());
			m_window->display();
		}

		ButtonType PressedButtonM() //�������� ������� �� ������ �� ����
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

		ButtonType PressedButtonS() //�������� ������� �� ������ �� ��������
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

		void loopSettings(sf::Color& colorP1, sf::Color& colorP2) //������� ��� ������ � ����� �������� (����� �� ������� ��� ���� ����������� � �����)
		{
			while (m_window->isOpen())
			{
				sf::Event event;
				while (m_window->pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						m_window->close();
				}

				ButtonType button = PressedButtonS(); //���������� button ����������� ��� ������� ������

				switch (button) //�������� ���� �� ������� ������������ ��� ������ �� ������
				{
					//---------------������ �����----------------------------
				case ButtonType::C_RED:
					std::cerr << "RED" << std::endl; //��� ������, ����� ������!
					if (m_buttonsS[9]->GetActivity())	colorP1 = sf::Color::Red;	//���� ������ ������ "������� ���� ��� 1 ������" ���� ����������� 1 ������
					if (m_buttonsS[10]->GetActivity()) colorP2 = sf::Color::Red;	//���������� ��� 2 ������ (� ��������� ������ ������ �� ������)				
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
					//------------------��������� ������----------------------------
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
				} //�������� �������� ��� �������

				DisplaySettings(); // ����� �� �����
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
		std::vector<std::shared_ptr<Button>> m_buttonsM; //������ ������ ��� ����
		std::vector<std::shared_ptr<Button>> m_buttonsS; //������ ������ ��� ��������
	};


}