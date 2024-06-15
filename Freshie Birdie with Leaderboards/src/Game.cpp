#include "Game.hpp"
#include "Globals.hpp"
#include "List.hpp"
#include <sstream>

Game::Game(sf::RenderWindow& window) : win(window),
run_game(true),
start_monitoring(false),
bird_collided(false),
display_best_score(false),
graduated(false),
showGrad(false),
pipe_counter(71),
pipe_spawn_time(70),
score(0), //Initializing the scores to 0
best_score(0) { 
    win.setFramerateLimit(60);

    bg_texture.loadFromFile("assets/bg.png"); // Load bg image texture
    //Image Source: https://codeheir.com/2020/09/12/how-to-code-flappy-bird-%F0%9F%90%A4/
    bg_sprite.setTexture(bg_texture);  // Set bg sprite texture
    bg_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);  // Scale bg sprite
    bg_sprite.setPosition(0, -250); // Positions the bg to coordinate (0,-250) 

    ground_texture.loadFromFile("assets/ground.png"); // Load ground image texture
    ground_sprite1.setTexture(ground_texture);  // Set 1st ground sprite texture
    ground_sprite2.setTexture(ground_texture); // Set 2nd ground sprite texture
    ground_sprite1.setScale(SCALE_FACTOR, SCALE_FACTOR);  // Scale 1st ground sprite texture
    ground_sprite2.setScale(SCALE_FACTOR, SCALE_FACTOR); // Scale 2nd ground sprite texture

    //When the left edge of one ground sprite goes off the screen, its position is updated by setting it next to the other ground sprite. 
    //This creates a continuous scrolling effect without any visible gaps.
    ground_sprite1.setPosition(0, 578);
    ground_sprite2.setPosition(ground_sprite1.getGlobalBounds().width, 578);

    restart_button_texture.loadFromFile("assets/button.png"); // Load button image texture
    restart_button_sprite.setTexture(restart_button_texture); // Set restart button sprite texture
    restart_button_sprite.setScale(0.5f, 0.5f); // Scale bg sprite texture
    restart_button_sprite.setPosition(220, 650); // Positions the bg to coordinate (220,650) 

    font.loadFromFile("assets/FlappyFont.ttf"); // Load font style

    score_text.setFont(font);
    score_text.setCharacterSize(80);
    score_text.setFillColor(sf::Color::White);
    score_text.setOutlineThickness(2.f); // Set the outline thickness
    score_text.setOutlineColor(sf::Color::Black); // Set the outline color
    sf::FloatRect textBounds = score_text.getLocalBounds();
    float textX = (window.getSize().x - textBounds.width) / 2.3; // Center the text horizontally
    float textY = 15.f - textBounds.height / 2.f; // Set the y-coordinate to 15, adjusted for the text height
    score_text.setPosition(textX, textY);
    score_text.setString("0");

    body_texture.loadFromFile("assets/body.png"); // Load body image texture
    body_sprite.setTexture(body_texture); // Set body sprite texture
    body_sprite.setScale(0.5f, 0.5f); // Scale body sprite
    sf::FloatRect bodyBounds = body_sprite.getLocalBounds(); // Get body sprite bounds
    body_sprite.setOrigin(bodyBounds.width / 2.f, bodyBounds.height / 2.f); // Set body sprite origin to its center
    body_sprite.setPosition(win.getSize().x / 2.f, win.getSize().y/4.f); // Set body sprite position to the middle of the window

    medal_texture.loadFromFile("assets/medal.png"); // Load medal image texture
    //Image Source: https://www.suarezarts.com/products/university-of-the-philippines-up-medal-2-inch
    medal_sprite.setTexture(medal_texture); // Set medal sprite texture
    medal_sprite.setScale(0.5f, 0.5f); // Scale medal sprite
    sf::FloatRect medalBounds = medal_sprite.getLocalBounds(); // Get medal sprite bounds
    medal_sprite.setOrigin(medalBounds.width / 2.f, medalBounds.height / 2.f); // Set medal sprite origin to its center
    sf::Vector2f medalOffset(-73.f, 14.f); // Adjust the offset values as per the desired position
    medal_sprite.setPosition(body_sprite.getPosition() + medalOffset); // Set medal sprite position relative to the body sprite

    best_score_text.setFont(font); // Initialize best_score_text font
    best_score_text.setCharacterSize(24); // Set best_score_text character size
    best_score_text.setFillColor(sf::Color::White);
    best_score_text.setOutlineThickness(2.f); // Set the outline thickness
    best_score_text.setOutlineColor(sf::Color::Black); // Set the outline color
    sf::Vector2f best_score_Offset(150.f, 7.f);
    best_score_text.setPosition(medal_sprite.getPosition() + best_score_Offset);
    best_score_text.setString("0"); // Initialize best_score_text to "Best: 0"

    // score2_text is different from score_text
    // score_text is the big one in the middle
    // score2_text is the score seen when the bird collided

    score2_text.setFont(font); // Initialize best_score_text font
    score2_text.setCharacterSize(24); // Set best_score_text character size
    score2_text.setFillColor(sf::Color::White);
    score2_text.setOutlineThickness(2.f); // Set the outline thickness
    score2_text.setOutlineColor(sf::Color::Black); // Set the outline color
    sf::Vector2f score2_Offset(150.f, -43.f);
    score2_text.setPosition(medal_sprite.getPosition() + score2_Offset);
    score2_text.setString("0"); // Initialize best_score_text to "Best: 0"

    over_texture.loadFromFile("assets/gameover.png"); // Load gameover image texture
    over_sprite.setTexture(over_texture);  // Set gameover sprite texture
    over_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);  // Scale gameover sprite texture
    over_sprite.setPosition(158, 25); // Positions the gameover to coordinate (158,25) 

    Pipe::loadTextures();

    deadBuffer.loadFromFile("assets/sfx/dead.wav"); //Loads the audio file
    dead.setBuffer(deadBuffer);
    flapBuffer.loadFromFile("assets/sfx/flap.wav"); //Loads the audio file
    flap.setBuffer(flapBuffer);
    scoresBuffer.loadFromFile("assets/sfx/score.wav"); //Loads the audio file
    scores.setBuffer(scoresBuffer);
    philippeBuffer.loadFromFile("assets/sfx/Philippe.wav"); //Loads the audio file
    philippe.setBuffer(philippeBuffer);
    audienceBuffer.loadFromFile("assets/sfx/audience.wav"); //Loads the audio file
    audience.setBuffer(audienceBuffer);
    //Sounds Source: https://github.com/DenizBasgoren/sfml-flappy-bird

    back_button_texture.loadFromFile("assets/back.png"); // Load button image texture
    back_button_sprite.setTexture(back_button_texture); // Set restart button sprite texture
    back_button_sprite.setScale(0.2f, 0.2f); // Scale bg sprite texture
    back_button_sprite.setPosition(15, 10); // Positions the bg to coordinate (40,300) 
    
    lb_texture.loadFromFile("assets/leaderboard.png"); // Load bg image texture
    //Image Source: https://codeheir.com/2020/09/12/how-to-code-flappy-bird-%F0%9F%90%A4/
    lb_sprite.setTexture(lb_texture);  // Set bg sprite texture
    lb_sprite.setScale(2.f, 3.5f);  // Scale bg sprite
    sf::FloatRect lbBounds = lb_sprite.getLocalBounds(); // Get body sprite bounds
    lb_sprite.setOrigin(lbBounds.width / 2.f, lbBounds.height / 2.f); // Set body sprite origin to its center
    lb_sprite.setPosition(win.getSize().x / 2.f, win.getSize().y/2.f + 70);

    float yPos = 1.f;

    leaderboard.read();

    for(int i = 0; i<5; i++){
        leaderboard_text[i].setFont(font);
        leaderboard_text[i].setCharacterSize(24);
        leaderboard_text[i].setFillColor(sf::Color::White);
        leaderboard_text[i].setOutlineThickness(2.f);
        leaderboard_text[i].setOutlineColor(sf::Color::Black);
        leaderboard_text[i].setPosition(win.getSize().x /2.5f, win.getSize().y/3+(i*50)+85);
        if(leaderboard.size>=i+1){
            leaderboard_text[i].setString(leaderboard[i]->name + " - " + toString(leaderboard[i]->score));
        }
        else{
            leaderboard_text[i].setString("");
        }
        yPos+=1.f;
    }
    backgroundMusic.openFromFile("assets/sfx/bg.wav");
    backgroundMusic.play();
    backgroundMusic.setVolume(50); // Adjust volume (0 to 100)
    backgroundMusic.setLoop(true); // Set to true to loop the music

    recordScore = false;
}

//It performs game logic and processing for each frame update. 
//It updates the ground, spawns pipes, checks collisions, checks scoring, and updates the bird's position.
void Game::doProcessing(sf::Time& dt) { 
    if (is_enter_pressed){
        moveGround(dt); 
        if (pipe_counter > pipe_spawn_time) { //checks if the pipe_counter variable has reached a certain value (pipe_spawn_time). It is used to control the spawning of new pipes.
            pipes.push_back(Pipe(dist(rd)));//adds a new Pipe object to the pipes vector. The dist(rd) part likely generates a random number used for determining the position or characteristics of the new pipe.
            pipe_counter = 0;
        }
        pipe_counter++; //keeps track of the elapsed time since the last pipe was spawned.
        for (int i = 0; i < pipes.size(); i++) { //iterates over all the pipes in the pipes vector.
            pipes[i].update(dt); //updates the movement of the individual pipe.
            if (pipes[i].getRightBound() < 0) //checks if the right boundary of the current pipe is less than zero, indicating that it has moved off the screen or is no longer visible. 
                pipes.erase(pipes.begin() + i); //If true, the erase function is called to remove the pipe from the pipes vector.
        }
        checkCollisions(); //checks if the bird collided a pipe or ground
        checkScore(); //verifies if the current score is higher than the recorded best
        updateBestScore(); // Update best score during processing
        updateScore();
    }
    bird.update(dt); ////updates the bird
}

void Game::startGameLoop() {
    Menu menu(win);
    menu.startMenuLoop();
    if (!menu.isGameStarted())
        return;
    getPlayerName();
    sf::Clock clock;
    is_enter_pressed = true; // Automatically 
    bird.setShouldFly(true);
    // Game Loop
    while (win.isOpen()) {
        sf::Time dt = clock.restart();
        sf::Event event;
        backgroundMusic.play();
        //Event Loop
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                win.close();
            if (event.type == sf::Event::KeyPressed && run_game) {
                if (event.key.code == sf::Keyboard::Space && is_enter_pressed){
                    bird.flapBird(dt);
                    flap.play();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !run_game) {
                if (restart_button_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                    restartGame();
                else if((back_button_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))){
                    playerName = "";
                    getPlayerName();
                }
            }
        }
        doProcessing(dt);
        draw();
        win.display();
    }
}


void Game::checkCollisions() {
    if (pipes.size() > 0) {
        if (pipes[0].sprite_down.getGlobalBounds().intersects(bird.bird_sprite.getGlobalBounds()) ||
            pipes[0].sprite_up.getGlobalBounds().intersects(bird.bird_sprite.getGlobalBounds()) ||
            bird.bird_sprite.getGlobalBounds().top >= 540) {
            run_game = false;
            bird_collided = true;
            recordScore = true;
            is_enter_pressed = false;
            dead.play();
            philippe.play();
        }
    }
}



void Game::checkScore() {
    if (pipes.size() > 0) {
        if (!start_monitoring) {
            if (bird.bird_sprite.getGlobalBounds().left > pipes[0].sprite_down.getGlobalBounds().left &&
                bird.getRightBound() < pipes[0].getRightBound())
                start_monitoring = true;
        } 
        else {
            if (bird.bird_sprite.getGlobalBounds().left > pipes[0].getRightBound()) {
                scores.play();
                score++;
                score_text.setString("" + toString(score));
                start_monitoring = false;
                if (score > best_score) {
                    display_best_score = true;
                }
            }
        }
    }
}


void Game::draw() {
    win.draw(bg_sprite);
    for (Pipe& pipe : pipes) {
        win.draw(pipe.sprite_down);
        win.draw(pipe.sprite_up);
    }
    win.draw(ground_sprite1);
    win.draw(ground_sprite2);
    win.draw(bird.bird_sprite);
    if (bird_collided) {
        win.draw(body_sprite);
        win.draw(over_sprite);
        win.draw(best_score_text);
        score2_text.setString("" + toString(score));
        win.draw(score2_text);
        if (display_best_score)
            win.draw(medal_sprite);
        win.draw(lb_sprite);
        for(int i=0; i<5; i++){
            win.draw(leaderboard_text[i]);
        }
    }
    else 
        win.draw(score_text);
    if (!run_game){
        win.draw(restart_button_sprite);
        // name_entered = true;
        win.draw(back_button_sprite);
    }
}

void Game::moveGround(sf::Time& dt) {
    ground_sprite1.move(-move_speed * dt.asSeconds(), 0.f);
    ground_sprite2.move(-move_speed * dt.asSeconds(), 0.f);
    if (ground_sprite1.getGlobalBounds().left + ground_sprite1.getGlobalBounds().width < 0)
        ground_sprite1.setPosition(ground_sprite2.getGlobalBounds().left + ground_sprite2.getGlobalBounds().width, 578);
    if (ground_sprite2.getGlobalBounds().left + ground_sprite2.getGlobalBounds().width < 0)
        ground_sprite2.setPosition(ground_sprite1.getGlobalBounds().left + ground_sprite1.getGlobalBounds().width, 578);
}

void Game::restartGame() {
    bird.resetBirdPosition();
    bird.setShouldFly(true);
    run_game = true;
    pipe_counter = 71;
    pipes.clear();
    score = 0;
    score_text.setString("0");
    display_best_score = false;
    bird_collided = false;
    is_enter_pressed = true;
}

std::string Game::toString(int num) {
    std::stringstream ss;
    ss << num;
    return ss.str();
}

void Game::updateBestScore() {
    if(!recordScore)
        return;
    recordScore = false;
    leaderboard.insert(playerName, score);
    best_score = leaderboard[0]->score;
    best_score_text.setString("" + toString(best_score));

}

void Game::updateScore(){
    for(int i = 0; i<5 && i<leaderboard.size; i++){
        leaderboard_text[i].setString(leaderboard[i]->name +" - " + toString(leaderboard[i]->score));
    }
    leaderboard.write();
}

void Game::getPlayerName() {
    sf::Text enterNameText;
    enterNameText.setFont(font);
    enterNameText.setCharacterSize(24);
    enterNameText.setFillColor(sf::Color::White);
    enterNameText.setOutlineThickness(2.f);
    enterNameText.setOutlineColor(sf::Color::Black);
    enterNameText.setString("Enter your name:");
    sf::FloatRect textBounds = enterNameText.getLocalBounds();
    float textX = (win.getSize().x - textBounds.width) / 2.f;
    float textY = (win.getSize().y - textBounds.height) / 2.f - 50.f;
    enterNameText.setPosition(textX, textY);

    sf::Text pressEnterText;
    pressEnterText.setFont(font);
    pressEnterText.setCharacterSize(24);
    pressEnterText.setFillColor(sf::Color::White);
    pressEnterText.setOutlineThickness(2.f);
    pressEnterText.setOutlineColor(sf::Color::Black);
    pressEnterText.setString("Press enter key to start.");
    sf::FloatRect textBounds2 = pressEnterText.getLocalBounds();
    float textX2 = (win.getSize().x - textBounds2.width) / 2.f;
    float textY2 = (win.getSize().y - textBounds2.height) / 1.75f;
    pressEnterText.setPosition(textX2, textY2);

    // if (name_entered)
    //     playerName = "";

    sf::Text playerNameText;
    playerNameText.setFont(font);
    playerNameText.setCharacterSize(24);
    playerNameText.setFillColor(sf::Color::White);
    playerNameText.setOutlineThickness(2.f);
    playerNameText.setOutlineColor(sf::Color::Black);
    playerNameText.setString(playerName);

    float playerNameWidth = playerNameText.getLocalBounds().width;
    textX = (win.getSize().x - playerNameWidth) / 2.f;
    playerNameText.setPosition(textX, textY + 50.f);
    playerName = "";

    while (win.isOpen()) {
    sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                win.close();
            if (event.type == sf::Event::TextEntered) {
                playerNameWidth = playerNameText.getLocalBounds().width;
                textX = (win.getSize().x - playerNameWidth) / 2.f;
                playerNameText.setPosition(textX, textY + 50.f);
                if (event.text.unicode < 128 && event.text.unicode != 8) {
                    // Check if the entered character is not a space
                    if (event.text.unicode != ' ') {
                        playerName += static_cast<char>(event.text.unicode);
                        playerNameText.setString(playerName);
                    }
                } else if (event.text.unicode == 8 && !playerName.empty()) {
                    playerName.pop_back();
                    playerNameText.setString(playerName);
                }
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && !playerName.empty()) {
                return;
            }
        }

        win.clear();
        win.draw(bg_sprite);
        win.draw(enterNameText);
        win.draw(pressEnterText);
        win.draw(playerNameText);
        win.display();
    }
}