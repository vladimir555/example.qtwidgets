#ifndef ENGINE_H
#define ENGINE_H


#include <QApplication>
#include <QMutex>

#include "utility/pattern/singleton.h"
#include "utility/pattern/initializable.h"

#include "db.h"
#include "inventory.h"


class Engine:
    public utility::pattern::IInitializable,
    public IInventory,
    public utility::pattern::Singleton<Engine>
{
public:
    Engine() = default;
    virtual ~Engine() = default;

    struct TConfig {
        QSize inventory_size;
    } config;

    void initialize() override;
    void finalize() override;

    int   moveCell(QSize const &from, QSize const &to) override;
    TCell get     (QSize const &pos) override;


private:
    friend class utility::pattern::Singleton<Engine>;

    Inventory::TSharedPtr   inventory();

    QMutex                  m_mutex;
    DB::TSharedPtr          m_db;
    Inventory::TSharedPtr   m_inventory;
};


#endif // ENGINE_H
