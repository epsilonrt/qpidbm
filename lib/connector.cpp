#include "node_p.h"
#include "property_p.h"
#include "connector.h"

// -----------------------------------------------------------------------------
//                          Class ConnectorPrivate
// -----------------------------------------------------------------------------
class ConnectorPrivate : public PropertyPrivate {

  public:
    ConnectorPrivate (QSqlDatabase & database, Connector * q) :
      PropertyPrivate (database, q),
      family (database), rows (-1)
    {}
    ConnectorFamily family;
    int rows;
    Q_DECLARE_PUBLIC (Connector);
};

// -----------------------------------------------------------------------------
//                          Class Connector
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
Connector::Connector (ConnectorPrivate &dd) : Property (dd) {}

// -----------------------------------------------------------------------------
Connector::Connector (QSqlDatabase & database) :
  Property (* new ConnectorPrivate (database, this)) {}

// -----------------------------------------------------------------------------
QString Connector::table() const {
  static QString t ("connector");

  return t;
}

// -----------------------------------------------------------------------------
QIcon Connector::icon() const {

  return QIcon (":/images/connector.png");
}

// -----------------------------------------------------------------------------
ConnectorFamily & Connector::family()  {
  Q_D (Connector);

  return d->family;
}

// -----------------------------------------------------------------------------
const ConnectorFamily & Connector::family() const  {
  Q_D (const Connector);

  return d->family;
}

// -----------------------------------------------------------------------------
int Connector::rows() const {
  Q_D (const Connector);

  return d->rows;
}

// -----------------------------------------------------------------------------
bool Connector::readFromDatabase() {
  Q_D (Connector);
  QSqlQuery q (database());

  q.prepare ("SELECT "
             "name,connector_family_id,rows "
             "FROM connector "
             "WHERE id=?");
  q.addBindValue (d->id);
  q.exec();

  if (q.next()) {
    bool hasChanged = false;
    QString name = q.value (0).toString();
    int connector_family_id =  q.value (1).toInt();
    int rows =  q.value (2).toInt();

    if (d->name != name) {
      d->name = name;
      hasChanged = true;
    }
    if (d->family.id() != connector_family_id) {
      d->family.setId (connector_family_id);
      hasChanged = true;
    }
    if (d->rows != rows) {
      d->rows = rows;
      hasChanged = true;
    }
    if (hasChanged) {
      emit changed();
    }
    return true;
  }

  return false;
}

// -----------------------------------------------------------------------------
bool Connector::writeToDatabase() {
  Q_D (const Connector);

  if (isWritable()) {
    QSqlQuery q (database());

    if (exists()) {
      if (hasName()) {
        q.prepare ("UPDATE connector "
                   "SET name=?,connector_family_id=?,rows=? "
                   "WHERE  id=?");
        q.addBindValue (d->name);
        q.addBindValue (d->family.id());
        q.addBindValue (d->rows);
        q.addBindValue (d->id);
      }
    }
    else {
      q.prepare ("INSERT INTO connector "
                 "(id,name,connector_family_id,rows) "
                 "VALUES (?,?,?,?)");
      q.addBindValue (d->id);
      q.addBindValue (d->name);
      q.addBindValue (d->family.id());
      q.addBindValue (d->rows);
    }

    if (q.exec()) {

      emit updated();
      return true;
    }
  }
  return false;
}

// -----------------------------------------------------------------------------
//                          Class ConnectorNode
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
ConnectorNode::ConnectorNode (int id, Node * parent) :
  PropertyNode (new Connector (parent->database()), parent) {

  data()->setId (id);
}

// -----------------------------------------------------------------------------
ConnectorNode::~ConnectorNode() {

  delete data();
}

// -----------------------------------------------------------------------------
Connector * ConnectorNode::data() const {

  return reinterpret_cast<Connector *> (PropertyNode::data());
}

// -----------------------------------------------------------------------------
QString ConnectorNode::name() const {
  
  return QString ("%1 (id=%2)").arg(data()->name()).arg(data()->id());
}

