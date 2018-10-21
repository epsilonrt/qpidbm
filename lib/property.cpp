#include "property_p.h"

// -----------------------------------------------------------------------------
//                          Class Property
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
Property::Property (PropertyPrivate &dd) : Record (dd) {}

// -----------------------------------------------------------------------------
Property::Property (QSqlDatabase & database) :
  Record (*new PropertyPrivate (database, this)) {}

// -----------------------------------------------------------------------------
/**
 * @brief Indique si l'enregistrement correspondant à l'identifiant id()
 * existe dans la base de données
 */
bool Property::exists() const {

  return exists (id());
}

// -----------------------------------------------------------------------------
/**
 * @brief Indique si l'enregistrement correspondant à id
 * existe dans la base de données
 */
bool Property::exists (int id) const {
  QSqlQuery q (database());

  q.prepare (QString ("SELECT 1 FROM %1 WHERE id=?").arg (table())) ;
  q.addBindValue (id);
  q.exec();
  return q.next();
}

// -----------------------------------------------------------------------------
/**
 * @brief Identifiant
 */
int Property::id() const {
  Q_D (const Property);

  return d->id;
}

// -----------------------------------------------------------------------------
/**
 * @brief Modifie l'identifiant et lecture des données dans la base de
 * données si l'identifiant existe.
 * @param id
 */
void Property::setId (int id) {
  Q_D (Property);

  d->id = id;
  if (exists()) {

    readFromDatabase();
  }
}

// -----------------------------------------------------------------------------
/**
 * @brief Liste des identifiants dans la table()
 */
QList<int> Property::identifiers() const {
  Q_D (const Property);
  QList<int> list;
  QSqlQuery q (database());

  q.prepare (QString ("SELECT id FROM %1").arg (table()));

  if (q.exec()) {
    while (q.next()) {
      list.append (q.value (0).toInt());
    }
  }
  return list;
}

// -----------------------------------------------------------------------------
/**
 * @brief Liste des noms présents dans la table
 */
QList<QString> Property::names() const {
  Q_D (const Property);
  QList<QString> list;
  QSqlQuery q (database());

  q.prepare (QString ("SELECT name FROM %1").arg (table()));

  if (q.exec()) {
    while (q.next()) {
      list.append (q.value (0).toString());
    }
  }
  return list;
}

// -----------------------------------------------------------------------------
/**
 * @brief Vérifie si un nom est présent dans la table
 */
bool Property::exists (const QString & n) const {
  if (hasName()) {
    QSqlQuery q (database());

    q.prepare (QString ("SELECT 1 FROM %1 WHERE name=?").arg (table()));
    q.addBindValue (n);
    q.exec();
    return q.next();
  }
  return false;
}

// -----------------------------------------------------------------------------
/**
 * @brief Indique si la propriété a un nom
 */
bool Property::hasName() const {
  return false;
}

/**
 * @brief Nom
 */
// -----------------------------------------------------------------------------
QString Property::name() const {
  Q_D (const Property);

  return d->name;
}

/**
 * @brief Modification du nom
 */
// -----------------------------------------------------------------------------
void Property::setName (const QString & name) {
  if (hasName()) {
    Q_D (Property);
    
    d->name = name;
  }
}

/**
 * @brief Ecriture des données dans la base de données
 */
// -----------------------------------------------------------------------------
bool Property::writeToDatabase() {

  if (hasName()) {
    Q_D (const Property);

    if (isWritable()) {
      QSqlQuery q (database());

      if (exists()) {
        if (hasName()) {
          q.prepare (QString (
                       "UPDATE %1 "
                       "SET name=? "
                       "WHERE  id=?"
                     ).arg (table()));
          q.addBindValue (name());
          q.addBindValue (d->id);
        }
      }
      else {
        q.prepare (QString (
                     "INSERT INTO %1 (id,name) "
                     "VALUES (?,?)"
                   ).arg (table()));
        q.addBindValue (d->id);
        q.addBindValue (d->name);
      }

      if (q.exec()) {

        emit updated();
        return true;
      }
    }
  }
  return false;
}

// -----------------------------------------------------------------------------
/**
 * @brief Chargement des données depuis la base de données
 */
bool Property::readFromDatabase() {

  if (hasName()) {
    Q_D (Property);
    QSqlQuery q (database());

    q.prepare (QString ("SELECT name FROM %1 WHERE id=?").arg (table()));
    q.addBindValue (d->id);
    q.exec();
    if (q.next()) {
      QString name = q.value (0).toString();

      if (d->name != name) {
        d->name = name;
        emit changed();
      }
      return true;
    }
  }
  return false;
}

// -----------------------------------------------------------------------------
/**
 * @brief Suppression
 * @return
 */
bool Property::deleteToDatabase() {
  Q_D (Property);
  QSqlQuery q (database());

  q.prepare (QString ("DELETE FROM %1 WHERE id=?").arg (table()));
  q.addBindValue (d->id);
  return q.exec();
}
