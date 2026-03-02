#include "Score.hpp"

Score::Score() : currentScore(0) {}

void Score::addPoints(int points) {
    currentScore += points;
}

int Score::getValue() const {
    return currentScore;
}

std::string Score::getScoreString() const {
    return "Score: " + std::to_string(currentScore);
}