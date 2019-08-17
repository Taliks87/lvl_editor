#include "widget_objects.h"
#include "ui_widget_objects.h"

WidgetObjects::WidgetObjects(GameData& data, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::WidgetObjects),
    treeModelPawn(data, this)
{
    ui->setupUi(this);
    auto& tree = ui->treeView;
//    tree->setSelectionMode(QAbstractItemView::SingleSelection);
    tree->setModel(&treeModelPawn);
}

WidgetObjects::~WidgetObjects()
{
    delete ui;
}

void WidgetObjects::setLevel(const QString& levelName)
{
    treeModelPawn.refreshLevelData(levelName);
}

void WidgetObjects::select_pawn(const QModelIndex& index)
{
    treeModelPawn.selectPawn(index);
    ui->treeView->reset();
}
