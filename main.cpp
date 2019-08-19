#include <QApplication>
#include <QHBoxLayout>

#include "editorwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    EditorWindow w;
    w.show();

    return app.exec();
}
