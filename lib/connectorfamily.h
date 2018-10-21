#ifndef CONNECTORFAMILY_H
#define CONNECTORFAMILY_H

/**
 * @class ConnectorFamily
 * @brief 
 */
class ConnectorFamilyPrivate;
class ConnectorFamily : public Property {
  public:

    ConnectorFamily (QSqlDatabase & database);

    int  columns() const;

    bool hasName() const { return true; }
    bool isWritable() const { return false; }
    Type type() const { return TypeConnectorFamily; }
    QString table() const;

  public slots:
    bool readFromDatabase();

  protected:
    ConnectorFamily (ConnectorFamilyPrivate &dd);

  private:
    Q_DECLARE_PRIVATE (ConnectorFamily)
    Q_DISABLE_COPY (ConnectorFamily)
};

#endif
