#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>


static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./db");
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Database unreachable"),
            qApp->tr("Unable to establish a database connection.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }
//    only to be used in order to write data into the db
//    QSqlQuery query;
//    query.exec("create table tgs (id int primary key, "
//               "sys_name varchar(20), cat varchar(20), price int, purchase_date date,"
//               "company varchar(20), end_guarantee_date date, last_edit date, user_manual varchar(50))");
//    query.exec("insert into tgs values(101, 'Dannye 233', 'Young', 100, '20170101', 'NI', '20190101', '20190101', '2N2222A')");
//    query.exec("insert into tgs values(102, 'Dannye 233', 'Young', 100, '20170101', 'NI', '20190101', '20190101', 'RELAY_TERMINOLOGY_LOOK_TIME_IMAGE')");
//    query.exec("insert into tgs values(103, 'Dannye 233', 'Young', 100, '20170101', 'NI', '20190101', '20190101', 'UHF_antenna')");
//    query.exec("insert into tgs values(104, 'Dannye 233', 'Young', 100, '20170101', 'NI', '20190101', '20190101', 'TRUE')");
//    query.exec("insert into tgs values(105, 'Dannye 233', 'Young', 100, '20170101', 'NI', '20190101', '20190101', 'TRUE')");
//    query.exec("insert into tgs values(106, 'Dannye 233', 'Young', 100, '20170101', 'NI', '20190101', '20190101', 'TRUE')");
//    query.exec("insert into tgs values(107, 'Dannye 233', 'Young', 100, '20170101', 'NI', '20190101', '20190101', 'TRUE')");
//    query.exec("insert into tgs values(108, 'Dannye 233', 'Young', 100, '20170101', 'NI', '20190101', '20190101', 'TRUE')");
//    query.exec("insert into tgs values(109, 'Dannye 233', 'Young', 100, '20170101', 'NI', '20190101', '20190101', 'TRUE')");
//    query.exec("insert into tgs values(110, 'Dannye 233', 'Young', 100, '20170101', 'NI', '20190101', '20190101', 'TRUE')");

    return true;
}

#endif
