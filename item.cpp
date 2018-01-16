#include "item.h"


Item::Item(Item::TType const &type, QString const &resource)
:
    m_icon_path(":/images/" + resource),
    m_type(type)
{
//    switch (m_type) {
//    case TYPE_APPLE:
//        m_icon_path = ":/images/apple";
//        break;
//    }
}


QString Item::getIconPath() const {
    return m_icon_path;
}


Item::TType Item::getType() const {
    return m_type;
}


bool Item::operator== (Item const &item) const {
    return m_type == item.m_type;
}
