#include "spinacz.h"
#include "qmltypesregistrator.h"

#include <QEvent>
#include <QKeyEvent>

Spinacz::Spinacz(QObject *parent)
    : QObject(parent)
    , mFeaturesRoot(new FeaturesRoot(this))
{
    QmlTypesRegistrator::registerTypes();
}

FeaturesRoot* Spinacz::featuresRoot() const
{
    return mFeaturesRoot;
}

#include <QDebug>
bool Spinacz::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched);

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if (keyEvent->key() == Qt::Key_W || keyEvent->key() == Qt::Key_Up
                || keyEvent->key() == Qt::Key_A || keyEvent->key() == Qt::Key_Left
                || keyEvent->key() == Qt::Key_S || keyEvent->key() == Qt::Key_Down
                || keyEvent->key() == Qt::Key_D || keyEvent->key() == Qt::Key_Right) {
            featuresRoot()->gameplay()->charactersLogic()->moveKeyPressed(keyEvent->key());
            return true;
        }

        if (keyEvent->key() == Qt::Key_1 || keyEvent->key() == Qt::Key_2
                || keyEvent->key() == Qt::Key_3) {
            featuresRoot()->gameplay()->charactersLogic()->changSelectedAntenaBoy(keyEvent->key());
            return true;
        }
    }

    if (event->type() == QEvent::KeyRelease) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if (keyEvent->key() == Qt::Key_W || keyEvent->key() == Qt::Key_Up
                || keyEvent->key() == Qt::Key_A || keyEvent->key() == Qt::Key_Left
                || keyEvent->key() == Qt::Key_S || keyEvent->key() == Qt::Key_Down
                || keyEvent->key() == Qt::Key_D || keyEvent->key() == Qt::Key_Right) {
            featuresRoot()->gameplay()->charactersLogic()->moveKeyReleased(keyEvent->key());
            return true;
        }
    }

    return QObject::eventFilter(watched, event);
}
