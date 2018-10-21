#ifndef FOLDERNODE_PRIVATE_H
#define FOLDERNODE_PRIVATE_H

#include "folder.h"
#include "node_p.h"
#include <QString>

class FolderNodePrivate : public ChildNodePrivate {
  public:
    FolderNodePrivate (const QString & name, Node * parent, FolderNode * q);

    QString name;
    Q_DECLARE_PUBLIC (FolderNode);
};
#endif
