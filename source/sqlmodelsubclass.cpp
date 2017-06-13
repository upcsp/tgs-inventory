#include "sqlmodelsubclass.h"

MyTableModel::MyTableModel(QObject * parent, QSqlDatabase db) :
QSqlTableModel(parent, db)
{}

QVariant MyTableModel::data(const QModelIndex& index, int role) const {
    if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    } else {
        return QSqlTableModel::data(index, role);
    }
}
