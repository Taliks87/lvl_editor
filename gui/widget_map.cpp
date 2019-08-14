#include "widget_map.h"
#include "ui_widget_map.h"

WidgetMap::WidgetMap(GameData* pData, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::WidgetMap)
{
    ui->setupUi(this);
}

WidgetMap::~WidgetMap()
{
    delete ui;
}
