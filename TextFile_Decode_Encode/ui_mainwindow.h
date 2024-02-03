/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QRadioButton *CompressFile;
    QRadioButton *DecompressFile;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QPushButton *OpenFile;
    QPushButton *SaveFile;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(923, 355);
        QFont font;
        font.setPointSize(11);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(100, 0, 961, 101));
        QFont font1;
        font1.setPointSize(28);
        label->setFont(font1);
        CompressFile = new QRadioButton(centralwidget);
        CompressFile->setObjectName("CompressFile");
        CompressFile->setGeometry(QRect(230, 110, 131, 31));
        DecompressFile = new QRadioButton(centralwidget);
        DecompressFile->setObjectName("DecompressFile");
        DecompressFile->setGeometry(QRect(510, 110, 121, 31));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(30, 180, 701, 31));
        textEdit_2 = new QTextEdit(centralwidget);
        textEdit_2->setObjectName("textEdit_2");
        textEdit_2->setGeometry(QRect(30, 240, 701, 31));
        OpenFile = new QPushButton(centralwidget);
        OpenFile->setObjectName("OpenFile");
        OpenFile->setGeometry(QRect(760, 180, 141, 31));
        QFont font2;
        font2.setPointSize(10);
        OpenFile->setFont(font2);
        SaveFile = new QPushButton(centralwidget);
        SaveFile->setObjectName("SaveFile");
        SaveFile->setGeometry(QRect(760, 240, 141, 31));
        SaveFile->setFont(font2);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 923, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "TEXT FILE COMPRESSION/DECOMPRESSION", nullptr));
        CompressFile->setText(QCoreApplication::translate("MainWindow", "COMPRESS", nullptr));
        DecompressFile->setText(QCoreApplication::translate("MainWindow", "DECOMPRESS", nullptr));
        OpenFile->setText(QCoreApplication::translate("MainWindow", "Open File", nullptr));
        SaveFile->setText(QCoreApplication::translate("MainWindow", "Save File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
