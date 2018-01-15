#include "item.h"


Item::Item(Item::Type const &type)
:
    m_type(type)
{
    switch (m_type) {
    case TYPE_APPLE:
        m_icon_path = "apple.png";
        break;
    }
}
