#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include "boardfamily.h"
#include "soc.h"

/**
 * @class BoardModel
 * @brief 
 */
class BoardModelPrivate;
class BoardModel : public Property {
  public:

    BoardModel (QSqlDatabase & database);

    BoardFamily & family();
    Soc & soc();

    bool hasName() const { return true; }
    bool isWritable() const { return true; }
    Type type() const { return TypeBoardModel; }
    QString table() const;
    QIcon icon() const;

  public slots:
    bool readFromDatabase();
    bool writeToDatabase();

  protected:
    BoardModel (BoardModelPrivate &dd);

  private:
    Q_DECLARE_PRIVATE (BoardModel)
    Q_DISABLE_COPY (BoardModel)
};

/**
 * @class BoardModelNode
 * @brief 
 */
class BoardModelNode : public PropertyNode {
  public:

    BoardModelNode (int id, Node * parent);
    virtual ~BoardModelNode ();
    BoardModel * data() const;
    void getChildren();
};

#endif
