#ifndef RANGESLISTMODEL_H
#define RANGESLISTMODEL_H

#include <QAbstractListModel>

#include "rangemodel.h"

class RangesListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    RangesListModel(QObject* parent = 0);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    void add(RangeModel* rangeModel);
    void removeAt(int index);

private:
    QList<RangeModel*> mRangesList;
};

#endif // RANGESLISTMODEL_H
