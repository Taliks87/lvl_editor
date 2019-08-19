#include "pawn_type/widget_pawn_types.h"
#include "ui_widget_pawn_types.h"
#include "data/pawn_type.h"

WidgetPawnTypes::WidgetPawnTypes(GameData& data, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::WidgetPawnTypes),
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

WidgetPawnTypes::~WidgetPawnTypes()
{
    delete ui;    
}

void WidgetPawnTypes::refreshData()
{
    ui->listView->reset();
}

void WidgetPawnTypes::setLevel(const QString& levelName)
{
    listModelObjectTypes.refreshLevelData(levelName);
}
