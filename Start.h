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
 sf::Text leaderboardText;
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
    //Leaderboard
    leaderboardText.setFont(font);
    leaderboardText.setString("Press Space to View Leaderboard");
    leaderboardText.setCharacterSize(30);
    leaderboardText.setPosition(265, 600);
    leaderboardText.setFillColor(sf::Color::White);
 };
 //Draw the start screen
 void draw(sf::RenderWindow& window){
    window.draw(titleText);
    window.draw(startText);
    window.draw(leaderboardText);
 };
 //Get the status of the start screen
 bool getStatus(){
    return status;
 }
 //Set the status of the start screen
 void setStatus(bool newStatus){
    status = newStatus;
 }
};


#endif