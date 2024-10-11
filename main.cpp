#include "Asteroid.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>


int main(){
    //-------------------------------- Seed Random Number Generator --------------------
    srand(static_cast<unsigned int>(time(0)));
    //-------------------------------- INITIALIZE FRAME --------------------------------
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1200, 1080), "Asteroids Prototype", sf::Style::Default,settings);

    //-------------------------------- LOAD FONT ----------------------------------------
    sf::Font font;
    font.loadFromFile("slkscre.ttf");
    //-------------------------------- LOAD LARGE COLLISION SOUND -----------------------------
    sf::SoundBuffer collisionBuffer;
    sf::Sound collisionSound;
    collisionBuffer.loadFromFile("bangLarge.wav");
    collisionSound.setBuffer(collisionBuffer);
    //-------------------------------- LOAD Medium COLLISION SOUND ----------------------------------
    sf::SoundBuffer smallCollisionBuffer;
    sf::Sound smallCollisionSound;
    smallCollisionBuffer.loadFromFile("bangMedium.wav");
    smallCollisionSound.setBuffer(smallCollisionBuffer);
    //-------------------------------- LOAD BEAT SOUND ----------------------------------
    sf::SoundBuffer beatBuffer;
    sf::Sound beatSound;
    beatBuffer.loadFromFile("beat2.wav");
    beatSound.setBuffer(beatBuffer);
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
    //-------------------------------- CREATE TITLE SCREEN TEXT --------------------------------
    sf::Text titleText;
    titleText.setFont(font);           // Set the loaded font
    titleText.setCharacterSize(100);    // Set the size of the text
    titleText.setFillColor(sf::Color::White); // Set the color of the text
    titleText.setPosition(275, 375);     // Set the position of the text on the screen
    titleText.setString("Asteroids");
    //-------------------------------- CREATE START SCREEN TEXT --------------------------------
    sf::Text startText;
    startText.setFont(font);           // Set the loaded font
    startText.setCharacterSize(30);    // Set the size of the text
    startText.setFillColor(sf::Color::White); // Set the color of the text
    startText.setPosition(385, 525);     // Set the position of the text on the screen
    startText.setString("Press Enter to Start");
    //-------------------------------- CREATE END SCREEN TEXT --------------------------------
    sf::Text endText;
    endText.setFont(font);           // Set the loaded font
    endText.setCharacterSize(50);    // Set the size of the text
    endText.setFillColor(sf::Color::White); // Set the color of the text
    endText.setPosition(400, 450);     // Set the position of the text on the screen
    endText.setString("Game Over");
    //-------------------------------- CREATE END SCORE TEXT --------------------------------
    sf::Text endScore;
    endScore.setFont(font);           // Set the loaded font
    endScore.setCharacterSize(30);    // Set the size of the text
    endScore.setFillColor(sf::Color::White); // Set the color of the text
    endScore.setPosition(400, 350);     // Set the position of the text on the screen
    //-------------------------------- CREATE RESTART SCREEN TEXT --------------------------------
    sf::Text restartText;
    restartText.setFont(font);           // Set the loaded font
    restartText.setCharacterSize(30);    // Set the size of the text
    restartText.setFillColor(sf::Color::White); // Set the color of the text
    restartText.setPosition(400, 580);     // Set the position of the text on the screen
    restartText.setString("Press Enter to Restart");
    //-------------------------------- INITIALIZE ROCKET --------------------------------
    std::vector<GameObject*> GameObjects{};
    GameObjects.push_back(new Rocket(GameObjects));
    //-------------------------------- INITIALIZE ASTEROIDS -----------------------------
    for (int i = 0; i < 8; i++) {
    int randomAsteroid = (rand() % 4) + 1;
    Asteroid* asteroid = new Asteroid(randomAsteroid, 1);
    // Exclusion Zone where asteroids cannot spawn
    float exclusionLeftZone = 400.0f;
    float exclusionRightZone = 800.0f;
    float exclusionTopZone = 300.0f;
    float exclusionBottomZone = 700.0f;
    float randomX;
    float randomY;
    // Randomize starting position within the window bounds
    do {
        randomX = static_cast<float>(rand() % 1200);
        randomY = static_cast<float>(rand() % 1080);
    } while (randomX > exclusionLeftZone && randomX < exclusionRightZone && randomY > exclusionTopZone && randomY < exclusionBottomZone);

    asteroid->setPosition(sf::Vector2f(randomX, randomY)); 

    // Randomize velocity for each asteroid
    float randomVelX = static_cast<float>((rand() % 200) - 100); // Random velocity between -100 and 100
    float randomVelY = static_cast<float>((rand() % 200) - 100);
    
    // Normalize the velocity vector to ensure it has the same speed
    float speed = 80.0f;  // Set a fixed speed for all asteroids
    float magnitude = std::sqrt(randomVelX * randomVelX + randomVelY * randomVelY);  // Calculate magnitude of the velocity vector

    // Set velocity if magnitude is greater than 0 (to avoid division by zero)
    if (magnitude > 0) {
        asteroid->setVelocity(sf::Vector2f(randomVelX / magnitude * speed, randomVelY / magnitude * speed));  // Normalize and set the velocity
    }

    GameObjects.push_back(asteroid);
    }
    //-------------------------------- INITIALIZE CLOCK ---------------------------------
    sf::Clock clock;
    //-------------------------------- CREATE START SCREEN --------------------------------
    bool startScreen = true;
    bool endScreen = false;
    //-------------------------------- MAIN GAME LOOP -----------------------------------
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter && startScreen == true) {
                    startScreen = false;
                    for (auto obj : GameObjects) {
                        delete obj;
                    }
                    GameObjects.clear();
                    GameObjects.push_back(new Rocket(GameObjects));
                    for (int i = 0; i < 8; i++) {
                    int randomAsteroid = (rand() % 4) + 1;
                    Asteroid* asteroid = new Asteroid(randomAsteroid, 1);
                    // Randomize starting position and velocity (same as before)
                    float exclusionLeftZone = 400.0f;
                    float exclusionRightZone = 800.0f;
                    float exclusionTopZone = 300.0f;
                    float exclusionBottomZone = 700.0f;
                    float randomX;
                    float randomY;

                    // Randomize starting position within the window bounds
                    do {
                        randomX = static_cast<float>(rand() % 1200);
                        randomY = static_cast<float>(rand() % 1080);
                    } while (randomX > exclusionLeftZone && randomX < exclusionRightZone && randomY > exclusionTopZone && randomY < exclusionBottomZone);

                    asteroid->setPosition(sf::Vector2f(randomX, randomY)); 

                    // Randomize velocity for each asteroid
                    float randomVelX = static_cast<float>((rand() % 200) - 100);
                    float randomVelY = static_cast<float>((rand() % 200) - 100);
                    float speed = 80.0f;
                    float magnitude = std::sqrt(randomVelX * randomVelX + randomVelY * randomVelY);

                    if (magnitude > 0) {
                        asteroid->setVelocity(sf::Vector2f(randomVelX / magnitude * speed, randomVelY / magnitude * speed));
                    }

                    GameObjects.push_back(asteroid);
                    }
                } 
                if (event.key.code == sf::Keyboard::Escape && endScreen == false && startScreen == false) {
                    endScreen = true;
                }
                if (event.key.code == sf::Keyboard::Enter && endScreen == true) {
                    score = 0;
                    for (auto obj : GameObjects) {
                        delete obj;
                    }
                    GameObjects.clear();  // Remove all existing game objects
                    // Reinitialize the rocket and asteroids
                    GameObjects.push_back(new Rocket(GameObjects));
                    for (int i = 0; i < 8; i++) {
                    int randomAsteroid = (rand() % 4) + 1;
                    Asteroid* asteroid = new Asteroid(randomAsteroid, 1);
                    // Randomize starting position and velocity (same as before)
                    float exclusionLeftZone = 400.0f;
                    float exclusionRightZone = 800.0f;
                    float exclusionTopZone = 300.0f;
                    float exclusionBottomZone = 700.0f;
                    float randomX;
                    float randomY;

                    // Randomize starting position within the window bounds
                    do {
                        randomX = static_cast<float>(rand() % 1200);
                        randomY = static_cast<float>(rand() % 1080);
                    } while (randomX > exclusionLeftZone && randomX < exclusionRightZone && randomY > exclusionTopZone && randomY < exclusionBottomZone);

                    asteroid->setPosition(sf::Vector2f(randomX, randomY)); 

                    // Randomize velocity for each asteroid
                    float randomVelX = static_cast<float>((rand() % 200) - 100);
                    float randomVelY = static_cast<float>((rand() % 200) - 100);
                    float speed = 80.0f;
                    float magnitude = std::sqrt(randomVelX * randomVelX + randomVelY * randomVelY);

                    if (magnitude > 0) {
                        asteroid->setVelocity(sf::Vector2f(randomVelX / magnitude * speed, randomVelY / magnitude * speed));
                    }

                    GameObjects.push_back(asteroid);
                    }

                    // Hide the end screen and return to the game
                    endScreen = false;
                    startScreen = true;
                }
            }
        }

        //-------------------------------- DELTA TIME ----------------------------------------
        sf::Time Time = clock.restart();
        float deltaTime = Time.asSeconds();

        window.clear(sf::Color::Black);
        if (startScreen == true) {
            window.draw(titleText);
            window.draw(startText);
            for (size_t i = 0; i < GameObjects.size(); i++) {
            // Check if it's an asteroid and draw accordingly
            if (Asteroid* asteroid = dynamic_cast<Asteroid*>(GameObjects[i])) {
                GameObjects[i]->updateMovement(deltaTime);
                asteroid->draw(window);  // Use the Asteroid-specific draw method
            } 
            }
        } else if (endScreen == true) {
            endScore.setString("Score: " + std::to_string(score));
            window.draw(endText);
            window.draw(endScore);
            window.draw(restartText);
        } else {
          //beatSound.play();
          scoreText.setString("Score: " + std::to_string(score));
          window.draw(scoreText);
          window.draw(exitText);
          //-------------------------------- UPDATE AND DRAW ROCKET -----------------------------------
          std::vector<GameObject*> objectsToDelete;
          for (size_t i = 0; i < GameObjects.size(); i++) {
            GameObjects[i]->updateMovement(deltaTime);
            Rocket* rocket = dynamic_cast<Rocket*>(GameObjects[i]);
            if (rocket) {
                sf::FloatRect rocketBounds = rocket->getBoundingBox();
                for (size_t j = 0; j < GameObjects.size(); j++) {
                    Asteroid* asteroid = dynamic_cast<Asteroid*>(GameObjects[j]);
                    if (asteroid) {
                        sf::FloatRect asteroidBounds = asteroid->getBoundingBox();
                        if (rocketBounds.intersects(asteroidBounds)) {
                            // Bounding boxes intersect, perform detailed collision check
                            if (asteroid->checkDetailedCollisionRocket(rocket)) {
                              collisionSound.play();
                              endScreen = true;
                              // Collision detected: mark both objects for
                              // deletion
                              objectsToDelete.push_back(GameObjects[i]);
                              objectsToDelete.push_back(GameObjects[j]);
                              break;
                            }
                        }
                    }   
                }
            }
        }
        // Remove all objects marked for deletion
            for (auto obj : objectsToDelete) {
                auto it = std::find(GameObjects.begin(), GameObjects.end(), obj);
                if (it != GameObjects.end()) {
                delete *it;
                GameObjects.erase(it);
                }
            }
        for (int l = 0; l < GameObjects.size(); l++) {
            Bullet* bullet = dynamic_cast<Bullet*>(GameObjects[l]);
            if (bullet) {
                for (size_t k = 0; k < GameObjects.size(); k++) {
                    Asteroid* asteroid = dynamic_cast<Asteroid*>(GameObjects[k]);
                    if (asteroid) {
                        if (asteroid->checkDetailedCollision(bullet)) {
                            smallCollisionSound.play();
                            score = score + 10;
                            if (asteroid->getSize() > 0 && asteroid->getSize() < 3) {
                            // Get the velocity of the current asteroid
                            sf::Vector2f asteroidVelocity = asteroid->getVelocity();
                            // Calculate the speed of the asteroid
                            float asteroidSpeed = asteroid->vectorMagnitude(asteroidVelocity);
                            // Increase the speed for smaller asteroids
                            float totalSmallerAsteroidSpeed = asteroidSpeed * 2 + 50;
                            // Generate two new smaller asteroids
                            for (int i = 0; i < 2; i++) {
                                // Create a new asteroid that is one size smaller
                                Asteroid* smallerAsteroid = new Asteroid(((rand() % 4) + 1), asteroid->getSize() + 1);
                                // Set the position of the new asteroid to the position of the original asteroid
                                smallerAsteroid->setPosition(asteroid->getPosition());
                                // Adjust velocity slightly to simulate the asteroids splitting in different directions
                                sf::Vector2f smallerAsteroidVelocity = asteroidVelocity;
                                float smallerAsteroidSpeed = 0.0f;
                                if (i == 0) {
                                    int randomAngle = rand() % 45 + 1;
                                    smallerAsteroidVelocity = sf::Vector2f(
                                        asteroidVelocity.x * cos(randomAngle * 3.14159f / 180) - asteroidVelocity.y * sin(randomAngle * 3.14159f / 180),
                                        asteroidVelocity.x * sin(randomAngle * 3.14159f / 180) + asteroidVelocity.y * cos(randomAngle * 3.14159f / 180)
                                    );
                                    smallerAsteroidSpeed = static_cast<float>(rand() % static_cast<int>(totalSmallerAsteroidSpeed / 2.0f)) + (totalSmallerAsteroidSpeed / 3);
                                    totalSmallerAsteroidSpeed -= smallerAsteroidSpeed;
                                } else {
                                    int randomAngle = -1 * (rand() % 45 + 1);
                                    // Rotate in the opposite direction for the second smaller asteroid
                                    smallerAsteroidVelocity = sf::Vector2f(
                                        asteroidVelocity.x * cos(randomAngle * 3.14159f / 180) - asteroidVelocity.y * sin(randomAngle * 3.14159f / 180),
                                        asteroidVelocity.x * sin(randomAngle * 3.14159f / 180) + asteroidVelocity.y * cos(randomAngle * 3.14159f / 180)
                                    );
                                    smallerAsteroidSpeed = totalSmallerAsteroidSpeed;
                                }
                                // Scale the velocity for the smaller asteroid
                                smallerAsteroidVelocity = (smallerAsteroidVelocity / asteroidSpeed) * smallerAsteroidSpeed;
                                // Set the velocity of the smaller asteroid
                                smallerAsteroid->setVelocity(smallerAsteroidVelocity);
                                // Add the smaller asteroid to the game objects list
                                GameObjects.push_back(smallerAsteroid);
                            }
                            }
                                // Collision detected: mark both objects for deletion
                                delete GameObjects[l];
                                GameObjects.erase(GameObjects.begin() + l);
                                l--;  // Adjust the index after removal
                                delete GameObjects[k];
                                GameObjects.erase(GameObjects.begin() + k);
                                k--;  // Adjust the index after removal
                                break;  // Stop checking other edges for this bullet
                        }
                    }
                }
            }
        }

        for (size_t i = 0; i < GameObjects.size(); i++) {
            // Check if it's an asteroid and draw accordingly
            if (Asteroid* asteroid = dynamic_cast<Asteroid*>(GameObjects[i])) {
                asteroid->draw(window);  // Use the Asteroid-specific draw method
            } 
            // Check if it's a bullet and draw using CircleShape
            else if (Bullet* bullet = dynamic_cast<Bullet*>(GameObjects[i])) {
                window.draw(bullet->getShape());  // Draw the bullet as a CircleShape
            } 
            // For other game objects like the Rocket, draw them using their sprite
            else if (Rocket* rocket = dynamic_cast<Rocket*>(GameObjects[i])) {
                rocket->draw(window);  // Draw other objects with their sprite
            }

            // Remove any objects that should be deleted
            if (GameObjects[i]->deleteStatus() == true) {
                delete GameObjects[i];
                GameObjects.erase(GameObjects.begin() + i);
                i--; // Adjust index after removal
            }
        }
        }
        //-------------------------------- DISPLAY WINDOW -------------------------------------
        window.display();
    }

    //-------------------------------- CLEANUP -------------------------------------------
    // Cleanup any remaining GameObjects (e.g., if the window is closed)
    for (auto obj : GameObjects) {
        delete obj;
    }
    return 0;
}
