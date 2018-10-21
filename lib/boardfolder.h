#ifndef BOARDFOLDERNODE_H
#define BOARDFOLDERNODE_H

#include "folder.h"

class BoardFolderNode : public FolderNode {
  public:

    FolderNode (const QString & name, Node * parent);
    virtual ~FolderNode();
    virtual void childrenFromDatabase() = 0;

    // must be reimplemented
    static Property::Type type() { return Property::TypeBoardFamily; }
    
  protected:
    FolderNode (FolderNodePrivate &dd);

  private:
    Q_DECLARE_PRIVATE (FolderNode);
    Q_DISABLE_COPY (FolderNode);
};

#endif
