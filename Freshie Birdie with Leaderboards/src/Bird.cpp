#include "Bird.hpp"
#include"Globals.hpp"
Bird::Bird() :
gravity(10),
flap_speed(250),
anim_counter(0),
texture_switch(1),
should_fly(false) {
	textures[0].loadFromFile("assets/birddown.png");
	textures[1].loadFromFile("assets/birdup.png");
	bird_sprite.setTexture(textures[0]);
	bird_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);
	resetBirdPosition();
}

void Bird::update(sf::Time& dt){ //updates the bird
	if (bird_sprite.getGlobalBounds().top < 548 && should_fly){ //checks if the top position of the bird sprite is less than 548
		if (anim_counter == 5){ //checks if the anim_counter is 5, then the switch in texture will be made
			bird_sprite.setTexture(textures[texture_switch]);
			if (texture_switch) 
				texture_switch = 0;
			else 
				texture_switch = 1;
			anim_counter = 0;
		}
		anim_counter++;
		velocity_y += gravity * dt.asSeconds(); //updates the velocity_y by adding the product of gravity and the time passed (dt) in seconds
		bird_sprite.move(0, velocity_y); //moves the bird sprite vertically by velocity_y units
		if (bird_sprite.getGlobalBounds().top < 0) //checks if the top position of the bird sprite is less than 0
			bird_sprite.setPosition(100, 0); //repositions the bird to coordinate (100,0)
	}
}

void Bird::flapBird(sf::Time& dt){ //function that makes the bird flap by updating its vertical velocity based on the elapsed time (dt)
	velocity_y = -flap_speed * dt.asSeconds(); //calculates the new vertical velocity. The negative value makes the bird go up
}

float Bird::getRightBound(){ //returns the rightmost boundary of the bird sprite
	return bird_sprite.getGlobalBounds().left+bird_sprite.getGlobalBounds().width; //calculates and returns the sum of the left coordinate and the width, which gives the rightmost boundary of the bird sprite
}

void Bird::resetBirdPosition(){ // resets the position and velocity of the bird sprite
	bird_sprite.setPosition(100, 50); //sets the position of the bird sprite to (100, 50)
	velocity_y = 0; //sets the vertical velocity of the bird to zero, effectively stopping its movement
}

void Bird::setShouldFly(bool should_fly){ //determine whether the bird should be allowed to fly or not
	this->should_fly = should_fly; //assigns the value of the should_fly parameter to the member variable should_fly of the Bird object
}

void Bird::changeBirdPicture() {
    textures[0].loadFromFile("assets/reward.png"); // Load the new bird image texture
	textures[1].loadFromFile("assets/reward.png"); // Load the new bird image texture
    bird_sprite.setTexture(textures[0]); // Set the new bird sprite texture
    bird_sprite.setOrigin(textures[0].getSize().x / 2.f, textures[0].getSize().y / 2.f); // Set the origin to the center of the new bird sprite
}