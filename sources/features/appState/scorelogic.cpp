#include "scorelogic.h"

ScoreLogic::ScoreLogic(QObject* parent)
    : QObject(parent)
    , m_MAX_LIFE_TIME(3 * 60 * 1000) // 3 * 60 * 1000 // 3min w milisec
    , m_lifeTime(3 * 60 * 1000) //MAX_LIFE_TIME())
    , m_score(0)
    , m_missionsCompleted(0)
{

}

#include <QDebug>
void ScoreLogic::reset()
{
    set_lifeTime(MAX_LIFE_TIME());
    set_score(0);
    set_missionsCompleted(0);
}

void ScoreLogic::onEsbekCatchAntenaBoy()
{
    set_score(score() - 30);
    set_lifeTime(lifeTime() - 20 * 1000); // + 10s
}

void ScoreLogic::onMissionCompleted()
{
    set_score(score() + 100);
    set_missionsCompleted(missionsCompleted() + 1);
    set_lifeTime(lifeTime() + 10 * 1000); // + 10s
}
