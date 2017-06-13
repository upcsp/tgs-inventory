#include <QtWidgets>
#include <QtSql>

#include "tableeditor.h"
#include "sqlmodelsubclass.h"

TableEditor::TableEditor(const QString &tableName, QWidget *parent)
    : QWidget(parent)
{

    model = new MyTableModel(this);
    model->setTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
//    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("System name"));
    model->setHeaderData(2, Qt::Horizontal, tr("Category"));
    model->setHeaderData(3, Qt::Horizontal, tr("Price €"));
    model->setHeaderData(4, Qt::Horizontal, tr("Purchase Date"));
    model->setHeaderData(5, Qt::Horizontal, tr("Company"));
    model->setHeaderData(6, Qt::Horizontal, tr("Guarantee-end Date"));
    model->setHeaderData(7, Qt::Horizontal, tr("Last-Manipulation"));
    model->setHeaderData(8, Qt::Horizontal, tr("..."));
    model->setHeaderData(9, Qt::Horizontal, tr("User Manual"));

    view = new QTableView;
    view->setModel(model);
    view->resizeColumnsToContents();
    view->setColumnHidden(model->fieldIndex("id"), true);
    view->setColumnWidth(8,140);
//    ButtonColumnDelegate *delegate = new ButtonColumnDelegate(view);
//    view->setItemDelegate(delegate);

    submitButton = new QPushButton(tr("Submit"));
    submitButton->setDefault(true);
    addButton = new QPushButton(tr("Add Item"));
    deleteButton = new QPushButton(tr("Delete Selected"));
    quitButton = new QPushButton(tr("Quit"));

    buttonBox = new QDialogButtonBox(Qt::Vertical);
    buttonBox->addButton(submitButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(addButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(deleteButton, QDialogButtonBox::ActionRole);

    mapper_find = new QSignalMapper(this);
    mapper_open = new QSignalMapper(this);

    connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(add()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteROW()));
    connect(view, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));
    connect(mapper_find, SIGNAL(mapped(int)), this, SLOT(find(int)));
    connect(mapper_open, SIGNAL(mapped(int)), this, SLOT(open(int)));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(view);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("TGS Inventory"));
    putButtons();
//    parseData();
}

void TableEditor::submit()
{
    model->database().transaction();
    if (model->submitAll()) {
        model->database().commit();
    } else {
        model->database().rollback();
        QMessageBox::warning(this, tr("Cached Table"),
                             tr("The database reported an error: %1")
                             .arg(model->lastError().text()));
    }
    putButtons();
}
void TableEditor::add()
{
    QSqlQuery query;
    int id;
    query.exec("SELECT MAX(id) FROM tgs");
    query.next();
    id = query.value(0).toInt() + 1;

    query.prepare("insert into tgs values(:id, 'sys', 'cat', 0, '01.01.2017', 'company', '01.05.2017', '01.01.2019', '...','Open')");
    query.bindValue(":id",id);
    query.exec();
    model->select();
    putButtons();

}

void TableEditor::deleteROW() {
      QModelIndexList selection = view->selectionModel()->selectedRows();
     // Multiple rows can be selected
     for(int i=0; i< selection.count(); i++)
     {
         QModelIndex index = selection.at(i);
         QSqlQuery query;
         QModelIndex id_index = model->index(index.row(), 0, QModelIndex());
         query.prepare("DELETE FROM tgs WHERE id = :id");
         query.bindValue(":id",id_index.data().toString());
         if( !query.exec() )
           qDebug() << query.lastError();
         else
           qDebug( "Deleted!" );
         model-> removeRow (index.row());
     }
     submit();
}

void TableEditor::onTableClicked(const QModelIndex &index)
{
    if(index.column() == 18 && index.isValid()) {
        QString cellText = index.data().toString();
        QString rel_url = "./datasheets/"+ cellText +".pdf";
        QFileInfo fi(rel_url);
        QString url = "file:///" + fi.absoluteFilePath();

        if(QFile::exists(fi.absoluteFilePath())) {
            QDesktopServices::openUrl(QUrl(url, QUrl::TolerantMode));
        }
        else {
            QMessageBox Msgbox;
            Msgbox.setText("File not found!");
            Msgbox.exec();
        }
    }

}

void TableEditor::open(int index)
{
        QModelIndex id_index = model->index(index, 8, QModelIndex());
        QString cellText = id_index.data().toString();
//        QString rel_url = "./datasheets/"+ cellText +".pdf";
//        QFileInfo fi(rel_url);
//        QString url = "file:///" + fi.absoluteFilePath();
         QString url = "file:///" + cellText;

        if(QFile::exists(cellText)) {
            QDesktopServices::openUrl(QUrl(url, QUrl::TolerantMode));
        }
        else {
            QMessageBox Msgbox;
            Msgbox.setText("File not found!");
            Msgbox.exec();
        }
}

void TableEditor::find(int index)
{
    QSqlQuery query;
    QModelIndex id_index = model->index(index, 0, QModelIndex());
    QString fileName = QFileDialog::getOpenFileName(this,
                tr("Choose System Manual"), "/home/", tr("PDF Files (*.pdf)"));
    query.prepare("UPDATE tgs SET user_manual = :fileName  WHERE id = :index");
    query.bindValue(":index", id_index.data().toString());
    query.bindValue(":fileName", fileName);

    if( !query.exec() )
      qDebug() << query.lastError();
    else
      qDebug( "Updated filename!" );
    model->select();
    view -> setModel(model);
    putButtons();
}

void TableEditor::putButtons()
{
    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM tgs");
    query.next();

    int last_row = query.value(0).toInt();
    for (int i=0; i<last_row; i++) {
        QModelIndex index_find = model->index(i,8);
        QModelIndex index_open = model->index(i,9);
        openButton = new QPushButton("Open");
        QString str = index_find.data().toString();
        QStringList list = str.split('/');
        QString final = ".../"+ list.takeLast();
        findButton = new QPushButton(final);
        if (str == "...") {
            openButton->setDisabled(true);
        }
        else{
            openButton->setDisabled(false);
        }
        view->setIndexWidget(index_open, openButton);
        view->setIndexWidget(index_find, findButton);

        connect(findButton, SIGNAL(clicked()), mapper_find, SLOT(map()));
        mapper_find->setMapping(findButton, i); // Number to be passed in the slot
        connect(openButton, SIGNAL(clicked()), mapper_open, SLOT(map()));
        mapper_open->setMapping(openButton, i); // Number to be passed in the slot
 }
}


//void TableEditor::parseData()
//{
//    QSqlQuery query;
//    query.exec("SELECT COUNT(*) FROM tgs");
//    query.next();

//    int last_row = query.value(0).toInt();
//    query.exec("SELECT purchase_date, end_guarantee_date, last_edit FROM tgs");
//    for (int i=0; i<last_row; i++) {
//        query.next();
//        QDate purchase_date = QDate::fromString(query.value(0).toInt(), "yyyyMMdd");
//        QDate end_guarantee_date = QDate::fromString(query.value(1).toInt(), "yyyyMMdd");
//        QDate last_edit = QDate::fromString(query.value(2).toInt(), "yyyyMMdd");
//        qDebug() << date.toString("dd.MM.yyyy");
//        qDebug() << query.value(1).toInt();
//    }
//}
