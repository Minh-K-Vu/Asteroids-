#ifndef ASTEROID_H
#define ASTEROID_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "GameObject.h"
#include "Rocket.h"
#include "Bullet.h"
using namespace std;

class Asteroid : public GameObject {
  private:
    sf::ConvexShape asteroidShape;
    sf::Vector2f position;
    sf::Vector2f asteroid_velocity;
    float scaleFactor = 8.0f;
    float turn_speed = 20.0f;
    bool delete_status;
    int size;
    // Set the origin of the shape to its center
    void setAsteroidOrigin() {
    // Calculate the centroid of the convex shape
    sf::Vector2f centroid(0.f, 0.f);
    int pointCount = asteroidShape.getPointCount();
    
    for (int i = 0; i < pointCount; ++i) {
        centroid += asteroidShape.getPoint(i);
    }
    
    centroid.x /= pointCount;
    centroid.y /= pointCount;
    
    asteroidShape.setOrigin(centroid);  // Set the origin to the centroid
}
    // Function to create asteroid shapes
    void createAsteroidShape1() {
        asteroidShape.setPointCount(6);
        asteroidShape.setPoint(0, sf::Vector2f(0 * scaleFactor, 0 * scaleFactor));
        asteroidShape.setPoint(1, sf::Vector2f(6 * scaleFactor, 10 * scaleFactor));
        asteroidShape.setPoint(2, sf::Vector2f(16 * scaleFactor, 6 * scaleFactor));
        asteroidShape.setPoint(3, sf::Vector2f(20 * scaleFactor, -4 * scaleFactor));
        asteroidShape.setPoint(4, sf::Vector2f(10 * scaleFactor, -10 * scaleFactor));
        asteroidShape.setPoint(5, asteroidShape.getPoint(0));
        setAsteroidOrigin(); // Set origin after points are defined
    }

    void createAsteroidShape2() {
        asteroidShape.setPointCount(9);
        asteroidShape.setPoint(0, sf::Vector2f(0 * scaleFactor, 0 * scaleFactor));
        asteroidShape.setPoint(1, sf::Vector2f(10 * scaleFactor, 10 * scaleFactor));
        asteroidShape.setPoint(2, sf::Vector2f(20 * scaleFactor, 5 * scaleFactor));
        asteroidShape.setPoint(3, sf::Vector2f(20 * scaleFactor, 0 * scaleFactor));
        asteroidShape.setPoint(4, sf::Vector2f(16 * scaleFactor, -4 * scaleFactor));
        asteroidShape.setPoint(5, sf::Vector2f(18 * scaleFactor, -8 * scaleFactor));
        asteroidShape.setPoint(6, sf::Vector2f(10 * scaleFactor, -10 * scaleFactor));
        asteroidShape.setPoint(7, sf::Vector2f(2 * scaleFactor, -8 * scaleFactor));
        asteroidShape.setPoint(8, asteroidShape.getPoint(0));
        setAsteroidOrigin(); // Set origin after points are defined
    }

    void createAsteroidShape3() {
        asteroidShape.setPointCount(8);
        asteroidShape.setPoint(0, sf::Vector2f(0 * scaleFactor, 0 * scaleFactor));
        asteroidShape.setPoint(1, sf::Vector2f(6 * scaleFactor, 10 * scaleFactor));
        asteroidShape.setPoint(2, sf::Vector2f(20 * scaleFactor, 4 * scaleFactor));
        asteroidShape.setPoint(3, sf::Vector2f(20 * scaleFactor, 0 * scaleFactor));
        asteroidShape.setPoint(4, sf::Vector2f(16 * scaleFactor, -10 * scaleFactor));
        asteroidShape.setPoint(5, sf::Vector2f(5 * scaleFactor, -10 * scaleFactor));
        asteroidShape.setPoint(6, sf::Vector2f(5 * scaleFactor, -5 * scaleFactor));
        asteroidShape.setPoint(7, asteroidShape.getPoint(0));
        setAsteroidOrigin(); // Set origin after points are defined
    }

    void createAsteroidShape4() {
        asteroidShape.setPointCount(7);
        asteroidShape.setPoint(0, sf::Vector2f(0 * scaleFactor, 0 * scaleFactor));
        asteroidShape.setPoint(1, sf::Vector2f(6 * scaleFactor, 12 * scaleFactor));
        asteroidShape.setPoint(2, sf::Vector2f(20 * scaleFactor, 8 * scaleFactor));
        asteroidShape.setPoint(3, sf::Vector2f(16 * scaleFactor, 4 * scaleFactor));
        asteroidShape.setPoint(4, sf::Vector2f(20 * scaleFactor, -4 * scaleFactor));
        asteroidShape.setPoint(5, sf::Vector2f(6 * scaleFactor, -8 * scaleFactor));
        asteroidShape.setPoint(6, asteroidShape.getPoint(0));
        setAsteroidOrigin(); // Set origin after points are defined
    }

  public:
    // Constructor that randomly chooses an asteroid shape
    Asteroid(int randomAsteroid, int size) {
        this->size = size;
        if (size == 1) {
            scaleFactor = 8.0f;
        } else if (size == 2) {
            scaleFactor = 4.0f;
        } else if (size == 3) {
            scaleFactor = 2.0f;
        }
        if (randomAsteroid == 1) {
            createAsteroidShape1();
        } else if (randomAsteroid == 2) {
            createAsteroidShape2();
        } else if (randomAsteroid == 3) {
            createAsteroidShape3();
        } else if (randomAsteroid == 4) {
            createAsteroidShape4();
        }
        asteroidShape.setFillColor(sf::Color::Transparent); // Fill color to transparent
        asteroidShape.setOutlineColor(sf::Color::White); // Outline color
        asteroidShape.setOutlineThickness(3); // Set the thickness of the outline
        asteroidShape.setPosition(position); // Set the position of the asteroid
    }
    void setPosition(sf::Vector2f position) { this->position = position; }
    //------------------- **SET VELOCITY** ------------------------
    void setVelocity(sf::Vector2f velocity) {
      this->asteroid_velocity = velocity;
    }
    //------------------- **Get Velocity** ------------------------
    sf::Vector2f getVelocity() {
      return asteroid_velocity;
    }
    // Drawing method for the asteroid
    void draw(sf::RenderTarget& target) const { target.draw(asteroidShape); }

    void updateMovement(float deltaTime) override {
    // Update position based on velocity and delta time
    position = position + asteroid_velocity * deltaTime;
    // Wrap around horizontally if the asteroid goes out of bounds
    if (position.x > 1200) {
        position.x = 0;
    } else if (position.x < 0) {
        position.x = 1200;
    }
    // Wrap around vertically if the asteroid goes out of bounds
    if (position.y > 1080) {
        position.y = 0;
    } else if (position.y < 0) {
        position.y = 1080;  // Fix: should update position.y, not position.x
    }
    // Update the position of the asteroid shape to match the new position
        asteroidShape.setPosition(position);
        float angle = asteroidShape.getRotation() + turn_speed * deltaTime;
        asteroidShape.setRotation(angle);
    }
    const sf::ConvexShape& getAsteroidShape() const { return asteroidShape; }

    //------------------- **GET EDGES** ------------------------
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> getEdges() const {
      std::vector<std::pair<sf::Vector2f, sf::Vector2f>> edges;
      int numberOfPoints = asteroidShape.getPointCount();
      for (int i = 0; i < numberOfPoints; i++){
        sf::Vector2f p1 = asteroidShape.getTransform().transformPoint(asteroidShape.getPoint(i));
        sf::Vector2f p2 = asteroidShape.getTransform().transformPoint(asteroidShape.getPoint((i + 1) % numberOfPoints));
        edges.push_back(std::make_pair(p1, p2));
      }
      return edges;
    }
    sf::FloatRect getBoundingBox() const {
        return asteroidShape.getGlobalBounds();
    }
    //------------------- **GET POINTS** ------------------------
    std::vector<sf::Vector2f> getPoints() const {
        std::vector<sf::Vector2f> points;
        int numberOfPoints = asteroidShape.getPointCount();
        for (int i = 0; i < numberOfPoints; i++) {
            sf::Vector2f point = asteroidShape.getPoint(i);
            points.push_back(point);
        }
        return points;
    }
    //------------------- **CHECK DETAILED COLLISION** ------------------------
    bool checkDetailedCollisionRocket(Rocket* rocket) {
    auto points = rocket->getPoints();
    auto edges = this->getEdges();
    
    for (const auto& point : points) {
        for (const auto& edge : edges) {
            float distance = distanceToLineSegment(point, edge.first, edge.second);
            if (distance <= 5.0f) {
              return true;  // Collision detected
            }
        }
    }
    return false;  // No collision detected
    }
    //------------------- Get Size ----------------------
    int getSize() {
        return size;
    }
    //------------------- Get Position ----------------------
    sf::Vector2f getPosition() {
        return position;
    }
    
    bool checkDetailedCollision(Bullet* bullet) {
    auto edges = this->getEdges();
    auto bulletPosition = bullet->getPosition();
    float bulletRadius = bullet->getRadius();
    for (const auto& edge : edges) {
        float distance = distanceToLineSegment(bulletPosition, edge.first, edge.second);
        if (distance <= bulletRadius) {
            return true;  // Collision detected
        }
    }
    return false;  // No collision detected
    }
    
    void markForDeletion() {
        delete_status = true;
    }
    bool deleteStatus() override { return delete_status; }; // Placeholder for delete status
};

#endif
