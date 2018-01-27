#include "rangeslistmodel.h"

RangesListModel::RangesListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

int RangesListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return mRangesList.count();
}

QVariant RangesListModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role)

    if (index.row() < 0 || index.row() >= mRangesList.count())
    {
        return QVariant();
    }

    RangeModel* rangeModel = mRangesList.at(index.row());
    return QVariant::fromValue<RangeModel*>(rangeModel);
}

void RangesListModel::add(RangeModel *rangeModel)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
        mRangesList.append(rangeModel);
    endInsertRows();
}

void RangesListModel::removeAt(int index)
{
    if (index < 0 || index >= mRangesList.count())
    {
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
        delete mRangesList.at(index);
        mRangesList.removeAt(index);
    endRemoveRows();
}

void RangesListModel::remove(RangeModel *rangeModel)
{
    if (mRangesList.contains(rangeModel))
    {
        removeAt(mRangesList.indexOf(rangeModel));
    }
}

RangeModel *RangesListModel::at(int index)
{
    if (index < 0 || index >= mRangesList.count())
    {
        return nullptr;
    }

    return mRangesList.at(index);
}
