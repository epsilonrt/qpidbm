#include "node_p.h"
#include "record_p.h"
#include "gpioconnector.h"

// -----------------------------------------------------------------------------
//                          Class GpioConnectorPrivate
// -----------------------------------------------------------------------------
class GpioConnectorPrivate : public RecordPrivate {
  public:
    GpioConnectorPrivate (QSqlDatabase & database, GpioConnector * q) :
      RecordPrivate (database, q), connector (database), gpio (database),
      num (-1)
    {}
    Connector connector;
    Gpio gpio;
    int num;
    Q_DECLARE_PUBLIC (GpioConnector);
};

// -----------------------------------------------------------------------------
//                          Class GpioConnector
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
GpioConnector::GpioConnector (GpioConnectorPrivate &dd) : Record (dd) {}

// -----------------------------------------------------------------------------
GpioConnector::GpioConnector (QSqlDatabase & database) :
  Record (* new GpioConnectorPrivate (database, this)) {}

// -----------------------------------------------------------------------------
QString GpioConnector::table() const {
  static QString t ("gpio_has_connector");

  return t;
}

// -----------------------------------------------------------------------------
QIcon GpioConnector::icon() const {
  Q_D (const GpioConnector);

  return d->connector.icon();
}

// -----------------------------------------------------------------------------
const Gpio & GpioConnector::gpio() const  {
  Q_D (const GpioConnector);

  return d->gpio;
}

// -----------------------------------------------------------------------------
const Connector & GpioConnector::connector() const  {
  Q_D (const GpioConnector);

  return d->connector;
}

// -----------------------------------------------------------------------------
int GpioConnector::number() const {
  Q_D (const GpioConnector);

  return d->num;
}

// -----------------------------------------------------------------------------
void GpioConnector::setNumber (int number) {
  Q_D (GpioConnector);

  d->num = number;
}

// -----------------------------------------------------------------------------
void GpioConnector::setId (int gpioId, int connectorId) {
  Q_D (GpioConnector);

  if (d->connector.exists (connectorId) && d->gpio.exists (gpioId)) {

    d->connector.setId (connectorId);
    d->gpio.setId (gpioId);
    readFromDatabase();
  }
}

// -----------------------------------------------------------------------------
bool GpioConnector::exists () const {
  Q_D (const GpioConnector);
  QSqlQuery q (database());

  q.prepare ("SELECT 1 "
             "FROM gpio_has_connector "
             "WHERE gpio_id=? AND connector_id=?");
  q.addBindValue (d->gpio.id());
  q.addBindValue (d->connector.id());
  q.exec();
  return q.next();
}

// -----------------------------------------------------------------------------
bool GpioConnector::readFromDatabase() {
  Q_D (GpioConnector);
  QSqlQuery q (database());

  q.prepare ("SELECT "
             "num "
             "FROM gpio_has_connector "
             "WHERE gpio_id=? AND connector_id=?");
  q.addBindValue (d->gpio.id());
  q.addBindValue (d->connector.id());
  q.exec();

  if (q.next()) {
    bool hasChanged = false;
    int num =  q.value (0).toInt();

    if (d->num != num) {
      d->num = num;
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
bool GpioConnector::writeToDatabase() {
  Q_D (const GpioConnector);

  QSqlQuery q (database());

  if (exists()) {
    q.prepare ("UPDATE gpio_has_connector "
               "SET num=? "
               "WHERE gpio_id=? AND connector_id=?");
    q.addBindValue (d->num);
    q.addBindValue (d->gpio.id());
    q.addBindValue (d->connector.id());
  }
  else {
    q.prepare ("INSERT INTO gpio_has_connector "
               "(num,gpio_id,connector_id) "
               "VALUES (?,?,?)");
    q.addBindValue (d->num);
    q.addBindValue (d->gpio.id());
    q.addBindValue (d->connector.id());
  }

  if (q.exec()) {

    emit updated();
    return true;
  }
  return false;
}

// -----------------------------------------------------------------------------
bool GpioConnector::deleteToDatabase() {
  Q_D (GpioConnector);
  QSqlQuery q (database());

  q.prepare ("DELETE FROM gpio_has_connector "
             "WHERE gpio_id=? AND connector_id=?");
  q.addBindValue (d->gpio.id());
  q.addBindValue (d->connector.id());
  return q.exec();
}

// -----------------------------------------------------------------------------
//                      Class GpioConnectorNodePrivate
// -----------------------------------------------------------------------------
class GpioConnectorNodePrivate : public ChildNodePrivate {
  public:
    GpioConnectorNodePrivate (int gpioId, int connectorId, Node * parent, GpioConnectorNode * q);
    virtual ~GpioConnectorNodePrivate();
    
    GpioConnector * data;
    Q_DECLARE_PUBLIC (GpioConnectorNode);
};

// -----------------------------------------------------------------------------
GpioConnectorNodePrivate::GpioConnectorNodePrivate (int gpioId, int connectorId, Node * parent, GpioConnectorNode * q) :
  ChildNodePrivate (parent, q), data (new GpioConnector (parent->database())) {
    
  data->setId (gpioId, connectorId);
}

// -----------------------------------------------------------------------------
GpioConnectorNodePrivate::~GpioConnectorNodePrivate () {
  
  delete data;
}

// -----------------------------------------------------------------------------
//                          Class GpioConnectorNode
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
GpioConnectorNode::GpioConnectorNode (GpioConnectorNodePrivate &dd) : ChildNode (dd) {}

// -----------------------------------------------------------------------------
GpioConnectorNode::GpioConnectorNode (int gpioId, int connectorId, Node * parent) :
  ChildNode (* new GpioConnectorNodePrivate (gpioId, connectorId, parent, this)) {}

// -----------------------------------------------------------------------------
GpioConnector * GpioConnectorNode::data() const {
  Q_D (const GpioConnectorNode);

  return  d->data;
}

// -----------------------------------------------------------------------------
QString GpioConnectorNode::name() const {
  Q_D (const GpioConnectorNode);
  
  return QString ("%1 (id=%2)").arg(d->data->connector().name()).arg(d->data->connector().id());
}

// -----------------------------------------------------------------------------
QString GpioConnectorNode::toolTip() const {
  Q_D (const GpioConnectorNode);

  QString str = QString ("#%1").arg(d->data->number());
  if (! d->data->toolTip().isEmpty()) {
    str += QChar('\n') + d->data->toolTip();
  }
  return str;
}

// -----------------------------------------------------------------------------
QIcon GpioConnectorNode::icon() const {
  Q_D (const GpioConnectorNode);

  return  d->data->icon();
}

// -----------------------------------------------------------------------------
Record::Type GpioConnectorNode::type() const {
  Q_D (const GpioConnectorNode);

  return  d->data->type();
}
