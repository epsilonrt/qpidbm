#include "node_p.h"
#include "property_p.h"
#include "boardfamily.h"
#include "boardmodel.h"

// -----------------------------------------------------------------------------
//                          Class BoardFamilyPrivate
// -----------------------------------------------------------------------------
class BoardFamilyPrivate : public PropertyPrivate {

  public:
    BoardFamilyPrivate (QSqlDatabase & database, BoardFamily * q) :
      PropertyPrivate (database, q)  {}
    QString i2c_syspath;
    QString spi_syspath;
    QString uart_syspath;

    Q_DECLARE_PUBLIC (BoardFamily);
};

// -----------------------------------------------------------------------------
//                          Class BoardFamily
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
BoardFamily::BoardFamily (BoardFamilyPrivate &dd) : Property (dd) {}

// -----------------------------------------------------------------------------
BoardFamily::BoardFamily (QSqlDatabase & database) :
  Property (* new BoardFamilyPrivate (database, this)) {}

// -----------------------------------------------------------------------------
QString BoardFamily::table() const {
  static QString t ("board_family");

  return t;
}

// -----------------------------------------------------------------------------
const QString & BoardFamily::i2cSysPath() const {
  Q_D (const BoardFamily);

  return d->i2c_syspath;
}

// -----------------------------------------------------------------------------
const QString & BoardFamily::spiSysPath() const {
  Q_D (const BoardFamily);

  return d->spi_syspath;
}

// -----------------------------------------------------------------------------
const QString & BoardFamily::uartSysPath() const {
  Q_D (const BoardFamily);

  return d->uart_syspath;
}

// -----------------------------------------------------------------------------
bool BoardFamily::readFromDatabase() {
  Q_D (BoardFamily);
  QSqlQuery q (database());

  q.prepare ("SELECT name,i2c_syspath,spi_syspath,uart_syspath FROM board_family WHERE id=?");
  q.addBindValue (d->id);
  q.exec();

  if (q.next()) {
    bool hasChanged = false;
    QString name = q.value (0).toString();
    QString i2c_syspath = q.value (1).toString();
    QString spi_syspath = q.value (2).toString();
    QString uart_syspath = q.value (3).toString();

    if (d->name != name) {
      d->name = name;
      hasChanged = true;
    }
    if (d->i2c_syspath != i2c_syspath) {
      d->i2c_syspath = i2c_syspath;
      hasChanged = true;
    }
    if (d->spi_syspath != spi_syspath) {
      d->spi_syspath = spi_syspath;
      hasChanged = true;
    }
    if (d->uart_syspath != uart_syspath) {
      d->uart_syspath = uart_syspath;
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
bool BoardFamily::writeToDatabase() {
  Q_D (const BoardFamily);

  if (isWritable()) {
    QSqlQuery q (database());

    if (exists()) {
      if (hasName()) {
        q.prepare ("UPDATE board_family "
                   "SET name=?,i2c_syspath=?,spi_syspath=?,uart_syspath=? "
                   "WHERE  id=?");
        q.addBindValue (d->name);
        q.addBindValue (d->i2c_syspath);
        q.addBindValue (d->spi_syspath);
        q.addBindValue (d->uart_syspath);
        q.addBindValue (d->id);
      }
    }
    else {
      q.prepare ("INSERT INTO board_family "
                 "(id,name,i2c_syspath,spi_syspath,uart_syspath) "
                 "VALUES (?,?,?,?,?)");
      q.addBindValue (d->id);
      q.addBindValue (d->name);
      q.addBindValue (d->i2c_syspath);
      q.addBindValue (d->spi_syspath);
      q.addBindValue (d->uart_syspath);
    }

    if (q.exec()) {

      emit updated();
      return true;
    }
  }
  return false;
}

// -----------------------------------------------------------------------------
//                          Class BoardFamilyNode
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
BoardFamilyNode::BoardFamilyNode (int id, Node * parent) :
  PropertyNode (new BoardFamily (parent->database()), parent) {

  data()->setId (id);
  getChildren();
}

// -----------------------------------------------------------------------------
BoardFamilyNode::~BoardFamilyNode() {

  delete data();
}

// -----------------------------------------------------------------------------
void BoardFamilyNode::getChildren() {
  QSqlQuery q (database());
  q.prepare ("SELECT id FROM board_model WHERE board_family_id = ?");
  q.addBindValue (data()->id());
  q.exec();
  clearChildren();

  while (q.next()) {

    int i = q.value (0).toInt();
    if (i >= 0) {

      append (new BoardModelNode (i, this));
    }
  }
}

// -----------------------------------------------------------------------------
BoardFamily * BoardFamilyNode::data() const {

  return reinterpret_cast<BoardFamily *> (PropertyNode::data());
}
