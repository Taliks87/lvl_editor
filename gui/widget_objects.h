#ifndef WIDGET_OBJECTS_H
#define WIDGET_OBJECTS_H

#include <QFrame>
#include "core/game_object.h"
#include "model/tree_model_pawn.h"

namespace Ui {
class WidgetObjects;
}

class WidgetObjects : public QFrame
{
    Q_OBJECT

public:
    explicit WidgetObjects(GameData& data, QWidget* parent = nullptr);
    ~WidgetObjects();

    void setLevel(const QString& levelName);
private:
    Ui::WidgetObjects *ui;    
    TreeModelPawn treeModelPawn;
private slots:
    void select_pawn(const QModelIndex& index);
};

#endif // WIDGET_OBJECTS_H
