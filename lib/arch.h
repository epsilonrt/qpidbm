#ifndef ARCH_H
#define ARCH_H

#include "property.h"

class Arch : public Property {
  public:

    Arch (QSqlDatabase & database) : 
      Property(database) {}
    QString table() const { static QString t("arch");  return t; }

    bool hasName() const { return true; }
    bool isWritable() const { return false; }
    Type type() const { return TypeArch; }
};
#endif
