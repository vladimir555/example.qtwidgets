#include "engine.h"


//namespace  {


//const QSize INVENTORY_SIZE(3, 3);


//} // unnamed


Engine::Engine()
:
    m_inventory(config.inventory_size, m_db)
{}


void Engine::initialize() {
    m_db.initialize();
    m_inventory.initialize();
}


void Engine::finalize() {
    m_inventory.finalize();
    m_db.finalize();
}


Inventory &Engine::inventory() {
    return m_inventory;
}
