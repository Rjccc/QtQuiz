#include "mainwindow.h"

#include <QApplication>
#include "cclient.h"
#include "authdialog.h"
#include <QDebug>

cClient *client = NULL;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AuthDialog *dlg = new AuthDialog();
    if(dlg->exec())
    {
        client = new cClient(nullptr,dlg->name);
        client->connectToServer();
        MainWindow w;
        w.show();
        return a.exec();
    }   else
    {
        return 0;
    }

    return a.exec();
}
