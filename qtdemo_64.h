#ifndef QTDEMO_64_H
#define QTDEMO_64_H

//#include <QtGui/QMainWindow>
#include <QMainWindow>
#include "ui_qtdemo_64.h"
#include <QUdpSocket>
#include <QHostAddress>

class Qtdemo_64 : public QMainWindow
{
	Q_OBJECT

public:
    Qtdemo_64(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~Qtdemo_64();
	void ConnectGui();
	void DisconnectGui();
	void UpdateButtons();

private:
	Ui::Qtdemo_64Class ui;
    QUdpSocket *mSocket;
    QHostAddress addr_destination;
    quint16 port_destination;


private slots:
	void on_DigitalIoBtn_clicked();
	void on_AnalogIoBtn_clicked();
	void on_WriteEepromBtn_clicked();
	void on_DisableGraphChk_stateChanged(int);
	void on_DeactivateBtn_clicked();
	void on_ReadEepromBtn_clicked();
	void on_ActivateBtn_clicked();
	void on_UpdateListBtn_clicked();
	void on_StopMeasBtn_clicked();
	void on_StartMeasBtn_clicked();
	void on_ShowEepromBtn_clicked();
	void on_OpenCommBtn_clicked();
    


    void on_darkRef_clicked();

    void on_whiteRef_clicked();

protected:
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *event);

public slots:
	void ReceiveDataIsHere(int WParam, int LParam);
	// avoid a name starting with "on_" here, otherwise you will get a
	// warning, as there is no defined signal, just an emit in "application.cpp"
    void readyReade();

};

#endif // QTDEMO_64_H
