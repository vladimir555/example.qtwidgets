#include "main_window.h"
#include "ui_main_window.h"
#include "QDebug"
#include "QStyledItemDelegate"
#include "QPainter"


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

    auto cell_width     = ui->buttonMainMenu->width();
    auto cell_height    = ui->buttonMainMenu->width();

    auto table_widget_source_item  = new QTableWidgetItem();
    table_widget_source_item->setTextAlignment(Qt::AlignBottom | Qt::AlignRight);

    auto pixmap = QPixmap("/Users/volodja/workspace/qtcreator/example.qtwidgets/apple.png").scaled
            (cell_width, cell_height);

    table_widget_source_item->setBackground(pixmap);
    table_widget_source_item->setText("1");
    table_widget_source_item->setFlags(table_widget_source_item->flags() ^ Qt::ItemIsEditable);

    ui->tableInventory->horizontalHeader()->setDefaultSectionSize(cell_width);
    ui->tableInventory->verticalHeader()->setDefaultSectionSize(cell_height);
    ui->tableInventory->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableInventory->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableInventory->setItemDelegate(new BackgroundDelegate(this));
    ui->tableInventory->setStyleSheet("selection-background-color: rgba(0, 0, 128, 10);");

    ui->tableSource->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableSource->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableSource->setItemDelegate(new BackgroundDelegate(this));
    ui->tableSource->setStyleSheet("selection-background-color: rgba(0, 0, 128, 10);");
    ui->tableSource->setItem(0, 0, table_widget_source_item);
    ui->tableSource->setFixedSize(cell_width, cell_height);

    this->adjustSize();
    this->setMaximumHeight(this->height());
    this->setMinimumHeight(this->height());
    this->setMaximumWidth(this->width());
    this->setMinimumWidth(this->width());
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButtonStart_clicked() {
    auto geometry = ui->layoutMenu->geometry();
    m_menu_height = geometry.bottom();
    geometry.setBottom(0);
    ui->layoutMenu->setGeometry(geometry);
}
