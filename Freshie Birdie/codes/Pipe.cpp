#include "Pipe.hpp"
#include"Globals.hpp"
Pipe::Pipe(int y_pos){
	sprite_down.setTexture(texture_down);  //Sets the sprite of pipe down
	sprite_up.setTexture(texture_up); //Sets the sprite of pipe up
	sprite_down.setScale(SCALE_FACTOR, SCALE_FACTOR); //Scales the sprite of pipe down
	sprite_up.setScale(SCALE_FACTOR, SCALE_FACTOR); //Scales the sprite of pipe down
	sprite_up.setPosition(WIN_WIDTH, y_pos); //y_pos is the y-coordinate where the pipes will be positioned vertically.
	sprite_down.setPosition(WIN_WIDTH, y_pos - pipe_distance - sprite_up.getGlobalBounds().height); //pipe_distance is the distance between the upper and lower pipes.
}

void Pipe::update(sf::Time& dt){ //updating the pipe sprites' positions over time
	sprite_up.move(-move_speed * dt.asSeconds(), 0.f); // the pipes are moved horizontally 
	sprite_down.move(-move_speed * dt.asSeconds(), 0.f); //to the left based on the elapsed time and  move speed
}

void Pipe::loadTextures(){ //declaring the textures as static, they are shared among all instances of the Pipe class. 
	texture_down.loadFromFile("assets/pipedown.png"); //This means that all pipe objects will use the same textures for their sprites. 
	texture_up.loadFromFile("assets/pipe.png"); // This can be useful when you want to conserve memory 
} //and avoid loading the same textures multiple times for each instance of the class.

float Pipe::getRightBound(){ //returning the right boundary position of the lower pipe sprite.
	return sprite_down.getGlobalBounds().left+sprite_down.getGlobalBounds().width;
}

sf::Texture Pipe::texture_down, Pipe::texture_up;