#include "map/widget_map.h"
#include "ui_widget_map.h"
#include <QSizePolicy>
#include <QDropEvent>
#include <QDebug>

WidgetMap::WidgetMap(GameData& data, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::WidgetMap),
    tableModelMap(data, this),
    pDelegateMap()
{    
    ui->setupUi(this);
    auto& table = ui->tableView;
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setDragEnabled(true);
    table->setAcceptDrops(true);
    table->setDropIndicatorShown(true);
    table->setModel(&tableModelMap);
    pDelegateMap = std::unique_ptr<ItemDelegateMap>(new ItemDelegateMap(table));
    table->setItemDelegate(pDelegateMap.get());
    connect(&tableModelMap, SIGNAL(change_completed(const QModelIndex&)), this, SLOT(on_tableView_clicked(const QModelIndex&)));
}

WidgetMap::~WidgetMap()
{    
    delete ui;
}

void WidgetMap::setLevel(const QString& levelName)
{
    ui->tableView->clearSelection();
    tableModelMap.refreshLevelData(levelName);    
}

void WidgetMap::on_tableView_clicked(const QModelIndex& index)
{
    QItemSelectionModel* selectionModel = ui->tableView->selectionModel();
    QItemSelection selection(index, index);
    selectionModel->select(selection, QItemSelectionModel::ClearAndSelect);

    if(index.isValid())
    {
        emit select_pawn(index);
    }
}


