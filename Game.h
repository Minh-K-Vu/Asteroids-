#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "GameObject.h"
#include "Rocket.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "End.h"

class Game {
private:
 std::vector<GameObject*>& GameObjects;
 std::vector<GameObject*>& objectsToDelete;
 int roundNumber;
 unsigned int randomSeed;
 sf::SoundBuffer collisionBuffer;
 sf::Sound collisionSound;
 sf::SoundBuffer smallCollisionBuffer;
 sf::Sound smallCollisionSound;
 int initialAsteroids = 8;
 sf::Vector2f rocketPosition;
public:
//================================
// CONSTRUCTOR
//================================
 Game(std::vector<GameObject*>& GameObjects, std::vector<GameObject*>& objectsToDelete) : GameObjects(GameObjects), objectsToDelete(objectsToDelete) {
    srand(static_cast<unsigned int>(time(0)));  // Seed random number generator
    randomSeed = rand(); 
    collisionBuffer.loadFromFile("bangLarge.wav");
    collisionSound.setBuffer(collisionBuffer);
    smallCollisionBuffer.loadFromFile("bangMedium.wav");
    smallCollisionSound.setBuffer(smallCollisionBuffer);
    GameObjects.push_back(new Rocket(GameObjects));
    this->roundNumber = 0;
    for (int i = 0; i < initialAsteroids; i++) {
    int randomAsteroid = (rand_r(&randomSeed) % 4) + 1;
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
        randomX = static_cast<float>(rand_r(&randomSeed) % 1200);
        randomY = static_cast<float>(rand_r(&randomSeed) % 1080);
    } while (randomX > exclusionLeftZone && randomX < exclusionRightZone && randomY > exclusionTopZone && randomY < exclusionBottomZone);

    asteroid->setPosition(sf::Vector2f(randomX, randomY)); 

    // Randomize velocity for each asteroid
    float randomVelX = static_cast<float>((rand_r(&randomSeed) % 200) - 100); // Random velocity between -100 and 100
    float randomVelY = static_cast<float>((rand_r(&randomSeed) % 200) - 100);
    
    // Normalize the velocity vector to ensure it has the same speed
    float speed = 80.0f;  // Set a fixed speed for all asteroids
    float magnitude = std::sqrt(randomVelX * randomVelX + randomVelY * randomVelY);  // Calculate magnitude of the velocity vector

    // Set velocity if magnitude is greater than 0 (to avoid division by zero)
    if (magnitude > 0) {
        asteroid->setVelocity(sf::Vector2f(randomVelX / magnitude * speed, randomVelY / magnitude * speed));  // Normalize and set the velocity
    }

    GameObjects.push_back(asteroid);
    }
 };
//================================
// RESET GAME
//================================
 void resetGame() {
    GameObjects.push_back(new Rocket(GameObjects));
    this->roundNumber = 0;
    for (int i = 0; i < initialAsteroids; i++) {
    int randomAsteroid = (rand_r(&randomSeed) % 4) + 1;
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
        randomX = static_cast<float>(rand_r(&randomSeed) % 1200);
        randomY = static_cast<float>(rand_r(&randomSeed) % 1080);
    } while (randomX > exclusionLeftZone && randomX < exclusionRightZone && randomY > exclusionTopZone && randomY < exclusionBottomZone);

    asteroid->setPosition(sf::Vector2f(randomX, randomY)); 

    // Randomize velocity for each asteroid
    float randomVelX = static_cast<float>((rand_r(&randomSeed) % 200) - 100); // Random velocity between -100 and 100
    float randomVelY = static_cast<float>((rand_r(&randomSeed) % 200) - 100);
    
    // Normalize the velocity vector to ensure it has the same speed
    float speed = 80.0f;  // Set a fixed speed for all asteroids
    float magnitude = std::sqrt(randomVelX * randomVelX + randomVelY * randomVelY);  // Calculate magnitude of the velocity vector

    // Set velocity if magnitude is greater than 0 (to avoid division by zero)
    if (magnitude > 0) {
        asteroid->setVelocity(sf::Vector2f(randomVelX / magnitude * speed, randomVelY / magnitude * speed));  // Normalize and set the velocity
    }

    GameObjects.push_back(asteroid);
    }
 };
//================================
// UPDATE MOVEMENT
//================================
 void updateMovement(float deltaTime) {
    for (auto& object : GameObjects) {
        object->updateMovement(deltaTime);
    }
 };
//================================
// CHECK ROCKET COLLISION
//================================
 bool checkRocketCollision(float deltaTime) {
   bool status = false;
   for (size_t i = 0; i < GameObjects.size(); i++) {
     GameObjects[i]->updateMovement(deltaTime);
     Rocket* rocket = dynamic_cast<Rocket*>(GameObjects[i]);
     if (rocket) {
       rocketPosition = rocket->getPosition();
       sf::FloatRect rocketBounds = rocket->getBoundingBox();
       for (size_t j = 0; j < GameObjects.size(); j++) {
         Asteroid* asteroid = dynamic_cast<Asteroid*>(GameObjects[j]);
         if (asteroid) {
           sf::FloatRect asteroidBounds = asteroid->getBoundingBox();
           if (rocketBounds.intersects(asteroidBounds)) {
             // Bounding boxes intersect, perform detailed collision check
             if (asteroid->checkDetailedCollisionRocket(rocket)) {
               collisionSound.play();
               // Collision detected: mark both objects fordeletion
               objectsToDelete.push_back(GameObjects[i]);
               objectsToDelete.push_back(GameObjects[j]);
               status = true;
               break;
             }
           }
         }
       }
     }
   }
   return status;
 };
//================================
// CHECK BULLET COLLISION
//================================
 bool checkBulletCollision() {
    bool status = false;
    for (int l = 0; l < GameObjects.size(); l++) {
            Bullet* bullet = dynamic_cast<Bullet*>(GameObjects[l]);
            if (bullet) {
                for (size_t k = 0; k < GameObjects.size(); k++) {
                    Asteroid* asteroid = dynamic_cast<Asteroid*>(GameObjects[k]);
                    if (asteroid) {
                        if (asteroid->checkDetailedCollision(bullet)) {
                            smallCollisionSound.play();
                            status = true;
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
                                Asteroid* smallerAsteroid = new Asteroid(((rand_r(&randomSeed) % 4) + 1), asteroid->getSize() + 1);
                                // Set the position of the new asteroid to the position of the original asteroid
                                smallerAsteroid->setPosition(asteroid->getPosition());
                                // Adjust velocity slightly to simulate the asteroids splitting in different directions
                                sf::Vector2f smallerAsteroidVelocity = asteroidVelocity;
                                float smallerAsteroidSpeed = 0.0f;
                                if (i == 0) {
                                    int randomAngle = (rand_r(&randomSeed) % 45) + 1;
                                    smallerAsteroidVelocity = sf::Vector2f(
                                        asteroidVelocity.x * cos(randomAngle * 3.14159f / 180) - asteroidVelocity.y * sin(randomAngle * 3.14159f / 180),
                                        asteroidVelocity.x * sin(randomAngle * 3.14159f / 180) + asteroidVelocity.y * cos(randomAngle * 3.14159f / 180)
                                    );
                                    smallerAsteroidSpeed = static_cast<float>(rand() % static_cast<int>(totalSmallerAsteroidSpeed / 2.0f)) + (totalSmallerAsteroidSpeed / 3);
                                    totalSmallerAsteroidSpeed -= smallerAsteroidSpeed;
                                } else {
                                    int randomAngle = -1 * ((rand_r(&randomSeed) % 45) + 1);
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
                            objectsToDelete.push_back(GameObjects[l]);
                            objectsToDelete.push_back(GameObjects[k]);
                        }
                    }
                }
            }
        }
        return status;
 }
//================================
// CHECK IF THERE ARE NO MORE ASTEROIDS
//================================
 bool checkNoAsteroids() {
    bool status = true;
    for (size_t i = 0; i < GameObjects.size(); i++) {
        Asteroid* asteroid = dynamic_cast<Asteroid*>(GameObjects[i]);
        if (asteroid) {
            status = false;
            break;
        }
    }
    return status;
 }
//================================
// NEW ROUND
//================================
 void newRound() {
    roundNumber++;
    for (int i = 0; i < initialAsteroids + roundNumber; i++) {
        int randomAsteroid = (rand_r(&randomSeed) % 4) + 1;
        Asteroid* asteroid = new Asteroid(randomAsteroid, 1);
        // Exclusion Zone where asteroids cannot spawn
        float exclusionLeftZone = rocketPosition.x - 250.0f;
        float exclusionRightZone = rocketPosition.x + 250.0f;
        float exclusionTopZone = rocketPosition.y - 250.0f;
        float exclusionBottomZone = rocketPosition.y + 250.0f;
        float randomX;
        float randomY;
        // Randomize starting position within the window bounds
        do {
            randomX = static_cast<float>(rand_r(&randomSeed) % 1200);
            randomY = static_cast<float>(rand_r(&randomSeed) % 1080);
        } while (randomX > exclusionLeftZone && randomX < exclusionRightZone && randomY > exclusionTopZone && randomY < exclusionBottomZone);

        asteroid->setPosition(sf::Vector2f(randomX, randomY)); 

        // Randomize velocity for each asteroid
        float randomVelX = static_cast<float>((rand_r(&randomSeed) % 200) - 100); // Random velocity between -100 and 100
        float randomVelY = static_cast<float>((rand_r(&randomSeed) % 200) - 100);
        
        // Normalize the velocity vector to ensure it has the same speed
        float speed = 80.0f;  // Set a fixed speed for all asteroids
        float magnitude = std::sqrt(randomVelX * randomVelX + randomVelY * randomVelY);  // Calculate magnitude of the velocity vector

        // Set velocity if magnitude is greater than 0 (to avoid division by zero)
        if (magnitude > 0) {
            asteroid->setVelocity(sf::Vector2f(randomVelX / magnitude * speed, randomVelY / magnitude * speed));  // Normalize and set the velocity
        }
        GameObjects.push_back(asteroid);
    }
}
//================================
// DRAW
//================================
 void draw(sf::RenderWindow& window) {
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
//================================
// DELETE GAME OBJECTS
//================================
 void deleteGameObjects() {
    for (auto& object : GameObjects) {
        delete object;
    }
    GameObjects.clear();
 }
//================================
// REMOVE OBJECTS TO DELETE
//================================
 void removeObjectsToDelete() {
    for (auto obj : objectsToDelete) {
        auto it = std::find(GameObjects.begin(), GameObjects.end(), obj);
        if (it != GameObjects.end()) {
            delete *it;
            GameObjects.erase(it);
            }
        };
        objectsToDelete.clear();
 };
};

#endif