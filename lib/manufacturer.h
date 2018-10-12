#ifndef MANUFACTURER_H
#define MANUFACTURER_H

#include "node.h"
#include "property.h"

class QString;
class ManufacturerPrivate;
class Manufacturer : public Node {
  public:

    Manufacturer (int id, const QString & name, Node * parent);
    virtual ~Manufacturer();
    virtual void childrenFromDatabase();

  protected:
    Manufacturer (ManufacturerPrivate &dd);

  private:
    Q_DECLARE_PRIVATE (Manufacturer);
    Q_DISABLE_COPY (Manufacturer);
};

#endif
