#include "score_keeper.h"

int ScoreKeeper::getScore() const
{
    return score;
}

void ScoreKeeper::setScore(int new_score)
{
    score = new_score;
}
