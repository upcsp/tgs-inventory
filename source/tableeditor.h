#ifndef TABLEEDITOR_H
#define TABLEEDITOR_H

#include <QDialog>
#include <QTableView>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStatusBar>
#include <QLabel>
#include "ui_tableeditor.h"

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QPushButton;
class QSqlTableModel;
QT_END_NAMESPACE

class TableEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TableEditor(const QString &tableName, QWidget *parent = 0);
    QTableView *view;
    void putButtons();
    void parseData();
private slots:
    void submit();
    void add();
    void deleteROW();
    void onTableClicked(const QModelIndex &index);
    void open(int index);
    void find(int index);
private:
    QPushButton *submitButton;
    QPushButton *addButton;
    QPushButton *quitButton;
    QPushButton *deleteButton;
    QPushButton* openButton;
    QPushButton* findButton;
    QDialogButtonBox *buttonBox;
//    Ui::TableEditor ui;
    QSqlTableModel *model;
    QSignalMapper *mapper_find;
    QSignalMapper *mapper_open;
    QVBoxLayout *mainLayout;
    QHBoxLayout *secLayout;
    QStatusBar* statusBar;
    QLabel *statusLabel;
};

#endif
