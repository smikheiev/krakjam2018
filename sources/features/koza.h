#ifndef KOZA_H
#define KOZA_H

#include <QObject>

class Koza : public QObject
{
    Q_OBJECT

public:
    explicit Koza(QObject *parent = nullptr);

    static int PassedAntenaBoysDistance;
    static int LastKozaDistance;
    static void AddAntenaBoysDistance(int xDist, int yDist);

    static Koza* theKoza;

signals:
    void showKoza();
};

#endif // KOZA_H
