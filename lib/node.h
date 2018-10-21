#ifndef NODE_H
#define NODE_H

#include "property.h"

class NodePrivate;
class RootNode;
class ChildNode;

/**
 * @class Node
 * @brief Noeud hiérarchique
 */
class Node {
  public:

    Node ();
    virtual ~Node();

    virtual void getChildren() {}
    virtual Node * parent() const = 0;
    virtual const RootNode * root() const = 0;

    const QList<Node *> & children() const;
    void append (Node * child);
    void clearChildren();

    virtual QSqlDatabase & database() const;

    virtual QString name() const;
    virtual QString toolTip() const;
    virtual QIcon icon() const;

  protected:
    Node (NodePrivate &dd);
    const QScopedPointer<NodePrivate> d_ptr;

  private:
    Q_DECLARE_PRIVATE (Node)
    Q_DISABLE_COPY (Node)
};

/**
 * @class ChildNode
 * @brief Noeud enfant (abstrait)
 */
class ChildNodePrivate;
class ChildNode : public Node {
  public:

    ChildNode (Node * parent);
    virtual Node * parent() const;
    virtual const RootNode * root() const;
    virtual Record::Type type() const = 0;

  protected:
    ChildNode (ChildNodePrivate &dd);

  private:
    Q_DECLARE_PRIVATE (ChildNode);
    Q_DISABLE_COPY (ChildNode);
};

/**
 * @class PropertyNode
 * @brief Noeud Propriété (abstrait)
 */
class PropertyNodePrivate;
class PropertyNode : public ChildNode {
  public:

    PropertyNode (Property * data, Node * parent);
    Property * data() const;
    
    virtual Record::Type type() const;
    virtual QString name() const;
    virtual QString toolTip() const;
    virtual QIcon icon() const;

  protected:
    PropertyNode (PropertyNodePrivate &dd);

  private:
    Q_DECLARE_PRIVATE (PropertyNode);
    Q_DISABLE_COPY (PropertyNode);
};

/**
 * @class RootNode
 * @brief Noeud racine
 */
class RootNodePrivate;
class RootNode : public Node {
  public:

    RootNode (QSqlDatabase & database);
    Node * parent() const { return 0; }
    QSqlDatabase & database() const;
    
    QString name() const;
    QString toolTip() const;
    void getChildren();
    const RootNode * root() const { return this; }

  protected:
    RootNode (RootNodePrivate &dd);

  private:
    Q_DECLARE_PRIVATE (RootNode);
    Q_DISABLE_COPY (RootNode);
};

#endif
