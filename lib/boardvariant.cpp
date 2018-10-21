#include "node_p.h"
#include "property_p.h"
#include "boardvariant.h"

// -----------------------------------------------------------------------------
//                          Class BoardVariantPrivate
// -----------------------------------------------------------------------------
class BoardVariantPrivate : public PropertyPrivate {

  public:
    BoardVariantPrivate (QSqlDatabase & database, BoardVariant * q) :
      PropertyPrivate (database, q), ram (-1), model (database), 
      gpio (database), manufacturer (database),
      default_i2c_id (-1), default_spi_id (-1), default_uart_id (-1)
    {}
    int ram;
    QString pcb_revision;
    BoardModel model;
    Gpio gpio;
    Manufacturer manufacturer;
    int default_i2c_id;
    int default_spi_id;
    int default_uart_id;
    Q_DECLARE_PUBLIC (BoardVariant);
};

// -----------------------------------------------------------------------------
//                          Class BoardVariant
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
BoardVariant::BoardVariant (BoardVariantPrivate &dd) : Property (dd) {}

// -----------------------------------------------------------------------------
BoardVariant::BoardVariant (QSqlDatabase & database) :
  Property (* new BoardVariantPrivate (database, this)) {}

// -----------------------------------------------------------------------------
QString BoardVariant::table() const {
  static QString t ("board");

  return t;
}

// -----------------------------------------------------------------------------
QIcon BoardVariant::icon() const {

  return QIcon (":/images/board_variant.png");
}

// -----------------------------------------------------------------------------
BoardModel & BoardVariant::model()  {
  Q_D (BoardVariant);

  return d->model;
}

// -----------------------------------------------------------------------------
Manufacturer & BoardVariant::manufacturer()  {
  Q_D (BoardVariant);

  return d->manufacturer;
}

// -----------------------------------------------------------------------------
Gpio & BoardVariant::gpio()  {
  Q_D (BoardVariant);

  return d->gpio;
}

// -----------------------------------------------------------------------------
int BoardVariant::defaultI2c() const {
  Q_D (const BoardVariant);

  return d->default_i2c_id;
}

// -----------------------------------------------------------------------------
int BoardVariant::defaultSpi() const {
  Q_D (const BoardVariant);

  return d->default_spi_id;
}


// -----------------------------------------------------------------------------
int BoardVariant::defaultUart() const {
  Q_D (const BoardVariant);

  return d->default_uart_id;
}

// -----------------------------------------------------------------------------
int BoardVariant::ramSize() const {
  Q_D (const BoardVariant);

  return d->ram;
}

// -----------------------------------------------------------------------------
const QString & BoardVariant::pcbRevision() const {
  Q_D (const BoardVariant);

  return d->pcb_revision;
}

// -----------------------------------------------------------------------------
bool BoardVariant::readFromDatabase() {
  Q_D (BoardVariant);
  QSqlQuery q (database());

  q.prepare ("SELECT "
             "name,ram,pcb_revision,board_model_id,gpio_id,manufacturer_id,default_i2c_id,default_spi_id,default_uart_id "
             "FROM board "
             "WHERE id=?");
  q.addBindValue (d->id);
  q.exec();

  if (q.next()) {
    bool hasChanged = false;
    QString name = q.value (0).toString();
    int ram = q.value (1).toInt();
    QString pcb_revision = q.value (2).toString();
    int board_model_id = q.value (3).toInt();
    int gpio_id = q.value (4).toInt();
    int manufacturer_id = q.value (5).toInt();
    int default_i2c_id = q.value (6).toInt();
    int default_spi_id = q.value (7).toInt();
    int default_uart_id = q.value (8).toInt();

    if (d->name != name) {
      d->name = name;
      hasChanged = true;
    }
    if (d->model.id() != board_model_id) {
      d->model.setId (board_model_id);
      hasChanged = true;
    }
    if (d->manufacturer.id() != manufacturer_id) {
      d->manufacturer.setId (manufacturer_id);
      hasChanged = true;
    }
    if (d->gpio.id() != gpio_id) {
      d->gpio.setId (gpio_id);
      hasChanged = true;
    }
    if (d->default_i2c_id != default_i2c_id) {
      d->default_i2c_id = default_i2c_id;
      hasChanged = true;
    }
    if (d->default_spi_id != default_spi_id) {
      d->default_spi_id = default_spi_id;
      hasChanged = true;
    }
    if (d->default_uart_id != default_uart_id) {
      d->default_uart_id = default_uart_id;
      hasChanged = true;
    }
    if (d->ram != ram) {
      d->ram = ram;
      hasChanged = true;
    }
    if (d->pcb_revision != pcb_revision) {
      d->pcb_revision = pcb_revision;
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
bool BoardVariant::writeToDatabase() {
  Q_D (const BoardVariant);

  if (isWritable()) {
    QSqlQuery q (database());

    if (exists()) {
      if (hasName()) {
        q.prepare ("UPDATE board "
                   "SET name=?,ram=?,pcb_revision=?,board_model_id=?,gpio_id=?,manufacturer_id=?,default_i2c_id=?,default_spi_id=?,default_uart_id=? "
                   "WHERE  id=?");
        q.addBindValue (d->name);
        q.addBindValue (d->ram);
        q.addBindValue (d->pcb_revision);
        q.addBindValue (d->model.id());
        q.addBindValue (d->gpio.id());
        q.addBindValue (d->manufacturer.id());
        q.addBindValue (d->default_i2c_id);
        q.addBindValue (d->default_spi_id);
        q.addBindValue (d->default_uart_id);
        q.addBindValue (d->id);
      }
    }
    else {
      q.prepare ("INSERT INTO board "
                 "(id,name,ram,pcb_revision,board_model_id,gpio_id,manufacturer_id,default_i2c_id,default_spi_id,default_uart_id) "
                 "VALUES (?,?,?,?,?,?,?,?,?,?)");
      q.addBindValue (d->id);
      q.addBindValue (d->name);
      q.addBindValue (d->ram);
      q.addBindValue (d->pcb_revision);
      q.addBindValue (d->model.id());
      q.addBindValue (d->gpio.id());
      q.addBindValue (d->manufacturer.id());
      q.addBindValue (d->default_i2c_id);
      q.addBindValue (d->default_spi_id);
      q.addBindValue (d->default_uart_id);
    }

    if (q.exec()) {

      emit updated();
      return true;
    }
  }
  return false;
}

// -----------------------------------------------------------------------------
//                          Class BoardVariantNode
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
BoardVariantNode::BoardVariantNode (int id, Node * parent) :
  PropertyNode (new BoardVariant (parent->database()), parent) {

  data()->setId (id);
}

// -----------------------------------------------------------------------------
BoardVariantNode::~BoardVariantNode() {

  delete data();
}

// -----------------------------------------------------------------------------
BoardVariant * BoardVariantNode::data() const {

  return reinterpret_cast<BoardVariant *> (PropertyNode::data());
}

