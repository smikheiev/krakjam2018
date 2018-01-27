#include "objectiveslistmodel.h"

ObjectivesListModel::ObjectivesListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

int ObjectivesListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return mObjectivesList.count();
}

QVariant ObjectivesListModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role)

    if (index.row() < 0 || index.row() >= mObjectivesList.count())
    {
        return QVariant();
    }

    ObjectiveModel* objectiveModel = mObjectivesList.at(index.row());
    return QVariant::fromValue<ObjectiveModel*>(objectiveModel);
}

void ObjectivesListModel::add(ObjectiveModel *objectiveModel)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
        mObjectivesList.append(objectiveModel);
        endInsertRows();
}

void ObjectivesListModel::remove(ObjectiveModel *objectiveModel)
{
    if (mObjectivesList.contains(objectiveModel))
    {
        removeAt(mObjectivesList.indexOf(objectiveModel));
    }
}

void ObjectivesListModel::removeAt(int index)
{
    if (index < 0 || index >= mObjectivesList.count())
    {
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
        delete mObjectivesList.at(index);
        mObjectivesList.removeAt(index);
        endRemoveRows();
}

ObjectiveModel *ObjectivesListModel::at(int index)
{
    if (index < 0 || index >= mObjectivesList.count())
    {
        return nullptr;
    }
    return mObjectivesList.at(index);
}
