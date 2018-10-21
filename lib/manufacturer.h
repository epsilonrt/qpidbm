#ifndef MANUFACTURER_H
#define MANUFACTURER_H

#include "node.h"

/**
 * @class Manufacturer
 * @brief 
 */
class Manufacturer : public Property {
  public:

    Manufacturer (QSqlDatabase & database) : 
      Property(database) {}
    QString table() const { static QString t("manufacturer");  return t; }
    QIcon icon() const;

    bool hasName() const { return true; }
    bool isWritable() const { return true; }
    Type type() const { return TypeManufacturer; }
};

/**
 * @class ManufacturerNode
 * @brief 
 */
class ManufacturerNode : public PropertyNode {
  public:

    ManufacturerNode (int id, Node * parent);
    virtual ~ManufacturerNode ();
    Manufacturer * data() const;
};

#endif
