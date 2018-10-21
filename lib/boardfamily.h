#ifndef BOARDFAMILY_H
#define BOARDFAMILY_H

#include "folder.h"

/**
 * @class BoardFamily
 * @brief 
 */
class BoardFamilyPrivate;
class BoardFamily : public Property {
  public:

    BoardFamily (QSqlDatabase & database);

    bool hasName() const { return true; }
    bool isWritable() const { return true; }
    Type type() const { return TypeBoardFamily; }
    QString table() const;
    
    const QString & i2cSysPath() const;
    const QString & spiSysPath() const;
    const QString & uartSysPath() const;

    QIcon icon() const { return FolderNode::folderIcon(); }

  public slots:
    bool readFromDatabase();
    bool writeToDatabase();

  protected:
    BoardFamily (BoardFamilyPrivate &dd);

  private:
    Q_DECLARE_PRIVATE (BoardFamily)
    Q_DISABLE_COPY (BoardFamily)
};

/**
 * @class BoardFamilyNode
 * @brief 
 */
class BoardFamilyNode : public PropertyNode {
  public:

    BoardFamilyNode (int id, Node * parent);
    virtual ~BoardFamilyNode ();
    BoardFamily * data() const;
    void getChildren();
};

#endif
