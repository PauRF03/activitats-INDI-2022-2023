/********************************************************************************
** Form generated from reading UI file 'MyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYFORM_H
#define UI_MYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MyGLWidget.h"
#include "customradiobutton.h"

QT_BEGIN_NAMESPACE

class Ui_MyForm
{
public:
    QHBoxLayout *horizontalLayout;
    MyGLWidget *widget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    customRadioButton *tercerap;
    customRadioButton *POVMorty;
    QPushButton *pushButton;

    void setupUi(QWidget *MyForm)
    {
        if (MyForm->objectName().isEmpty())
            MyForm->setObjectName(QString::fromUtf8("MyForm"));
        MyForm->resize(945, 726);
        horizontalLayout = new QHBoxLayout(MyForm);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new MyGLWidget(MyForm);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(widget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(MyForm);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        tercerap = new customRadioButton(groupBox);
        tercerap->setObjectName(QString::fromUtf8("tercerap"));
        tercerap->setGeometry(QRect(0, 20, 112, 31));
        tercerap->setChecked(true);
        POVMorty = new customRadioButton(groupBox);
        POVMorty->setObjectName(QString::fromUtf8("POVMorty"));
        POVMorty->setGeometry(QRect(0, 50, 112, 23));

        verticalLayout->addWidget(groupBox);

        pushButton = new QPushButton(MyForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(MyForm);
        QObject::connect(pushButton, SIGNAL(clicked()), MyForm, SLOT(close()));
        QObject::connect(POVMorty, SIGNAL(enviacamera(int)), widget, SLOT(canviacamera(int)));
        QObject::connect(POVMorty, SIGNAL(clicked()), POVMorty, SLOT(gestorclic()));
        QObject::connect(tercerap, SIGNAL(clicked()), tercerap, SLOT(gestorclic()));
        QObject::connect(tercerap, SIGNAL(enviacamera(int)), widget, SLOT(canviacamera(int)));
        QObject::connect(widget, SIGNAL(teclaC(bool)), POVMorty, SLOT(canviEstat(bool)));
        QObject::connect(widget, SIGNAL(teclaC(bool)), tercerap, SLOT(canviEstat(bool)));

        QMetaObject::connectSlotsByName(MyForm);
    } // setupUi

    void retranslateUi(QWidget *MyForm)
    {
        MyForm->setWindowTitle(QCoreApplication::translate("MyForm", "IDI-Lab", nullptr));
        groupBox->setTitle(QString());
        tercerap->setText(QCoreApplication::translate("MyForm", "3ra pers.", nullptr));
        POVMorty->setText(QCoreApplication::translate("MyForm", "1ra pers.", nullptr));
        pushButton->setText(QCoreApplication::translate("MyForm", "&Sortir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyForm: public Ui_MyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
