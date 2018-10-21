#include "property_p.h"
#include "connectorfamily.h"

// -----------------------------------------------------------------------------
//                          Class ConnectorFamilyPrivate
// -----------------------------------------------------------------------------
class ConnectorFamilyPrivate : public PropertyPrivate {

  public:
    ConnectorFamilyPrivate (QSqlDatabase & database, ConnectorFamily * q) :
      PropertyPrivate (database, q),
      columns (-1)
    {}
    int columns;
    Q_DECLARE_PUBLIC (ConnectorFamily);
};

// -----------------------------------------------------------------------------
//                          Class ConnectorFamily
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
ConnectorFamily::ConnectorFamily (ConnectorFamilyPrivate &dd) : Property (dd) {}

// -----------------------------------------------------------------------------
ConnectorFamily::ConnectorFamily (QSqlDatabase & database) :
  Property (* new ConnectorFamilyPrivate (database, this)) {}

// -----------------------------------------------------------------------------
QString ConnectorFamily::table() const {
  static QString t ("connector_family");

  return t;
}

// -----------------------------------------------------------------------------
int ConnectorFamily::columns() const {
  Q_D (const ConnectorFamily);

  return d->columns;
}

// -----------------------------------------------------------------------------
bool ConnectorFamily::readFromDatabase() {
  Q_D (ConnectorFamily);
  QSqlQuery q (database());

  q.prepare ("SELECT "
             "name,columns "
             "FROM connector_family "
             "WHERE id=?");
  q.addBindValue (d->id);
  q.exec();

  if (q.next()) {
    bool hasChanged = false;
    QString name = q.value (0).toString();
    int columns =  q.value (1).toInt();

    if (d->name != name) {
      d->name = name;
      hasChanged = true;
    }
    if (d->columns != columns) {
      d->columns = columns;
      hasChanged = true;
    }
    if (hasChanged) {
      emit changed();
    }
    return true;
  }

  return false;
}
