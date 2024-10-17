#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "GameObject.h"
#include "Rocket.h"

#include <cmath>

class Bullet : public GameObject {
    private:
     sf::CircleShape bulletShape;
     sf::Vector2f bullet_velocity;
     float bullet_speed = 800.0f;
     float angle;
     float max_life_time = 1.0f;
     sf::Vector2f initial_position;
     bool delete_status = false;
     float life_time = 0;
     sf::Vector2f bullet_position;
     float bullet_radius = 3.0f;
     sf::SoundBuffer smallCollisionBuffer;
    sf::Sound smallCollisionSound;
    public:
     Bullet(float angle, sf::Vector2f position) : angle(angle) {
      bulletShape.setRadius(bullet_radius);  // Set the radius of the bullet
      bulletShape.setFillColor(sf::Color::White);  // White color
      bulletShape.setOrigin(bullet_radius, bullet_radius);  // Set origin to the center of the circle
      
      float radianAngle = angle * 3.14159f / 180.0f;  // Convert angle to radians
      sf::Vector2f bullet_direction(cos(radianAngle), sin(radianAngle));  // Calculate direction
      bullet_velocity = bullet_speed * bullet_direction;
      smallCollisionBuffer.loadFromFile("Audio/bangMedium.wav");
      smallCollisionSound.setBuffer(smallCollisionBuffer);
      initial_position = position + bullet_direction * 20.0f;  // Offset the bullet from the rocket's position
      bulletShape.setPosition(initial_position);  // Set the initial position of the bullet
     }
     
     void updateMovement(float deltaTime) override {
        bullet_position = bulletShape.getPosition();
        bulletShape.setPosition(bullet_position + bullet_velocity * deltaTime);  // Move the bullet
        bullet_position = bulletShape.getPosition();
        
        // Handle screen wrapping
        if (bullet_position.x > 1200) {
          bulletShape.setPosition(0, bullet_position.y);
        } else if (bullet_position.x < 0) {
          bulletShape.setPosition(1200, bullet_position.y);
        }
        if (bullet_position.y > 1080) {
          bulletShape.setPosition(bullet_position.x, 0);
        } else if (bullet_position.y < 0) {
          bulletShape.setPosition(bullet_position.x, 1080);
        }
        
        // Check if bullet should be deleted after a certain lifetime
        life_time += deltaTime;
        if (life_time > max_life_time) {
          delete_status = true;
        }
     }

     // Get the bullet's current position
     sf::Vector2f getPosition() { 
        return bulletShape.getPosition(); 
     }

     // Get the radius of the bullet for collision detection
     float getRadius() { 
        return bullet_radius; 
     }
     // Play small collision sound
     void playSmallCollisionSound() {
        smallCollisionSound.play();
     }

     // Draw the bullet using the CircleShape
     sf::CircleShape getShape() { 
        return bulletShape; 
     }
     void markForDeletion() { delete_status = true; }
     // Check if the bullet should be deleted
     bool deleteStatus() override { 
        return delete_status; 
     }

};
#endif
