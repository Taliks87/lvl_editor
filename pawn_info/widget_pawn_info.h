#ifndef WIDGET_OBJECTS_H
#define WIDGET_OBJECTS_H

#include <QFrame>
#include "data/game_data.h"
#include "pawn_info/table_model_pawn.h"
#include "pawn_info/item_delegate_pawn.h"

namespace Ui {
class WidgetPawnInfo;
}

class WidgetPawnInfo : public QFrame
{
    Q_OBJECT

public:
    explicit WidgetPawnInfo(GameData& data, QWidget* parent = nullptr);
    ~WidgetPawnInfo();

    void setLevel(const QString& levelName);
private:
    Ui::WidgetPawnInfo* ui;
    TableModelPawn tableModelPawn;
    std::unique_ptr<ItemDelegatePawn> pDelegatePawn;
private slots:
    void select_pawn(const QModelIndex& index);
};

#endif // WIDGET_OBJECTS_H
