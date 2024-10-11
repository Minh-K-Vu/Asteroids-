#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>

class GameObject {
  private:
  public:
  virtual ~GameObject() = default;
  virtual void updateMovement(float deltaTime) = 0;
  virtual bool deleteStatus() = 0;
  float distanceToLineSegment(sf::Vector2f point, sf::Vector2f lineStart, sf::Vector2f lineEnd) {
    float lineLengthSquared = (lineEnd - lineStart).x * (lineEnd - lineStart).x + (lineEnd - lineStart).y * (lineEnd - lineStart).y;
    if (lineLengthSquared == 0.0f) {
      return std::sqrt((point - lineStart).x * (point - lineStart).x + (point - lineStart).y * (point - lineStart).y);  // Return distance to a point
    }
    float t = std::max(0.f, std::min(1.f, ((point - lineStart).x * (lineEnd - lineStart).x + (point - lineStart).y * (lineEnd - lineStart).y) / lineLengthSquared));
    sf::Vector2f projection = lineStart + t * (lineEnd - lineStart);
    return std::sqrt((point - projection).x * (point - projection).x + (point - projection).y * (point - projection).y);
}
  float vectorMagnitude(sf::Vector2f vector) {
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
  }
};

#endif