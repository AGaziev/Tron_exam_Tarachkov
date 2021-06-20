#pragma once
#include <SFML/Audio.hpp>
#include "Button.hpp"
#include <thread>
#include <chrono>

const int mainW = 300; //
const int mainH = 100; //Размеры основных кнопок
const int clrSize = 100; //Размеры цветов

namespace Tron
{
	class Menu
	{
	public:
		
		Menu(std::shared_ptr<sf::RenderWindow> window); //создает векторы с пустыми(!) кнопками для меню и для настроек		

		#pragma region Setup
		bool SetTextures();
		bool SetMusic();		
		bool Setup();
		#pragma endregion

		#pragma region Main Menu
		ButtonType PressedButtonM(); //проверка нажатия на кнопки из меню
		void Animation(int& i, bool Up); //функция для анимации лого
		void DisplayMenu(); //функция вывода меню
		#pragma endregion
		
		#pragma region Settings
		void DisplaySettings(); //функция вывода настроек
		ButtonType PressedButtonS(); //провекра нажатия на кнопки из настроек
		sf::Texture getTexture(int tmp); //получаем текстуры шлемов для их последующей передачи в класс Game
		void loopSettings(sf::Color& colorP1, sf::Color& colorP2); //функция для работы с окном настроек 
		#pragma endregion

		void turnOnOff(bool tmp); // включить/выключить музыку	

	private:
		std::shared_ptr<sf::RenderWindow> m_window;
		std::vector<std::shared_ptr<Button>> m_buttonsM; //вектор кнопок для МЕНЮ
		std::vector<std::shared_ptr<Button>> m_buttonsS; //вектор кнопок для НАСТРОЕК

		sf::Texture m_textureP1, m_textureP2;
		sf::Texture m_LogoT, m_RightT, m_LeftT, m_BackgroundT;
		sf::Texture m_iconP1T, m_iconP2T, m_FrameT;

		sf::Sprite m_spriteP1, m_spriteP2; //надписи Р1 и Р2 (на кнопках цвета)
		sf::Sprite m_Logo, m_RightMainPerson, m_LeftMainPerson, m_Background; //спрайты для меню
		sf::Sprite m_iconP1, m_iconP2, m_Frame; //иконки шлемов и граница		
		
		sf::Music m_music;		

		void PressColorBut(sf::Color& colorP1, sf::Color& colorP2, int numberBut);
	

	};


}