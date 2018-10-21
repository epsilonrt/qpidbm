#include "node_p.h"
#include "property_p.h"
#include "boardmodel.h"
#include "boardvariant.h"

// -----------------------------------------------------------------------------
//                          Class BoardModelPrivate
// -----------------------------------------------------------------------------
class BoardModelPrivate : public PropertyPrivate {

  public:
    BoardModelPrivate (QSqlDatabase & database, BoardModel * q) :
      PropertyPrivate (database, q),
      family (database), soc (database)
    {}
    BoardFamily family;
    Soc soc;
    Q_DECLARE_PUBLIC (BoardModel);
};

// -----------------------------------------------------------------------------
//                          Class BoardModel
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
BoardModel::BoardModel (BoardModelPrivate &dd) : Property (dd) {}

// -----------------------------------------------------------------------------
BoardModel::BoardModel (QSqlDatabase & database) :
  Property (* new BoardModelPrivate (database, this)) {}

// -----------------------------------------------------------------------------
QString BoardModel::table() const {
  static QString t ("board_model");

  return t;
}

// -----------------------------------------------------------------------------
QIcon BoardModel::icon() const {

  return QIcon (":/images/board.png");
}

// -----------------------------------------------------------------------------
BoardFamily & BoardModel::family()  {
  Q_D (BoardModel);

  return d->family;
}

// -----------------------------------------------------------------------------
Soc & BoardModel::soc()  {
  Q_D (BoardModel);

  return d->soc;
}

// -----------------------------------------------------------------------------
bool BoardModel::readFromDatabase() {
  Q_D (BoardModel);
  QSqlQuery q (database());

  q.prepare ("SELECT "
             "name,board_family_id,soc_id "
             "FROM board_model "
             "WHERE id=?");
  q.addBindValue (d->id);
  q.exec();

  if (q.next()) {
    bool hasChanged = false;
    QString name = q.value (0).toString();
    int board_family_id =  q.value (1).toInt();
    int soc_id =  q.value (2).toInt();

    if (d->name != name) {
      d->name = name;
      hasChanged = true;
    }
    if (d->family.id() != board_family_id) {
      d->family.setId (board_family_id);
      hasChanged = true;
    }
    if (d->soc.id() != soc_id) {
      d->soc.setId (soc_id);
      hasChanged = true;
    }
    if (hasChanged) {
      emit changed();
    }
    return true;
  }

  return false;
}

// -----------------------------------------------------------------------------
bool BoardModel::writeToDatabase() {
  Q_D (const BoardModel);

  if (isWritable()) {
    QSqlQuery q (database());

    if (exists()) {
      if (hasName()) {
        q.prepare ("UPDATE board_model "
                   "SET name=?,board_family_id=?,soc_id=? "
                   "WHERE  id=?");
        q.addBindValue (d->name);
        q.addBindValue (d->family.id());
        q.addBindValue (d->soc.id());
        q.addBindValue (d->id);
      }
    }
    else {
      q.prepare ("INSERT INTO board_model "
                 "(id,name,board_family_id,soc_id) "
                 "VALUES (?,?,?,?)");
      q.addBindValue (d->id);
      q.addBindValue (d->name);
      q.addBindValue (d->family.id());
      q.addBindValue (d->soc.id());
    }

    if (q.exec()) {

      emit updated();
      return true;
    }
  }
  return false;
}

// -----------------------------------------------------------------------------
//                          Class BoardModelNode
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
BoardModelNode::BoardModelNode (int id, Node * parent) :
  PropertyNode (new BoardModel (parent->database()), parent) {

  data()->setId (id);
  getChildren();
}

// -----------------------------------------------------------------------------
BoardModelNode::~BoardModelNode() {

  delete data();
}

// -----------------------------------------------------------------------------
BoardModel * BoardModelNode::data() const {

  return reinterpret_cast<BoardModel *> (PropertyNode::data());
}

// -----------------------------------------------------------------------------
void BoardModelNode::getChildren() {
  QSqlQuery q (database());
  q.prepare ("SELECT id FROM board WHERE board_model_id = ?");
  q.addBindValue (data()->id());
  q.exec();
  clearChildren();

  while (q.next()) {

    int i = q.value (0).toInt();
    if (i >= 0) {

      append (new BoardVariantNode (i, this));
    }
  }
}
