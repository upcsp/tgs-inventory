#ifndef SQLMODELSUBCLASS_H
#define SQLMODELSUBCLASS_H
#include <QVariant>
#include <QSqlTableModel>

class MyTableModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit MyTableModel(QObject * parent = 0,
                          QSqlDatabase db = QSqlDatabase() ); // the same arguments as QSqlTableModel
     QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
};
#endif // SQLMODELSUBCLASS_H
