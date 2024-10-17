#ifndef BULLET_TEST_H
#define BULLET_TEST_H

#include "Bullet.h"
#include <iostream>

class BulletTest {
public:
    void runTests() {
        std::cout << "--- RUNNING UNIT TESTS: BULLET.H ---" << std::endl;
        testInitialPosition();
        testMovementUpdate();
        testLifetimeAndDeletion();
        testScreenWrapping();
    }

private:
    // Test 1: Check if the bullet is initialized at the correct position
    void testInitialPosition() {
        sf::Vector2f rocketPosition(600, 500);
        float rocketAngle = 45.0f;  // Example angle
        Bullet bullet(rocketAngle, rocketPosition);

        sf::Vector2f initialBulletPosition = bullet.getPosition();

        // Check if the bullet is properly offset from the rocket's initial position
        if (initialBulletPosition == rocketPosition) {
            std::cout << "TEST 1-1 FAILED: BULLET INITIAL POSITION INCORRECT (NOT OFFSET)" << std::endl;
        } else {
            std::cout << "TEST 1-1 PASSED: BULLET INITIAL POSITION CORRECT" << std::endl;
        }
    }

    // Test 2: Verify bullet movement in the correct direction
    void testMovementUpdate() {
        sf::Vector2f rocketPosition(600, 500);
        float rocketAngle = 45.0f;  // Angle in degrees
        Bullet bullet(rocketAngle, rocketPosition);

        // Simulate 1 second of movement
        float deltaTime = 1.0f;
        sf::Vector2f oldPosition = bullet.getPosition();
        bullet.updateMovement(deltaTime);
        sf::Vector2f newPosition = bullet.getPosition();

        // Ensure the bullet moved (position should be different)
        if (oldPosition == newPosition) {
            std::cout << "TEST 2-1 FAILED: BULLET DID NOT MOVE" << std::endl;
        } else {
            std::cout << "TEST 2-1 PASSED: BULLET MOVED CORRECTLY" << std::endl;
        }
    }

    // Test 3: Check if bullet is marked for deletion after its lifetime
    void testLifetimeAndDeletion() {
        sf::Vector2f rocketPosition(600, 500);
        Bullet bullet(45.0f, rocketPosition);

        float deltaTime = 0.5f;  // Simulate 0.5 seconds of updates
        for (int i = 0; i < 3; ++i) {
            bullet.updateMovement(deltaTime);  // Run the update multiple times to simulate time passage
        }

        if (!bullet.deleteStatus()) {
            std::cout << "TEST 3-1 FAILED: BULLET NOT DELETED AFTER EXCEEDING LIFETIME" << std::endl;
        } else {
            std::cout << "TEST 3-1 PASSED: BULLET DELETED AFTER EXCEEDING LIFETIME" << std::endl;
        }
    }

    // Test 4: Ensure the bullet wraps around the screen correctly
    void testScreenWrapping() {
        sf::Vector2f rocketPosition(1195, 500);  // Close to the right edge of the screen
        Bullet bullet(0.0f, rocketPosition);  // Moving to the right

        float deltaTime = 0.1f;
        bullet.updateMovement(deltaTime);  // Update the bullet position

        sf::Vector2f newPosition = bullet.getPosition();
        
        // Check if bullet wraps around to the left side
        if (newPosition.x < 5) {  // Bullet should now be near the left edge
            std::cout << "TEST 4-1 PASSED: BULLET WRAPPED AROUND SCREEN CORRECTLY" << std::endl;
        } else {
            std::cout << "TEST 4-1 FAILED: BULLET DID NOT WRAP AROUND SCREEN" << std::endl;
        }
    }
};

#endif