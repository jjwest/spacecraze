#include "score_keeper.h"

int ScoreKeeper::getScore() const
{
    return score;
}

void ScoreKeeper::increaseScore(int increment)
{
    score += increment;
}

void ScoreKeeper::reset()
{
    score = 0;
}
