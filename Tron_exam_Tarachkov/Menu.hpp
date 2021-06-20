#pragma once
#include <SFML/Audio.hpp>
#include "Button.hpp"
#include <thread>
#include <chrono>

const int mainW = 300; //
const int mainH = 100; //������� �������� ������
const int clrSize = 100; //������� ������

namespace Tron
{
	class Menu
	{
	public:
		
		Menu(std::shared_ptr<sf::RenderWindow> window); //������� ������� � �������(!) �������� ��� ���� � ��� ��������		

		#pragma region Setup
		bool SetTextures();
		bool SetMusic();		
		bool Setup();
		#pragma endregion

		#pragma region Main Menu
		ButtonType PressedButtonM(); //�������� ������� �� ������ �� ����
		void Animation(int& i, bool Up); //������� ��� �������� ����
		void DisplayMenu(); //������� ������ ����
		#pragma endregion
		
		#pragma region Settings
		void DisplaySettings(); //������� ������ ��������
		ButtonType PressedButtonS(); //�������� ������� �� ������ �� ��������
		sf::Texture getTexture(int tmp); //�������� �������� ������ ��� �� ����������� �������� � ����� Game
		void loopSettings(sf::Color& colorP1, sf::Color& colorP2); //������� ��� ������ � ����� �������� 
		#pragma endregion

		void turnOnOff(bool tmp); // ��������/��������� ������	

	private:
		std::shared_ptr<sf::RenderWindow> m_window;
		std::vector<std::shared_ptr<Button>> m_buttonsM; //������ ������ ��� ����
		std::vector<std::shared_ptr<Button>> m_buttonsS; //������ ������ ��� ��������

		sf::Texture m_textureP1, m_textureP2;
		sf::Texture m_LogoT, m_RightT, m_LeftT, m_BackgroundT;
		sf::Texture m_iconP1T, m_iconP2T, m_FrameT;

		sf::Sprite m_spriteP1, m_spriteP2; //������� �1 � �2 (�� ������� �����)
		sf::Sprite m_Logo, m_RightMainPerson, m_LeftMainPerson, m_Background; //������� ��� ����
		sf::Sprite m_iconP1, m_iconP2, m_Frame; //������ ������ � �������		
		
		sf::Music m_music;		

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
	

	};


}