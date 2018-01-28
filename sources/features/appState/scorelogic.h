#ifndef SCORELOGIC_H
#define SCORELOGIC_H

#include <QObject>

#include "../../macros.h"

class ScoreLogic : public QObject
{
    Q_OBJECT

    AUTO_Q_PROPERTY_CONSTANT(int, MAX_LIFE_TIME)
    AUTO_Q_PROPERTY(int, lifeTime)
    AUTO_Q_PROPERTY(int, score)
    AUTO_Q_PROPERTY(int, missionsCompleted)

public:
    ScoreLogic(QObject* parent);

    void reset();

public slots:
    void onEsbekCatchAntenaBoy();
    void onMissionCompleted();
    void onAllAntenaBoysAreInJail();
};

#endif // SCORELOGIC_H
