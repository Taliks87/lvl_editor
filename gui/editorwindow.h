#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QShowEvent>
#include <QVector>
#include "core/game_object_description.h"

namespace Ui {
    class EditorWindow;
}

class DialogEnterLevel;
class WidgetObjectTypes;

enum LevelEvent{
    none = 0,
    create,
    load
};

class EditorWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit EditorWindow(QWidget* parent = nullptr);
    ~EditorWindow() override;

protected:
    void showEvent(QShowEvent *event) override;

private:
    void fillObjectTypesView();

    Ui::EditorWindow *ui;
    DialogEnterLevel* dialogLevelName;
    WidgetObjectTypes* widgetObjectTypes;

    const QString rootPath;
    const QString configPath;
    QVector<GObjectType> gObjectTypes;
    GRules gRules;
    LevelEvent levelEvent;
    QString levelName;
private slots:
    void on_action_create_triggered();
    void enter_level(const QString& levelName);
    void on_action_save_triggered();
};

#endif // EDITORWINDOW_H
