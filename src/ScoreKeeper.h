#ifndef _SCORE_KEEPER_H_
#define _SCORE_KEEPER_H_

class ScoreKeeper
{
public:
    ScoreKeeper() = default;
    int get() const;
    void set(int new_score);
    void reset();

private:
    int score = 0;
};


#endif // _SCORE_KEEPER_H_
