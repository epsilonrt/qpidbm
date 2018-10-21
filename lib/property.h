#ifndef PROPERTY_H
#define PROPERTY_H

#include <QList>
#include "record.h"

class PropertyPrivate;
/**
 * @class Property
 * @brief Propriété stockée dans la base de données
 * Une propriété est indentifié par un id() présent dans une table().
 * Encapsule les opérations d'écriture, lecture, modification en db.
 */
class Property : public Record {
  public:
    Property (QSqlDatabase & database);

    virtual int id() const;
    virtual void setId (int id);
    virtual bool exists() const;
    virtual QList<int> identifiers() const;
    virtual bool exists (int id) const;

    virtual QString name() const;
    virtual void setName (const QString & name);
    virtual QList<QString> names() const;
    virtual bool exists (const QString & name) const;

    virtual bool hasName() const;

  public slots:
    virtual bool readFromDatabase();
    virtual bool writeToDatabase();
    virtual bool deleteToDatabase();

  protected:
    Property (PropertyPrivate &dd);

  private:
    Q_DECLARE_PRIVATE (Property)
    Q_DISABLE_COPY (Property)
};
#endif
