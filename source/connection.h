/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

//! [0]
static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./db");
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
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
//! [0]

#endif
