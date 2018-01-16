#ifndef CELL_H
#define CELL_H


#include "item.h"


struct TCell {
    Item::TSharedPtr    item;
    int                 count;
};


#endif // CELL_H
