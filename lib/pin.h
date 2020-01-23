#ifndef PIN_H
#define PIN_H

#include "property.h"

class Pin : public Property {
  public:

    Pin (QSqlDatabase & database) : 
      Property(database) {}
    QString table() const { static QString t("pin");  return t; }

    bool hasName() const { return true; }
    bool isWritable() const { return true; }
    Type type() const { return TypePin; }
};
#endif
