#include "widget_object_types.h"
#include "ui_widget_object_types.h"
#include "core/game_object_description.h"

WidgetObjectTypes::WidgetObjectTypes(GameData& data, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::WidgetObjectTypes),
    listModelObjectTypes(data, this)
{
    ui->setupUi(this);
    auto& list = ui->listView;
    list->setSelectionMode(QAbstractItemView::SingleSelection);
    list->setDragEnabled(true);
    list->setAcceptDrops(true);
    list->setDropIndicatorShown(true);
    list->setModel(&listModelObjectTypes);
}

void WidgetObjectTypes::refreshData()
{
    ui->listView->reset();
}

WidgetObjectTypes::~WidgetObjectTypes()
{
    delete ui;    
}
