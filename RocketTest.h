#ifndef ROCKETTEST_H
#define ROCKETTEST_H
#include "Rocket.h"
#include "GameObject.h"
#include <iostream>

class RocketTest {
public:
    // Run all tests for Rocket
    void runTests() {
        std::cout << "--- RUNNING UNIT TESTS: ROCKET.H ---" << std::endl;
        testInitialPosition();
        testForwardMovement();
        testRotation();
        testBulletShooting();
        testBoundingBox();
    }

private:
    // Test initial position of the rocket
    void testInitialPosition() {
        std::vector<GameObject*> gameObjects;
        Rocket rocket(gameObjects);
        sf::Vector2f initialPosition = rocket.getPosition();
        
        if (initialPosition != sf::Vector2f(600, 500)) {
            std::cout << "TEST 1-1 FAILED: INCORRECT INITIAL ROCKET POSITION" << std::endl;
        } else {
            std::cout << "TEST 1-1 PASSED: CORRECT INITIAL POSITION" << std::endl;
        }
    }

    // Test forward movement of the rocket
    void testForwardMovement() {
        std::vector<GameObject*> gameObjects;
        Rocket rocket(gameObjects);
        sf::Vector2f initialPosition = rocket.getPosition();
        rocket.handleInput(sf::Keyboard::W);
        sf::Vector2f updatedPosition = rocket.getPosition();
        if (updatedPosition == initialPosition) {
            std::cout << "TEST 2-1 FAILED: ROCKET DID NOT MOVE FORWARD" << std::endl;
        } else {
            std::cout << "TEST 2-1 PASSED: MOVED" << std::endl;
        }
    }

    // Test rotation of the rocket
    void testRotation() {
        std::vector<GameObject*> gameObjects;
        Rocket rocket(gameObjects);
        float initialRotation = rocket.getRotation();
        rocket.handleInput(sf::Keyboard::D);
        
        if (rocket.getRotation() == initialRotation) {
            std::cout << "TEST 3-1 FAILED: ROCKET DID NOT ROTATE" << std::endl;
        } else {
            std::cout << "TEST 3-1 PASSED: ROTATED" << std::endl;
        }
    }

    // Test bullet shooting from the rocket
    void testBulletShooting() {
        std::vector<GameObject*> gameObjects;
        Rocket rocket(gameObjects);

        int initialBulletCount = gameObjects.size();
        rocket.handleInput(sf::Keyboard::Space);
        
        if (gameObjects.size() == initialBulletCount) {
            std::cout << "TEST 4-1 FAILED: ROCKET DID NOT SHOOT A BULLET" << std::endl;
        } else {
            std::cout << "TEST 4-1 PASSED: SHOOTED" << std::endl;
        }
    }

    // Test bounding box of the rocket
    void testBoundingBox() {
        std::vector<GameObject*> gameObjects;
        Rocket rocket(gameObjects);

        sf::FloatRect boundingBox = rocket.getBoundingBox();
        
        if (boundingBox.width <= 0 || boundingBox.height <= 0) {
            std::cout << "TEST 5-1 FAILED: ROCKET BOUNDING BOX INCORRECT" << std::endl;
        } else {
            std::cout << "TEST 5-1 PASSED: CORRECT BOUNDING BOX" << std::endl;
        }
    }
};
#endif