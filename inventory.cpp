#include "inventory.h"
#include "exception.h"
#include "utility/assert.h"
#include <QDebug>


Inventory::Inventory(QSize const &size, DB::TSharedPtr const &db)
:
    m_size  (size),
    m_items (size.height()),
    m_db    (utility::assertExists(db, "db is null"))
{
    for (auto h = 0; h < size.height(); h++)
        m_items[h].resize(size.width());
}


void Inventory::add(QSize const &pos, Item const &item) {
    assertPos(pos);
    if (cell(pos).count == 0)
        cell(pos).item = Item::create(item);
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


TCell Inventory::get(QSize const &pos) {
    return cell(pos);
}


void Inventory::initialize() {
    for (auto h = 0; h < m_size.height(); h++) {
        for (auto w = 0; w < m_size.width(); w++) {
            auto pos  = QSize(w, h);
            cell(pos) = m_db->getCell(pos);
        }
    }
}


void Inventory::finalize() {
}


void Inventory::assertPos(QSize const &pos) const {
    if (pos.width()  < 0 || pos.width()  > m_size.width() ||
        pos.height() < 0 || pos.height() > m_size.height())
        throw Exception("inventory: wrong index " +
            QString::number(pos.width()) + ", " +
            QString::number(pos.height()));
}


TCell &Inventory::cell(QSize const &pos) {
    return m_items[pos.height()][pos.width()];
}
