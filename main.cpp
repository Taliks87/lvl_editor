#include <QApplication>
#include <QHBoxLayout>

#include "gui/editorwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    gui::EditorWindow w;
    w.show();


    return app.exec();
}