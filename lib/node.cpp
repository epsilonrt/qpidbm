#include "node_p.h"
#include "folder.h"

// -----------------------------------------------------------------------------
//                          Abstract Class Node
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
NodePrivate::NodePrivate (Node * q) : q_ptr (q) {}

// -----------------------------------------------------------------------------
NodePrivate::~NodePrivate() {
  qDeleteAll (children);
}

// -----------------------------------------------------------------------------
// protected
Node::Node (NodePrivate &dd) : d_ptr (&dd) {}

// -----------------------------------------------------------------------------
Node::Node () : d_ptr (new NodePrivate (this))  {}

// -----------------------------------------------------------------------------
Node::~Node() {}

// -----------------------------------------------------------------------------
const QList<Node *> & Node::children() const {

  return d_ptr->children;
}

// -----------------------------------------------------------------------------
void Node::append (Node * child) {

  d_ptr->children.append (child);
}

// -----------------------------------------------------------------------------
void Node::clearChildren() {
  Q_D (Node);

  if (!d->children.isEmpty()) {

    qDeleteAll (d->children);
    d->children.clear();
  }
}

// -----------------------------------------------------------------------------
QSqlDatabase & Node::database() const {

  return  root()->database();
}

// -----------------------------------------------------------------------------
QString Node::name() const {

  return QString();
}

// -----------------------------------------------------------------------------
QString Node::toolTip() const {

  return QString();
}

// -----------------------------------------------------------------------------
QIcon Node::icon() const {

  return QIcon();
}

// -----------------------------------------------------------------------------
//                       Abstract Class ChildNode
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
ChildNodePrivate::ChildNodePrivate (Node * parent, ChildNode * q) :
  NodePrivate (q), parent (parent) { }

// -----------------------------------------------------------------------------
ChildNode::ChildNode (ChildNodePrivate &dd) : Node (dd) {}

// -----------------------------------------------------------------------------
ChildNode::ChildNode (Node * parent) :
  Node (* new ChildNodePrivate (parent, this)) {}

// -----------------------------------------------------------------------------
Node * ChildNode::parent() const {
  Q_D (const ChildNode);

  return  d->parent;
}

// -----------------------------------------------------------------------------
const RootNode * ChildNode::root() const {
  Q_D (const ChildNode);

  if (d->parent) {
    return  d->parent->root();
  }
  return 0;
}

// -----------------------------------------------------------------------------
//                       Abstract Class PropertyNode
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
PropertyNodePrivate::PropertyNodePrivate (Property * data, Node * parent, PropertyNode * q) :
  ChildNodePrivate (parent, q), data (data) { }

// -----------------------------------------------------------------------------
PropertyNode::PropertyNode (PropertyNodePrivate &dd) : ChildNode (dd) {}

// -----------------------------------------------------------------------------
PropertyNode::PropertyNode (Property * data, Node * parent) :
  ChildNode (* new PropertyNodePrivate (data, parent, this)) {}

// -----------------------------------------------------------------------------
Property * PropertyNode::data() const {
  Q_D (const PropertyNode);

  return  d->data;
}

// -----------------------------------------------------------------------------
QString PropertyNode::name() const {
  Q_D (const PropertyNode);

  return  d->data->name();
}

// -----------------------------------------------------------------------------
QString PropertyNode::toolTip() const {
  Q_D (const PropertyNode);

  return  d->data->toolTip();
}

// -----------------------------------------------------------------------------
QIcon PropertyNode::icon() const {
  Q_D (const PropertyNode);

  return  d->data->icon();
}

// -----------------------------------------------------------------------------
Record::Type PropertyNode::type() const {
  Q_D (const PropertyNode);

  return  d->data->type();
}

// -----------------------------------------------------------------------------
//                          Class RootNode
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
RootNodePrivate::RootNodePrivate (QSqlDatabase & db, RootNode * q) :
  NodePrivate (q), database (db) { }

// -----------------------------------------------------------------------------
RootNode::RootNode (RootNodePrivate &dd) : Node (dd) {}

// -----------------------------------------------------------------------------
RootNode::RootNode (QSqlDatabase & database) :
  Node (* new RootNodePrivate (database, this)) {

  getChildren();
}

// -----------------------------------------------------------------------------
QString RootNode::name() const {
  QSqlDatabase & db = database();

  if (db.hostName().isEmpty()) {
    QFileInfo finfo (db.databaseName());

    if (finfo.exists()) {

      return finfo.fileName();
    }
  }
  else {

    return db.databaseName();
  }

  return QString();
}

// -----------------------------------------------------------------------------
QString RootNode::toolTip() const {
  QSqlDatabase & db = database();

  if (db.hostName().isEmpty()) {
    QFileInfo finfo (db.databaseName());

    if (finfo.exists()) {
      return QString ("%1:/%2").arg (db.driverName().toLower()).arg (finfo.absolutePath());
    }
  }
  else {
    return QString ("%1://%2@%3:%4").arg (db.driverName().toLower()).arg (db.userName()).arg (db.hostName()).arg (db.port());
  }

  return QString();
}

// -----------------------------------------------------------------------------
QSqlDatabase & RootNode::database() const {
  Q_D (const RootNode);

  return  d->database;
}

// -----------------------------------------------------------------------------
void RootNode::getChildren() {

  clearChildren();
  append (new ManufacturerFolderNode (QObject::tr ("Manufacturer"), this));
  append (new SocFolderNode (QObject::tr ("Soc"), this));
  append (new ConnectorFolderNode (QObject::tr ("Connector"), this));
  append (new GpioFolderNode (QObject::tr ("Gpio"), this));
  append (new BoardFolderNode (QObject::tr ("Board"), this));
}
