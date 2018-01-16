#ifndef DB_H
#define DB_H


#include <QSize>
#include <QSqlDatabase>
#include <QSharedPointer>

#include "cell.h"

#include "utility/pattern/initializable.h"
#include "utility/smart_ptr.h"


class DB: public utility::pattern::IInitializable {
public:
    DEFINE_SMART_PTR(DB)
    DEFINE_CREATE(DB)
    DB() = default;
    virtual ~DB() = default;

    virtual void initialize() override;
    virtual void finalize() override;

    void updateCell(QSize const &pos, TCell const &cell);
    TCell getCell(QSize const &pos);

    // todo: full table loading method

private:
    QSharedPointer<QSqlDatabase> m_database;

};


#endif // DB_H
