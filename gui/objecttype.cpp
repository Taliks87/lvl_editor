#include "gui/objecttype.h"
#include "ui_objecttype.h"

namespace gui {
    ObjectType::ObjectType(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ObjectType)
    {
        ui->setupUi(this);
    }

    ObjectType::~ObjectType()
    {
        delete ui;
    }
}
