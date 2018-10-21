#include <QFileIconProvider>
#include "folder_p.h"
#include "socfamily.h"
#include "boardfamily.h"
#include "manufacturer.h"
#include "gpio.h"
#include "connector.h"

// -----------------------------------------------------------------------------
//                          Class FolderNode
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
FolderNodePrivate::FolderNodePrivate (const QString & n, Node * parent, FolderNode * q) :
  ChildNodePrivate (parent, q), name (n) {}

// -----------------------------------------------------------------------------
FolderNode::FolderNode (FolderNodePrivate &dd) : ChildNode (dd) {}

// -----------------------------------------------------------------------------
FolderNode::FolderNode (const QString & name, Node * parent) :
  ChildNode (* new FolderNodePrivate (name, parent, this)) {}

// -----------------------------------------------------------------------------
QString FolderNode::name() const {
  Q_D (const FolderNode);

  return  d->name;
}

// -----------------------------------------------------------------------------
QIcon FolderNode::icon() const {
  
  return folderIcon();
}

// -----------------------------------------------------------------------------
QIcon FolderNode::folderIcon() {
  static QFileIconProvider iconProvider;
  
  return iconProvider.icon (QFileIconProvider::Folder);
}

// -----------------------------------------------------------------------------
//                          Class ManufacturerFolderNode
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void ManufacturerFolderNode::getChildren() {
  QSqlQuery q ("SELECT id FROM manufacturer", database());

  clearChildren();
  q.exec();
  while (q.next()) {

    int i = q.value (0).toInt();
    if (i >= 0) {

      append (new ManufacturerNode (i, this));
    }
  }
}

// -----------------------------------------------------------------------------
//                          Class SocFolderNode
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void SocFolderNode::getChildren() {
  QSqlQuery q ("SELECT id FROM soc_family", database());

  clearChildren();
  q.exec();
  while (q.next()) {

    int i = q.value (0).toInt();
    if (i >= 0) {

      append (new SocFamilyNode (i, this));
    }
  }
}


// -----------------------------------------------------------------------------
//                          Class BoardFolderNode
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void BoardFolderNode::getChildren() {
  QSqlQuery q ("SELECT id FROM board_family", database());

  clearChildren();
  q.exec();
  while (q.next()) {

    int i = q.value (0).toInt();
    if (i >= 0) {

      append (new BoardFamilyNode (i, this));
    }
  }
}

// -----------------------------------------------------------------------------
//                          Class GpioFolderNode
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void GpioFolderNode::getChildren() {
  QSqlQuery q ("SELECT id FROM gpio", database());

  clearChildren();
  q.exec();
  while (q.next()) {

    int i = q.value (0).toInt();
    if (i >= 0) {

      append (new GpioNode (i, this));
    }
  }
}

// -----------------------------------------------------------------------------
//                          Class ConnectorFolderNode
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
void ConnectorFolderNode::getChildren() {
  QSqlQuery q ("SELECT id FROM connector ORDER BY id ASC", database());

  clearChildren();
  q.exec();
  while (q.next()) {

    int i = q.value (0).toInt();
    if (i >= 0) {

      append (new ConnectorNode (i, this));
    }
  }
}

