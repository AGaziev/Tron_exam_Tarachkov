#include "Menu.hpp"
#include "Game.hpp"
#include <memory>

const int W = 800;
const int H = 900;

void LogoSetup(sf::Sprite& Logo);

int main()
{
    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(W, H), "Tron!");

    Tron::Menu menu(window);
    if (!menu.Setup())
        return 1;

    Tron::Game Game(window);
    sf::Texture TeamLogoT;
    if (!TeamLogoT.loadFromFile("..\\assets\\CompanyLogo.png"))
        return 0;
    sf::Sprite TeamLogo(TeamLogoT);
    LogoSetup(TeamLogo);
    sf::Color ColorP1 = sf::Color::White, ColorP2 = sf::Color::Yellow;
    
    bool Logo = true;
    int i = 0,j=0;
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        if (Logo) {
            TeamLogo.setTextureRect(sf::IntRect(0,0,1*j-100,44));
            j++;
            window->clear();
            window->draw(TeamLogo);
            window->display();
            if (j >= 377)
            {
                Logo = false;
                std::this_thread::sleep_for(std::chrono::milliseconds(1500));
                menu.turnOnOff(true);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        else{
            if (i < 8)
                menu.Animation(i, false);
            else if (i < 16)
                menu.Animation(i, true);
            else if (i == 16)
                i = 0;

        Tron::ButtonType button = menu.PressedButtonM();

        switch (button)
        {
        case Tron::ButtonType::NEWGAME:
            menu.turnOnOff(false);
            Game.SetColors(ColorP1, ColorP2, menu.getTexture(1), menu.getTexture(2));
            if (!Game.Setup())
                return 1;
            Game.LifeCycle();
            menu.turnOnOff(true);
            break;

        case Tron::ButtonType::SETTINGS:
            menu.loopSettings(ColorP1, ColorP2);
            Game.SetColors(ColorP1, ColorP2, menu.getTexture(1), menu.getTexture(2));
            break;

        case Tron::ButtonType::EXIT:
            window->close();
        }

        menu.DisplayMenu();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
    }

    return 0;
}

void LogoSetup(sf::Sprite& Logo) {
    Logo.setOrigin(Logo.getGlobalBounds().width / 2, Logo.getGlobalBounds().height / 2);
    Logo.setPosition(W / 2, H / 2);
    Logo.setScale(2.5, 2.5);
}