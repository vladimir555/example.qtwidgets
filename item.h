#ifndef ITEM_H
#define ITEM_H


#include <QString>

#include "utility/smart_ptr.h"


class Item {
public:
    DEFINE_SMART_PTR(Item)
    DEFINE_CREATE(Item)
    Item();

    enum TType {
        TYPE_APPLE
    };

    Item(TType const &type, QString const &resource);
    ~Item() = default;

    QString  getIconPath() const;
    TType    getType() const;

    bool     operator== (Item const &item) const;

private:
    QString  m_icon_path;
    TType    m_type;
};


#endif // ITEM_H
