#ifndef ITEM_H
#define ITEM_H


#include <QString>


class Item {
public:
    Item();

    enum Type {
        TYPE_APPLE
    };

    Item(Type const &type);
    ~Item() = default;

private:
    QString m_icon_path;
    Type    m_type;
};


#endif // ITEM_H
