#ifndef ROCKET_H
#define ROCKET_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include "GameObject.h"
#include "Asteroid.h"
#include "Bullet.h"
#include <vector>

class Rocket : public GameObject {
private:
 sf::SoundBuffer thrustBuffer;
 sf::Sound thrustSound;
 float thrustSoundCooldown = 0.0f;
 float thrustSoundCooldownTime = 0.18f;
 sf::SoundBuffer fireBuffer;
 sf::Sound fireSound;
 sf::ConvexShape rocketShape;
 float angle = 0.0f;
 float turn_speed = 300.0f;
 sf::Vector2f rocket_velocity = {0.0f, 0.0f};
 float rocket_max_speed = 500.0f;
 float rocket_acceleration = 450.0f;
 float friction = 150.0f;
 float bulletCooldown = 0.0f;
 float bulletCooldownTime = 0.3f;
 std::vector<GameObject*>& gameObjects;
 float scaleFactor = 1.0f;  // Scaling factor for the rocket shape
 bool delete_status = false;
 // Set the origin of the rocket to the centroid of the convex shape
 void setRocketOrigin() {
   sf::Vector2f centroid(10.0f * scaleFactor, -5.0f * scaleFactor);
   rocketShape.setOrigin(centroid);  // Set the origin to the centroid
    }

    // Create the initial rocket shape
    void createRocket() {
        rocketShape.setPointCount(5);  // Create a triangle-like shape for the rocket
        rocketShape.setPoint(0, sf::Vector2f(0 * scaleFactor, 0 * scaleFactor));      // Tip of the rocket
        rocketShape.setPoint(1, sf::Vector2f(-5 * scaleFactor, 5 * scaleFactor));     // Left point
        rocketShape.setPoint(2, sf::Vector2f(25 * scaleFactor, -5 * scaleFactor));    // Right point
        rocketShape.setPoint(3, sf::Vector2f(-5 * scaleFactor, -15 * scaleFactor));   // Back left
        rocketShape.setPoint(4, sf::Vector2f(0 * scaleFactor, -10 * scaleFactor));    // Back right
        setRocketOrigin();
    }
    // Create the moving rocket shape
    void createMovingRocket() {
        rocketShape.setPointCount(8);
        rocketShape.setPoint(0, sf::Vector2f(0 * scaleFactor, 0 * scaleFactor));
        rocketShape.setPoint(1, sf::Vector2f(-5 * scaleFactor, 5 * scaleFactor));
        rocketShape.setPoint(2, sf::Vector2f(25 * scaleFactor, -5 * scaleFactor));
        rocketShape.setPoint(3, sf::Vector2f(-5 * scaleFactor, -15 * scaleFactor));
        rocketShape.setPoint(4, sf::Vector2f(0 * scaleFactor, -10 * scaleFactor));
        rocketShape.setPoint(5, rocketShape.getPoint(0));
        rocketShape.setPoint(6, sf::Vector2f(-7 * scaleFactor, -5 * scaleFactor));
        rocketShape.setPoint(7, sf::Vector2f(0 * scaleFactor, -10 * scaleFactor));
        setRocketOrigin(); // Set origin after points are defined
     }
     // Calculate center point of convex shape
     sf::Vector2f calculateCenter(const sf::ConvexShape& shape) {
       sf::Vector2f center(0, 0);
       for (int i = 0; i < shape.getPointCount(); i++){
          center += shape.getPoint(i);
       }
       return center / static_cast<float>(shape.getPointCount());
     }
     // Calculate distance between two points
     float distance(const sf::Vector2f& p1, const sf::Vector2f& p2) {
        return std::sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
     }
     // Check if a point is inside a polygon
     bool isPointInsidePolygon(const sf::ConvexShape& polygon, sf::Vector2f& point) {
       int intersection_count = 0;
       for (int i = 0; i < polygon.getPointCount(); i++){
          sf::Vector2f p1 = polygon.getPoint(i) + polygon.getPosition();
          sf::Vector2f p2 = polygon.getPoint((i + 1) % polygon.getPointCount()) + polygon.getPosition();
          if ((point.y > p1.y) != (point.y > p2.y)) {
            float slope = (p2.x - p1.x) / (p2.y - p1.y);
            float xAtY = p1.x + (point.y - p1.y) * slope;
            if (point.x < xAtY) {
              intersection_count++;
            }
          }
       }
       return (intersection_count % 2 == 1);
     }

public:
    // Constructor to initialize the rocket
    Rocket(std::vector<GameObject*>& gameObjects) : gameObjects(gameObjects) {
        thrustBuffer.loadFromFile("thrust.wav"); //Load Thrust Sound
        thrustSound.setBuffer(thrustBuffer);  //Set Thrust Sound
        fireBuffer.loadFromFile("fire.wav"); //Load Fire Sound
        fireSound.setBuffer(fireBuffer); //Set Fire Sound
        createRocket(); // Initialize the rocket shape
        rocketShape.setPosition(sf::Vector2f(600, 500));  // Set default position
        rocketShape.setRotation(angle); // Set default rotation
        rocketShape.setFillColor(sf::Color::Transparent); // Fill color to transparent
        rocketShape.setOutlineColor(sf::Color::White); // Outline color
        rocketShape.setOutlineThickness(2); // Set the thickness of the outline

    }

    //------------------- **UPDATE MOVEMENT** ------------------------
    void updateMovement(float deltaTime) override {
        //---------------------- ROTATION ------------------------------
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            angle = angle + (turn_speed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            angle = angle - (turn_speed * deltaTime);
        }
        rocketShape.setRotation(angle);
        float radianAngle = angle * 3.14159f / 180.0f;
        sf::Vector2f rocket_direction(cos(radianAngle), sin(radianAngle));

        //------------------- FORWARD MOVEMENT -------------------------
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if (thrustSoundCooldown > 0.0f) {
              thrustSoundCooldown -= deltaTime;
            } else {
              thrustSound.play();
              thrustSoundCooldown = thrustSoundCooldownTime;
            }
            rocket_velocity += (rocket_acceleration * rocket_direction * deltaTime);
            float rocket_speed = std::sqrt(rocket_velocity.x * rocket_velocity.x + rocket_velocity.y * rocket_velocity.y);
            if (rocket_speed > rocket_max_speed) {
                rocket_velocity = (rocket_velocity / rocket_speed) * rocket_max_speed;
            }
            createMovingRocket();
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
          createRocket();
        }
        //----------------------- FRICTION -----------------------------
        float rocket_speed = std::sqrt(rocket_velocity.x * rocket_velocity.x + rocket_velocity.y * rocket_velocity.y);
        if (rocket_speed > 0) {
            rocket_velocity *= (1.0f - friction * deltaTime / rocket_speed);
            if (rocket_speed < 0.05f) {
                rocket_velocity = {0.0f, 0.0f};
            }
        }

        //-------------------- UPDATE LOCATION -------------------------
        sf::Vector2f rocket_position = rocketShape.getPosition();
        if (rocket_position.x > 1200) { rocket_position.x = 0; }
        else if (rocket_position.x < 0) { rocket_position.x = 1200; }
        if (rocket_position.y > 1080) { rocket_position.y = 0; }
        else if (rocket_position.y < 0) { rocket_position.y = 1080; }
        rocketShape.setPosition(rocket_position + rocket_velocity * deltaTime);

        //---------------------- SHOOTING MECHANISM --------------------
        if (bulletCooldown > 0) {
            bulletCooldown -= deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && bulletCooldown <= 0.0f) {
          fireSound.play();
          gameObjects.push_back(new Bullet(angle, rocketShape.getPosition()));
          bulletCooldown = bulletCooldownTime;
        }
    }
    //------------------- **GET EDGES** ------------------------
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> getEdges() {
        std::vector<std::pair<sf::Vector2f, sf::Vector2f>> edges;
        for (int i = 0; i < rocketShape.getPointCount(); i++) {
            sf::Vector2f start = rocketShape.getPoint(i) + rocketShape.getPosition();
            sf::Vector2f end = rocketShape.getPoint((i + 1) % rocketShape.getPointCount()) + rocketShape.getPosition();
            edges.push_back(std::make_pair(start, end));
        }
        return edges;
    }
    //------------------- COLLISION DETECTION ------------------------
    // bool checkDetailedCollision(Asteroid* asteroid) {
    // auto points = asteroid->getPoints();
    // auto edges = this->getEdges();
    
    // for (const auto& point : points) {
    //     for (const auto& edge : edges) {
    //         float distance = distanceToLineSegment(point, edge.first, edge.second);
    //         if (distance <= 2.0f) {
    //           return true;  // Collision detected
    //         }
    //     }
    // }
    // return false;  // No collision detected
    // }
    //------------------- **GET BOUNDING BOX** ------------------------
    sf::FloatRect getBoundingBox() const {
        return rocketShape.getGlobalBounds();
    }

    
    std::vector<sf::Vector2f> getPoints() {
    std::vector<sf::Vector2f> points;
    int numberOfPoints = rocketShape.getPointCount();
    for (int i = 0; i < numberOfPoints; i++) {
        // Add the rocket's position to each point to get the global coordinates
        sf::Vector2f rocketPoint = rocketShape.getPoint(i) + rocketShape.getPosition();
        points.push_back(rocketPoint);
    }
    return points;
}

      //------------------- **DRAW THE ROCKET** ------------------------
    void draw(sf::RenderWindow& window) { window.draw(rocketShape); };
    void markForDeletion() { delete_status = true; }
    bool deleteStatus() override { return false; };
};

#endif
