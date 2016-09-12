#include "score_keeper.h"

int ScoreKeeper::get() const
{
    return score;
}

void ScoreKeeper::increase(int increment)
{
    score += increment;
}

void ScoreKeeper::reset()
{
    score = 0;
}
