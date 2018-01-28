#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QVector>

const int TILE_SIZE = 100;

const int ESBEK_SPEED = 1;
const int ESBEK_KILL_RADIUS = 80;

const int ANTENA_BOY_SIZE = 50;
const QVector<int> ANTENA_BOY_RANGE_RADIUSES = QVector<int>{150, 100, 75};
const QVector<int> ANTENA_BOY_SPEEDS = QVector<int>{4, 5, 6};

const int HQ_RANGE_RADIUS = 150;
const int OBJECTIVE_RANGE_RADIUS = 75;

const int ROUND_TIME_MS = 30000;

#endif // CONSTANTS_H
