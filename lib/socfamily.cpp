#include "node_p.h"
#include "property_p.h"
#include "soc.h"

// -----------------------------------------------------------------------------
//                          Class SocFamilyPrivate
// -----------------------------------------------------------------------------
class SocFamilyPrivate : public PropertyPrivate {

  public:
    SocFamilyPrivate (QSqlDatabase & database, SocFamily * q) :
      PropertyPrivate (database, q), arch (database)  {}
    Arch arch;
    Q_DECLARE_PUBLIC (SocFamily);
};

// -----------------------------------------------------------------------------
//                          Class SocFamily
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
SocFamily::SocFamily (SocFamilyPrivate &dd) : Property (dd) {}

// -----------------------------------------------------------------------------
SocFamily::SocFamily (QSqlDatabase & database) :
  Property (* new SocFamilyPrivate (database, this)) {}

// -----------------------------------------------------------------------------
QString SocFamily::table() const {
  static QString t ("soc_family");

  return t;
}

// -----------------------------------------------------------------------------
Arch & SocFamily::arch()  {
  Q_D (SocFamily);

  return d->arch;
}

// -----------------------------------------------------------------------------
bool SocFamily::readFromDatabase() {
  Q_D (SocFamily);
  QSqlQuery q (database());

  q.prepare ("SELECT name,arch_id FROM soc_family WHERE id=?");
  q.addBindValue (d->id);
  q.exec();

  if (q.next()) {
    bool hasChanged = false;
    QString name = q.value (0).toString();
    int arch_id =  q.value (1).toInt();

    if (d->name != name) {
      d->name = name;
      hasChanged = true;
    }
    if (d->arch.id() != arch_id) {
      d->arch.setId (arch_id);
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
//                          Class SocFamilyNode
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
SocFamilyNode::SocFamilyNode (int id, Node * parent) :
  PropertyNode (new SocFamily (parent->database()), parent) {

  data()->setId (id);
  getChildren();
}

// -----------------------------------------------------------------------------
SocFamilyNode::~SocFamilyNode() {
  
  delete data();
}

// -----------------------------------------------------------------------------
void SocFamilyNode::getChildren() {
  QSqlQuery q (database());
  q.prepare ("SELECT id FROM soc WHERE soc_family_id = ?");
  q.addBindValue (data()->id());
  q.exec();
  clearChildren();

  while (q.next()) {

    int i = q.value (0).toInt();
    if (i >= 0) {

      append (new SocNode (i, this));
    }
  }
}

// -----------------------------------------------------------------------------
SocFamily * SocFamilyNode::data() const {

  return reinterpret_cast<SocFamily *> (PropertyNode::data());
}
