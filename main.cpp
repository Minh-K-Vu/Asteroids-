#include "Rocket.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main()
{
  //-------------------------------- INITIALIZE FRAME --------------------------------
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1200,800), "Asteroids", sf::Style::Default, settings);

	//-------------------------------- INITIALIZE ROCKET --------------------------------
  std::vector <GameObject*> GameObjects{};
  GameObjects.push_back(new Rocket(GameObjects));
  //-------------------------------- INITIALIZE CLOCK ---------------------------------
  sf::Clock clock;
  //-------------------------------- MAIN GAME LOOP -----------------------------------
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      };
    }
  window.clear(sf::Color::Black);
  //-------------------------------- DELTA TIME ----------------------------------------
    sf::Time Time = clock.restart();
    float deltaTime = Time.asSeconds();
  for (size_t i = 0; i < GameObjects.size();) {
    //-------------------------------- ROCKET MOVEMENT -----------------------------------
    GameObjects[i]->updateMovement(deltaTime);
    //-------------------------------- DRAW ROCKET -------------------------------------
    window.draw(GameObjects[i]->getSprite());
    if (GameObjects[i]->deleteStatus() == true) {
      delete GameObjects[i];
      GameObjects.erase(GameObjects.begin() + i);
    } else {
      i++;
    }
  }
  window.display();
  }
  return 0;
}