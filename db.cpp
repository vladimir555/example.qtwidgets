#include "db.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QSharedPointer>
#include <QResource>
#include <QApplication>
#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include <QDebug>

#include "exception.h"

#include "utility/assert.h"


namespace {


QString const DB_TYPE               = "QSQLITE";
//QString const DB_NAME               = "/Users/volodja/workspace/qtcreator/example.qtwidgets/example_qwidgets.sqlite";
//QString const DB_NAME             = "/home/volodja/workspace/example.qtwidgets/example_qwidgets.sqlite";
//QString const DB_NAME             = ":/db/inventory";
QString const TABLE_ITEMS           = "items";
QString const TABLE_ITEM_TYPES      = "item_types";
QString const FIELD_ID_TYPE         = TABLE_ITEMS + ".id_type";
QString const FIELD_COUNT           = TABLE_ITEMS + ".count_";
QString const FIELD_ID_W            = TABLE_ITEMS + ".id_w";
QString const FIELD_ID_H            = TABLE_ITEMS + ".id_h";
QString const FIELD_RESOURCE        = TABLE_ITEM_TYPES + ".resource";


}


void DB::initialize() {
    QString const DB_DIR  = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString const DB_NAME = DB_DIR + "/" + QApplication::applicationDisplayName() + ".sqlite";

    if (!QFile(DB_NAME).exists()) {
        qDebug() << "create " << DB_NAME;
        QDir().mkdir(DB_DIR);
        QFile::copy(":/db/inventory", DB_NAME);
    }

    m_database = QSharedPointer<QSqlDatabase>::create(QSqlDatabase::addDatabase(DB_TYPE));
    m_database->setDatabaseName(DB_NAME);

    if (!m_database->open())
        throw Exception("db: " + m_database->lastError().text());
}


void DB::finalize() {
    if (m_database && m_database->isOpen())
        m_database->close();
    m_database.clear();
}


void DB::updateCell(QSize const &pos, TCell const &cell) {
    utility::assertExists(m_database, "db: not initialized");

    QString id_type = "0";
    QString count   = QString::number(cell.count);

    if (cell.item)
        id_type = QString::number(cell.item->getType());

    QString query =
        "update " + TABLE_ITEMS + " set " + FIELD_ID_W + " = " + QString::number(pos.width()) +
        ", " + FIELD_ID_H + " = " + QString::number(pos.height()) + ", " +
            FIELD_ID_TYPE + " = " + id_type + ", " + FIELD_COUNT + " = " + count;



    m_database->exec(query);

    if (m_database->lastError().isValid())
        throw Exception("db: " + m_database->lastError().text());
}


TCell DB::getCell(QSize const &pos) {
    utility::assertExists(m_database, "db: not initialized");

    QString query =
        "select " + FIELD_ID_TYPE + ", " + FIELD_COUNT + ", " + FIELD_RESOURCE +
        " from "  + TABLE_ITEMS + " inner join " + TABLE_ITEM_TYPES +
        " where " + FIELD_ID_W  + " = " + QString::number(pos.width()) +
        " and "   + FIELD_ID_H  + " = " + QString::number(pos.height()) + ";";

    auto result = m_database->exec(query);

    if (m_database->lastError().isValid())
        throw Exception("db: " + m_database->lastError().text());

    if (result.size() > 1)
        throw Exception("db: inventory rows by w h > 1 ");

    TCell cell;
    cell.count = 0;
    if (result.next()) {
        if (result.value(FIELD_COUNT).canConvert<int>())
            cell.count = result.value(FIELD_COUNT).toInt();

        if (result.value(FIELD_ID_TYPE).canConvert<int>() &&
            result.value(FIELD_RESOURCE).canConvert<QString>()
        )
            cell.item = Item::create
                (static_cast<Item::TType>(result.value(FIELD_ID_TYPE).toInt()),
                 result.value(FIELD_RESOURCE).toString());
    }

    return cell;
}
