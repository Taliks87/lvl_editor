#include <QSizePolicy>
#include <QDropEvent>
#include <QDebug>
#include "widget_map.h"
#include "ui_widget_map.h"

WidgetMap::WidgetMap(GameData& data, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::WidgetMap),
    tableModelMap(data, this),
    pDelegateMap(nullptr)
{    
    ui->setupUi(this);
    auto& table = ui->tableView;
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setDragEnabled(true);
    table->setAcceptDrops(true);
    table->setDropIndicatorShown(true);
    table->setModel(&tableModelMap);
    pDelegateMap = new ItemDelegateMap(table);
    table->setItemDelegate(pDelegateMap);
}

WidgetMap::~WidgetMap()
{
    delete pDelegateMap;
    delete ui;
}

void WidgetMap::setLevel(const QString& levelName)
{
    tableModelMap.refreshLevelData(levelName);
}

void WidgetMap::on_tableView_clicked(const QModelIndex& index)
{
    if(index.isValid())
    {
        emit select_pawn(index);
    }
}

void WidgetMap::dropItemOnMap(int column, int row)
{
    QItemSelectionModel* selectionModel = ui->tableView->selectionModel();
    QModelIndex selectIndex = tableModelMap.index(row, column, QModelIndex());
    QItemSelection selection(selectIndex, selectIndex);
    selectionModel->select(selection, QItemSelectionModel::ClearAndSelect);

    on_tableView_clicked(selectIndex);
}
