#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>

class GameObject {
  private:
  public:
  virtual ~GameObject() = default;
  virtual void updateMovement(float deltaTime) = 0;
  virtual sf::Sprite getSprite() = 0;
  virtual bool deleteStatus() = 0;
};

#endif