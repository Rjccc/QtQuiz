#include "authdialog.h"
#include "ui_authdialog.h"

AuthDialog::AuthDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthDialog)
{
    ui->setupUi(this);
}

AuthDialog::~AuthDialog()
{
    delete ui;
}

void AuthDialog::accept()
{
    if(ui->lineEdit->text().isEmpty())
    {
        return;
    }   else
    {
        name = ui->lineEdit->text();
        QDialog::accept();
    }
}
