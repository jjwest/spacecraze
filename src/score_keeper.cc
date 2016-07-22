#include "score_keeper.h"

int ScoreKeeper::getScore() const
{
    return score;
}

void ScoreKeeper::increaseScore(int increment)
{
    score += increment;
}
