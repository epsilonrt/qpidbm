#include "node_p.h"
#include "property_p.h"
#include "soc.h"

// -----------------------------------------------------------------------------
//                          Class SocPrivate
// -----------------------------------------------------------------------------
class SocPrivate : public PropertyPrivate {

  public:
    SocPrivate (QSqlDatabase & database, Soc * q) :
      PropertyPrivate (database, q), i2c_count (-1), spi_count (-1), uart_count (-1),
      family (database), manufacturer (database)
    {}
    int i2c_count;
    int spi_count;
    int uart_count;
    SocFamily family;
    Manufacturer manufacturer;
    Q_DECLARE_PUBLIC (Soc);
};

// -----------------------------------------------------------------------------
//                          Class Soc
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
Soc::Soc (SocPrivate &dd) : Property (dd) {}

// -----------------------------------------------------------------------------
Soc::Soc (QSqlDatabase & database) :
  Property (* new SocPrivate (database, this)) {}

// -----------------------------------------------------------------------------
QString Soc::table() const {
  static QString t ("soc");

  return t;
}

// -----------------------------------------------------------------------------
QIcon Soc::icon() const {

  return QIcon (":/images/soc.png");
}

// -----------------------------------------------------------------------------
SocFamily & Soc::family()  {
  Q_D (Soc);

  return d->family;
}

// -----------------------------------------------------------------------------
Manufacturer & Soc::manufacturer()  {
  Q_D (Soc);

  return d->manufacturer;
}

// -----------------------------------------------------------------------------
int Soc::numberOfI2c() const {
  Q_D (const Soc);

  return d->i2c_count;
}

// -----------------------------------------------------------------------------
int Soc::numberOfSpi() const {
  Q_D (const Soc);

  return d->spi_count;
}

// -----------------------------------------------------------------------------
int Soc::numberOfUart() const {
  Q_D (const Soc);

  return d->uart_count;
}

// -----------------------------------------------------------------------------
bool Soc::readFromDatabase() {
  Q_D (Soc);
  QSqlQuery q (database());

  q.prepare ("SELECT "
             "name,soc_family_id,manufacturer_id,i2c_count,spi_count,uart_count "
             "FROM soc "
             "WHERE id=?");
  q.addBindValue (d->id);
  q.exec();

  if (q.next()) {
    bool hasChanged = false;
    QString name = q.value (0).toString();
    int soc_family_id =  q.value (1).toInt();
    int manufacturer_id =  q.value (2).toInt();
    int i2c_count =  q.value (3).toInt();
    int spi_count =  q.value (4).toInt();
    int uart_count =  q.value (5).toInt();

    if (d->name != name) {
      d->name = name;
      hasChanged = true;
    }
    if (d->family.id() != soc_family_id) {
      d->family.setId (soc_family_id);
      hasChanged = true;
    }
    if (d->manufacturer.id() != manufacturer_id) {
      d->manufacturer.setId (manufacturer_id);
      hasChanged = true;
    }
    if (d->i2c_count != i2c_count) {
      d->i2c_count = i2c_count;
      hasChanged = true;
    }
    if (d->spi_count != spi_count) {
      d->spi_count = spi_count;
      hasChanged = true;
    }
    if (d->uart_count != uart_count) {
      d->uart_count = uart_count;
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
bool Soc::writeToDatabase() {
  Q_D (const Soc);

  if (isWritable()) {
    QSqlQuery q (database());

    if (exists()) {
      if (hasName()) {
        q.prepare ("UPDATE soc "
                   "SET name=?,soc_family_id=?,manufacturer_id=?,i2c_count=?,spi_count=?,uart_count=? "
                   "WHERE  id=?");
        q.addBindValue (d->name);
        q.addBindValue (d->family.id());
        q.addBindValue (d->manufacturer.id());
        q.addBindValue (d->i2c_count);
        q.addBindValue (d->spi_count);
        q.addBindValue (d->uart_count);
        q.addBindValue (d->id);
      }
    }
    else {
      q.prepare ("INSERT INTO soc "
                 "(id,name,soc_family_id,manufacturer_id,i2c_count,spi_count,uart_count) "
                 "VALUES (?,?,?,?,?,?,?)");
      q.addBindValue (d->id);
      q.addBindValue (d->name);
      q.addBindValue (d->family.id());
      q.addBindValue (d->manufacturer.id());
      q.addBindValue (d->i2c_count);
      q.addBindValue (d->spi_count);
      q.addBindValue (d->uart_count);
    }

    if (q.exec()) {

      emit updated();
      return true;
    }
  }
  return false;
}

// -----------------------------------------------------------------------------
//                          Class SocNode
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
SocNode::SocNode (int id, Node * parent) :
  PropertyNode (new Soc (parent->database()), parent) {

  data()->setId (id);
}

// -----------------------------------------------------------------------------
SocNode::~SocNode() {

  delete data();
}

// -----------------------------------------------------------------------------
Soc * SocNode::data() const {

  return reinterpret_cast<Soc *> (PropertyNode::data());
}
