#ifndef INVENTORY_H
#define INVENTORY_H


#include <QVector>
#include <QSharedPointer>
#include <QSize>

#include "item.h"
#include "cell.h"
#include "db.h"

#include "utility/pattern/initializable.h"
#include "utility/smart_ptr.h"


class IInventory {
public:
    DEFINE_INTERFACE(IInventory)

    virtual int   moveCell(QSize const &from, QSize const &to) = 0;
    virtual TCell get     (QSize const &pos) = 0;
};


class Inventory:
    public utility::pattern::IInitializable,
    public IInventory
{
public:
    DEFINE_SMART_PTR(Inventory)
    DEFINE_CREATE(Inventory)
    Inventory(QSize const &size, DB::TSharedPtr const &db);
    virtual ~Inventory() = default;

    void  add           (QSize const &pos, Item const &item);
    void  decreaseItem  (QSize const &pos);
    int   moveCell      (QSize const &from, QSize const &to) override;
    TCell get           (QSize const &pos) override;

    virtual void initialize() override;
    virtual void finalize() override;

private:
    void  assertPos(QSize const &pos) const;
    TCell &cell(QSize const &pos);

    QSize                       m_size;
    QVector<QVector<TCell> >    m_items;

    DB::TSharedPtr m_db;
};


#endif // INVENTORY_H
