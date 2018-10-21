#ifndef GPIOCONNECTOR_H
#define GPIOCONNECTOR_H

#include "connector.h"
#include "gpio.h"

/**
 * @class GpioConnector
 * @brief 
 */
class GpioConnectorPrivate;
class GpioConnector : public Record {

  public:
    GpioConnector (QSqlDatabase & database);

    void setId (int gpioId, int connectorId);
    const Connector & connector() const;
    const Gpio & gpio() const;
    bool exists() const;

    int number() const;
    void setNumber (int number);

    QIcon icon() const;

    bool isWritable() const { return true; }
    Type type() const { return TypeConnector; }
    QString table() const;

  public slots:
    bool readFromDatabase();
    bool writeToDatabase();
    bool deleteToDatabase();

  protected:
    GpioConnector (GpioConnectorPrivate &dd);

  private:
    Q_DECLARE_PRIVATE (GpioConnector)
    Q_DISABLE_COPY (GpioConnector)
};

/**
 * @class GpioConnectorNode
 * @brief 
 */
class GpioConnectorNodePrivate;
class GpioConnectorNode : public ChildNode {
public:

    GpioConnectorNode (int gpioId, int connectorId, Node * parent);
    GpioConnector * data() const;
    Record::Type type() const;
    QString name() const;
    QString toolTip() const;
    QIcon icon() const;

  protected:
    GpioConnectorNode (GpioConnectorNodePrivate &dd);

  private:
    Q_DECLARE_PRIVATE (GpioConnectorNode);
    Q_DISABLE_COPY (GpioConnectorNode);
};

#endif
