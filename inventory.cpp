#include "inventory.h"
#include "exception.h"


Inventory::Inventory(QSize const &size)
:
    m_items(size.height())
{
    for (auto row: m_items)
        row.resize(size.width());
}


void Inventory::add(QSize const &pos, Item const &item) {
    assertPos(pos);
    if (cell(pos).count == 0)
        cell(pos).item = QSharedPointer<Item>::create(item);
    else {
        if (cell(pos).item && *cell(pos).item == item)
            cell(pos).count++;
        else
            Exception("inventory: source and destination items are not equal");
    }
}


void Inventory::decreaseItem(QSize const &pos) {
    assertPos(pos);
    if (cell(pos).count > 0) {
        cell(pos).count--;
        //todo: sound
    }
}


int Inventory::moveCell(QSize const &from, QSize const &to) {
    assertPos(from);
    assertPos(to);

    if (cell(from).count > 0 && cell(from).item == cell(to).item) {
        if (cell(from).item == cell(to).item) {
            cell(to).count  += cell(from).count;
            cell(from).count = 0;
        } else
            throw Exception("inventory: source and destination items are not equal");
    }
    return cell(to).count;
}


void Inventory::assertPos(QSize const &pos) const {
    if (pos.width()  < 0 || pos.width()  > m_size.width() ||
        pos.height() < 0 || pos.height() > m_size.height())
        throw Exception("inventory: wrong index " +
            QString::number(pos.width()) + ", " +
            QString::number(pos.height()));
}


Inventory::TCell &Inventory::cell(QSize const &pos) {
    return m_items[pos.height() - 1][pos.width()];
}
