#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QSqlDatabase>
#include <QSqlError>

class Node;
class TreeModel : public QAbstractItemModel {

  public:
    TreeModel (const QString & sqlite3Filename, QObject *parent = 0);
    ~TreeModel();

    bool isOpen() const;
    QSqlError lastError() const;

    QModelIndex index (int row, int column,
                       const QModelIndex &parent) const;
    QModelIndex parent (const QModelIndex &child) const;

    int rowCount (const QModelIndex &parent) const;
    int columnCount (const QModelIndex &parent) const;
    QVariant data (const QModelIndex &index, int role) const;
    QVariant headerData (int section, Qt::Orientation orientation,
                         int role) const;

  private:
    Node * nodeFromIndex (const QModelIndex &index) const;
    Node * root;
};

#endif
