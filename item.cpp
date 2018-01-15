#include "item.h"


Item::Item(Item::Type const &type)
:
    m_type(type)
{
    switch (m_type) {
    case TYPE_APPLE:
        m_icon_path = ":/images/apple";
        break;
    }
}


QString Item::getIconPath() const {
    return m_icon_path;
}


Item::Type Item::getType() const {
    return m_type;
}
