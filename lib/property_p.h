#ifndef PROPERTY_PRIVATE_H
#define PROPERTY_PRIVATE_H

#include "property.h"
#include "record_p.h"

class PropertyPrivate : public RecordPrivate {
  public:
    PropertyPrivate (QSqlDatabase & database, Property * q) :
      RecordPrivate (database, q), id(-1)
      {}
    int id;
    QString name;
    Q_DECLARE_PUBLIC (Property);
};
#endif
