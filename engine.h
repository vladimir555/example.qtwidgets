#ifndef ENGINE_H
#define ENGINE_H


#include "utility/pattern/singleton.h"
#include "utility/pattern/initializable.h"

#include "db.h"
#include "inventory.h"


class Engine:
    public utility::pattern::Singleton<Engine>,
    public utility::pattern::IInitializable
{
public:
    Engine();
    virtual ~Engine() = default;
    friend class utility::pattern::Singleton<Engine>;

    struct TConfig {
        QSize inventory_size;
    } config;

    virtual void initialize() override;
    virtual void finalize() override;

    Inventory &inventory();

private:
    DB          m_db;
    Inventory   m_inventory;
};


#endif // ENGINE_H
