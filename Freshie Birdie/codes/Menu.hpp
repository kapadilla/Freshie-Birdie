#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.hpp"

class Menu {
public:
    Menu(sf::RenderWindow& window);
    void startMenuLoop();
    bool isGameStarted();
private:
    sf::RenderWindow& win;
    sf::Texture background_texture, title_texture, button_texture, button2_texture, mechanics_texture;
    sf::Sprite background_sprite, title_sprite, button_sprite, button2_sprite, mechanics_sprite;
    bool is_game_started;
    sf::Clock mechanicsClock;
    bool showMechanics;
    void setMechanicsVisible();
};
