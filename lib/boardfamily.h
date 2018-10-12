#ifndef BOARDFAMILY_H
#define BOARDFAMILY_H

#include "node.h"

class QString;
class BoardFamilyNode : public Node {
  public:

    BoardFamilyNode (int id, const QString & name, Node * parent);
    virtual void childrenFromDatabase();
};
#endif
