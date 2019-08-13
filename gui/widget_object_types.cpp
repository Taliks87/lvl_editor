#include "widget_object_types.h"
#include "ui_widget_object_types.h"

WidgetObjectTypes::WidgetObjectTypes(QVector<GObjectType>* pData_, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::WidgetObjectTypes),
    listModelObjectTypes(pData_)
{
    ui->setupUi(this);    
    ui->listView->setModel(&listModelObjectTypes);
}

WidgetObjectTypes::~WidgetObjectTypes()
{
    delete ui;    
}
