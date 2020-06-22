/********************************************************************************
** Form generated from reading UI file 'analog_io.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALOG_IO_H
#define UI_ANALOG_IO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_analog_io
{
public:
    QPushButton *okButton;
    QGroupBox *groupBox;
    QLineEdit *AO1Edt;
    QLineEdit *AO2Edt;
    QPushButton *SetAnalogOutBtn;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *groupBox_2;
    QLineEdit *AI2Edt;
    QPushButton *GetAnalogInBtn;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *AI1Edt;
    QGroupBox *groupBox_3;
    QLineEdit *ThermistorX11Edt;
    QLineEdit *E1V2Edt;
    QLineEdit *E5VIOEdt;
    QLineEdit *E5VUSBEdt;
    QLineEdit *NTC1X8Edt;
    QLineEdit *NTC2X9Edt;
    QPushButton *GetOnboardAIBtn;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;

    void setupUi(QDialog *analog_io)
    {
        if (analog_io->objectName().isEmpty())
            analog_io->setObjectName(QString::fromUtf8("analog_io"));
        analog_io->resize(381, 541);
        QFont font;
        font.setPointSize(8);
        analog_io->setFont(font);
        okButton = new QPushButton(analog_io);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(270, 500, 81, 25));
        groupBox = new QGroupBox(analog_io);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 30, 341, 101));
        AO1Edt = new QLineEdit(groupBox);
        AO1Edt->setObjectName(QString::fromUtf8("AO1Edt"));
        AO1Edt->setGeometry(QRect(112, 30, 101, 20));
        AO2Edt = new QLineEdit(groupBox);
        AO2Edt->setObjectName(QString::fromUtf8("AO2Edt"));
        AO2Edt->setGeometry(QRect(112, 60, 101, 20));
        SetAnalogOutBtn = new QPushButton(groupBox);
        SetAnalogOutBtn->setObjectName(QString::fromUtf8("SetAnalogOutBtn"));
        SetAnalogOutBtn->setGeometry(QRect(230, 50, 101, 23));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 81, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 60, 81, 16));
        groupBox_2 = new QGroupBox(analog_io);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 150, 341, 101));
        AI2Edt = new QLineEdit(groupBox_2);
        AI2Edt->setObjectName(QString::fromUtf8("AI2Edt"));
        AI2Edt->setGeometry(QRect(112, 60, 101, 20));
        GetAnalogInBtn = new QPushButton(groupBox_2);
        GetAnalogInBtn->setObjectName(QString::fromUtf8("GetAnalogInBtn"));
        GetAnalogInBtn->setGeometry(QRect(230, 40, 101, 23));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 30, 71, 16));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 60, 71, 16));
        AI1Edt = new QLineEdit(groupBox_2);
        AI1Edt->setObjectName(QString::fromUtf8("AI1Edt"));
        AI1Edt->setGeometry(QRect(112, 30, 101, 20));
        groupBox_3 = new QGroupBox(analog_io);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 260, 341, 221));
        ThermistorX11Edt = new QLineEdit(groupBox_3);
        ThermistorX11Edt->setObjectName(QString::fromUtf8("ThermistorX11Edt"));
        ThermistorX11Edt->setGeometry(QRect(112, 40, 101, 20));
        E1V2Edt = new QLineEdit(groupBox_3);
        E1V2Edt->setObjectName(QString::fromUtf8("E1V2Edt"));
        E1V2Edt->setGeometry(QRect(112, 70, 101, 20));
        E5VIOEdt = new QLineEdit(groupBox_3);
        E5VIOEdt->setObjectName(QString::fromUtf8("E5VIOEdt"));
        E5VIOEdt->setGeometry(QRect(112, 100, 101, 20));
        E5VUSBEdt = new QLineEdit(groupBox_3);
        E5VUSBEdt->setObjectName(QString::fromUtf8("E5VUSBEdt"));
        E5VUSBEdt->setGeometry(QRect(112, 130, 101, 20));
        NTC1X8Edt = new QLineEdit(groupBox_3);
        NTC1X8Edt->setObjectName(QString::fromUtf8("NTC1X8Edt"));
        NTC1X8Edt->setGeometry(QRect(112, 160, 101, 20));
        NTC2X9Edt = new QLineEdit(groupBox_3);
        NTC2X9Edt->setObjectName(QString::fromUtf8("NTC2X9Edt"));
        NTC2X9Edt->setGeometry(QRect(112, 190, 101, 20));
        GetOnboardAIBtn = new QPushButton(groupBox_3);
        GetOnboardAIBtn->setObjectName(QString::fromUtf8("GetOnboardAIBtn"));
        GetOnboardAIBtn->setGeometry(QRect(230, 110, 101, 23));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 40, 71, 16));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 70, 46, 14));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 100, 46, 14));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 130, 46, 14));
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 160, 61, 16));
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 190, 61, 16));
        QWidget::setTabOrder(AO1Edt, AO2Edt);
        QWidget::setTabOrder(AO2Edt, SetAnalogOutBtn);
        QWidget::setTabOrder(SetAnalogOutBtn, AI1Edt);
        QWidget::setTabOrder(AI1Edt, AI2Edt);
        QWidget::setTabOrder(AI2Edt, GetAnalogInBtn);
        QWidget::setTabOrder(GetAnalogInBtn, ThermistorX11Edt);
        QWidget::setTabOrder(ThermistorX11Edt, E1V2Edt);
        QWidget::setTabOrder(E1V2Edt, E5VIOEdt);
        QWidget::setTabOrder(E5VIOEdt, E5VUSBEdt);
        QWidget::setTabOrder(E5VUSBEdt, NTC1X8Edt);
        QWidget::setTabOrder(NTC1X8Edt, NTC2X9Edt);
        QWidget::setTabOrder(NTC2X9Edt, GetOnboardAIBtn);
        QWidget::setTabOrder(GetOnboardAIBtn, okButton);

        retranslateUi(analog_io);
        QObject::connect(okButton, SIGNAL(clicked()), analog_io, SLOT(accept()));

        QMetaObject::connectSlotsByName(analog_io);
    } // setupUi

    void retranslateUi(QDialog *analog_io)
    {
        analog_io->setWindowTitle(QCoreApplication::translate("analog_io", "Test Analog IO", nullptr));
        okButton->setText(QCoreApplication::translate("analog_io", "OK", nullptr));
        groupBox->setTitle(QCoreApplication::translate("analog_io", "Analog Output", nullptr));
        SetAnalogOutBtn->setText(QCoreApplication::translate("analog_io", "Set Analog Out", nullptr));
        label->setText(QCoreApplication::translate("analog_io", "Pin 17 (AO1)", nullptr));
        label_2->setText(QCoreApplication::translate("analog_io", "Pin 26 (AO2)", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("analog_io", "Analog Input HD26-F connector", nullptr));
        GetAnalogInBtn->setText(QCoreApplication::translate("analog_io", "Get Analog In", nullptr));
        label_3->setText(QCoreApplication::translate("analog_io", "Pin 9 (AI1)", nullptr));
        label_4->setText(QCoreApplication::translate("analog_io", "Pin 18 (AI2) ", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("analog_io", "Onboard Analog Input", nullptr));
        GetOnboardAIBtn->setText(QCoreApplication::translate("analog_io", "Get Onboard AI", nullptr));
        label_5->setText(QCoreApplication::translate("analog_io", "Thermistor X11", nullptr));
        label_6->setText(QCoreApplication::translate("analog_io", "1V2", nullptr));
        label_7->setText(QCoreApplication::translate("analog_io", "5VIO", nullptr));
        label_8->setText(QCoreApplication::translate("analog_io", "5VUSB", nullptr));
        label_9->setText(QCoreApplication::translate("analog_io", "NTC1 X8", nullptr));
        label_10->setText(QCoreApplication::translate("analog_io", "NTC2 X9", nullptr));
    } // retranslateUi

};

namespace Ui {
    class analog_io: public Ui_analog_io {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALOG_IO_H
