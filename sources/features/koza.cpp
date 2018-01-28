#include "koza.h"

Koza::Koza(QObject *parent)
    : QObject(parent)
{
}

int Koza::PassedAntenaBoysDistance = 0;
int Koza::LastKozaDistance = 0;
Koza* Koza::theKoza = nullptr;

void Koza::AddAntenaBoysDistance(int xDist, int yDist)
{
    Koza::PassedAntenaBoysDistance += xDist;
    Koza::PassedAntenaBoysDistance += yDist;

    if (Koza::PassedAntenaBoysDistance - Koza::LastKozaDistance > 15000)
    {
        Koza::LastKozaDistance = Koza::PassedAntenaBoysDistance;
        emit Koza::theKoza->showKoza();
    }
}
