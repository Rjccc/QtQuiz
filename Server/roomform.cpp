#include "roomform.h"
#include "ui_roomform.h"

RoomForm::RoomForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomForm)
{
    ui->setupUi(this);
}

RoomForm::~RoomForm()
{
    delete ui;
}
