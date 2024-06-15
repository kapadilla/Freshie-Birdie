#include<SFML/Graphics.hpp>
#include"Globals.hpp"
#include"Game.hpp"
int main(){
	sf::RenderWindow win(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Freshie Birdie");
	sf::Image icon;
    icon.loadFromFile("assets/icon.png");
    win.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	Game game(win);
	game.startGameLoop();
	return 0;
}