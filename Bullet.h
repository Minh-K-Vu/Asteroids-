#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameObject.h"
#include "Rocket.h"
#include <cmath>

class Bullet : public GameObject {
    private:
     sf::Texture bulletTexture;
     sf::Sprite bulletSprite;
     sf::Vector2f bullet_velocity;
     float bullet_speed = 800.0f;
     float angle;
     float max_life_time = 0.9f;
     sf::Vector2f initial_position;
     bool delete_status = false;
     float life_time = 0;
    public:
     Bullet(float angle, sf::Vector2f position) : angle(angle) {
      bulletTexture.loadFromFile("assets/bullet.png"); // Import Bullet Texture
      bulletSprite.setTexture(bulletTexture); // Set Bullet Sprite
      bulletSprite.setScale(2.0f, 2.0f);
      sf::Vector2u textureSize = bulletTexture.getSize(); // Get Size Of Bullet Texture
      bulletSprite.setOrigin(textureSize.x/2.0f, textureSize.y/ 2.0f); // Set Origin To The Center Of Sprite
      initial_position = position;
      bulletSprite.setPosition(position);  // Set Default Location
      bulletSprite.setRotation(angle); // Set Default Rotation
      //-----------
      float radianAngle = angle * 3.14159f / 180.0f;
      sf::Vector2f bullet_direction(cos(radianAngle), sin(radianAngle));
      bullet_velocity = bullet_speed * bullet_direction;
     }
     void updateMovement(float deltaTime) override {
        sf::Vector2f bullet_position = bulletSprite.getPosition();
        bulletSprite.setPosition(bullet_position + bullet_velocity * deltaTime);
        bullet_position = bulletSprite.getPosition();
        if (bullet_position.x > 1200) {
          bulletSprite.setPosition(0, bullet_position.y);
        } else if (bullet_position.x < 0) {
          bulletSprite.setPosition(1200, bullet_position.y);
        }
        if (bullet_position.y > 800) {
          bulletSprite.setPosition(bullet_position.x, 0);
        } else if (bullet_position.y < 0) {
          bulletSprite.setPosition(bullet_position.x, 800);
        }
        life_time += deltaTime;
        if (life_time > max_life_time){
          delete_status = true;
        }
     };
     sf::Sprite getSprite() override {return bulletSprite;};
     bool deleteStatus() override { return delete_status; };
};
#endif
