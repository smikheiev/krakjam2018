#ifndef OBJECTIVESLISTMODEL_H
#define OBJECTIVESLISTMODEL_H

#include <QAbstractListModel>

#include "../map/objectivemodel.h"

class ObjectivesListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    ObjectivesListModel(QObject* parent = 0);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    void add(ObjectiveModel* objectiveModel);
    void remove(ObjectiveModel* objectiveModel);
    void removeAt(int index);
    ObjectiveModel* at(int index);

private:
    QList<ObjectiveModel*> mObjectivesList;
};

#endif // OBJECTIVESLISTMODEL_H
