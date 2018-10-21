#ifndef RECORD_PRIVATE_H
#define RECORD_PRIVATE_H

#include <QtCore>
#include <QtSql>
#include "record.h"

class RecordPrivate {
  public:
    RecordPrivate (QSqlDatabase & database, Record * q);

    Record * q_ptr;
    QSqlDatabase & database;
    Q_DECLARE_PUBLIC (Record);
};
#endif
