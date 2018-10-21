#ifndef SOC_H
#define SOC_H

#include "socfamily.h"
#include "manufacturer.h"
#include "pin.h"

/**
 * @class Soc
 * @brief 
 */
class SocPrivate;
class Soc : public Property {
  public:

    Soc (QSqlDatabase & database);

    SocFamily & family();
    Manufacturer & manufacturer();
    int numberOfI2c() const;
    int numberOfSpi() const;
    int numberOfUart() const;

    bool hasName() const { return true; }
    bool isWritable() const { return true; }
    Type type() const { return TypeSoc; }
    QString table() const;
    QIcon icon() const;

  public slots:
    bool readFromDatabase();
    bool writeToDatabase();

  protected:
    Soc (SocPrivate &dd);

  private:
    Q_DECLARE_PRIVATE (Soc)
    Q_DISABLE_COPY (Soc)
};

/**
 * @class SocNode
 * @brief 
 */
class SocNode : public PropertyNode {
  public:

    SocNode (int id, Node * parent);
    virtual ~SocNode ();
    Soc * data() const;
};

#endif
