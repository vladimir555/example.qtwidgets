#ifndef ENGINE_H
#define ENGINE_H


#include <QApplication>

#include "utility/pattern/singleton.h"
#include "utility/pattern/initializable.h"

#include "db.h"
#include "inventory.h"


class Engine:
    public utility::pattern::IInitializable,
    public utility::pattern::Singleton<Engine>
{
public:
    Engine() = default;
    virtual ~Engine() = default;

    struct TConfig {
        QSize inventory_size;
    } config;

    virtual void initialize() override;
    virtual void finalize() override;

    Inventory::TSharedPtr inventory();

private:
    friend class utility::pattern::Singleton<Engine>;

    DB::TSharedPtr          m_db;
    Inventory::TSharedPtr   m_inventory;
};


#endif // ENGINE_H
