#ifndef DIALOG_LEVEL_H
#define DIALOG_LEVEL_H

#include <QDialog>

namespace Ui {
    class DialogEnterLevel;
}

class DialogEnterLevel : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEnterLevel(QWidget *parent = nullptr);
    DialogEnterLevel(const DialogEnterLevel&) = delete;
    DialogEnterLevel& operator=(const DialogEnterLevel&) = delete;
    void setup_window(const QString& lableText);
    ~DialogEnterLevel();

private:
    Ui::DialogEnterLevel *ui;

signals:
    void enter_name(const QString& str);
private slots:
    void ok_clicked();
};

#endif // DIALOG_LEVEL_H
