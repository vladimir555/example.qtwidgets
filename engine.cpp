#include "engine.h"

#include "exception.h"

#include <QMessageBox>

#include "utility/assert.h"


void Engine::initialize() {
    try {
        if (!m_db) {
            m_db = DB::create();
            m_db->initialize();
        }

        if (!m_inventory) {
            m_inventory = Inventory::create(config.inventory_size, m_db);
            m_inventory->initialize();
        }
    } catch (Exception const &e) {
        QMessageBox mbox;
        mbox.critical(0, "Fatal error", e.what());
        throw;
    }
}


void Engine::finalize() {

    try {
        if (m_inventory)
            m_inventory->finalize();
        if (m_db)
            m_db->finalize();

    } catch (Exception const &e) {
        QMessageBox mbox;
        mbox.critical(0, "Fatal error", e.what());
    }
}


Inventory::TSharedPtr Engine::inventory() {
    return utility::assertExists(m_inventory, "inventory not initialized");
}
