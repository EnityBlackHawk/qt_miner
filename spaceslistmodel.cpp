#include "spaceslistmodel.h"
#include "minergen.h"


SpacesListModel::SpacesListModel() : QAbstractListModel(nullptr), _data(8, 8)
{

}

SpacesListModel::~SpacesListModel()
{
    for(auto& x : _data) {
        delete x;
    }
}

void SpacesListModel::init()
{
    MinerGen mg(8, 8);
    Matrix<std::unique_ptr<Space>> gen = mg.generate();
    beginInsertRows(QModelIndex(), 0, gen.size() - 1);

    for(int i = 0; i < gen.getLine(); i++) {
        for(int j = 0; j < gen.getColumn(); j++) {
            _data.push_at(i, j, gen(i, j).release());
        }
    }

    endInsertRows();
    emit dataChanged(index(0), index(_data.size() - 1));
}

void SpacesListModel::openSpace(int index_)
{
    bool wasChanged = _data[index_]->open();
    if(wasChanged) {
        emit dataChanged(index(index_), index(index_));
    }
}

int SpacesListModel::rowCount(const QModelIndex &parent) const
{
    return _data.count();
}

QVariant SpacesListModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case ValueRole:
        return _data.at(index.row())->getValue();
    case IsOpenRole:
        return _data.at(index.row())->getIsOpen();
    default:
        return {};
    }
}

QHash<int, QByteArray> SpacesListModel::roleNames() const
{
    return {
        {ValueRole, "value"},
        {IsOpenRole, "isOpen"}
    };
}
