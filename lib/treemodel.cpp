#include <QtCore>
#include <QtSql>

#include "treemodel.h"
#include "node.h"
#include "folder.h"

// ---------------------------------------------------------------------------
TreeModel::TreeModel (const QString & sqlite3Filename, QObject *parent)
  : QAbstractItemModel (parent), root (0)  {

  static QSqlDatabase db = QSqlDatabase::addDatabase ("QSQLITE");

  db.setDatabaseName (sqlite3Filename);
  if (db.open()) {

    root = new RootNode (db);
  }
}

// ---------------------------------------------------------------------------
TreeModel::~TreeModel() {

  if (root) {
    
    root->database().close();
  }
}

// ---------------------------------------------------------------------------
bool TreeModel::isOpen() const {
  
  if (root) {
    
    return root->database().isOpen();
  }
  return false;
}

// ---------------------------------------------------------------------------
QSqlError TreeModel::lastError() const {
  
  if (root) {
    
    return root->database().lastError();
  }
  return QSqlError();
}

// ---------------------------------------------------------------------------
QModelIndex TreeModel::index (int row, int column,
                              const QModelIndex &parent) const {
  if (root == 0) {
    return QModelIndex();
  }
  Node *parentNode = nodeFromIndex (parent);
  return createIndex (row, column, parentNode->children() [row]);
}

// ---------------------------------------------------------------------------
QModelIndex TreeModel::parent (const QModelIndex &child) const {

  Node *node = nodeFromIndex (child);
  if (!node) {
    return QModelIndex();
  }
  Node *parentNode = node->parent();
  if (!parentNode) {
    return QModelIndex();
  }
  Node *grandparentNode = parentNode->parent();
  if (!grandparentNode) {
    return QModelIndex();
  }

  int row = grandparentNode->children().indexOf (parentNode);
  return createIndex (row, child.column(), parentNode);
}

// ---------------------------------------------------------------------------
int TreeModel::rowCount (const QModelIndex &parent) const {

  Node *parentNode = nodeFromIndex (parent);
  if (!parentNode) {

    return 0;
  }
  return parentNode->children().count();
}

// ---------------------------------------------------------------------------
int TreeModel::columnCount (const QModelIndex & /* parent */) const {

  return 1;
}

// ---------------------------------------------------------------------------
QVariant TreeModel::data (const QModelIndex &index, int role) const {
  Node * node = nodeFromIndex (index);

  if (node) {
    switch (role) {

      case Qt::DecorationRole:

        return node->icon();
        break;

      case Qt::DisplayRole:
        return node->name();
        break;

      case Qt::ToolTipRole:
        return node->toolTip();
        break;

      default:
        break;
    }
  }

  return QVariant();
}

// ---------------------------------------------------------------------------
QVariant TreeModel::headerData (int section,
                                Qt::Orientation orientation,
                                int role) const {

  if (section == 0 && orientation == Qt::Horizontal) {

    if (role == Qt::DisplayRole) {

      return root->name();
    }
    else if (role == Qt::ToolTipRole) {

      return root->toolTip();
    }
  }
  return QVariant();
}

// ---------------------------------------------------------------------------
Node *TreeModel::nodeFromIndex (const QModelIndex & index) const {

  if (index.isValid()) {

    return static_cast<Node *> (index.internalPointer());
  }
  else {

    return root;
  }
}
