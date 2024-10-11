#ifndef START_H
#define START_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "GameObject.h"
#include "Rocket.h"
#include "Bullet.h"

class Start {
private:
 sf::Font font;
 sf::Text titleText;
 sf::Text startText;
 bool status = true;

public:
 Start(){
    font.loadFromFile("slkscre.ttf");
    //Set the title text
    titleText.setFont(font);
    titleText.setString("Asteroids");
    titleText.setCharacterSize(100);
    titleText.setPosition(275, 375);
    titleText.setFillColor(sf::Color::White);
    //Set the start text
    startText.setFont(font);
    startText.setString("Press Enter to Start");
    startText.setCharacterSize(30);
    startText.setPosition(385, 525);
    startText.setFillColor(sf::Color::White);
 };
 void draw(sf::RenderWindow& window){
    window.draw(titleText);
    window.draw(startText);
 };
 bool getStatus(){
    return status;
 }
 void setStatus(bool newStatus){
    status = newStatus;
 }
};


#endif