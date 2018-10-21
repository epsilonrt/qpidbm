#ifndef BOARDVARIANT_H
#define BOARDVARIANT_H

#include "boardmodel.h"
#include "manufacturer.h"
#include "gpio.h"

/**
 * @class BoardVariant
 * @brief 
 */
class BoardVariantPrivate;
class BoardVariant : public Property {
  public:

    BoardVariant (QSqlDatabase & database);

    int ramSize() const;
    const QString & pcbRevision() const;
    BoardModel & model();
    Gpio & gpio();
    Manufacturer & manufacturer();
    int defaultI2c() const;
    int defaultSpi() const;
    int defaultUart() const;

    bool hasName() const { return true; }
    bool isWritable() const { return true; }
    Type type() const { return TypeBoardVariant; }
    QString table() const;
    QIcon icon() const;

  public slots:
    bool readFromDatabase();
    bool writeToDatabase();

  protected:
    BoardVariant (BoardVariantPrivate &dd);

  private:
    Q_DECLARE_PRIVATE (BoardVariant)
    Q_DISABLE_COPY (BoardVariant)
};

/**
 * @class BoardVariantNode
 * @brief 
 */
class BoardVariantNode : public PropertyNode {
  public:

    BoardVariantNode (int id, Node * parent);
    virtual ~BoardVariantNode ();
    BoardVariant * data() const;
};

#endif
