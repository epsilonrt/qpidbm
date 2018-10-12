#ifndef GPIO_H
#define GPIO_H

#include "node.h"

class QString;
class GpioNode : public Node {
  public:

    GpioNode (int id, const QString & name, Node * parent);
    virtual void childrenFromDatabase();

    int variantId() const;
};
#endif
