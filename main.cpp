#include "Asteroid.h"
#include "Game.h"
#include "Start.h"
#include "End.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>


int main(){
    //-------------------------------- INITIALIZE FRAME --------------------------------
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1200, 1080), "Asteroids Prototype", sf::Style::Default,settings);
    //-------------------------------- LOAD FONT ----------------------------------------
    sf::Font font;
    font.loadFromFile("slkscre.ttf");
    //-------------------------------- CREATE SCORE TEXT --------------------------------
    sf::Text scoreText;
    scoreText.setFont(font);           // Set the loaded font
    scoreText.setCharacterSize(30);    // Set the size of the text
    scoreText.setFillColor(sf::Color::White); // Set the color of the text
    scoreText.setPosition(10, 10);     // Set the position of the text on the screen
    int score = 0;  // Initialize score variable
    //-------------------------------- CREATE EXIT GAME TEXT --------------------------------
    sf::Text exitText;
    exitText.setFont(font);           // Set the loaded font
    exitText.setCharacterSize(30);    // Set the size of the text
    exitText.setFillColor(sf::Color::White); // Set the color of the text
    exitText.setPosition(800, 10);     // Set the position of the text on the screen
    exitText.setString("Press ESC to Exit");
    //-------------------------------- CREATE START SCREEN --------------------------------
    Start startScreen;
    //-------------------------------- CREATE END SCREEN --------------------------------
    End endScreen;
    //-------------------------------- INITIALIZE GAME OBJECTS --------------------------------
    std::vector<GameObject*> GameObjects{};
    std::vector<GameObject*> objectsToDelete;
    Game game(GameObjects, objectsToDelete);
    //-------------------------------- INITIALIZE CLOCK ---------------------------------
    sf::Clock clock;
    //-------------------------------- MAIN GAME LOOP -----------------------------------
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                //-------------------------------- START GAME --------------------------------
                if (event.key.code == sf::Keyboard::Enter && startScreen.getStatus() == true) {
                    startScreen.setStatus(false);
                    game.deleteGameObjects();
                    game.resetGame();
                } 
                //-------------------------------- END GAME --------------------------------
                if (event.key.code == sf::Keyboard::Escape && endScreen.getStatus() == false && startScreen.getStatus() == false) {
                    endScreen.setStatus(true);
                }
                //-------------------------------- RESTART GAME --------------------------------
                if (event.key.code == sf::Keyboard::Enter && endScreen.getStatus() == true) {
                    score = 0;
                    game.deleteGameObjects();
                    game.resetGame();
                    endScreen.setStatus(false);
                    startScreen.setStatus(true);
                }
            }
        }

        //-------------------------------- DELTA TIME ----------------------------------------
        sf::Time Time = clock.restart();
        float deltaTime = Time.asSeconds();

        window.clear(sf::Color::Black);
        //-------------------------------- START SCREEN --------------------------------
        if (startScreen.getStatus() == true) {
            startScreen.draw(window);
            for (size_t i = 0; i < GameObjects.size(); i++) {
            // Check if it's an asteroid and draw accordingly
            if (Asteroid* asteroid = dynamic_cast<Asteroid*>(GameObjects[i])) {
                GameObjects[i]->updateMovement(deltaTime);
                asteroid->draw(window);  // Use the Asteroid-specific draw method
            } 
            }

        } 
        //-------------------------------- END SCREEN --------------------------------
        else if (endScreen.getStatus() == true) {
            endScreen.setScore(score);
            endScreen.draw(window);
        } 
        //-------------------------------- GAME SCREEN --------------------------------
        else {
          //beatSound.play();
          scoreText.setString("Score: " + std::to_string(score));
          window.draw(scoreText);
          window.draw(exitText);
          //-------------------------------- UPDATE AND DRAW GAME OBJECTS --------------------------------
          endScreen.setStatus(game.checkRocketCollision(deltaTime));
          // Remove all objects marked for deletion
          game.removeObjectsToDelete();
          if (game.checkBulletCollision()) {
              score = score + 10;
          };
          game.removeObjectsToDelete();
          if (game.checkNoAsteroids()) {
              game.newRound();
          }
          game.draw(window);
        };
        //-------------------------------- DISPLAY WINDOW -------------------------------------
        window.display();
    }

    //-------------------------------- CLEANUP -------------------------------------------
    // Cleanup any remaining GameObjects (e.g., if the window is closed)
    game.deleteGameObjects();
    return 0;
}
