#ifndef FOLDER_H
#define FOLDER_H

#include "node.h"

class QString;
class Folder : public Node {
  public:

    Folder (Type type, const QString & name, Node * parent);
    virtual void childrenFromDatabase();
};
#endif
