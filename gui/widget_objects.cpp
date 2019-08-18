#include "widget_objects.h"
#include "ui_widget_objects.h"
#include <memory>

WidgetObjects::WidgetObjects(GameData& data, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::WidgetObjects),
    treeModelPawn(data, this)
{
    ui->setupUi(this);
    auto& tree = ui->treeView;
    tree->setModel(&treeModelPawn);
    pDelegatePawn = std::unique_ptr<ItemDelegatePawn>(new ItemDelegatePawn(tree));
    tree->setItemDelegate(pDelegatePawn.get());
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
