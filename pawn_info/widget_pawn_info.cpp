#include "pawn_info/widget_pawn_info.h"
#include "ui_widget_pawn_info.h"
#include <memory>

WidgetPawnInfo::WidgetPawnInfo(GameData& data, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::WidgetPawnInfo),
    tableModelPawn(data, this)
{
    ui->setupUi(this);
    auto& tree = ui->treeView;
    tree->setModel(&tableModelPawn);
    pDelegatePawn = std::unique_ptr<ItemDelegatePawn>(new ItemDelegatePawn(tree));
    tree->setItemDelegate(pDelegatePawn.get());
}

WidgetPawnInfo::~WidgetPawnInfo()
{
    delete ui;
}

void WidgetPawnInfo::setLevel(const QString& levelName)
{
    tableModelPawn.refreshLevelData(levelName);
}

void WidgetPawnInfo::select_pawn(const QModelIndex& index)
{
    tableModelPawn.selectPawn(index);
    ui->treeView->reset();
}
