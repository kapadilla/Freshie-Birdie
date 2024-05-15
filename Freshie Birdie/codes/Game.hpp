#pragma once
#include <SFML/Graphics.hpp>
#include "Bird.hpp"
#include <vector>
#include "Pipe.hpp"
#include <random>
#include "Menu.hpp"
#include <SFML/Audio.hpp>

class Game {
public:
    Game(sf::RenderWindow&);
    sf::RenderWindow& win;
    void startGameLoop();
    int getScore();
private:
    sf::Texture bg_texture, ground_texture, restart_button_texture, body_texture, medal_texture, over_texture;
    sf::Sprite bg_sprite, ground_sprite1, ground_sprite2, restart_button_sprite, body_sprite, medal_sprite, over_sprite;
    Bird bird;
    bool is_enter_pressed, run_game, start_monitoring, bird_collided, display_best_score, graduated, showGrad;
    const int move_speed = 270;
    void draw();
    void moveGround(sf::Time&);
    void doProcessing(sf::Time&);
    void checkCollisions();
    void restartGame();
    void checkScore();
    void updateBestScore(); 
    std::string toString(int);
    int pipe_counter, pipe_spawn_time, score, best_score;
    std::vector<Pipe> pipes;
    std::random_device rd;
    std::uniform_int_distribution<int> dist{ 250,550 };
    sf::Font font;
    sf::Text score_text, score2_text, best_score_text;
    sf::SoundBuffer deadBuffer, flapBuffer, scoresBuffer, philippeBuffer, audienceBuffer;
    sf::Sound dead, flap, scores, philippe, audience;
};