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

		void PressColorBut(sf::Color& colorP1, sf::Color& colorP2, int numberBut);
	

	};


}