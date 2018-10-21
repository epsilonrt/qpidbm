#ifndef NODE_PRIVATE_H
#define NODE_PRIVATE_H

#include <QtCore>
#include <QtSql>
#include "node.h"

class NodePrivate {
  public:
    NodePrivate (Node * q);
    virtual ~NodePrivate();

    Node * q_ptr;
    QList<Node *> children;

    Q_DECLARE_PUBLIC (Node)
};

class RootNodePrivate : public NodePrivate {
  public:
    RootNodePrivate (QSqlDatabase & db, RootNode * q);

    QSqlDatabase & database;
    Q_DECLARE_PUBLIC (RootNode);
};

class ChildNodePrivate : public NodePrivate {
  public:
    ChildNodePrivate (Node * parent, ChildNode * q);

    Node * parent;
    Q_DECLARE_PUBLIC (ChildNode);
};

class Property;
class PropertyNodePrivate : public ChildNodePrivate {
  public:
    PropertyNodePrivate (Property * data, Node * parent, PropertyNode * q);

    Property * data;
    Q_DECLARE_PUBLIC (PropertyNode);
};

#endif
