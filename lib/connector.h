#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "connectorfamily.h"

/**
 * @class Connector
 * @brief 
 */
class ConnectorPrivate;
class Connector : public Property {
  public:

    Connector (QSqlDatabase & database);

    ConnectorFamily & family();
    const ConnectorFamily & family() const;
    int rows() const;

    bool hasName() const { return true; }
    bool isWritable() const { return true; }
    Type type() const { return TypeConnector; }
    QString table() const;
    QIcon icon() const;

  public slots:
    bool readFromDatabase();
    bool writeToDatabase();

  protected:
    Connector (ConnectorPrivate &dd);

  private:
    Q_DECLARE_PRIVATE (Connector)
    Q_DISABLE_COPY (Connector)
};

/**
 * @class ConnectorNode
 * @brief 
 */
class ConnectorNode : public PropertyNode {
  public:

    ConnectorNode (int id, Node * parent);
    virtual ~ConnectorNode ();
    Connector * data() const;
    QString name() const;
};

#endif
