#ifndef SCORE_HPP
#define SCORE_HPP

#include <string>

class Score {
public:
    Score();
    void addPoints(int points);
    int getValue() const;
    std::string getScoreString() const;

private:
    int currentScore;
};

#endif