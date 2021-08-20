#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *getUi() {return ui;}

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_toolButton_clicked();

    void on_calendarWidget_selectionChanged();

    void on_pushButton_3_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_10_clicked();

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_tableView_2_doubleClicked(const QModelIndex &index);

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase database;
    QSqlQueryModel *querymodel;
    QSqlTableModel *customersmodel;
    QSqlTableModel *invoicesmodel;
    QSqlTableModel *ordersmodel;
    double id;
    double invid;




};
#endif // MAINWINDOW_H
