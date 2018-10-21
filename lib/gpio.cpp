#include "node_p.h"
#include "property_p.h"
#include "gpio.h"
#include "gpioconnector.h"

// -----------------------------------------------------------------------------
//                          Class GpioPrivate
// -----------------------------------------------------------------------------
class GpioPrivate : public PropertyPrivate {

  public:
    GpioPrivate (QSqlDatabase & database, Gpio * q) :
      PropertyPrivate (database, q),
      boardFamily (database)
    {}
    BoardFamily boardFamily;
    Q_DECLARE_PUBLIC (Gpio);
};

// -----------------------------------------------------------------------------
//                          Class Gpio
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
Gpio::Gpio (GpioPrivate &dd) : Property (dd) {}

// -----------------------------------------------------------------------------
Gpio::Gpio (QSqlDatabase & database) :
  Property (* new GpioPrivate (database, this)) {}

// -----------------------------------------------------------------------------
QString Gpio::table() const {
  static QString t ("gpio");

  return t;
}

// -----------------------------------------------------------------------------
QIcon Gpio::icon() const {

  return QIcon (":/images/gpio.png");
}

// -----------------------------------------------------------------------------
BoardFamily & Gpio::boardFamily()  {
  Q_D (Gpio);

  return d->boardFamily;
}

// -----------------------------------------------------------------------------
bool Gpio::readFromDatabase() {
  Q_D (Gpio);
  QSqlQuery q (database());

  q.prepare ("SELECT "
             "name,board_family_id "
             "FROM gpio "
             "WHERE id=?");
  q.addBindValue (d->id);
  q.exec();

  if (q.next()) {
    bool hasChanged = false;
    QString name = q.value (0).toString();
    int board_family_id =  q.value (1).toInt();

    if (d->name != name) {
      d->name = name;
      hasChanged = true;
    }
    if (d->boardFamily.id() != board_family_id) {
      d->boardFamily.setId (board_family_id);
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
bool Gpio::writeToDatabase() {
  Q_D (const Gpio);

  if (isWritable()) {
    QSqlQuery q (database());

    if (exists()) {
      if (hasName()) {
        q.prepare ("UPDATE gpio "
                   "SET name=?,board_family_id=? "
                   "WHERE  id=?");
        q.addBindValue (d->name);
        q.addBindValue (d->boardFamily.id());
        q.addBindValue (d->id);
      }
    }
    else {
      q.prepare ("INSERT INTO gpio "
                 "(id,name,board_family_id) "
                 "VALUES (?,?,?)");
      q.addBindValue (d->id);
      q.addBindValue (d->name);
      q.addBindValue (d->boardFamily.id());
    }

    if (q.exec()) {

      emit updated();
      return true;
    }
  }
  return false;
}

// -----------------------------------------------------------------------------
//                          Class GpioNode
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
GpioNode::GpioNode (int id, Node * parent) :
  PropertyNode (new Gpio (parent->database()), parent) {

  data()->setId (id);
  getChildren();
}

// -----------------------------------------------------------------------------
GpioNode::~GpioNode() {

  delete data();
}

// -----------------------------------------------------------------------------
Gpio * GpioNode::data() const {

  return reinterpret_cast<Gpio *> (PropertyNode::data());
}

// -----------------------------------------------------------------------------
void GpioNode::getChildren() {
  QSqlQuery q (database());
  q.prepare ("SELECT connector_id,num "
             "FROM gpio_has_connector "
             "WHERE gpio_id = ? "
             "ORDER BY num ASC");
  q.addBindValue (data()->id());
  q.exec();
  clearChildren();

  while (q.next()) {

    append (new GpioConnectorNode (data()->id(), q.value (0).toInt(), this));
  }
}
