#ifndef END_H
#define END_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "GameObject.h"
#include "Rocket.h"
#include "Bullet.h"

class End {
private:
 sf::Font font;
 sf::Text endText;
 sf::Text restartText;
 sf::Text endScore;
 bool status = false;

public:
 End(){
    font.loadFromFile("slkscre.ttf");
    //Set the end text
    endText.setFont(font);           // Set the loaded font
    endText.setCharacterSize(50);    // Set the size of the text
    endText.setFillColor(sf::Color::White); // Set the color of the text
    endText.setPosition(400, 450);     // Set the position of the text on the screen
    endText.setString("Game Over");
    //Set the restart text
    restartText.setFont(font);           // Set the loaded font
    restartText.setCharacterSize(30);    // Set the size of the text
    restartText.setFillColor(sf::Color::White); // Set the color of the text
    restartText.setPosition(400, 580);     // Set the position of the text on the screen
    restartText.setString("Press Enter to Restart");
    //Set the end score text
    endScore.setFont(font);
    endScore.setCharacterSize(30);
    endScore.setFillColor(sf::Color::White);
    endScore.setPosition(400, 350);
 };
 // Draw the end screen
 void draw(sf::RenderWindow& window){
    window.draw(endText);
    window.draw(restartText);
    window.draw(endScore);
 };
 // Get the status of the end screen
 bool getStatus(){
    return status;
 }
 // Set the status of the end screen
 void setStatus(bool newStatus){
    status = newStatus;
 }
 // Set the score of the end screen
 void setScore(int newScore){
    endScore.setString("Score: " + std::to_string(newScore));
 }
};


#endif