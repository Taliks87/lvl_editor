#include "widget_map.h"
#include "ui_widget_map.h"

WidgetMap::WidgetMap(GameData& data, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::WidgetMap),
    tableModelMap(data)
{    
    ui->setupUi(this);
    auto& table = ui->tableView;
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setDragEnabled(true);
    table->setAcceptDrops(true);
    table->setDropIndicatorShown(true);
    table->setModel(&tableModelMap);
}

WidgetMap::~WidgetMap()
{
    delete ui;
}

void WidgetMap::setLevel(const QString& levelName)
{
    tableModelMap.refreshLevelMap(levelName);
}
