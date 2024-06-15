#include "Menu.hpp"

Menu::Menu(sf::RenderWindow& window) : win(window), 
is_game_started(false),
showMechanics(false) {
    background_texture.loadFromFile("assets/bg.png"); //Loads the texture of background
	background_sprite.setTexture(background_texture); //Sets the sprite of background
	background_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR); //Scales the sprite of background
	background_sprite.setPosition(0,-250); //Positions the sprite of background
    
    title_texture.loadFromFile("assets/title.png"); //Loads the texture of title
    title_sprite.setTexture(title_texture); //Sets the sprite of title
    title_sprite.setScale(0.5f, 0.5f); //Scales the sprite of title
    title_sprite.setPosition(51, 60); //Positions the sprite of title

    button_texture.loadFromFile("assets/button.png"); //Loads the texture of button
    button_sprite.setTexture(button_texture); //Sets the sprite of button
    button_sprite.setScale(0.5f, 0.5f); //Scales the sprite of button
    button_sprite.setPosition(220, 620); //Positions the sprite of button

    button2_texture.loadFromFile("assets/button.png"); //Loads the texture of button
    button2_sprite.setTexture(button2_texture); //Sets the sprite of button
    button2_sprite.setScale(0.5f, 0.5f); //Scales the sprite of button
    button2_sprite.setPosition(220, 660); //Positions the sprite of button

    mechanics_texture.loadFromFile("assets/mechanics.png"); //Loads the texture of background
	mechanics_sprite.setTexture(mechanics_texture); //Sets the sprite of background
	mechanics_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR); //Scales the sprite of background
	mechanics_sprite.setPosition(0,-250); //Positions the sprite of background

}

void Menu::startMenuLoop() {
    while (win.isOpen()) {
        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                win.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = win.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                if (button_sprite.getGlobalBounds().contains(mousePos)) {
                    showMechanics = true;
                }
                if (showMechanics && button2_sprite.getGlobalBounds().contains(mousePos)) {
                    showMechanics = false;
                    is_game_started = true;
                    return;
                }   
            }
        }

        win.clear();
        win.draw(background_sprite);
        win.draw(title_sprite);
        win.draw(button_sprite);

        if (showMechanics) {
            win.clear();
            win.draw(mechanics_sprite);
            win.draw(button2_sprite);
        }
        win.display();
    }
}


bool Menu::isGameStarted() { 
    return is_game_started; //flag that indicates if the use clicked the button
}

