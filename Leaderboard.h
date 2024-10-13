#ifndef LEADERBOARD_H
#define LEADERBOARD_H


#include <SFML/Graphics.hpp>    
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

class Leaderboard {
private:
    std::vector<std::pair<std::string, int>> scores;
    const std::string filename = "leaderboard.txt";
    sf::Font font;
    sf::Text leaderboardText;
    bool status;
public: 
    Leaderboard(){
        font.loadFromFile("slkscre.ttf");
        leaderboardText.setFont(font);
        leaderboardText.setCharacterSize(30);
        leaderboardText.setFillColor(sf::Color::White);
        loadScores();
    };
    void loadScores(){
        std::ifstream file(filename);
        scores.clear();
        std::string name;
        int score;
        while (file >> name >> score) {
            scores.push_back({name, score});
        }
        file.close();
    };
    void saveScores(){
        std::ofstream file(filename);
        for (const auto& score : scores) {
            file << score.first << " " << score.second << std::endl;
        }
        file.close();
    };
    void addScore(const std::string& name, int score){
        scores.push_back(std::make_pair(name, score));

    // Sort by score in descending order
    std::sort(scores.begin(), scores.end(), [](const auto& lhs, const auto& rhs) {
        return lhs.second > rhs.second;
    });

    // Keep only top 10 scores
    if (scores.size() > 10) {
        scores.resize(10);
    }

        saveScores();
    };
    bool isTop10Score(int score){
        if (scores.size() < 10) return true;
        return score > scores[9].second;
    };
    void draw(sf::RenderWindow& window){

        std::string leaderboardString = "Leaderboard\n";
        for (size_t i = 0; i < scores.size(); ++i) {
            leaderboardString += std::to_string(i + 1) + ". " + scores[i].first + " - " + std::to_string(scores[i].second) + "\n";
        }
        leaderboardString += "\nPress ESC to Exit";
        leaderboardText.setString(leaderboardString);
        leaderboardText.setPosition(500, 100);
        window.draw(leaderboardText);
    };
    bool getStatus(){
        return status;
    };
    void setStatus(bool newStatus){
        status = newStatus;
    };
};
#endif