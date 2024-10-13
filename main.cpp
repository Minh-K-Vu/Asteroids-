#include "Asteroid.h"
#include "Game.h"
#include "Start.h"
#include "End.h"
#include "Leaderboard.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>

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
    //-------------------------------- CREATE LEADERBOARD --------------------------------
    Leaderboard leaderboard;
    //-------------------------------- INITIALIZE GAME OBJECTS --------------------------------
    std::vector<GameObject*> GameObjects{};
    std::vector<GameObject*> objectsToDelete;
    Game game(GameObjects, objectsToDelete);
    sf::String playerName;
    bool enteringName = false;
    //-------------------------------- INITIALIZE CLOCK ---------------------------------
    sf::Clock clock;
    //-------------------------------- MAIN GAME LOOP -----------------------------------
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            //-------------------------------- ENTER NAME --------------------------------
            if (enteringName && event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8) { // Backspace
                    if (!playerName.isEmpty()) {
                        playerName.erase(playerName.getSize() - 1, 1);  // Remove the last character
                    }
                } 
                else if ((event.text.unicode >= 'A' && event.text.unicode <= 'Z') || // Uppercase letters
                        (event.text.unicode >= 'a' && event.text.unicode <= 'z') || // Lowercase letters
                        (playerName.getSize() < 10)) { // Ensure name length is less than 10
                    playerName += static_cast<char>(event.text.unicode);  // Append character to playerName
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                //-------------------------------- START GAME --------------------------------
                if (event.key.code == sf::Keyboard::Enter && startScreen.getStatus() == true) {
                    startScreen.setStatus(false);
                    game.deleteGameObjects();
                    game.resetGame();
                } 
                //-------------------------------- VIEW LEADERBOARD --------------------------------
                if (event.key.code == sf::Keyboard::Space && startScreen.getStatus() == true) {
                    startScreen.setStatus(false);
                    leaderboard.setStatus(true);
                }
                //-------------------------------- EXIT LEADERBOARD --------------------------------
                if (event.key.code == sf::Keyboard::Escape && leaderboard.getStatus() == true) {
                    leaderboard.setStatus(false);
                    startScreen.setStatus(true);
                }
                //-------------------------------- END GAME --------------------------------
                if (event.key.code == sf::Keyboard::Escape && endScreen.getStatus() == false && startScreen.getStatus() == false) {
                    endScreen.setStatus(true);
                }
                //-------------------------------- ENTER NAME --------------------------------
                if (event.key.code == sf::Keyboard::Return && enteringName == true) {
                    if (playerName != "") {
                    leaderboard.addScore(playerName, score);
                    enteringName = false;
                    playerName = "";
                    score = 0;
                    game.deleteGameObjects();
                    game.resetGame();
                    endScreen.setStatus(false);
                    startScreen.setStatus(true);
                    }
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
        } else if (leaderboard.getStatus() == true) {
            leaderboard.draw(window);
        }
        //-------------------------------- END SCREEN --------------------------------
        else if (endScreen.getStatus() == true) {
            endScreen.setScore(score);
            endScreen.draw(window);
        } 
        //-------------------------------- ENTER NAME SCREEN --------------------------------
        else if (enteringName) {
            sf::Text promptText("Enter your name:", font, 30);
            promptText.setPosition(300, 300);
            window.draw(promptText);

            sf::Text nameText(playerName, font, 30);
            nameText.setPosition(300, 400);
            window.draw(nameText);
        //-------------------------------- GAME SCREEN --------------------------------
        } else {
          //beatSound.play();
          scoreText.setString("Score: " + std::to_string(score));
          window.draw(scoreText);
          window.draw(exitText);
          //-------------------------------- UPDATE AND DRAW GAME OBJECTS --------------------------------
          game.updateMovement(deltaTime);
          if (game.checkRocketCollision(deltaTime) && leaderboard.isTop10Score(score)) {
            enteringName = true;
          }
          else if (game.checkRocketCollision(deltaTime)){
            endScreen.setStatus(true);
          };
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
