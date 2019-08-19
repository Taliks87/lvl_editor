#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QShowEvent>
#include <QVector>
#include "data/game_data.h"

namespace Ui {
    class EditorWindow;
}

class DialogEnterLevel;
class WidgetObjectTypes;
class WidgetMap;
class WidgetObjects;

enum LevelEvent{
    none = 0,
    create,
    save,
    load
};

class EditorWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit EditorWindow(QWidget* parent = nullptr);
    EditorWindow(const EditorWindow&) = delete;
    EditorWindow& operator=(const EditorWindow&) = delete;
    ~EditorWindow() override;

private:
    void fillObjectTypesView();

    Ui::EditorWindow *ui;
    DialogEnterLevel* dialogLevelName;
    WidgetObjectTypes* widgetObjectTypes;
    WidgetMap* widgetMap;
    WidgetObjects* widgetObjects;

    const QString rootPath;
    const QString configPath;
    GameData gameData;
    LevelEvent levelEvent;
    QString activelevelName;

private slots:
    void on_action_create_triggered();
    void enter_level(const QString& activelevelName);
    void on_action_save_triggered();
    void on_action_load_triggered();
};

#endif // EDITORWINDOW_H
