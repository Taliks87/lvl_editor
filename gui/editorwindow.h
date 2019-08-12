#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>

namespace Ui {
    class EditorWindow;
}

namespace gui {
    class DialogEnterLevel;

    enum LevelEvent{
        none = 0,
        create,
        load,
        save
    };

    class EditorWindow : public QMainWindow
    {
        Q_OBJECT
    public:
        explicit EditorWindow(QWidget* parent = nullptr);
        ~EditorWindow();

    private:
        Ui::EditorWindow *ui;
        DialogEnterLevel* windowLevel;
        LevelEvent levelEvent;
    private slots:
        void on_action_create_triggered();        
        void enter_level(const QString& fileName);
    };
}

#endif // EDITORWINDOW_H
