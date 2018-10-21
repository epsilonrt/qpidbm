#ifndef GPIO_H
#define GPIO_H

#include "boardfamily.h"

/**
 * @class Gpio
 * @brief 
 */
class GpioPrivate;
class Gpio : public Property {
  public:

    Gpio (QSqlDatabase & database);

    BoardFamily & boardFamily();

    bool hasName() const { return true; }
    bool isWritable() const { return true; }
    Type type() const { return TypeGpio; }
    QString table() const;
    QIcon icon() const;

  public slots:
    bool readFromDatabase();
    bool writeToDatabase();

  protected:
    Gpio (GpioPrivate &dd);

  private:
    Q_DECLARE_PRIVATE (Gpio)
    Q_DISABLE_COPY (Gpio)
};

/**
 * @class GpioNode
 * @brief 
 */
class GpioNode : public PropertyNode {
  public:

    GpioNode (int id, Node * parent);
    virtual ~GpioNode ();
    Gpio * data() const;
    void getChildren();
};

#endif
