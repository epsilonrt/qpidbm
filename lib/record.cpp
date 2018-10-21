#include "record_p.h"

// -----------------------------------------------------------------------------
//                          Class Record
// -----------------------------------------------------------------------------
RecordPrivate::RecordPrivate (QSqlDatabase & database, Record * q) :
  q_ptr (q), database (database) {}

// -----------------------------------------------------------------------------
Record::Record (RecordPrivate &dd) : d_ptr (&dd) {}

// -----------------------------------------------------------------------------
Record::Record (QSqlDatabase & database) :
  d_ptr (new RecordPrivate (database, this))  {}

// -----------------------------------------------------------------------------
Record::~Record() = default;

// -----------------------------------------------------------------------------
/**
 * @brief Infobulle
 * @return
 */
QString Record::toolTip() const {

  return QString();
}

// -----------------------------------------------------------------------------
/**
 * @brief Icone
 */
QIcon Record::icon() const {

  return QIcon();
}

// -----------------------------------------------------------------------------
Record::Type Record::type() const {

  return TypeNone;
}

// -----------------------------------------------------------------------------
/**
 * @brief Indique si les données sont modifiables
 */
bool Record::isWritable() const {

  return false;
}

// -----------------------------------------------------------------------------
/**
 * @brief Base de données utilisée
 */
QSqlDatabase & Record::database() const {
  
  return  d_ptr->database;
}
