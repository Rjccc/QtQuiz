#ifndef ROOMFORM_H
#define ROOMFORM_H

#include <QWidget>

namespace Ui {
class RoomForm;
}

class RoomForm : public QWidget
{
    Q_OBJECT

public:
    explicit RoomForm(QWidget *parent = nullptr);
    ~RoomForm();

private:
    Ui::RoomForm *ui;
    int maxPlayers = 4;

};

#endif // ROOMFORM_H
