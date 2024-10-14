#ifndef SPACESLISTMODEL_H
#define SPACESLISTMODEL_H

#include <QAbstractListModel>
#include <space.h>
#include "matrix.h"

class SpacesListModel : public QAbstractListModel
{
    Q_OBJECT

public:

    enum Roles {
        ValueRole = Qt::UserRole,
        IsOpenRole,
    };

    SpacesListModel();
    ~SpacesListModel();
    Q_INVOKABLE void init();


public slots:
    void openSpace(int index);
    void onExploded();

signals:
    void explode();

private:

    Matrix<Space*> _data;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
};

#endif // SPACESLISTMODEL_H
