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
#include <QtWidgets/QSlider>
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
    customRadioButton *Esquerra;
    customRadioButton *Dreta;
    QGroupBox *groupBox_2;
    QSlider *horizontalSlider;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QWidget *MyForm)
    {
        if (MyForm->objectName().isEmpty())
            MyForm->setObjectName(QString::fromUtf8("MyForm"));
        MyForm->resize(819, 726);
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
        Esquerra = new customRadioButton(groupBox);
        Esquerra->setObjectName(QString::fromUtf8("Esquerra"));
        Esquerra->setGeometry(QRect(0, 20, 151, 23));
        Esquerra->setChecked(true);
        Dreta = new customRadioButton(groupBox);
        Dreta->setObjectName(QString::fromUtf8("Dreta"));
        Dreta->setGeometry(QRect(0, 40, 161, 23));

        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(MyForm);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalSlider = new QSlider(groupBox_2);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(0, 20, 160, 16));
        horizontalSlider->setMaximum(360);
        horizontalSlider->setSingleStep(5);
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(groupBox_2);

        pushButton_2 = new QPushButton(MyForm);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

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
        QObject::connect(Dreta, SIGNAL(clicked()), Dreta, SLOT(gestorClic()));
        QObject::connect(Esquerra, SIGNAL(clicked()), Esquerra, SLOT(gestorClic()));
        QObject::connect(Dreta, SIGNAL(canviaEspelma(int)), widget, SLOT(canviaEspelma(int)));
        QObject::connect(Esquerra, SIGNAL(canviaEspelma(int)), widget, SLOT(canviaEspelma(int)));
        QObject::connect(widget, SIGNAL(teclaT(bool)), Dreta, SLOT(canviEstat(bool)));
        QObject::connect(widget, SIGNAL(teclaT(bool)), Esquerra, SLOT(canviEstat(bool)));
        QObject::connect(widget, SIGNAL(enviaAngle(int)), horizontalSlider, SLOT(setValue(int)));
        QObject::connect(horizontalSlider, SIGNAL(sliderMoved(int)), widget, SLOT(repAngle(int)));
        QObject::connect(pushButton_2, SIGNAL(clicked()), widget, SLOT(canviaEstat()));

        QMetaObject::connectSlotsByName(MyForm);
    } // setupUi

    void retranslateUi(QWidget *MyForm)
    {
        MyForm->setWindowTitle(QCoreApplication::translate("MyForm", "IDI-Lab", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MyForm", "Selecciona espelma", nullptr));
        Esquerra->setText(QCoreApplication::translate("MyForm", "Espelma esquerra", nullptr));
        Dreta->setText(QCoreApplication::translate("MyForm", "Espelma dreta", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MyForm", "Angle de rotaci\303\263", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MyForm", "Apagar/Encendre", nullptr));
        pushButton->setText(QCoreApplication::translate("MyForm", "&Sortir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyForm: public Ui_MyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
