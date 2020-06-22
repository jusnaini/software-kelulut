/********************************************************************************
** Form generated from reading UI file 'digital_io.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIGITAL_IO_H
#define UI_DIGITAL_IO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_digital_io
{
public:
    QPushButton *okButton;
    QGroupBox *groupBox;
    QCheckBox *DO1Chk;
    QCheckBox *DO2Chk;
    QCheckBox *DO3Chk;
    QCheckBox *DO4Chk;
    QCheckBox *DO5Chk;
    QCheckBox *DO6Chk;
    QCheckBox *DO7Chk;
    QCheckBox *DO8Chk;
    QCheckBox *DO9Chk;
    QCheckBox *DO10Chk;
    QCheckBox *PWM1Chk;
    QCheckBox *PWM2Chk;
    QCheckBox *PWM3Chk;
    QCheckBox *PWM5Chk;
    QCheckBox *PWM6Chk;
    QCheckBox *PWM7Chk;
    QLineEdit *DutyCycle1Edt;
    QLineEdit *DutyCycle2Edt;
    QLineEdit *DutyCycle3Edt;
    QLineEdit *DutyCycle5Edt;
    QLineEdit *DutyCycle6Edt;
    QLineEdit *DutyCycle7Edt;
    QLineEdit *Frequency123Edt;
    QLineEdit *Frequency567Edt;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QGroupBox *groupBox_2;
    QPushButton *GetDigitalInputsBtn;
    QCheckBox *DI1Chk;
    QCheckBox *DI2Chk;
    QCheckBox *DI3Chk;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;

    void setupUi(QDialog *digital_io)
    {
        if (digital_io->objectName().isEmpty())
            digital_io->setObjectName(QString::fromUtf8("digital_io"));
        digital_io->resize(556, 562);
        QFont font;
        font.setPointSize(8);
        digital_io->setFont(font);
        okButton = new QPushButton(digital_io);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(450, 520, 77, 25));
        groupBox = new QGroupBox(digital_io);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 20, 521, 341));
        DO1Chk = new QCheckBox(groupBox);
        DO1Chk->setObjectName(QString::fromUtf8("DO1Chk"));
        DO1Chk->setGeometry(QRect(80, 40, 72, 18));
        DO2Chk = new QCheckBox(groupBox);
        DO2Chk->setObjectName(QString::fromUtf8("DO2Chk"));
        DO2Chk->setGeometry(QRect(80, 70, 72, 18));
        DO3Chk = new QCheckBox(groupBox);
        DO3Chk->setObjectName(QString::fromUtf8("DO3Chk"));
        DO3Chk->setGeometry(QRect(80, 100, 72, 18));
        DO4Chk = new QCheckBox(groupBox);
        DO4Chk->setObjectName(QString::fromUtf8("DO4Chk"));
        DO4Chk->setGeometry(QRect(80, 130, 72, 18));
        DO5Chk = new QCheckBox(groupBox);
        DO5Chk->setObjectName(QString::fromUtf8("DO5Chk"));
        DO5Chk->setGeometry(QRect(80, 160, 72, 18));
        DO6Chk = new QCheckBox(groupBox);
        DO6Chk->setObjectName(QString::fromUtf8("DO6Chk"));
        DO6Chk->setGeometry(QRect(80, 190, 72, 18));
        DO7Chk = new QCheckBox(groupBox);
        DO7Chk->setObjectName(QString::fromUtf8("DO7Chk"));
        DO7Chk->setGeometry(QRect(80, 220, 72, 18));
        DO8Chk = new QCheckBox(groupBox);
        DO8Chk->setObjectName(QString::fromUtf8("DO8Chk"));
        DO8Chk->setGeometry(QRect(80, 250, 72, 18));
        DO9Chk = new QCheckBox(groupBox);
        DO9Chk->setObjectName(QString::fromUtf8("DO9Chk"));
        DO9Chk->setGeometry(QRect(80, 280, 72, 18));
        DO10Chk = new QCheckBox(groupBox);
        DO10Chk->setObjectName(QString::fromUtf8("DO10Chk"));
        DO10Chk->setGeometry(QRect(80, 310, 72, 18));
        PWM1Chk = new QCheckBox(groupBox);
        PWM1Chk->setObjectName(QString::fromUtf8("PWM1Chk"));
        PWM1Chk->setGeometry(QRect(190, 40, 72, 18));
        PWM2Chk = new QCheckBox(groupBox);
        PWM2Chk->setObjectName(QString::fromUtf8("PWM2Chk"));
        PWM2Chk->setGeometry(QRect(190, 70, 72, 18));
        PWM3Chk = new QCheckBox(groupBox);
        PWM3Chk->setObjectName(QString::fromUtf8("PWM3Chk"));
        PWM3Chk->setGeometry(QRect(190, 100, 72, 18));
        PWM5Chk = new QCheckBox(groupBox);
        PWM5Chk->setObjectName(QString::fromUtf8("PWM5Chk"));
        PWM5Chk->setGeometry(QRect(190, 160, 72, 18));
        PWM6Chk = new QCheckBox(groupBox);
        PWM6Chk->setObjectName(QString::fromUtf8("PWM6Chk"));
        PWM6Chk->setGeometry(QRect(190, 190, 72, 18));
        PWM7Chk = new QCheckBox(groupBox);
        PWM7Chk->setObjectName(QString::fromUtf8("PWM7Chk"));
        PWM7Chk->setGeometry(QRect(190, 220, 72, 18));
        DutyCycle1Edt = new QLineEdit(groupBox);
        DutyCycle1Edt->setObjectName(QString::fromUtf8("DutyCycle1Edt"));
        DutyCycle1Edt->setGeometry(QRect(280, 40, 61, 20));
        DutyCycle2Edt = new QLineEdit(groupBox);
        DutyCycle2Edt->setObjectName(QString::fromUtf8("DutyCycle2Edt"));
        DutyCycle2Edt->setGeometry(QRect(280, 70, 61, 20));
        DutyCycle3Edt = new QLineEdit(groupBox);
        DutyCycle3Edt->setObjectName(QString::fromUtf8("DutyCycle3Edt"));
        DutyCycle3Edt->setGeometry(QRect(280, 100, 61, 20));
        DutyCycle5Edt = new QLineEdit(groupBox);
        DutyCycle5Edt->setObjectName(QString::fromUtf8("DutyCycle5Edt"));
        DutyCycle5Edt->setGeometry(QRect(280, 160, 61, 20));
        DutyCycle6Edt = new QLineEdit(groupBox);
        DutyCycle6Edt->setObjectName(QString::fromUtf8("DutyCycle6Edt"));
        DutyCycle6Edt->setGeometry(QRect(280, 190, 61, 20));
        DutyCycle7Edt = new QLineEdit(groupBox);
        DutyCycle7Edt->setObjectName(QString::fromUtf8("DutyCycle7Edt"));
        DutyCycle7Edt->setGeometry(QRect(280, 220, 61, 20));
        Frequency123Edt = new QLineEdit(groupBox);
        Frequency123Edt->setObjectName(QString::fromUtf8("Frequency123Edt"));
        Frequency123Edt->setGeometry(QRect(380, 60, 51, 41));
        Frequency567Edt = new QLineEdit(groupBox);
        Frequency567Edt->setObjectName(QString::fromUtf8("Frequency567Edt"));
        Frequency567Edt->setGeometry(QRect(360, 180, 51, 41));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(270, 20, 91, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(380, 20, 121, 41));
        label_2->setWordWrap(true);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 40, 46, 14));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 70, 46, 14));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 100, 46, 14));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 130, 46, 14));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 160, 46, 14));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 190, 46, 14));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 220, 46, 14));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 250, 46, 14));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 280, 46, 14));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 310, 46, 14));
        groupBox_2 = new QGroupBox(digital_io);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 380, 521, 131));
        GetDigitalInputsBtn = new QPushButton(groupBox_2);
        GetDigitalInputsBtn->setObjectName(QString::fromUtf8("GetDigitalInputsBtn"));
        GetDigitalInputsBtn->setGeometry(QRect(190, 60, 111, 23));
        DI1Chk = new QCheckBox(groupBox_2);
        DI1Chk->setObjectName(QString::fromUtf8("DI1Chk"));
        DI1Chk->setGeometry(QRect(80, 30, 72, 18));
        DI2Chk = new QCheckBox(groupBox_2);
        DI2Chk->setObjectName(QString::fromUtf8("DI2Chk"));
        DI2Chk->setGeometry(QRect(80, 60, 72, 18));
        DI3Chk = new QCheckBox(groupBox_2);
        DI3Chk->setObjectName(QString::fromUtf8("DI3Chk"));
        DI3Chk->setGeometry(QRect(80, 90, 72, 18));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 30, 46, 14));
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 60, 46, 14));
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 90, 46, 14));
        QWidget::setTabOrder(DO1Chk, DO2Chk);
        QWidget::setTabOrder(DO2Chk, DO3Chk);
        QWidget::setTabOrder(DO3Chk, DO4Chk);
        QWidget::setTabOrder(DO4Chk, DO5Chk);
        QWidget::setTabOrder(DO5Chk, DO6Chk);
        QWidget::setTabOrder(DO6Chk, DO7Chk);
        QWidget::setTabOrder(DO7Chk, DO8Chk);
        QWidget::setTabOrder(DO8Chk, DO9Chk);
        QWidget::setTabOrder(DO9Chk, DO10Chk);
        QWidget::setTabOrder(DO10Chk, PWM1Chk);
        QWidget::setTabOrder(PWM1Chk, PWM2Chk);
        QWidget::setTabOrder(PWM2Chk, PWM3Chk);
        QWidget::setTabOrder(PWM3Chk, PWM5Chk);
        QWidget::setTabOrder(PWM5Chk, PWM6Chk);
        QWidget::setTabOrder(PWM6Chk, PWM7Chk);
        QWidget::setTabOrder(PWM7Chk, DutyCycle1Edt);
        QWidget::setTabOrder(DutyCycle1Edt, DutyCycle2Edt);
        QWidget::setTabOrder(DutyCycle2Edt, DutyCycle3Edt);
        QWidget::setTabOrder(DutyCycle3Edt, DutyCycle5Edt);
        QWidget::setTabOrder(DutyCycle5Edt, DutyCycle6Edt);
        QWidget::setTabOrder(DutyCycle6Edt, DutyCycle7Edt);
        QWidget::setTabOrder(DutyCycle7Edt, Frequency123Edt);
        QWidget::setTabOrder(Frequency123Edt, Frequency567Edt);
        QWidget::setTabOrder(Frequency567Edt, DI1Chk);
        QWidget::setTabOrder(DI1Chk, DI2Chk);
        QWidget::setTabOrder(DI2Chk, DI3Chk);
        QWidget::setTabOrder(DI3Chk, GetDigitalInputsBtn);
        QWidget::setTabOrder(GetDigitalInputsBtn, okButton);

        retranslateUi(digital_io);
        QObject::connect(okButton, SIGNAL(clicked()), digital_io, SLOT(accept()));

        QMetaObject::connectSlotsByName(digital_io);
    } // setupUi

    void retranslateUi(QDialog *digital_io)
    {
        digital_io->setWindowTitle(QCoreApplication::translate("digital_io", "Test Digital IO", nullptr));
        okButton->setText(QCoreApplication::translate("digital_io", "OK", nullptr));
        groupBox->setTitle(QCoreApplication::translate("digital_io", "Digital Outputs", nullptr));
        DO1Chk->setText(QCoreApplication::translate("digital_io", "DO1", nullptr));
        DO2Chk->setText(QCoreApplication::translate("digital_io", "DO2", nullptr));
        DO3Chk->setText(QCoreApplication::translate("digital_io", "DO3", nullptr));
        DO4Chk->setText(QCoreApplication::translate("digital_io", "DO4", nullptr));
        DO5Chk->setText(QCoreApplication::translate("digital_io", "DO5", nullptr));
        DO6Chk->setText(QCoreApplication::translate("digital_io", "DO6", nullptr));
        DO7Chk->setText(QCoreApplication::translate("digital_io", "DO7", nullptr));
        DO8Chk->setText(QCoreApplication::translate("digital_io", "DO8", nullptr));
        DO9Chk->setText(QCoreApplication::translate("digital_io", "DO9", nullptr));
        DO10Chk->setText(QCoreApplication::translate("digital_io", "DO10", nullptr));
        PWM1Chk->setText(QCoreApplication::translate("digital_io", "PWM", nullptr));
        PWM2Chk->setText(QCoreApplication::translate("digital_io", "PWM", nullptr));
        PWM3Chk->setText(QCoreApplication::translate("digital_io", "PWM", nullptr));
        PWM5Chk->setText(QCoreApplication::translate("digital_io", "PWM", nullptr));
        PWM6Chk->setText(QCoreApplication::translate("digital_io", "PWM", nullptr));
        PWM7Chk->setText(QCoreApplication::translate("digital_io", "PWM", nullptr));
        label->setText(QCoreApplication::translate("digital_io", "DutyCycle [%]", nullptr));
        label_2->setText(QCoreApplication::translate("digital_io", "Frequency (500-300000 Hz)", nullptr));
        label_3->setText(QCoreApplication::translate("digital_io", "Pin 11", nullptr));
        label_4->setText(QCoreApplication::translate("digital_io", "Pin 2", nullptr));
        label_5->setText(QCoreApplication::translate("digital_io", "Pin 20", nullptr));
        label_6->setText(QCoreApplication::translate("digital_io", "Pin 12", nullptr));
        label_7->setText(QCoreApplication::translate("digital_io", "Pin 3", nullptr));
        label_8->setText(QCoreApplication::translate("digital_io", "Pin 21", nullptr));
        label_9->setText(QCoreApplication::translate("digital_io", "Pin 13", nullptr));
        label_10->setText(QCoreApplication::translate("digital_io", "Pin 4", nullptr));
        label_11->setText(QCoreApplication::translate("digital_io", "Pin 22", nullptr));
        label_12->setText(QCoreApplication::translate("digital_io", "Pin 25", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("digital_io", "Digital Inputs", nullptr));
        GetDigitalInputsBtn->setText(QCoreApplication::translate("digital_io", "Get Digital Inputs", nullptr));
        DI1Chk->setText(QCoreApplication::translate("digital_io", "DI1", nullptr));
        DI2Chk->setText(QCoreApplication::translate("digital_io", "DI2", nullptr));
        DI3Chk->setText(QCoreApplication::translate("digital_io", "DI3", nullptr));
        label_13->setText(QCoreApplication::translate("digital_io", "Pin 24", nullptr));
        label_14->setText(QCoreApplication::translate("digital_io", "Pin 7", nullptr));
        label_15->setText(QCoreApplication::translate("digital_io", "Pin 16", nullptr));
    } // retranslateUi

};

namespace Ui {
    class digital_io: public Ui_digital_io {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIGITAL_IO_H
