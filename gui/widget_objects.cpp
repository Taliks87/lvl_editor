#include "widget_objects.h"
#include "ui_widget_objects.h"

WidgetObjects::WidgetObjects(GameData* pData, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::WidgetObjects)
{
    ui->setupUi(this);
}

WidgetObjects::~WidgetObjects()
{
    delete ui;
}
