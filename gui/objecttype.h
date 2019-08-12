#ifndef OBJECTTYPE_H
#define OBJECTTYPE_H

#include <QWidget>

namespace Ui {
    class ObjectType;
}

namespace gui {
    class ObjectType : public QWidget
    {
        Q_OBJECT

    public:
        explicit ObjectType(QWidget* parent = nullptr);
        ~ObjectType();

    private:
        Ui::ObjectType *ui;
    };
}

#endif // OBJECTTYPE_H
