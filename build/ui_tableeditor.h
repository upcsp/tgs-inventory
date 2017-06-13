/********************************************************************************
** Form generated from reading UI file 'tableeditor.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLEEDITOR_H
#define UI_TABLEEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TableEditor
{
public:

    void setupUi(QWidget *TableEditor)
    {
        if (TableEditor->objectName().isEmpty())
            TableEditor->setObjectName(QStringLiteral("TableEditor"));
        TableEditor->resize(400, 300);

        retranslateUi(TableEditor);

        QMetaObject::connectSlotsByName(TableEditor);
    } // setupUi

    void retranslateUi(QWidget *TableEditor)
    {
        TableEditor->setWindowTitle(QApplication::translate("TableEditor", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TableEditor: public Ui_TableEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLEEDITOR_H
