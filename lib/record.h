#ifndef RECORD_H
#define RECORD_H

#include <QObject>
#include <QIcon>
#include <QString>
#include <QSqlDatabase>

class RecordPrivate;
/**
 * @class Record
 * @brief Enregistrement dans la base de données (Abstract)
 */
class Record : public QObject {
    Q_OBJECT
  public:
    enum Type { TypeBoardFamily, TypeBoardModel, TypeBoardVariant,
                TypeGpio, TypeConnectorFamily, TypeConnector,
                TypePin, TypePinType, TypePinMode, TypePinName, TypeFunction,
                TypeSocFamily, TypeSoc,
                TypeManufacturer, TypeArch,
                TypeNone = -1
              };

    Record (QSqlDatabase & database);
    virtual ~Record();

    virtual QString toolTip() const;
    virtual QIcon icon() const;

    virtual bool isWritable() const;
    virtual Type type() const;

    QSqlDatabase & database() const;
    virtual QString table() const = 0;

  public slots:
    virtual bool readFromDatabase() = 0;
    virtual bool writeToDatabase() = 0;
    virtual bool deleteToDatabase() = 0;

  signals:
    void updated();
    void changed();

  protected:
    Record (RecordPrivate &dd);
    const QScopedPointer<RecordPrivate> d_ptr;

  private:
    Q_DECLARE_PRIVATE (Record)
    Q_DISABLE_COPY (Record)
};
#endif
