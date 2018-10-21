#ifndef FOLDER_H
#define FOLDER_H

#include "node.h"
#include "property.h"

class QString;

class FolderNodePrivate;
class FolderNode : public ChildNode {
  public:

    FolderNode (const QString & name, Node * parent);

    virtual QString name() const;
    virtual QIcon icon() const;
    static  QIcon folderIcon();
    
  protected:
    FolderNode (FolderNodePrivate &dd);

  private:
    Q_DECLARE_PRIVATE (FolderNode)
    Q_DISABLE_COPY (FolderNode)
};

class BoardFolderNode : public FolderNode {
  public:

    BoardFolderNode (const QString & name, Node * parent) :
      FolderNode (name, parent) { getChildren(); }
    void getChildren();
    
    virtual Record::Type type() const { return Record::TypeBoardFamily; }
};

class GpioFolderNode : public FolderNode {
  public:

    GpioFolderNode (const QString & name, Node * parent) :
      FolderNode (name, parent) { getChildren(); }
    void getChildren();

    virtual Record::Type type() const { return Record::TypeGpio; }
};

class SocFolderNode : public FolderNode {
  public:

    SocFolderNode (const QString & name, Node * parent) :
      FolderNode (name, parent) { getChildren(); }
    void getChildren();

    virtual Record::Type type() const { return Record::TypeSocFamily; }
};

class ManufacturerFolderNode : public FolderNode {
  public:

    ManufacturerFolderNode (const QString & name, Node * parent) :
      FolderNode (name, parent) { getChildren(); }
    void getChildren();

    virtual Record::Type type() const { return Record::TypeManufacturer; }
};

class ConnectorFolderNode : public FolderNode {
  public:

    ConnectorFolderNode (const QString & name, Node * parent) :
      FolderNode (name, parent) { getChildren(); }
    void getChildren();

    virtual Record::Type type() const { return Record::TypeConnector; }
};

#endif
