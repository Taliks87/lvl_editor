#include "dialog_windows/dialog_enter_level.h"
#include "ui_dialog_enter_level.h"
#include <QPushButton>

DialogEnterLevel::DialogEnterLevel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEnterLevel)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Ok),    SIGNAL(clicked()), SLOT(ok_clicked()));
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel),SIGNAL(clicked()), SLOT(close()));
}

void DialogEnterLevel::setup_window(const QString& lableText)
{
    ui->label->setText(lableText);
}

void DialogEnterLevel::ok_clicked()
{
    emit enter_name(ui->lineEdit->text());
    ui->lineEdit->setText("");
    close();
}

DialogEnterLevel::~DialogEnterLevel()
{
    delete ui;
}

