#ifndef INVENTORY_H
#define INVENTORY_H


#include <QVector>
#include <QSharedPointer>
#include <QSize>

#include "item.h"
#include "cell.h"
#include "db.h"

#include "utility/pattern/initializable.h"


class Inventory: public utility::pattern::IInitializable {
public:
    Inventory(QSize const &size, DB &db);
    virtual ~Inventory() = default;

    void  add           (QSize const &pos, Item const &item);
    void  decreaseItem  (QSize const &pos);
    int   moveCell      (QSize const &from, QSize const &to);

    virtual void initialize() override;
    virtual void finalize() override;

private:
    void  assertPos(QSize const &pos) const;
    TCell &cell(QSize const &pos);

    QSize                       m_size;
    QVector<QVector<TCell> >    m_items;

    DB &m_db;
};


#endif // INVENTORY_H
