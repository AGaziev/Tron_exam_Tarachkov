#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include "Menu.hpp"
#include "Game.hpp"
using Tron::ButtonType;


int main()
{
    const int W = 800;
    const int H = 900;

    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(W, H), "Tron!");

    Tron::Menu menu(window);
    if (!menu.Setup())
        return 1;
    Tron::Game Game(window);
    sf::Color ColorP1, ColorP2;

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        ButtonType button = menu.PressedButtonM();

        switch (button)
        {
        case ButtonType::NEWGAME:
            std::cerr << "Button 'New Game' pressed" << std::endl;
            Game.Settup();
            Game.LifeCycle();
            break;

        case ButtonType::SETTINGS:
            menu.loopSettings(ColorP1, ColorP2);
            Game.SetColors(ColorP1, ColorP2);
            break;

        case ButtonType::EXIT:
            window->close();
        }

        menu.DisplayMenu();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return 0;
}
