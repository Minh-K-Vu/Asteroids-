#ifndef GAMEOBJECTTEST_H
#define GAMEOBJECTTEST_H

#include <iostream>
#include "GameObject.h"
#include "Asteroid.h"

class gameObjectTest {
public: 
	// Run all tests for GameObject
	void runTests() {
		std::cout << "--- RUNNING UNIT TESTS: GAMEOBJECT.H ---" << std::endl;
		testMagnitude();
		testDistance();
	}
private:
	// Test vector magnitude calculation
	void testMagnitude() {
		Asteroid test(1, 1);
		if (test.vectorMagnitude({ -1,1 }) - sqrt(2) > 0.0001) {
			std::cout << "TEST 1-1 FAILED: INCORRECT VECTOR MAGNITUDE CALCULATION" << std::endl;
			return;
		}
		else {
			std::cout << "TEST 1-1 PASSED" << std::endl;
		}
	}
	// Test distance to line segment calculation
	void testDistance() {
		Asteroid test(1, 1);
		if (test.distanceToLineSegment({ 0,0 }, { 1,-1 }, { 1,1 }) != 1) {
			std::cout << "TEST 2-1 FAILED: INCORRECT DISTANCE TO LINE SEGMENT CALCULATION" << std::endl;
		}
		else {
			std::cout << "TEST 2-1 PASSED" << std::endl;
		}
	}
};
#endif