#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QtMath>

class Utils {

public:
    static qreal distance(int posX_1, int posY_1, int posX_2, int posY_2) {
        return qSqrt(qPow(posX_2 - posX_1, 2) + qPow(posY_2 - posY_1, 2));
    }
};

#endif // UTILS_H
