#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_actionSave_triggered();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_actionClear_triggered();

    void on_actionDefind_triggered();

private:
    Ui::MainWindow *ui;

    //BeemoLin
    void OpenDB();
    void WriteDB(QString filePath);
    void ReadError(QString query);
    void CountLate(QString query);
    void ReadDB();
    void ReadDB(QString query);
    QString GetWhere();
    QString GetDayOff(QString revert);
    void OverTime(QString query);
    void CountOverTime(QString query);
    void DayOff(QString query);
    void CountDayOff(QString query);
    QSqlDatabase db;
    QSqlTableModel *t_model;
    QSqlQueryModel *error_model;
};

#endif // MAINWINDOW_H
