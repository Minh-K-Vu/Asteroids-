#ifndef ASTEROIDTEST_H
#define ASTEROIDTEST_H
#include "Asteroid.h"
#include <iostream>

class asteroidTest {
public:
	void runTests() {
		std::cout << "--- RUNNING UNIT TESTS: ASTEROID.H ---" << std::endl;
		testVertices();
		testScaleFactor();
		testPosition();
		testVelocity();
	}
private:
// Test the number of vertices in the asteroid shape based on the size
	void testVertices() {
		Asteroid test1(1, 1);
		if (test1.getAsteroidShape().getPointCount() != 6) {
			std::cout << "TEST 1-1 FAILED: ASTEROID SHAPE INCORRECTLY INITIALISED (INCORRECT VERTEX COUNT)" << std::endl;
		}
		else {
			std::cout << "TEST 1-1 PASSED: CORRECT VERTEX COUNT" << std::endl;
		}
		Asteroid test2(2, 1);
		if (test2.getAsteroidShape().getPointCount() != 9) {
			std::cout << "TEST 1-2 FAILED: ASTEROID SHAPE INCORRECTLY INITIALISED (INCORRECT VERTEX COUNT)" << std::endl;
		}
		else {
			std::cout << "TEST 1-2 PASSED: CORRECT VERTEX COUNT" << std::endl;
		}
		Asteroid test3(3, 1);
		if (test3.getAsteroidShape().getPointCount() != 8) {
			std::cout << "TEST 1-3 FAILED: ASTEROID SHAPE INCORRECTLY INITIALISED (INCORRECT VERTEX COUNT)" << std::endl;
		}
		else {
			std::cout << "TEST 1-3 PASSED: CORRECT VERTEX COUNT" << std::endl;
		}
		Asteroid test4(4, 1);
		if (test4.getAsteroidShape().getPointCount() != 7) {
			std::cout << "TEST 1-4 FAILED: ASTEROID SHAPE INCORRECTLY INITIALISED (INCORRECT VERTEX COUNT)" << std::endl;
		} else {
			std::cout << "TEST 1-4 PASSED: CORRECT VERTEX COUNT" << std::endl;
		}
	}
	// Test the scale factor of the asteroid based on the size
	void testScaleFactor() {
		Asteroid test1(1, 1);
		if (test1.getScaleFactor() != 8) {
			std::cout << "TEST 2-1 FAILED: ASTEROID SCALE FACTOR INCORRECTLY INITIALISED" << std::endl;
		}
		else {
			std::cout << "TEST 2-1 PASSED: CORRECT SCALE FACTOR" << std::endl;
		}
		Asteroid test2(1, 2);
		if (test2.getScaleFactor() != 4) {
			std::cout << "TEST 2-2 FAILED: ASTEROID SCALE FACTOR INCORRECTLY INITIALISED" << std::endl;
		}
		else {
			std::cout << "TEST 2-2 PASSED: CORRECT SCALE FACTOR" << std::endl;
		}
		Asteroid test3(1, 3);
		if (test3.getScaleFactor() != 2) {
			std::cout << "TEST 2-3 FAILED: ASTEROID SCALE FACTOR INCORRECTLY INITIALISED" << std::endl;
		}
		else {
			std::cout << "TEST 2-3 PASSED: CORRECT SCALE FACTOR" << std::endl;
		}	
	}
	// Test the position of the asteroid
	void testPosition() {
		Asteroid test1(1, 1);
		sf::Vector2f positionVector = { 320, 480 };
		test1.setPosition(positionVector);
		if (test1.getPosition() != positionVector) {
			std::cout << "TEST 3-1 FAILED: ASTEROID POSITION SETTER/GETTER FAILED" << std::endl;
		}
		else {
			std::cout << "TEST 3-1 PASSED: GOT POSITION" << std::endl;
		}
	}
	// Test the velocity of the asteroid
	void testVelocity() {
		Asteroid test1(1, 1);
		sf::Vector2f velocityVector = { 260, 950 };
		test1.setVelocity(velocityVector);
		if (test1.getVelocity() != velocityVector) {
			std::cout << "TEST 4-1 FAILED: ASTEROID VELOCITY SETTER/GETTER FAILED" << std::endl;
		}
		else {
			std::cout << "TEST 4-1 PASSED: GOT VELOCITY" << std::endl;
		}
	}
};
#endif