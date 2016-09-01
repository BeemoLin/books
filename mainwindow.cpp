#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    OpenDB();
    ReadDB();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Save Delimiter-Separated Value"),
                                                    QDir::currentPath(), "All files (*.*);;"
                                                    "CSV (*.csv);; TSV (*.tsv)");
    if(!fileName.isEmpty()) {
        WriteDB(fileName);
    }

    ReadDB();
}


void MainWindow::on_actionSave_triggered()
{
    QString textData;

    QAbstractItemModel *model = this->ui->tableView->model();

    int rows = model->rowCount();
    int columns = model->columnCount();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

                textData += model->data(model->index(i,j)).toString();
                if(j + 1 < columns) {
                    textData += ",";      // for .csv file format
                }
        }
        textData += "\n";             // (optional: for new line segmentation)
    }

    // [Save to file] (header file <QFile> needed)
    // .csv
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                       QDir::currentPath(), tr("CSV (*.csv);; TSV (*.tsv)"));

    if(!fileName.isEmpty()) {
        QFile csvFile(fileName);

        QTextStream in(&csvFile);

        //in.setCodec("UTF-8");
        in.setCodec("big5");

        if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

            QTextStream out(&csvFile);
            out << textData;

            csvFile.close();
        }
    }
}

void MainWindow::on_actionClear_triggered()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "清空資料庫", "確認清空資料庫?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";

        t_model->clear();
        db.close();

        if (!db.open()) {
            qDebug("Error occurred opening the database.");
            qDebug("%s.", qPrintable(db.lastError().text()));
            exit(-1);
        }

        QSqlQuery que(db);

        que.prepare ("DROP TABLE IF EXISTS main;");

        if (!que.exec()) {
            qDebug("Error occurred drop table.");
            qDebug("%s", qPrintable(db.lastError().text()));
            exit(-1);
        }
    } else {
        qDebug() << "Yes was *not* clicked";
    }

}

void MainWindow::on_pushButton_clicked()
{
    ReadDB(GetWhere());
    ReadError(GetWhere());
    //CountLate(GetWhere());
}

void MainWindow::on_pushButton_2_clicked()
{
    this->ui->lineEdit_id->setText("");
    this->ui->lineEdit_year->setText("");
    this->ui->lineEdit_month->setText("");

    ReadDB();
}

void MainWindow::on_pushButton_3_clicked()
{
    QString where = GetWhere();

    where = "WHERE" + where;
    qDebug("%s", qPrintable(where));

    OverTime(where + GetDayOff("NOT"));
    CountOverTime(where + GetDayOff("NOT"));
    DayOff(where + GetDayOff(""));
    CountDayOff(where + GetDayOff(""));
}

void MainWindow::on_pushButton_4_clicked()
{
    if (!t_model->submitAll()) {
        qDebug() << t_model->lastError ();
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    this->ui->checkBox_1->setChecked(false);
    this->ui->checkBox_2->setChecked(false);
    this->ui->checkBox_3->setChecked(false);
    this->ui->checkBox_4->setChecked(false);
    this->ui->checkBox_5->setChecked(false);
    this->ui->checkBox_6->setChecked(false);
    this->ui->checkBox_7->setChecked(false);
    this->ui->checkBox_8->setChecked(false);
    this->ui->checkBox_9->setChecked(false);
    this->ui->checkBox_10->setChecked(false);
    this->ui->checkBox_11->setChecked(false);
    this->ui->checkBox_12->setChecked(false);
    this->ui->checkBox_13->setChecked(false);
    this->ui->checkBox_14->setChecked(false);
    this->ui->checkBox_15->setChecked(false);
    this->ui->checkBox_16->setChecked(false);
    this->ui->checkBox_17->setChecked(false);
    this->ui->checkBox_18->setChecked(false);
    this->ui->checkBox_19->setChecked(false);
    this->ui->checkBox_20->setChecked(false);
    this->ui->checkBox_21->setChecked(false);
    this->ui->checkBox_22->setChecked(false);
    this->ui->checkBox_23->setChecked(false);
    this->ui->checkBox_24->setChecked(false);
    this->ui->checkBox_25->setChecked(false);
    this->ui->checkBox_26->setChecked(false);
    this->ui->checkBox_27->setChecked(false);
    this->ui->checkBox_28->setChecked(false);
    this->ui->checkBox_29->setChecked(false);
    this->ui->checkBox_30->setChecked(false);
    this->ui->checkBox_31->setChecked(false);
}

void MainWindow::on_pushButton_6_clicked()
{
    QString textData;

    textData += "出勤明細資料\n";
    textData += "日期,刷卡時間,廠別,群組代號,群組名稱,員工代號,姓名,卡片號碼,狀態\n";

    QAbstractItemModel *model = this->ui->tableView->model();

    int rows = model->rowCount();
    int columns = model->columnCount();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

                textData += model->data(model->index(i,j)).toString();
                if(j + 1 < columns) {
                    textData += ",";      // for .csv file format
                }
        }
        textData += "\n";             // (optional: for new line segmentation)
    }

    // [Save to file] (header file <QFile> needed)
    // .csv
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                       "/出勤明細", tr("CSV (*.csv);; TSV (*.tsv)"));

    if(!fileName.isEmpty()) {
        QFile csvFile(fileName);

        QTextStream in(&csvFile);

        //in.setCodec("UTF-8");
        in.setCodec("big5");

        if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

            QTextStream out(&csvFile);
            out << textData;

            csvFile.close();
        }
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    QString textData;

    textData += "出勤明細資料\n";
    textData += "日期,刷卡時間,廠別,群組代號,群組名稱,員工代號,姓名,卡片號碼,狀態\n";

    if(this->ui->tableView->selectionModel()) {
        QAbstractItemModel *model = this->ui->tableView->model();
        int rows = model->rowCount();
        int columns = model->columnCount();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {

                    textData += model->data(model->index(i,j)).toString();
                    if(j + 1 < columns) {
                        textData += ",";      // for .csv file format
                    }
            }
            textData += "\n";             // (optional: for new line segmentation)
        }
    }

    textData += "\n每日加班明細\n";
    textData += "日期,刷卡時間,總加班時間,兩小時內,兩小時以上\n";

    if(this->ui->tableView_2->selectionModel()) {
        QAbstractItemModel *model = this->ui->tableView_2->model();
        int rows = model->rowCount();
        int columns = model->columnCount();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {

                    textData += model->data(model->index(i,j)).toString();
                    if(j + 1 < columns) {
                        textData += ",";      // for .csv file format
                    }
            }
            textData += "\n";             // (optional: for new line segmentation)
        }
    }

    textData += "\n平日加班統計\n";
    textData += "總加班時間,兩小時內,兩小時以上\n";

    if(this->ui->tableView_3->selectionModel()) {
        QAbstractItemModel *model = this->ui->tableView_3->model();
        int rows = model->rowCount();
        int columns = model->columnCount();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {

                    textData += model->data(model->index(i,j)).toString();
                    if(j + 1 < columns) {
                        textData += ",";      // for .csv file format
                    }
            }
            textData += "\n";             // (optional: for new line segmentation)
        }
    }

    textData += "\n假日加班明細\n";
    textData += "假日加班,8小時內,兩小時內,兩小時以上\n";

    if(this->ui->tableView_4->selectionModel()) {
        QAbstractItemModel *model = this->ui->tableView_4->model();
        int rows = model->rowCount();
        int columns = model->columnCount();


        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {

                    textData += model->data(model->index(i,j)).toString();
                    if(j + 1 < columns) {
                        textData += ",";      // for .csv file format
                    }
            }
            textData += "\n";             // (optional: for new line segmentation)
        }
    }

    textData += "\n假日加班統計\n";
    textData += "假日總加班時數,8小時內,兩小時內,兩小時以上\n";

    if(this->ui->tableView_5->selectionModel()) {
        QAbstractItemModel *model = this->ui->tableView_5->model();

        int rows = model->rowCount();
        int columns = model->columnCount();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {

                    textData += model->data(model->index(i,j)).toString();
                    if(j + 1 < columns) {
                        textData += ",";      // for .csv file format
                    }
            }
            textData += "\n";             // (optional: for new line segmentation)
        }
    }

    textData += "\n異常刷卡與遲到統計\n";
    textData += "日期,員工代號,姓名,上班時間,下班時間,工作時數\n";

    QTableView *table = new QTableView();

    table->setWindowTitle("");
    QAbstractItemModel *model = error_model;

    int rows = model->rowCount();
    int columns = model->columnCount();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

                textData += model->data(model->index(i,j)).toString();
                if(j + 1 < columns) {
                    textData += ",";      // for .csv file format
                }
        }
        textData += "\n";             // (optional: for new line segmentation)
    }

    // [Save to file] (header file <QFile> needed)
    // .csv
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                       "/加班工時統計", tr("CSV (*.csv);; TSV (*.tsv)"));

    if(!fileName.isEmpty() && textData != "") {
        QFile csvFile(fileName);

        QTextStream in(&csvFile);

        //in.setCodec("UTF-8");
        in.setCodec("big5");

        if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

            QTextStream out(&csvFile);
            out << textData;

            csvFile.close();
        }
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    int selected_row = this->ui->tableView->currentIndex().row() + 1;
    t_model->insertRow(selected_row);
    t_model->setRecord(selected_row, t_model->record(this->ui->tableView->currentIndex().row()));
    this->ui->tableView->selectRow(selected_row);
}

void MainWindow::on_pushButton_9_clicked()
{
    int selected_row = this->ui->tableView->currentIndex().row();
    t_model->removeRow(selected_row);
}

void MainWindow::OpenDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName (qApp->applicationDirPath()
                        + QDir::separator()
                        + "books.sqlite");
    if (!db.open()) {
        qDebug("Error occurred opening the database.");
        qDebug("%s.", qPrintable(db.lastError().text()));
        exit(-1);
    }
}

void MainWindow::ReadError(QString query)
{
    QSqlQuery que(db);

    QString sql = "";

    QString checkin_time = " CASE WHEN factory LIKE '%二廠%' THEN '08:30:00' ELSE '08:00:00' END ";

    QString work_hr = "((strftime('%s', check_out) - strftime('%s', check_in))/3600) || ':' || strftime('%M:%S', (strftime('%s', check_out) - strftime('%s', check_in))/86400.0 - 0.5)";

    sql ="SELECT work_date, id, name, check_in, check_out, " + work_hr + " FROM (";
    sql += "SELECT MIN(time) AS check_in, MAX(time) AS check_out, * FROM main ";
    sql += "WHERE" + query;
    sql += " GROUP BY work_date, id ORDER BY work_date, time ASC)";
    sql += " WHERE (check_out - check_in) < 1 OR (strftime('%s', check_in) > strftime('%s', " + checkin_time + ")) ";

    qDebug("%s.", qPrintable(sql));

    //Suppression + creation of the table
    que.prepare(sql);

    if (!que.exec()) {
        qDebug("Error occurred creating table.");
        qDebug("%s.", qPrintable(db.lastError().text()));
        exit(-1);
    }

    error_model = new QSqlQueryModel;
    error_model->setQuery(que);
    error_model->setHeaderData(0, Qt::Horizontal, tr("日期"));
    error_model->setHeaderData(1, Qt::Horizontal, tr("員工代號"));
    error_model->setHeaderData(2, Qt::Horizontal, tr("姓名"));
    error_model->setHeaderData(3, Qt::Horizontal, tr("上班時間"));
    error_model->setHeaderData(4, Qt::Horizontal, tr("下班時間"));
    error_model->setHeaderData(5, Qt::Horizontal, tr("工作時數"));

    if(error_model->rowCount() > 0) {
        QTableView *table = new QTableView();

        table->setWindowTitle("異常刷卡與遲到統計");
        table->setMinimumSize(650, 300);
        table->setModel(error_model);
        table->show();
    }
}

void MainWindow::ReadDB()
{
    t_model = new QSqlTableModel(this,db);
    t_model->setTable("main");
    t_model->setSort(0,Qt::AscendingOrder);
    t_model->setHeaderData(0, Qt::Horizontal, tr("日期"));
    t_model->setHeaderData(1, Qt::Horizontal, tr("時間"));
    t_model->setHeaderData(2, Qt::Horizontal, tr("廠別"));
    t_model->setHeaderData(3, Qt::Horizontal, tr("群組代號"));
    t_model->setHeaderData(4, Qt::Horizontal, tr("群組名稱"));
    t_model->setHeaderData(5, Qt::Horizontal, tr("員工代號"));
    t_model->setHeaderData(6, Qt::Horizontal, tr("姓名"));
    t_model->setHeaderData(7, Qt::Horizontal, tr("卡片號碼"));
    t_model->setHeaderData(8, Qt::Horizontal, tr("狀態"));
    t_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    if (t_model->select())
    {
        this->ui->tableView->setModel(t_model);
    }
    else
    {
        //  It cannot find the table!!!!!
       qDebug() << t_model->lastError().driverText();
    }
}

void MainWindow::ReadDB(QString query)
{
    t_model = new QSqlTableModel(this,db);
    t_model->setTable("main");
    t_model->setSort(0,Qt::AscendingOrder);
    t_model->setHeaderData(0, Qt::Horizontal, tr("日期"));
    t_model->setHeaderData(1, Qt::Horizontal, tr("時間"));
    t_model->setHeaderData(2, Qt::Horizontal, tr("廠別"));
    t_model->setHeaderData(3, Qt::Horizontal, tr("群組代號"));
    t_model->setHeaderData(4, Qt::Horizontal, tr("群組名稱"));
    t_model->setHeaderData(5, Qt::Horizontal, tr("員工代號"));
    t_model->setHeaderData(6, Qt::Horizontal, tr("姓名"));
    t_model->setHeaderData(7, Qt::Horizontal, tr("卡片號碼"));
    t_model->setHeaderData(8, Qt::Horizontal, tr("狀態"));
    t_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    t_model->setFilter(query);
    if (t_model->select())
    {
        this->ui->tableView->setModel(t_model);
    }
    else
    {
        //  It cannot find the table!!!!!
       qDebug() << t_model->lastError().driverText();
    }
}

void MainWindow::CountLate(QString query)
{
    QSqlQuery que(db);

    QString sql = "";

    QString checkin_time = " CASE WHEN factory LIKE '%二廠%' THEN '08:30:00' ELSE '08:00:00' END ";

    QString to_hr = "(strftime('%s', late_time)/3600) || ':' || strftime('%M:%S', strftime('%s', late_time)/86400.0 - 0.5)";

    sql += "SELECT" + to_hr + " AS late_time FROM (";
    sql += "SELECT SUM(strftime('%s', late_time) - strftime('%s', " + checkin_time + ")) AS late_time FROM (";
    sql += "SELECT MIN(time) AS late_time, * FROM main ";
    sql += "WHERE" + query;
    sql += " GROUP BY work_date, id ORDER BY work_date, time ASC)";
    sql += " WHERE (strftime('%s', late_time) > strftime('%s', " + checkin_time + "))) ";

    qDebug("%s.", qPrintable(sql));

    //Suppression + creation of the table
    que.prepare(sql);

    if (!que.exec()) {
        qDebug("Error occurred creating table.");
        qDebug("%s.", qPrintable(db.lastError().text()));
        exit(-1);
    }

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(que);
    model->setHeaderData(0, Qt::Horizontal, tr("遲到時數"));

    //this->ui->tableView_6->setModel(model);
}

void MainWindow::OverTime(QString query)
{
    QSqlQuery que(db);

    QString overtime = " CASE WHEN factory LIKE '%二廠%' THEN '18:30:00' ELSE '18:00:00' END ";

    query += " AND ";
    query += " strftime('%s', time) > strftime('%s', " + overtime + ") ";

    QString sql = "";
    sql = "SELECT work_date, time, TIME(case when work_time > 0 then work_time else '0' end, 'unixepoch') AS work_time, TIME(case when under_2HR > 0 then under_2HR else '0' end , 'unixepoch') AS under_2HR, TIME(case when over_2HR > 0 then over_2HR else '0' end, 'unixepoch') AS over_2HR FROM (";
    sql += "SELECT work_date, time, work_time, case when work_time > 7200 then 7200 else work_time end AS under_2HR, case when (work_time - 7200) > 0 then (work_time - 7200) else '0' end AS over_2HR FROM(SELECT work_date, time, (strftime('%s', time) - strftime('%s', " + overtime + ")) AS work_time FROM main ";
    sql += query;

    sql += "))";

    //Suppression + creation of the table
    que.prepare(sql);

    if (!que.exec()) {
        qDebug("Error occurred creating table.");
        qDebug("%s.", qPrintable(db.lastError().text()));
        exit(-1);
    }

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(que);
    model->setHeaderData(0, Qt::Horizontal, tr("日期"));
    model->setHeaderData(1, Qt::Horizontal, tr("刷卡時間"));
    model->setHeaderData(2, Qt::Horizontal, tr("總加班時間"));
    model->setHeaderData(3, Qt::Horizontal, tr("兩小時內"));
    model->setHeaderData(4, Qt::Horizontal, tr("兩小時以上"));

    this->ui->tableView_2->setModel(model);
}

void MainWindow::CountOverTime(QString query)
{
    QSqlQuery que(db);

    QString overtime = " CASE WHEN factory LIKE '%二廠%' THEN '18:30:00' ELSE '18:00:00' END ";

    query += " AND ";
    query += " strftime('%s', time) > strftime('%s', " + overtime + ") ";

    QString sql = "";
    sql = "SELECT ((CASE WHEN SUM(work_time) > 0 THEN SUM(work_time) ELSE '0' END)/3600) || ':' || strftime('%M:%S', (CASE WHEN SUM(work_time) > 0 THEN SUM(work_time) ELSE '0' END)/86400.0 - 0.5) AS work_time, ";
    sql += "((CASE WHEN SUM(under_2HR) > 0 THEN SUM(under_2HR) ELSE '0' END)/3600) || ':' || strftime('%M:%S', (CASE WHEN SUM(under_2HR) > 0 THEN SUM(under_2HR) ELSE '0' END)/86400.0 - 0.5) AS under_2HR, ";
    sql += "((CASE WHEN SUM(over_2HR) > 0 THEN SUM(over_2HR) ELSE '0' END)/3600) || ':' || strftime('%M:%S', (CASE WHEN SUM(over_2HR) > 0 THEN SUM(over_2HR) ELSE '0' END)/86400.0 - 0.5) AS over_2HR FROM (";
    sql += "SELECT work_time, case when work_time > 7200 then 7200 else work_time end AS under_2HR, case when (work_time - 7200) > 0 then (work_time - 7200) else '0' end AS over_2HR FROM(SELECT work_date, time, (strftime('%s', time) - strftime('%s', " + overtime + ")) AS work_time FROM main ";
    sql += query;
    sql += "))";

    //Suppression + creation of the table
    que.prepare(sql);

    if (!que.exec()) {
        qDebug("Error occurred creating table.");
        qDebug("%s.", qPrintable(db.lastError().text()));
        exit(-1);
    }

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(que);
    model->setHeaderData(0, Qt::Horizontal, tr("總加班時數"));
    model->setHeaderData(1, Qt::Horizontal, tr("兩小時內"));
    model->setHeaderData(2, Qt::Horizontal, tr("兩小時以上"));

    this->ui->tableView_3->setModel(model);
}

void MainWindow::DayOff(QString query)
{
    QSqlQuery que(db);

    qDebug("%s.", qPrintable(query));

    QString overtime = " CASE WHEN factory LIKE '%二廠%' THEN '08:30:00' ELSE '08:00:00' END ";
    QString HR_10 = "36000";
    QString HR_8 = "28800";
    QString HR_5 = "19800";
    QString HR_1_30 = "5400";

    QString sql = "";

    sql += "SELECT work_date, (under_8HR/3600) || ':' || strftime('%M:%S', under_8HR/86400.0 - 0.5) AS under_8HR, (under_2HR/3600) || ':' || strftime('%M:%S', under_2HR/86400.0 - 0.5) AS under_2HR, (over_2HR/3600) || ':' || strftime('%M:%S', over_2HR/86400.0 - 0.5) AS over_2HR FROM (";
    sql += "SELECT work_date, CASE WHEN work_time > " + HR_8 + " THEN " + HR_8 + " ELSE work_time END AS under_8HR, CASE WHEN (work_time - " + HR_8 + ") > 0 THEN (CASE WHEN work_time > " + HR_10 + " THEN 7200 ELSE (work_time - " + HR_8 + " ) END) ELSE 0 END AS under_2HR, CASE WHEN (work_time - " + HR_10 + ") > 0 THEN (work_time - " + HR_10 + ") ELSE '0' END AS over_2HR FROM (";
    sql += "SELECT work_date, CASE WHEN strftime('%s', MAX(time)) - (CASE WHEN strftime('%s', MIN(time)) > strftime('%s', " + overtime + ") THEN strftime('%s', MIN(time)) ELSE strftime('%s', " + overtime + ") END) > " + HR_5 + " THEN strftime('%s', MAX(time)) - (CASE WHEN strftime('%s', MIN(time)) > strftime('%s', " + overtime + ") THEN strftime('%s', MIN(time)) ELSE strftime('%s', " + overtime + ") END) - " + HR_1_30 + " ELSE strftime('%s', MAX(time)) - (CASE WHEN strftime('%s', MIN(time)) > strftime('%s', " + overtime + ") THEN strftime('%s', MIN(time)) ELSE strftime('%s', " + overtime + ") END) END AS work_time FROM main ";
    sql += query;
    sql += " GROUP BY work_date, id";
    sql += "))";

    //qDebug("ZZZ %s ZZZ", qPrintable(sql));

    //Suppression + creation of the table
    que.prepare(sql);

    if (!que.exec()) {
        qDebug("Error occurred creating table.");
        qDebug("%s.", qPrintable(db.lastError().text()));
        exit(-1);
    }

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(que);
    model->setHeaderData(0, Qt::Horizontal, tr("假日加班"));
    model->setHeaderData(1, Qt::Horizontal, tr("上班時數"));
    model->setHeaderData(1, Qt::Horizontal, tr("八小時內"));
    model->setHeaderData(2, Qt::Horizontal, tr("兩小時內"));
    model->setHeaderData(3, Qt::Horizontal, tr("兩小時以上"));

    this->ui->tableView_4->setModel(model);
}

void MainWindow::CountDayOff(QString query)
{
    QSqlQuery que(db);

    qDebug("%s.", qPrintable(query));

    /*
    QString overtime = " CASE WHEN factory LIKE '%二廠%' THEN '08:30:00' ELSE '08:00:00' END ";
    QString HR_5 = "19800";
    QString HR_1_30 = "5400";

    QString sql = "";
    sql += "SELECT (SUM(work_time)/3600) || ':' || strftime('%M:%S', SUM(work_time)/86400.0 - 0.5) AS work_time FROM (";
    sql += "SELECT CASE WHEN strftime('%s', MAX(time)) - (CASE WHEN strftime('%s', MIN(time)) > strftime('%s', " + overtime + ") THEN strftime('%s', MIN(time)) ELSE strftime('%s', " + overtime + ") END) > " + HR_5 + " THEN strftime('%s', MAX(time)) - (CASE WHEN strftime('%s', MIN(time)) > strftime('%s', " + overtime + ") THEN strftime('%s', MIN(time)) ELSE strftime('%s', " + overtime + ") END) - " + HR_1_30 + " ELSE strftime('%s', MAX(time)) - (CASE WHEN strftime('%s', MIN(time)) > strftime('%s', " + overtime + ") THEN strftime('%s', MIN(time)) ELSE strftime('%s', " + overtime + ") END) END AS work_time FROM main ";
    sql += query;
    sql += " GROUP BY work_date, id";
    sql += ")";
    */
    QString overtime = " CASE WHEN factory LIKE '%二廠%' THEN '08:30:00' ELSE '08:00:00' END ";
    QString HR_10 = "36000";
    QString HR_8 = "28800";
    QString HR_5 = "19800";
    QString HR_1_30 = "5400";

    QString sql = "";

    sql += "SELECT work_date, (SUM(under_8HR)/3600) || ':' || strftime('%M:%S', SUM(under_8HR)/86400.0 - 0.5) AS under_8HR, (SUM(under_2HR)/3600) || ':' || strftime('%M:%S', SUM(under_2HR)/86400.0 - 0.5) AS under_2HR, (SUM(over_2HR)/3600) || ':' || strftime('%M:%S', SUM(over_2HR)/86400.0 - 0.5) AS over_2HR FROM (";
    sql += "SELECT work_date, CASE WHEN work_time > " + HR_8 + " THEN " + HR_8 + " ELSE work_time END AS under_8HR, CASE WHEN (work_time - " + HR_8 + ") > 0 THEN (CASE WHEN work_time > " + HR_10 + " THEN 7200 ELSE (work_time - " + HR_8 + " ) END) ELSE 0 END AS under_2HR, CASE WHEN (work_time - " + HR_10 + ") > 0 THEN (work_time - " + HR_10 + ") ELSE '0' END AS over_2HR FROM (";
    sql += "SELECT work_date, CASE WHEN strftime('%s', MAX(time)) - (CASE WHEN strftime('%s', MIN(time)) > strftime('%s', " + overtime + ") THEN strftime('%s', MIN(time)) ELSE strftime('%s', " + overtime + ") END) > " + HR_5 + " THEN strftime('%s', MAX(time)) - (CASE WHEN strftime('%s', MIN(time)) > strftime('%s', " + overtime + ") THEN strftime('%s', MIN(time)) ELSE strftime('%s', " + overtime + ") END) - " + HR_1_30 + " ELSE strftime('%s', MAX(time)) - (CASE WHEN strftime('%s', MIN(time)) > strftime('%s', " + overtime + ") THEN strftime('%s', MIN(time)) ELSE strftime('%s', " + overtime + ") END) END AS work_time FROM main ";
    sql += query;
    sql += " GROUP BY work_date, id";
    sql += "))";

    //Suppression + creation of the table
    que.prepare(sql);

    if (!que.exec()) {
        qDebug("Error occurred creating table.");
        qDebug("%s.", qPrintable(db.lastError().text()));
        exit(-1);
    }

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(que);
    model->setHeaderData(0, Qt::Horizontal, tr("假日總加班時數"));
    model->setHeaderData(1, Qt::Horizontal, tr("八小時內"));
    model->setHeaderData(2, Qt::Horizontal, tr("兩小時內"));
    model->setHeaderData(3, Qt::Horizontal, tr("兩小時以上"));

    this->ui->tableView_5->setModel(model);
}

void MainWindow::WriteDB(QString filePath)
{
    QMessageBox msgBox;
    //msgBox.setText("The document has been modified.");
    //msgBox.exec();
    db.close();

    if (!db.open()) {
        qDebug("Error occurred opening the database.");
        qDebug("%s.", qPrintable(db.lastError().text()));
        exit(-1);
    }

    QSqlQuery que(db);

    que.prepare ("DROP TABLE IF EXISTS main;");

    if (!que.exec()) {
        qDebug("Error occurred drop table.");
        qDebug("%s", qPrintable(db.lastError().text()));
        exit(-1);
    }

    que.prepare ("CREATE TABLE IF NOT EXISTS main('work_date', 'time', 'factory', 'group',\
     'group_name', 'id', 'name', 'card_id', 'status');");

    if (!que.exec()) {
        qDebug("Error occurred creating table.");
        qDebug("%s", qPrintable(db.lastError().text()));
        exit(-1);
    }

    QFile f(filePath);
    if(f.open (QIODevice::ReadOnly)){

        QTextStream in(&f);

        //in.setCodec("UTF-8");
        in.setCodec("big5");

        que.exec("BEGIN");
        que.prepare("INSERT INTO main\
        ('work_date', 'time', 'factory', 'group', 'group_name',\
        'id', 'name', 'card_id', 'status')\
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");


        int rowSize = 0;

        //Travel through the csv file "excel.csv"
        while(!in.atEnd()) {
            rowSize++;
            // split every lines on comma
            QStringList line = in.readLine().split(',');

            /*for every values on a line, append it to the INSERT request*/
            for(int i = 0;i < line.length();++i){
                que.addBindValue(line.at(i));
            }

            que.exec();
        }
        que.exec("END");

        f.close ();

        QString qStr = QString::fromUtf8("共匯入 %1 筆資料").arg(rowSize);
        msgBox.setText(qStr);
        msgBox.exec();
    } else {
        qDebug("Error can't open file.");
        exit(-1);
    }

    ReadDB();
}

QString MainWindow::GetWhere()
{
    //QString query = "SELECT * FROM main ";
    QString where = " 1 = 1 ";

    QString id = this->ui->lineEdit_id->text();
    QString year = this->ui->lineEdit_year->text();
    QString month = this->ui->lineEdit_month->text();

    if(id != "") {
        where += " AND ";
        where += QString("id = '%1'").arg(id);
    }
    if(year != "") {
        where += " AND ";
        where += QString("work_date like '%1\/\%'").arg(year);
    }
    if(month != "") {
        where += " AND ";
        where += QString("work_date like '\%\/%1\/\%'").arg(month);
    }

    //where += " GROUP BY work_date, id ";

    return where;
}

QString MainWindow::GetDayOff(QString revert)
{
    QString where = "";

    if(revert == "") {
        where += " AND ( work_date != work_date ";
    }

    if(this->ui->checkBox_1->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("01");
    }

    if(this->ui->checkBox_2->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("02");
    }

    if(this->ui->checkBox_3->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("03");
    }

    if(this->ui->checkBox_4->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("04");
    }

    if(this->ui->checkBox_5->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("05");
    }

    if(this->ui->checkBox_6->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("06");
    }

    if(this->ui->checkBox_7->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("07");
    }

    if(this->ui->checkBox_8->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("08");
    }

    if(this->ui->checkBox_9->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("09");
    }

    if(this->ui->checkBox_10->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("10");
    }

    if(this->ui->checkBox_11->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("11");
    }

    if(this->ui->checkBox_12->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("12");
    }

    if(this->ui->checkBox_13->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("13");
    }

    if(this->ui->checkBox_14->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("14");
    }

    if(this->ui->checkBox_15->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("15");
    }

    if(this->ui->checkBox_16->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("16");
    }

    if(this->ui->checkBox_17->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("17");
    }

    if(this->ui->checkBox_18->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("18");
    }

    if(this->ui->checkBox_19->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("19");
    }

    if(this->ui->checkBox_20->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("20");
    }


    if(this->ui->checkBox_21->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("21");
    }


    if(this->ui->checkBox_22->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("22");
    }


    if(this->ui->checkBox_23->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("23");
    }


    if(this->ui->checkBox_24->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("24");
    }


    if(this->ui->checkBox_25->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("25");
    }


    if(this->ui->checkBox_26->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("26");
    }


    if(this->ui->checkBox_27->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("27");
    }


    if(this->ui->checkBox_28->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("28");
    }


    if(this->ui->checkBox_29->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("29");
    }


    if(this->ui->checkBox_30->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("30");
    }


    if(this->ui->checkBox_31->checkState()) {
        if(revert != "") {
            where += " AND ";
        } else {
            where += " OR ";
        }
        where += QString(" work_date " + revert + " LIKE '\%\/%1' ").arg("31");
    }

    if(revert == "") {
        where += " ) ";
    }

    return where;
}

void MainWindow::on_actionDefind_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("參數設定");
    msgBox.setText("<一廠>08:00~17:30\r\n<二廠>08:30~18:00\r\n下班後班小時開始計算加班\r\n(請確認資料<<廠別>>欄位設定正確)");
    msgBox.exec();
}
