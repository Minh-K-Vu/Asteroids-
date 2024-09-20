#ifndef ROCKET_H
#define ROCKET_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "GameObject.h"
#include "Bullet.h"
#include <vector>

class Rocket : public GameObject {
    private:
     sf::Texture rocketTexture;
     sf::Sprite rocketSprite;
     float angle = 0.0f;
     float turn_speed = 300.0f;
     sf::Vector2u textureSize;
     sf::Vector2f rocket_velocity = {0.0f, 0.0f};
     float rocket_max_speed = 500.0f;
     float rocket_acceleration = 450.0f;
     float friction = 150.0f;
     float bulletCooldown = 0.0f;
     float bulletCooldownTime = 0.4f;
     std::vector<GameObject*>& gameObjects;
    public:
    //------------------- **INITIALIZE ROCKET** -----------------------
     Rocket(std::vector<GameObject*>& gameObjects) : gameObjects(gameObjects) {
      rocketTexture.loadFromFile("assets/spaceship_normal.png"); // Import Rocket Texture
      rocketSprite.setTexture(rocketTexture); // Set Rocket Sprite
      rocketSprite.setScale(2.0f, 2.0f);
      textureSize = rocketTexture.getSize(); // Get Size Of Rocket Texture
      rocketSprite.setOrigin(textureSize.x/2.0f, textureSize.y/ 2.0f); // Set Origin To The Center Of Sprite
      rocketSprite.setPosition(sf::Vector2f(600, 400)); // Set Default Location
      rocketSprite.setRotation(angle); // Set Default Rotation
     }
     //------------------- **UPDATE MOVEMENT** ------------------------
     void updateMovement(float deltaTime) override {
     //---------------------- ROTATION ------------------------------
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
      angle = angle + (turn_speed * deltaTime);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
      angle = angle - (turn_speed * deltaTime);
      }
      rocketSprite.setRotation(angle);
      float radianAngle = angle * 3.14159f / 180.0f;
      sf::Vector2f rocket_direction(cos(radianAngle), sin(radianAngle));
      //------------------- FORWARD MOVEMENT -------------------------
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        rocket_velocity += (rocket_acceleration * rocket_direction * deltaTime);
        float rocket_speed = std::sqrt(rocket_velocity.x * rocket_velocity.x + rocket_velocity.y * rocket_velocity.y);
        if (rocket_speed > rocket_max_speed) {
          rocket_velocity = (rocket_velocity/rocket_speed)* rocket_max_speed;
        }
        rocketTexture.loadFromFile("assets/PSD to PNG conversion.png");
        rocketSprite.setTexture(rocketTexture);
      }
      if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        rocketTexture.loadFromFile("assets/spaceship_normal.png");
        rocketSprite.setTexture(rocketTexture); 
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
      sf::Vector2f rocket_position = rocketSprite.getPosition();
        if (rocket_position.x > 1200) {rocket_position.x = 0;}
        else if (rocket_position.x < 0) {rocket_position.x = 1200;}
        if (rocket_position.y > 800) {rocket_position.y = 0;}
        else if (rocket_position.y < 0) {rocket_position.y = 800;}
        rocketSprite.setPosition(rocket_position + rocket_velocity * deltaTime);
      //---------------------- SHOOTING MECHANISM ------
        if (bulletCooldown > 0) {
            bulletCooldown -= deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && bulletCooldown <= 0.0f) {
          gameObjects.push_back(new Bullet(angle, rocketSprite.getPosition()));
          bulletCooldown = bulletCooldownTime; 
        }
     }
     sf::Sprite getSprite() override { return rocketSprite; };
     bool deleteStatus() override { return false; };
  };

#endif