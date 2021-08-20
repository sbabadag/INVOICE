#include "mainwindow.h"

#include "customsqlmodel.h"
#include "editablesqlmodel.h"

#include <QApplication>
#include <QTableView>

#include <stdlib.h>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}
