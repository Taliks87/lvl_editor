#include "pawn_type/widget_object_types.h"
#include "ui_widget_object_types.h"
#include "data/pawn_type.h"

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

WidgetObjectTypes::~WidgetObjectTypes()
{
    delete ui;    
}

void WidgetObjectTypes::refreshData()
{
    ui->listView->reset();
}


void WidgetObjectTypes::setLevel(const QString& levelName)
{
    listModelObjectTypes.refreshLevelData(levelName);
}
