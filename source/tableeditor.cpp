#include <QtWidgets>
#include <QtSql>

#include "tableeditor.h"


TableEditor::TableEditor(const QString &tableName, QWidget *parent)
    : QWidget(parent)
{

    model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("System name"));
    model->setHeaderData(2, Qt::Horizontal, tr("Category"));
    model->setHeaderData(3, Qt::Horizontal, tr("Price"));
    model->setHeaderData(4, Qt::Horizontal, tr("Purchase Date"));
    model->setHeaderData(5, Qt::Horizontal, tr("Company"));
    model->setHeaderData(6, Qt::Horizontal, tr("Guarantee-end Date"));
    model->setHeaderData(7, Qt::Horizontal, tr("Last-Manipulation"));
    model->setHeaderData(8, Qt::Horizontal, tr("User Manual"));


    view = new QTableView;
    view->setModel(model);
    view->resizeColumnsToContents();

    submitButton = new QPushButton(tr("Submit"));
    submitButton->setDefault(true);
    addButton = new QPushButton(tr("Add Item"));
    deleteButton = new QPushButton(tr("Delete Selected"));
    quitButton = new QPushButton(tr("Quit"));

    buttonBox = new QDialogButtonBox(Qt::Vertical);
    buttonBox->addButton(submitButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(addButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(deleteButton, QDialogButtonBox::ActionRole);

    connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(add()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteROW()));
    connect(view, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(view);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("TGS Inventory"));
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
}
void TableEditor::add()
{
    QSqlQuery query;
    int id;
    query.exec("SELECT MAX(id) FROM tgs");
    query.next();
    id = query.value(0).toInt() + 1;

    query.prepare("insert into tgs values(:id, 'sys', 'cat', 0, '20170101', 'company', '20190101', '20190101', 'pdf_name')");
    query.bindValue(":id",id);
    query.exec();

    model->select();
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
    if(index.column() == 8 && index.isValid()) {
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
