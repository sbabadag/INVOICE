#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlTableModel>
#include <QTableView>
#include <QtSql/QSqlRelationalTableModel>
#include <editablesqlmodel.h>
#include <QMessageBox>
#include <QSqlRecord>
#include <QDebug>
#include <random>





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->calendarWidget->setVisible(false);

    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("127.0.0.1");
    database.setUserName("root");
    database.setPassword("Seloken343542");
    database.setDatabaseName("avm_database");

    if (database.open())
    {
   //     querymodel = new QSqlQueryModel();
        querymodel = new EditableSqlModel();

        ordersmodel = new QSqlTableModel();
        customersmodel = new QSqlTableModel();
        invoicesmodel = new QSqlTableModel();


         ordersmodel->setTable("orders");
         ordersmodel->select();
         ordersmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);

         ordersmodel->setFilter("ID=1");

        ui->tableView->setModel(ordersmodel);
        ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);

        QSqlQuery query;
            query.prepare("SELECT * FROM customers");
            query.exec();
            query.first();
            ui->comboBox->addItem(query.value(1).toString());
           while(query.next())
            ui->comboBox->addItem(query.value(1).toString());

           invoicesmodel = new QSqlTableModel();
            invoicesmodel->setTable("invoice");
            invoicesmodel->select();
            invoicesmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
            invoicesmodel->setFilter("ID=1");
}

    ordersmodel->setTable("orders");
    ordersmodel->select();
    ordersmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);

   querymodel->setQuery("SELECT * from orders");

   ui->tableView->setModel(ordersmodel);
   ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);

   ui->tableView_2->setModel(invoicesmodel);
   ui->tableView_2->setEditTriggers(QAbstractItemView::SelectedClicked);

   //

   ui->tableView->setVisible(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

}


void MainWindow::on_pushButton_2_clicked()
{
    database.transaction();//Start things up
     if(ordersmodel->submitAll())
         ordersmodel->database().commit();
     else{
         database.rollback(); //RollBACK
     }


}


void MainWindow::on_toolButton_clicked()
{
    ui->calendarWidget->setVisible(true);
}


void MainWindow::on_calendarWidget_selectionChanged()
{
  //  ui->lineEdit_3->setText(ui->calendarWidget->selectedDate().toString());
    ui->calendarWidget->setVisible(false);
}


void MainWindow::on_pushButton_3_clicked()
{

 //   ordersmodel->setFilter("");
 //   ordersmodel->select();

      QSqlRecord newRecord = ordersmodel->record();
      newRecord.setValue("ID", id);
      newRecord.setValue("invid",invid);
      newRecord.setValue("description", "");
      newRecord.setValue("quantity",0);
      newRecord.setValue("unit","");
      newRecord.setValue("rate",0);
      newRecord.setValue("sett",0);
      newRecord.setValue("amount",0);





      if (ordersmodel->insertRecord(-1, newRecord)) {
          qDebug() << "New record inserted";
      } else  qDebug() << "No record inserted";


      database.transaction();//Start things up
       if(ordersmodel->submitAll())
           database.commit();
       else{
           database.rollback(); //RollBACK

       }

}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
     id = index + 1;

    customersmodel->setTable("customers");
    customersmodel->select();
    ui->lineEdit->setText(customersmodel->index(index,1).data().toString());
    ui->textEdit->setText(customersmodel->index(index,2).data().toString());

    customersmodel->setFilter(QString("ID=%1").arg(id));
    invoicesmodel->setFilter(QString("ID=%1").arg(id));


    customersmodel->setTable("customers");
    customersmodel->select();
    customersmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    ordersmodel->setFilter(QString("ID=%1 AND invid=%2").arg(id).arg(invid));

   ui->tableView->setModel(ordersmodel);
   ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);


}



void MainWindow::on_pushButton_4_clicked()
{

}


void MainWindow::on_pushButton_7_clicked()
{
  ui->lineEdit->setText("");
  ui->textEdit->setText("");
}


void MainWindow::on_pushButton_11_clicked()
{


    database.transaction();//Start things up
     if(invoicesmodel->submitAll())
         invoicesmodel->database().commit();
     else{
         database.rollback(); //RollBACK

     }
}


void MainWindow::on_pushButton_10_clicked()
{
  QDate now ;

 // invoicesmodel->setFilter("");
 // invoicesmodel->select();

    QSqlRecord newRecord = invoicesmodel->record();
    newRecord.setValue("THEDATE", now.currentDate());
    newRecord.setValue("INVNO", now.currentDate().toJulianDay()+invoicesmodel->rowCount());
    newRecord.setValue("ID",id);




    if (invoicesmodel->insertRecord(-1, newRecord)) {
        qDebug() << "New record inserted";
    } else  qDebug() << "No record inserted";


    database.transaction();//Start things up
     if(invoicesmodel->submitAll())
         database.commit();
     else{
         database.rollback(); //RollBACK

     }

}


void MainWindow::on_tableView_2_clicked(const QModelIndex &index)
{

    QString S;
  //  int idd = invoicesmodel->index(index.row(),0).data().toInt();
    int idd = invoicesmodel->record(ui->tableView_2->currentIndex().row()).value("invid").toInt();

    ordersmodel->setFilter(QString("ID=%1 AND invid=%2").arg(id).arg(idd));
    invid = idd;
    ui->tableView->setVisible(true);

    QSqlQuery query;
    query.exec(QString("SELECT SUM(amount) FROM orders WHERE ID=%1 AND invid=%2").arg(id).arg(invid));
        if (query.next()) {
            S = query.value(0).toString();
        }
    query.finish();

    ui->lineEdit_7->setText(S);
    ui->lineEdit_6->setText(S);
    ui->lineEdit_5->setText("");






}


void MainWindow::on_tableView_2_doubleClicked(const QModelIndex &index)
{

}


void MainWindow::on_pushButton_8_clicked()
{

    QSqlRecord newRecord = customersmodel->record();
    newRecord.setValue("name", ui->lineEdit->text());
    newRecord.setValue("address", ui->textEdit->toPlainText());

    if (customersmodel->insertRecord(customersmodel->rowCount(), newRecord)) {
        qDebug() << "New record inserted";
    } else  qDebug() << "No record inserted";


    database.transaction();//Start things up
     if(customersmodel->submitAll())
         database.commit();
     else{
         database.rollback(); //RollBACK

     }

     ui->comboBox->clear();
     QSqlQuery query;
         query.prepare("SELECT * FROM customers");
         query.exec();
         query.first();
         ui->comboBox->addItem(query.value(1).toString());
        while(query.next())
         ui->comboBox->addItem(query.value(1).toString());

}

