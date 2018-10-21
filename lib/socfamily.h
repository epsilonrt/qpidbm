#ifndef SOCFAMILY_H
#define SOCFAMILY_H

#include "arch.h"
#include "folder.h"

/**
 * @class SocFamily
 * @brief 
 */
class SocFamilyPrivate;
class SocFamily : public Property {
  public:

    SocFamily (QSqlDatabase & database);

    Arch & arch();

    bool hasName() const { return true; }
    bool isWritable() const { return false; }
    Type type() const { return TypeSocFamily; }
    QString table() const;

    QIcon icon() const { return FolderNode::folderIcon(); }

  public slots:
    bool readFromDatabase();

  protected:
    SocFamily (SocFamilyPrivate &dd);

  private:
    Q_DECLARE_PRIVATE (SocFamily)
    Q_DISABLE_COPY (SocFamily)
};

/**
 * @class SocFamilyNode
 * @brief 
 */
class SocFamilyNode : public PropertyNode {
  public:

    SocFamilyNode (int id, Node * parent);
    virtual ~SocFamilyNode ();
    SocFamily * data() const;
    void getChildren();
};

#endif
