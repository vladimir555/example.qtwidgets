#ifndef INVENTORY_H
#define INVENTORY_H


#include <QVector>
#include <QSharedPointer>
#include <QSize>

#include "item.h"


class Inventory {
public:
    struct TCell {
        QSharedPointer<Item const>  item;
        int                         count;
    };

    Inventory(QSize const &size);
    ~Inventory() = default;

    void  add           (QSize const &pos, Item const &item);
    void  decreaseItem  (QSize const &pos);
    int   moveCell      (QSize const &from, QSize const &to);

private:
    void  assertPos(QSize const &pos) const;
    TCell &cell(QSize const &pos);


    QSize                       m_size;
    QVector<QVector<TCell> >    m_items;
};


#endif // INVENTORY_H
