#include "esbeklogic.h"
#include "../../utils.h"
#include <QDebug>

EsbekLogic::EsbekLogic(MapModel* mapModel, CharactersLogic* charactersLogic, QObject *parent)
    : QObject(parent)
    , mMapModel(mapModel)
    , mCharactersLogic(charactersLogic)
{
    createEsbeks();
}

void EsbekLogic::resetEsbeks()
{
    mEsbekModelsList.clear();
    createEsbeks();
}

void EsbekLogic::createEsbeks() {
    for (int i = 0; i < 2; ++i)
    {
        addEsbekToRandomPosition();
    }

    updateVariantList();
}

void EsbekLogic::addEsbekToRandomPosition() {
    QPoint startPoint = mMapModel->getRandomEsbekStartPosition();
    EsbekModel* esbek = new EsbekModel(mEsbekModelsList.size(), this);
    setEsbekToStartPosition(esbek, startPoint.x(), startPoint.y());
    esbek->set_moveX(1);
    mEsbekModelsList.append(esbek);
}

void EsbekLogic::updateVariantList() {
    QVariantList vl;
    for (int i = 0; i < mEsbekModelsList.count(); ++i)
    {
        vl.append(QVariant::fromValue(mEsbekModelsList.at(i)));
    }
    set_esbekList(vl);
}

void EsbekLogic::tryToCatchAntenaBoyToJail()
{
    for (EsbekModel* esbek : mEsbekModelsList) {
        for (int i = 0; i < mCharactersLogic->mAntenaBoyList.count(); ++i)
        {
            AntenaBoyModel* boy = mCharactersLogic->mAntenaBoyList.at(i);
            if (boy->isInactive()) continue;

            qreal distanse = Utils::distance(esbek->posX(), esbek->posY(), boy->posX(), boy->posY());
            if (distanse < esbek->killRadius())
            {
                mCharactersLogic->catchedByEsbek(boy);

                emit esbekCatchAntenaBoy();

                esbek->lastDirection = getOppositDirection(esbek->lastDirection);
            }
        }
    }

    // sprawdzenie czy przypadkiem wszystkie ziomki nie siedza w wiezieniu
    for (int i = 0; i < mCharactersLogic->mAntenaBoyList.count(); ++i)
    {
        AntenaBoyModel* boy = mCharactersLogic->mAntenaBoyList.at(i);
        if (!boy->isInactive()) {
            return;
        }
    }

    emit allAntenaBoysAreInJail();
}

void EsbekLogic::setEsbekToStartPosition(EsbekModel *esbek, int startX, int startY)
{
    QPoint startPosition = QPoint(startX, startY);
    int posX = startPosition.x() * TILE_SIZE;
    int posY = startPosition.y() * TILE_SIZE;

    esbek->set_posX(posX);
    esbek->set_posY(posY);
}

void EsbekLogic::moveEsbek()
{
    for (EsbekModel* esbek : mEsbekModelsList) {
        moveEsbek(esbek);
    }
}

void EsbekLogic::onObjectiveCompleted()
{
    objectiveCompletedCnt++;
    if (objectiveCompletedCnt % 4 == 3) {
        addEsbekToRandomPosition();
        updateVariantList();
    }
}

void EsbekLogic::moveEsbek(EsbekModel* esbekModel)
{
    tryToCatchAntenaBoyToJail();

    if (esbekModel->posX() % TILE_SIZE != 0 || esbekModel->posY() % TILE_SIZE != 0) {
        setDirectionMove(esbekModel, esbekModel->lastDirection);
        return;
    }

    QVector<EsbekModel::DIRECTION> allPossibleDirections = QVector<EsbekModel::DIRECTION>
            {EsbekModel::UP, EsbekModel::DOWN, EsbekModel::LEFT, EsbekModel::RIGHT};
    QVector<EsbekModel::DIRECTION> directionsToSelectRandom;
    for (int i=0; i<allPossibleDirections.count(); i++) {
        if (allPossibleDirections.at(i) == getOppositDirection(esbekModel->lastDirection)) continue;

        if (canMove(esbekModel, allPossibleDirections.at(i))) {
            directionsToSelectRandom.append(allPossibleDirections.at(i));
        }
    }

    EsbekModel::DIRECTION directionToMove = EsbekModel::DIRECTION::NONE;
    if (directionsToSelectRandom.size() == 0)
    {
        directionToMove = getOppositDirection(esbekModel->lastDirection);
    }
    else
    {
        int randomIndex = (qrand() % directionsToSelectRandom.count());
        directionToMove = directionsToSelectRandom.at(randomIndex);
    }

    setDirectionMove(esbekModel, directionToMove);
}

EsbekModel::DIRECTION EsbekLogic::getOppositDirection(EsbekModel::DIRECTION direction) {
    switch (direction) {
        case EsbekModel::UP:
            return EsbekModel::DOWN;
        case EsbekModel::DOWN:
            return EsbekModel::UP;
        case EsbekModel::RIGHT:
            return EsbekModel::LEFT;
        case EsbekModel::LEFT:
            return EsbekModel::RIGHT;
        default:
            return EsbekModel::NONE;
    }
}

void EsbekLogic::setDirectionMove(EsbekModel* esbekModel, EsbekModel::DIRECTION directionMove)
{
    esbekModel->set_moveX(0);
    esbekModel->set_moveY(0);

    esbekModel->lastDirection = directionMove;

    int newPosX;
    int newPosY;
    switch (directionMove) {
        case EsbekModel::LEFT:
            esbekModel->set_moveX(-1);
            newPosX = esbekModel->posX() - ESBEK_SPEED;
            if (newPosX < 0) {
                newPosX = 0;
            }
            esbekModel->set_posX(newPosX);
            break;
        case EsbekModel::RIGHT:
            esbekModel->set_moveX(1);
            esbekModel->set_posX(esbekModel->posX() + ESBEK_SPEED);
            break;
        case EsbekModel::UP:
            esbekModel->set_moveY(-1);
            newPosY = esbekModel->posY() - ESBEK_SPEED;
            if (newPosY < 0) {
                newPosY = 0;
            }
            esbekModel->set_posY(newPosY);
            break;
        case EsbekModel::DOWN:
            esbekModel->set_moveY(1);
            esbekModel->set_posY(esbekModel->posY() + ESBEK_SPEED);
            break;
        default:
            qDebug() << "ERROR ERROR ERROR !!!!!!!!!!!!!!!!";
            break;
    }
}

bool EsbekLogic::canMove(EsbekModel* esbekModel, EsbekModel::DIRECTION direction) {
    switch (direction) {
        case EsbekModel::UP:
            return canMoveUp(esbekModel);
        case EsbekModel::DOWN:
            return canMoveDown(esbekModel);
        case EsbekModel::RIGHT:
            return canMoveRight(esbekModel);
        case EsbekModel::LEFT:
            return canMoveLeft(esbekModel);
        default:
            return false;
    }
}

bool EsbekLogic::canMoveUp(EsbekModel* esbekModel)
{
    if (esbekModel->posY() - ESBEK_SPEED < 0) return false;
    return mMapModel->tryToMove(esbekModel->posX(), esbekModel->posY() - ESBEK_SPEED, TILE_SIZE);
}

bool EsbekLogic::canMoveDown(EsbekModel* esbekModel)
{
    return mMapModel->tryToMove(esbekModel->posX(), esbekModel->posY() + ESBEK_SPEED, TILE_SIZE);
}

bool EsbekLogic::canMoveLeft(EsbekModel* esbekModel)
{
    if (esbekModel->posX() - ESBEK_SPEED < 0) return false;
    return mMapModel->tryToMove(esbekModel->posX() - ESBEK_SPEED, esbekModel->posY(), TILE_SIZE);
}

bool EsbekLogic::canMoveRight(EsbekModel* esbekModel)
{
    return mMapModel->tryToMove(esbekModel->posX() + ESBEK_SPEED, esbekModel->posY(), TILE_SIZE);
}

