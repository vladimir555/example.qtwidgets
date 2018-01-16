#include "main_window.h"
#include "ui_main_window.h"

#include "engine.h"

#include <QDebug>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QThread>


class BackgroundDelegate: public QStyledItemDelegate {
public:
    explicit BackgroundDelegate(QObject *parent = 0)
        : QStyledItemDelegate(parent)
    {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
        // Fill the background before calling the base class paint
        // otherwise selected cells would have a white background
        QVariant background = index.data(Qt::BackgroundRole);
        if (background.canConvert<QBrush>())
            painter->fillRect(option.rect, background.value<QBrush>());

        QStyledItemDelegate::paint(painter, option, index);

        // To draw a border on selected cells
//        if(option.state & QStyle::State_Selected) {
//            painter->save();
//            QPen pen(Qt::black, 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
//            int w = pen.width()/2;
//            painter->setPen(pen);
//            painter->drawRect(option.rect.adjusted(w,w,-w,-w));
//            painter->restore();
//        }
    }
};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //image: url(/Users/volodja/workspace/qtcreator/example.qtwidgets/apple.png)

    ui->setupUi(this);

    auto cell_width     = ui->buttonMenu->width();
    auto cell_height    = ui->buttonMenu->width();
    auto style_sheet    = "selection-background-color: rgba(0, 128, 0, 128);";
    auto icon_path      = ":/images/apple";

    auto table_widget_source_item  = new QTableWidgetItem();
    table_widget_source_item->setTextAlignment(Qt::AlignBottom | Qt::AlignRight);

    auto pixmap = QPixmap(icon_path).scaled(cell_width, cell_height);

    table_widget_source_item->setBackground(pixmap);
    table_widget_source_item->setText("1");
    table_widget_source_item->setFlags(table_widget_source_item->flags() ^ Qt::ItemIsEditable);

    ui->tableInventory->horizontalHeader()->setDefaultSectionSize(cell_width);
    ui->tableInventory->verticalHeader()->setDefaultSectionSize(cell_height);
    ui->tableInventory->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableInventory->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableInventory->setItemDelegate(new BackgroundDelegate(this));
    ui->tableInventory->setStyleSheet(style_sheet);

    ui->tableSource->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableSource->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableSource->setItemDelegate(new BackgroundDelegate(this));
    ui->tableSource->setStyleSheet(style_sheet);
    ui->tableSource->setItem(0, 0, table_widget_source_item);
    ui->tableSource->setFixedSize(cell_width, cell_height);

    this->adjustSize();
    this->setMaximumHeight(this->height());
    this->setMinimumHeight(this->height());
    this->setMaximumWidth(this->width());
    this->setMinimumWidth(this->width());

    Engine::instance().config.inventory_size =
        QSize(ui->tableInventory->columnCount(), ui->tableInventory->rowCount());

    Engine::instance().initialize();

    for (int h = 0; h < Engine::instance().config.inventory_size.height(); h++) {
        for (int w = 0; w < Engine::instance().config.inventory_size.width(); w++) {
            TCell cell = Engine::instance().inventory()->get(QSize(w, h));
            if (cell.item && cell.count > 0) {
                auto pixmap = QPixmap(cell.item->getIconPath()).scaled(cell_width, cell_height);

                auto table_widget_item = new QTableWidgetItem();

                table_widget_item->setBackground(pixmap);
                table_widget_item->setText(QString::number(cell.count));
                table_widget_item->setFlags(table_widget_source_item->flags() ^ Qt::ItemIsEditable);

                ui->tableInventory->setItem(w, h, table_widget_item);
            }
        }
    }
}


MainWindow::~MainWindow() {
    Engine::instance().finalize();
    delete ui;
}


void MainWindow::on_buttonStart_clicked() {
    auto geometry = ui->layoutMenu->geometry();
    m_menu_height = geometry.bottom();
    for (auto i = m_menu_height; i > 0; i--) {
        geometry.setBottom(i);
        ui->layoutMenu->setGeometry(geometry);
//        QThread::msleep(100);
    }
//    QSound::play(":/sounds/bite");
}


void MainWindow::on_buttonMenu_clicked() {
    auto geometry = ui->layoutMenu->geometry();
    for (auto i = 0; i < m_menu_height; i++) {
        geometry.setBottom(i);
        ui->layoutMenu->setGeometry(geometry);
        ui->layoutMenu->update();
//        QThread::msleep(10);
    }
}

void MainWindow::on_buttonExit_clicked() {
    QApplication::quit();
}
