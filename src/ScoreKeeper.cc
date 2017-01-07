#include "ScoreKeeper.h"

int ScoreKeeper::get() const
{
    return score;
}

void ScoreKeeper::set(int new_score)
{
    score = new_score;
}

void ScoreKeeper::reset()
{
    score = 0;
}
