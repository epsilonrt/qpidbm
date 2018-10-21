#include "manufacturer.h"

// -----------------------------------------------------------------------------
//                          Class Manufacturer
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
QIcon Manufacturer::icon() const {

  return QIcon (":/images/manufacturer.png");
}

// -----------------------------------------------------------------------------
//                          Class ManufacturerNode
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
ManufacturerNode::ManufacturerNode (int id, Node * parent) :
  PropertyNode (new Manufacturer (parent->database()), parent) {

  data()->setId (id);
}

// -----------------------------------------------------------------------------
ManufacturerNode::~ManufacturerNode() {

  delete data();
}

// -----------------------------------------------------------------------------
Manufacturer * ManufacturerNode::data() const {

  return reinterpret_cast<Manufacturer *> (PropertyNode::data());
}
