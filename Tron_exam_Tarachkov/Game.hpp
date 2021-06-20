#pragma once
#include <SFML/Audio.hpp>
#include"Player.hpp"
#include <thread>
#include <chrono>

namespace Tron
{

	class Game
	{
	public:
		
		Game(std::shared_ptr<sf::RenderWindow> window);

		#pragma region SETUP		
		void SetColors(sf::Color colorP1, sf::Color colorP2, sf::Texture P1, sf::Texture P2);		
		bool SetMusic();
		bool SetBackground();
		bool SetPlayers();
		bool SetInfo();

		bool Setup();
		#pragma endregion

		void LifeCycle();
		void Restart();

	private:
		
		std::shared_ptr<sf::RenderWindow> m_window;
		int m_width, m_height;
		sf::Color m_colorP1, m_colorP2;

		sf::RenderTexture m_map;
		bool map[80][80] = { 0 };
		Player m_P1, m_P2;

		sf::Texture m_textureBack, m_textureHUD;
		sf::Texture m_textureCrash;
		sf::Texture m_TexturePlayer1, m_TexturePlayer2;
		
		sf::Sprite m_back,m_HUD;
		sf::Sprite m_spriteBackground; 
		sf::Sprite m_Crash;
		sf::Sprite m_Player1, m_Player2;
		

		int m_scoreP1=0, m_scoreP2=0;
		sf::Font font;
		sf::Text m_scoreTextP1, m_scoreTextP2;
		sf::Text m_PrSpace;
		
		sf::Music g_music;
		sf::SoundBuffer buffer;
		sf::Sound m_crashSound;		
				

	};

}