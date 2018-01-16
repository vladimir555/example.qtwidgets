#ifndef DB_H
#define DB_H


#include <QSize>
#include <QSqlDatabase>

#include "cell.h"

#include "utility/pattern/initializable.h"


class DB: public utility::pattern::IInitializable {
public:
    DB() = default;
    virtual ~DB() = default;

    virtual void initialize() override;
    virtual void finalize() override;

    void updateCell(QSize const &pos, TCell const &cell);
    TCell getCell(QSize const &pos);

private:
    QSqlDatabase m_database;

};


#endif // DB_H
