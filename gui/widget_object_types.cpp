#include "widget_object_types.h"
#include "ui_widget_object_types.h"
#include "core/game_object_description.h"


WidgetObjectTypes::WidgetObjectTypes(GameData* pData, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::WidgetObjectTypes),
    listModelObjectTypes(pData, this)
{
    ui->setupUi(this);
    ui->listView->setDragEnabled(true);
}

void WidgetObjectTypes::refreshData()
{
    ui->listView->setModel(&listModelObjectTypes);
}

WidgetObjectTypes::~WidgetObjectTypes()
{
    delete ui;    
}
