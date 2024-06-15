#pragma once
#include <SFML/Graphics.hpp>
#include "Bird.hpp"
#include <vector>
#include "Pipe.hpp"
#include <random>
#include "Menu.hpp"
#include <SFML/Audio.hpp>
#include "List.hpp"

using namespace std;

class Game {
public:
    Game(sf::RenderWindow&);
    sf::RenderWindow& win;
    void startGameLoop();
    int getScore();
    void getPlayerName();
    list leaderboard;
private:
    sf::Texture bg_texture, ground_texture, restart_button_texture, body_texture, medal_texture, over_texture, back_button_texture, lb_texture;
    sf::Sprite bg_sprite, ground_sprite1, ground_sprite2, restart_button_sprite, body_sprite, medal_sprite, over_sprite, back_button_sprite, lb_sprite;
    Bird bird;
    bool is_enter_pressed, run_game, start_monitoring, bird_collided, display_best_score, graduated, showGrad, name_entered, recordScore;
    const int move_speed = 270;
    void draw();
    void moveGround(sf::Time&);
    void doProcessing(sf::Time&);
    void checkCollisions();
    void restartGame();
    void checkScore();
    void updateBestScore(); 
    void updateScore(); 
    string toString(int);
    int pipe_counter, pipe_spawn_time, score, best_score;
    vector<Pipe> pipes;
    random_device rd;
    uniform_int_distribution<int> dist{ 250,550 };
    sf::Font font;
    sf::Text score_text, score2_text, best_score_text, leaderboard_text[5];
    sf::SoundBuffer deadBuffer, flapBuffer, scoresBuffer, philippeBuffer, audienceBuffer;
    sf::Sound dead, flap, scores, philippe, audience;
    string playerName;
    sf::Music backgroundMusic;
};