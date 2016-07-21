#ifndef _SCORE_KEEPER_H_
#define _SCORE_KEEPER_H_

class ScoreKeeper
{
public:
    ScoreKeeper() = default;
    int getScore() const;
    void setScore(int new_score);

private:
    int score = 0;
};


#endif // _SCORE_KEEPER_H_
