#ifndef WIDGET_OBJECT_TYPES_H
#define WIDGET_OBJECT_TYPES_H

#include <QFrame>
#include "model/list_model_object_types.h"

namespace Ui {
class WidgetObjectTypes;
}

class WidgetObjectTypes : public QFrame
{
    Q_OBJECT

public:
    explicit WidgetObjectTypes(QVector<GObjectType>* pData_, QWidget *parent = nullptr);
    ~WidgetObjectTypes();

private:
    Ui::WidgetObjectTypes *ui;
    ListModelObjectTypes listModelObjectTypes;
};

#endif // WIDGET_OBJECT_TYPES_H
