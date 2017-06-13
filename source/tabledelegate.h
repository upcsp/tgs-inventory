//#ifndef TABLEDELEGATE_H
//#define TABLEDELEGATE_H
//#include <QStyledItemDelegate>
//#include <QWidget>
//#include <QPushButton>
//#include <QTableView>

//class ButtonColumnDelegate : public QStyledItemDelegate
//{
//    Q_OBJECT

//public:

//    explicit ButtonColumnDelegate(QObject *parent = 0);
//    ~ButtonColumnDelegate();

//    void paint(QPainter *painter, const QStyleOptionViewItem &option,
//               const QModelIndex &index) const;

//    bool editorEvent(QEvent *event, QAbstractItemModel *model,
//                     const QStyleOptionViewItem &option, const QModelIndex &index);

//public slots:
//    void findManual(const QModelIndex &index);
//    void openManual(const QModelIndex &index);

//private:
//    QTableView *myWidget;
//    QPushButton *btn_open;
//    QPushButton *btn_find;
//    bool isOneCellInEditMode;
//    QPersistentModelIndex currentEditedCellIndex;
//};
//#endif // TABLEDELEGATE_H
