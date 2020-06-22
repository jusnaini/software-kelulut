#include <QtGui>
#include <QApplication>
#include <QPushButton>
#include "qtdemo_64.h"
#include "ui_qtdemo_64.h"
#include "eeprom.h"
#include "analog_io.h"
#include "digital_io.h"
#include <libavs/as5216.h>
#include "application.h"
#include "plot.h"
#include <QMessageBox>
#include <QKeyEvent>
#include <QUdpSocket>
#include <QHostAddress>

//#define localIP "127.0.0.1"
#define localIP "10.47.118.232"
#define localPort 12345

QHostAddress g_clientIP{}; //declare global variable for client IP address
quint16 g_clientPort{}; //declare global variable for client port number

int darkRef = 0; //dark reference indicator
int whiteRef = 0; //white reference indicator

double g_buffer_dark[MAX_NR_PIXELS];
double g_buffer_white[MAX_NR_PIXELS];




Qtdemo_64::Qtdemo_64(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);


	ui.PreScanChk->hide();
	connect(qApp, SIGNAL(DataIsHere(int, int)), this, SLOT(ReceiveDataIsHere(int, int)));
	ui.UpdateListBtn->setEnabled(false);
	ui.ActivateBtn->setEnabled(false);
	ui.DeactivateBtn->setEnabled(false);
	ui.DigitalIoBtn->setEnabled(false);
	ui.AnalogIoBtn->setEnabled(false);
	ui.ShowEepromBtn->setEnabled(false);
	ui.ReadEepromBtn->setEnabled(false);
	ui.WriteEepromBtn->setEnabled(false);
	ui.StartMeasBtn->setEnabled(false);
	ui.StopMeasBtn->setEnabled(false);
    ui.darkRef->setEnabled(false);
    ui.whiteRef->setEnabled(false);

    QStatusBar* statusbar = statusBar();

    //Establish UDP connection
    mSocket = new QUdpSocket(this);
    mSocket->bind(QHostAddress(localIP),localPort);
    statusbar->showMessage(tr("Waiting for connection.. "));
    connect(mSocket, SIGNAL(readyRead()), this, SLOT(readyReade()));
}

Qtdemo_64::~Qtdemo_64()
{
    extern long m_DeviceHandle;
    if (m_DeviceHandle!=INVALID_AVS_HANDLE_VALUE)
    {
      int l_Res = AVS_StopMeasure(m_DeviceHandle);
      if (ERR_SUCCESS != l_Res)
      {
          QMessageBox::critical(this, tr("QT4 Demo"),
                tr("Error in AVS_StopMeasure, code %1").arg(l_Res),
                QMessageBox::Ok, QMessageBox::Ok);
      }
    }
    AVS_Done();
}

void Qtdemo_64::ReceiveDataIsHere(int WParam, int LParam)
{
    extern unsigned int l_Time;
    extern unsigned int m_PreviousTimeStamp;
    extern long m_DeviceHandle;
    extern double l_pSpectrum[MAX_NR_PIXELS];
	unsigned char l_saturated[MAX_NR_PIXELS];
    extern unsigned short m_NrPixels;
    extern unsigned int m_Measurements;
    extern unsigned int m_Failures;
    extern QTime m_Time;
    int	l_Ticks;
    int i=0;
    unsigned int l_Dif;
    QString l_Line;
    QString myDatagram;
    double l_AvgScantimeRAM;

    int NrScans = QString(ui.NrMeasEdt->text()).toUInt();


	QStatusBar* statusbar = statusBar();

	if (WParam >= ERR_SUCCESS)
	{
		if ((LParam == m_DeviceHandle) && (m_NrPixels > 0))
		{
			if (ERR_SUCCESS == WParam) // normal measurements
			{
				statusbar->showMessage(tr("Meas.Status: success"));
				m_Measurements++;
                if (ERR_SUCCESS == AVS_GetScopeData(m_DeviceHandle,&l_Time,l_pSpectrum))//returns pixel value
				{
                    //check if pixel saturated
                    if (ERR_SUCCESS == AVS_GetSaturatedPixels(m_DeviceHandle, l_saturated))//returns saturated pixel(1)
						{
							bool saturated = false;
							extern unsigned short m_NrPixels;
							for (int j = 0; j <= m_NrPixels-1; j++){
								saturated = saturated || (l_saturated[j] != 0);
							}
                            ui.SaturatedChk->setChecked(saturated); //indicator if pixel saturated
						}

                    //set dark reference
                    if (darkRef == 1){
                        QString myDatagram2;
                        for(int i=0; i<=MAX_NR_PIXELS-1; i++)
                        {
                           g_buffer_dark[i] = g_buffer_dark[i]+ (l_pSpectrum[i]/NrScans);
                           if(i== (MAX_NR_PIXELS-1))
                           {
                               myDatagram2+=QString::number(l_pSpectrum[i]);
                               myDatagram+=QString::number(g_buffer_dark[i]);
                           }
                           else
                           {
                               myDatagram2+=QString::number(l_pSpectrum[i]) + ",";
                               myDatagram+=QString::number(g_buffer_dark[i])+",";
                           }
                        }
                        myDatagram = "darkRef,"+myDatagram;
                        auto datagram = myDatagram.toLatin1();
                        mSocket->writeDatagram(datagram,g_clientIP,g_clientPort);
                    }

                    //set white reference
                    else if(whiteRef == 1)
                    {
                        QString myDatagram2;
                        for(int i=0; i<=MAX_NR_PIXELS-1; i++)
                        {
                           g_buffer_white[i] = g_buffer_white[i]+ (l_pSpectrum[i]/NrScans);
                           if(i== (MAX_NR_PIXELS-1))
                           {
                               myDatagram2+=QString::number(l_pSpectrum[i]);
                               myDatagram+=QString::number(g_buffer_white[i]);
                           }
                           else
                           {
                               myDatagram2+=QString::number(l_pSpectrum[i]) + ",";
                               myDatagram+=QString::number(g_buffer_white[i])+",";
                           }
                        }
                        myDatagram = "whiteRef,"+myDatagram;
                        auto datagram = myDatagram.toLatin1();
                        mSocket->writeDatagram(datagram,g_clientIP,g_clientPort);
                    }

                    //normal measurement if pixel not saturated
                    else
                    {
                        for(i=0; i<=MAX_NR_PIXELS-1; i++)
                        {
                           if(i== (MAX_NR_PIXELS-1))
                           {

                             if(l_pSpectrum[i] > g_buffer_white[i])
                                 l_pSpectrum[i] = g_buffer_white[i] - g_buffer_dark[i];
                             else
                                 l_pSpectrum[i] = l_pSpectrum[i] - g_buffer_dark[i];
                             myDatagram+=QString::number(l_pSpectrum[i]);
                           }
                           else
                           {
                              if(l_pSpectrum[i] > g_buffer_white[i])
                                   l_pSpectrum[i] = g_buffer_white[i]-g_buffer_dark[i];
                              else
                                   l_pSpectrum[i] = l_pSpectrum[i] - g_buffer_dark[i];
                              myDatagram+=QString::number(l_pSpectrum[i]) + ",";
                           }
                        }
                        myDatagram = "spec,"+myDatagram;
                        auto datagram = myDatagram.toLatin1();
                        mSocket->writeDatagram(datagram,g_clientIP,g_clientPort);
                    }


                   ui.plot->update_plot();// Display graph
                   l_Dif = l_Time - m_PreviousTimeStamp;  // l_Time in 10 us ticks
                   m_PreviousTimeStamp = l_Time;
                   if (l_Dif != 0)
                   {
                       ui.LastScanEdt->setText(QString("%1").arg(l_Dif/100.0,7,'f',2)); //millisec
                   }
                }//end of if(ERR_SUCCESS == AVS_GetScopeData())


                //else ERR_SUCCESS != AVS_GetScopeData()
                else
                {
                    statusbar->showMessage(tr("Meas.Status: no data available"));
                }

				l_Ticks = m_Time.elapsed();
				ui.TimeSinceStartEdt->setText(QString("%1").arg(l_Ticks/1000));
				ui.NrScansEdt->setText(QString("%1").arg(m_Measurements));
				double timeperscan = double(l_Ticks) / double(m_Measurements);
				ui.TimePerScanEdt->setText(QString("%1").arg(timeperscan,7,'f',2));
                if (QString(ui.NrMeasEdt->text()).toInt() > 0)
                    ui.StartMeasBtn->setEnabled(QString(ui.NrMeasEdt->text()).toUInt() == m_Measurements);

                if(QString(ui.NrMeasEdt->text()).toUInt() == m_Measurements) //last measurement done
                {
                    darkRef = 0;
                    whiteRef = 0;
                    ui.darkRef->setEnabled(true);
                    ui.whiteRef->setEnabled(true);
                }




			}
			else	// StoreToRam measurements
			{
				l_AvgScantimeRAM = 0.0;
				statusbar->showMessage(tr("Meas.Status: Reading RAM"));
				for (int j = 1; j <= WParam; j++)
				{
					if (ERR_SUCCESS == AVS_GetScopeData(m_DeviceHandle, &l_Time, l_pSpectrum))
					{
                        ui.plot->update_plot();
						l_Dif = l_Time - m_PreviousTimeStamp;  //l_Time in 10 us ticks
						m_PreviousTimeStamp = l_Time;
						if (l_Dif != 0)
						{
							ui.LastScanEdt->setText(QString("%1").arg(l_Dif/100.0,7,'f',2)); //millisec
						}
						if (j>1)
						{
							l_AvgScantimeRAM = (l_AvgScantimeRAM*(j-2)+l_Dif/100.0) / (j-1);
							ui.TimePerScanEdt->setText(QString("%1").arg(l_AvgScantimeRAM,7,'f',3));
						}
					}
					else
					{
						statusbar->showMessage(tr("Meas.Status: No Data Available"));
					}
					l_Ticks = m_Time.elapsed();
					ui.TimeSinceStartEdt->setText(QString("%1").arg(l_Ticks/1000));
					ui.NrScansEdt->setText(QString("%1").arg(j));
				}
				statusbar->showMessage(tr("Meas.Status: Finished Reading RAM"));
				ui.StartMeasBtn->setEnabled(true);

			}
		}

	}
	else  // WParam < 0 indicates an error
	{
		statusbar->showMessage(tr("Meas.Status: failed. Error %1").arg(WParam));
		m_Failures++;
	}
	ui.NrFailuresEdt->setText(QString("%1").arg(m_Failures));
}

void Qtdemo_64::on_OpenCommBtn_clicked()
{
  QString status_flag; //connection status
  //QString MsgToClient; //datagram for client
  QStatusBar* statusbar = statusBar();

  statusbar->showMessage(tr("Open communication busy"));
  status_flag = "Busy";

  // AVS_Register(HWND(this->winId()));
  int l_Port = AVS_Init(0);

  if (l_Port > 0)
  {
    statusbar->showMessage(tr("Connected: USB"));
    //status_flag = "USB";
    ui.UpdateListBtn->setEnabled(true);
    on_UpdateListBtn_clicked();
  }
  else 
  {
    AVS_Done();
    l_Port = AVS_Init(-1);
    if (l_Port > 0)
    {
        statusbar->showMessage(tr("Connected: RS-232"));
        //status_flag = "RS232";
        ui.UpdateListBtn->setEnabled(true);
        on_UpdateListBtn_clicked();
    }
    else
    {
        statusbar->showMessage(tr("Open communication failed"));
        status_flag = "No device connected";
        AVS_Done();
        mSocket->writeDatagram(status_flag.toLatin1(),g_clientIP,g_clientPort);
    }
  }
}

void Qtdemo_64::on_ShowEepromBtn_clicked()
{
    eeprom w2;
    w2.exec();
    w2.activateWindow();
    w2.raise();
}

void Qtdemo_64::on_StartMeasBtn_clicked()
{
    bool ok;
    MeasConfigType l_PrepareMeasData;
    QLocale::setDefault(QLocale::Dutch);
    QStatusBar* statusbar = statusBar();

    ui.StartMeasBtn->setEnabled(false);  // prevent second pressing of the button

    extern long m_DeviceHandle;
    int l_Res = AVS_UseHighResAdc(m_DeviceHandle,1);
    if (ERR_SUCCESS != l_Res)
        QMessageBox::critical(this, tr("QT4 Demo"),
            tr("AVS_UseHighResAdc failed, Error %1").arg(l_Res),
            QMessageBox::Ok, QMessageBox::Ok);
    
	l_PrepareMeasData.m_StartPixel = QString(ui.StartPixelEdt->text()).toInt(&ok);
    l_PrepareMeasData.m_StopPixel = QString(ui.StopPixelEdt->text()).toInt(&ok);
    l_PrepareMeasData.m_IntegrationTime = QString(ui.IntTimeEdt->text()).toDouble(&ok);
    double l_NanoSec = QString(ui.IntDelayEdt->text()).toInt(&ok);
    l_PrepareMeasData.m_IntegrationDelay = (unsigned int)(6.0*(l_NanoSec+20.84)/125.0);
    l_PrepareMeasData.m_NrAverages = QString(ui.AvgEdt->text()).toInt(&ok);
    l_PrepareMeasData.m_CorDynDark.m_Enable = ui.DarkCorrChk->isChecked();
    l_PrepareMeasData.m_CorDynDark.m_ForgetPercentage = QString(ui.DarkCorrPercEdt->text()).toInt(&ok);
    l_PrepareMeasData.m_Smoothing.m_SmoothPix = QString(ui.SmoothNrPixelsEdt->text()).toInt(&ok);
    l_PrepareMeasData.m_Smoothing.m_SmoothModel = QString(ui.SmoothModelEdt->text()).toInt(&ok);
    l_PrepareMeasData.m_SaturationDetection = QString(ui.SatDetEdt->text()).toInt(&ok);
    l_PrepareMeasData.m_Trigger.m_Mode = ui.HardwareTriggerRBtn->isChecked();
    l_PrepareMeasData.m_Trigger.m_Source = ui.SynchTriggerRBtn->isChecked();
    l_PrepareMeasData.m_Trigger.m_SourceType = ui.LevelTriggerRBtn->isChecked();
    l_PrepareMeasData.m_Control.m_StrobeControl = QString(ui.FlashesPerScanEdt->text()).toInt(&ok);
    l_NanoSec = QString(ui.LaserDelayEdt->text()).toDouble(&ok);
    l_PrepareMeasData.m_Control.m_LaserDelay = (unsigned int)(6.0*l_NanoSec/125.0);
    l_NanoSec = QString(ui.LaserWidthEdt->text()).toDouble(&ok);
    l_PrepareMeasData.m_Control.m_LaserWidth = (unsigned int)(6.0*l_NanoSec/125.0);
    l_PrepareMeasData.m_Control.m_LaserWaveLength = QString(ui.LaserWavEdt->text()).toDouble(&ok);
    l_PrepareMeasData.m_Control.m_StoreToRam = QString(ui.StoreToRamEdt->text()).toInt(&ok);

    l_Res = AVS_PrepareMeasure(m_DeviceHandle,&l_PrepareMeasData);
    if (ERR_SUCCESS != l_Res) 
        QMessageBox::critical(this, tr("QT4 Demo"),
            tr("AVS_PrepareMeasure failed, Error %1").arg(l_Res),
            QMessageBox::Ok, QMessageBox::Ok);
    else
    {
        extern DeviceConfigType DeviceConfig;
        if (DeviceConfig.m_Detector.m_SensorType == SENS_TCD1304)
        {
            int l_Res = AVS_SetPrescanMode(m_DeviceHandle, ui.PreScanChk->isChecked());
            if (ERR_SUCCESS != l_Res)
                    QMessageBox::critical(this, tr("QT4 Demo"),
                        tr("AVS_SetPrescanMode failed, Error %1").arg(l_Res),
                        QMessageBox::Ok, QMessageBox::Ok);
        }
        short l_NrOfScans = QString(ui.NrMeasEdt->text()).toInt(&ok);
        if ((l_PrepareMeasData.m_Control.m_StoreToRam>0) && (l_NrOfScans!=1))
        {
            l_NrOfScans=1;
            ui.NrMeasEdt->setText(QString("%1").arg(l_NrOfScans));
            QMessageBox::information(this,tr("QT4 Demo"),
                            tr("%1 Scans will be stored to RAM.\n"
                                "The number of measurements (a_Nmsr\n"
                                "in AVS_Measure) has been set to 1 ").arg(l_PrepareMeasData.m_Control.m_StoreToRam),
                                QMessageBox::Ok, QMessageBox::Ok);
        }
        // Start Measurement
        extern QTime m_Time;
        m_Time.start();
        extern unsigned int m_Measurements;
        extern unsigned int m_Failures;
        m_Measurements = 0;
        m_Failures = 0;
        ui.TimeSinceStartEdt->setText(QString("%1").arg(0));
        ui.NrScansEdt->setText(QString("%1").arg(0));
        ui.NrFailuresEdt->setText(QString("%1").arg(0));
        extern unsigned short m_StartPixels;
        extern unsigned short m_StopPixels;
        m_StartPixels = l_PrepareMeasData.m_StartPixel;
        m_StopPixels = l_PrepareMeasData.m_StopPixel;
        l_Res = AVS_MeasureCallback(m_DeviceHandle, &application::callback, l_NrOfScans);
        if (ERR_SUCCESS != l_Res)
        {
            switch (l_Res)
            {
                case ERR_INVALID_PARAMETER:
                    statusbar->showMessage(tr("Meas.Status: invalid parameter"));
                    break;
                default:
                    statusbar->showMessage(tr("Meas.Status: start failed, code: %1").arg(l_Res));
            }
        }
        else
        {
            statusbar->showMessage(tr("Meas.Status: pending"));
        }
    }

}

void Qtdemo_64::on_StopMeasBtn_clicked()
{
    extern long m_DeviceHandle;
    int l_Res = AVS_StopMeasure(m_DeviceHandle);
    if (ERR_SUCCESS != l_Res) 
        QMessageBox::critical(this, tr("QT4 Demo"),
            tr("AVS_StopMeasure failed"),
            QMessageBox::Ok, QMessageBox::Ok);
    ui.StartMeasBtn->setEnabled(true);
    ui.darkRef->setEnabled(true);
    ui.whiteRef->setEnabled(true);
    darkRef=0;
    whiteRef=0;
}

void Qtdemo_64::on_UpdateListBtn_clicked()
{
    unsigned int        l_Size = 0;
    unsigned int        l_RequiredSize = 0;
    int                 l_NrDevices;
    char*               l_pData = NULL;
    AvsIdentityType*    l_pId; 

    //for UDP datagram
    QString MsgtoClient;

	int saveRow;
	if (!ui.SpectrometerList->selectedItems().isEmpty())
		saveRow = ui.SpectrometerList->currentItem()->row();
	else
		saveRow = 0;
	ui.SpectrometerList->clearContents();
	l_NrDevices = AVS_GetNrOfDevices();
	l_RequiredSize = l_NrDevices * sizeof(AvsIdentityType);
    if (l_RequiredSize > 0)
    {
		delete [] l_pData;
        l_pData = new char[l_RequiredSize];
        l_pId = (AvsIdentityType*)l_pData;
        l_Size = l_RequiredSize;
        l_NrDevices = AVS_GetList(l_Size, &l_RequiredSize, l_pId);
		ui.SpectrometerList->setColumnCount(2);
		ui.SpectrometerList->setRowCount(l_NrDevices);

        QString MsgtoClient2 = l_pData;

        for (int i = 0; i < l_NrDevices; i++)
        {
			QTableWidgetItem *serialnumItem = new QTableWidgetItem(l_pId->SerialNumber);
			ui.SpectrometerList->setItem(i, 0, serialnumItem);
			QTableWidgetItem *statusItem = new QTableWidgetItem("");
			switch (l_pId->Status)
				{
					case UNKNOWN              : statusItem->setText("UNKNOWN");
												ui.SpectrometerList->setItem(i, 1, statusItem);
                                                MsgtoClient = "UNKNOWN";
                                                //SendtoClient(l_pData,MsgtoClient);
                                                break;
					case AVAILABLE            : statusItem->setText("AVAILABLE");
												ui.SpectrometerList->setItem(i, 1, statusItem);
                                                MsgtoClient = "AVAILABLE";
                                                //SendtoClient(l_pData,MsgtoClient);
                                                break;
					case IN_USE_BY_APPLICATION: statusItem->setText("IN_USE_BY_APPLICATION");
												ui.SpectrometerList->setItem(i, 1, statusItem);
                                                MsgtoClient = "IN_USE_BY_APPLICATION";
                                                break;
					case IN_USE_BY_OTHER      : statusItem->setText("IN_USE_BY_OTHER");
												ui.SpectrometerList->setItem(i, 1, statusItem);
                                                MsgtoClient = "IN_USE_BY_OTHER";
                                                break;
					default                   : statusItem->setText("??????");
												ui.SpectrometerList->setItem(i, 1, statusItem);
                                                MsgtoClient = "??????";
                                                break;
                }
                l_pId++;
        }
        //write datagram here

        //QString MsgtoClient2 = l_pData;
        auto datagram = (MsgtoClient2 + ','+MsgtoClient).toLatin1();
        mSocket->writeDatagram(datagram,g_clientIP,g_clientPort);

        delete [] l_pData;
	}
    ui.SpectrometerList->setCurrentCell(saveRow,1);
	UpdateButtons();
}

void Qtdemo_64::on_ActivateBtn_clicked()
{
    AvsIdentityType l_Active ;
    AvsHandle l_hDevice ;
    int i, l_len;
    QString s = ui.SpectrometerList->selectedItems().first()->text();
    QByteArray temp = s.toLatin1();
    l_len = s.length();
    for (i = 0; i < AVS_SERIAL_LEN-1; i++)
    {
        l_Active.SerialNumber[i] = temp[i];
    }
    l_Active.SerialNumber[AVS_SERIAL_LEN-1] = 0;
    l_hDevice = AVS_Activate(&l_Active);
    if (INVALID_AVS_HANDLE_VALUE == l_hDevice)
    {
        QMessageBox::critical(this, tr("QT4 Demo"),
            tr("Error opening device %1").arg(l_Active.SerialNumber),
            QMessageBox::Ok, QMessageBox::Ok);
    }
    else
    {
        extern long m_DeviceHandle;    
		m_DeviceHandle = l_hDevice;

        on_UpdateListBtn_clicked(); //serialnr,status
        ConnectGui(); // detector, nr_pixels, fpga, firmware, dll
        on_ReadEepromBtn_clicked();
    }
}

void Qtdemo_64::ConnectGui()
{
    DeviceConfigType*  l_pDeviceData = NULL;
    unsigned int       l_Size;
    char a_Fpga[16];
    char a_As5216[16];
    char a_Dll[16];
    extern long m_DeviceHandle;
    extern unsigned short m_NrPixels;
    extern unsigned short m_StartPixels;
    extern unsigned short m_StopPixels;
    extern double m_pLambda[4096];

    int l_Res = AVS_GetVersionInfo(m_DeviceHandle, a_Fpga, a_As5216, a_Dll);
    if (ERR_SUCCESS == l_Res)
    {
        ui.FPGAVerEdt->setText(QString(a_Fpga));
        ui.FirmwareVerEdt->setText(QString(a_As5216));
        ui.DLLVerEdt->setText(QString(a_Dll));
    }

    if (ERR_SUCCESS == AVS_GetNumPixels(m_DeviceHandle, &m_NrPixels))
    {
        ui.NrPixelsEdt->setText(QString("%1").arg(m_NrPixels));
    }
    l_Res = AVS_GetParameter(m_DeviceHandle, 0, &l_Size, l_pDeviceData);

    if ( l_Res == ERR_INVALID_SIZE)
    {
        l_pDeviceData = (DeviceConfigType*)new char[l_Size];
    }
    l_Res = AVS_GetParameter(m_DeviceHandle, l_Size, &l_Size, l_pDeviceData);
    if (l_Res != ERR_SUCCESS)
    {
        DisconnectGui();
        return;
    }
    else
    {
        extern DeviceConfigType DeviceConfig;
        memcpy( &DeviceConfig, l_pDeviceData, sizeof(DeviceConfigType) );
    }
    QString dev_sensor;
    switch (l_pDeviceData->m_Detector.m_SensorType)
    {
        case SENS_HAMS8378_256 : ui.DetectorEdt->setText("HAMS8378_256");
                             dev_sensor ="HAMS8378_256";
                             break;
        case SENS_HAMS8378_1024 : ui.DetectorEdt->setText("HAMS8378_1024");
                             dev_sensor ="HAMS8378_1024";
                             break;
        case SENS_ILX554   : ui.DetectorEdt->setText("ILX554");
                             dev_sensor = "ILX554";
                             break;
        case SENS_HAMS9201 : ui.DetectorEdt->setText("HAMS9201");
                             dev_sensor = "HAMS9201" ;
                             break;
        case SENS_TCD1304  : ui.DetectorEdt->setText("TCD1304");
                             dev_sensor = "TCD1304";
                             ui.PreScanChk->show();
                             ui.PreScanChk->setCheckState(Qt::Checked);
                             l_Res = AVS_SetPrescanMode(m_DeviceHandle, ui.PreScanChk->isChecked());
                             break;
        case SENS_TSL1301  : ui.DetectorEdt->setText("TSL1301");
                             dev_sensor = "TSL1301";
                             break;
        case SENS_TSL1401  : ui.DetectorEdt->setText("TSL1401");
                             dev_sensor = "TSL1401";
                             break;
        case SENS_HAMS8378_512 : ui.DetectorEdt->setText("HAMS8378_512");
                             dev_sensor = "HAMS8378_512";
                             break;
        case SENS_HAMS9840  : ui.DetectorEdt->setText("HAMS9840");
                             dev_sensor = "HAMS9840";
                             break;
        case SENS_ILX511    : ui.DetectorEdt->setText("ILX511");
                             dev_sensor = "ILX511";
                             break;
        case SENS_HAMS10420_2048X64 : ui.DetectorEdt->setText("HAMS10420_2048X64");
                             dev_sensor = "SENS_HAMS10420_2048X64";
                             break;
        case SENS_HAMS11071_2048X64 : ui.DetectorEdt->setText("HAMS11071_2048X64");
                             dev_sensor = "SENS_HAMS11071_2048X64";
                             break;
        case SENS_HAMS7031_1024X122 : ui.DetectorEdt->setText("HAMS7031_1024X122");
                             dev_sensor = "SENS_HAMS7031_1024X122";
                             break;
        case SENS_HAMS7031_1024X58  : ui.DetectorEdt->setText("HAMS7031_1024X58");
                             dev_sensor = "SENS_HAMS7031_1024X58";
                             break;
        case SENS_HAMS11071_2048X16 : ui.DetectorEdt->setText("HAMS11071_2048X16");
                             dev_sensor = "SENS_HAMS11071_2048X16";
                             break;
        default            : ui.DetectorEdt->setText("???????");
                             dev_sensor = "???????";
                             break;

    }
    m_StartPixels = l_pDeviceData->m_StandAlone.m_Meas.m_StartPixel;
    m_StopPixels = l_pDeviceData->m_StandAlone.m_Meas.m_StopPixel;
//    if (NULL != m_pLambda)
//    {
//        // delete old structure because number of pixels could have been changed.
//        delete [] m_pLambda;
//        m_pLambda = NULL;
//    }
//    m_pLambda = new double[m_NrPixels];

    if (ERR_SUCCESS != AVS_GetLambda(m_DeviceHandle,m_pLambda)) 
        QMessageBox::critical(this, tr("QT4 Demo"),
            tr("AVS_GetLambda failed"),
            QMessageBox::Ok, QMessageBox::Ok);
	delete [] l_pDeviceData;
	ui.plot->setAxisScale(ui.plot->xBottom, m_pLambda[0], m_pLambda[m_NrPixels-1]);

    /*
    QString fpga = QString(a_Fpga);
    QString as5216 = QString(a_As5216);
    QString dll = QString (a_Dll);
    QString pixel = QString("%1").arg(m_NrPixels);
    auto datagram = (dev_sensor+","+pixel+","+fpga+","+as5216+","+dll).toLatin1();
    mSocket->writeDatagram(datagram,g_clientIP,g_clientPort);
    */
}

void Qtdemo_64::DisconnectGui()
{
//	if (NULL != m_pLambda)
//    {
//        delete [] m_pLambda;
//        m_pLambda = NULL;
//    }
    
    ui.DetectorEdt->clear();
    ui.NrPixelsEdt->clear();
    ui.FPGAVerEdt->clear();
    ui.FirmwareVerEdt->clear();
    ui.DLLVerEdt->clear();
}

void Qtdemo_64::UpdateButtons()
{
	QString s = ui.SpectrometerList->selectedItems().first()->text();


    ui.ActivateBtn->setEnabled(s == "AVAILABLE");
    if(s=="AVAILABLE")
        {
        ui.SpectrometerList->setCurrentCell(0,0);
        }

    ui.DeactivateBtn->setEnabled(s == "IN_USE_BY_APPLICATION");
	ui.DigitalIoBtn->setEnabled(s == "IN_USE_BY_APPLICATION");
	ui.AnalogIoBtn->setEnabled(s == "IN_USE_BY_APPLICATION");
	ui.ShowEepromBtn->setEnabled(s == "IN_USE_BY_APPLICATION");
	ui.ReadEepromBtn->setEnabled(s == "IN_USE_BY_APPLICATION");
	ui.WriteEepromBtn->setEnabled(s == "IN_USE_BY_APPLICATION");
	ui.StartMeasBtn->setEnabled(s == "IN_USE_BY_APPLICATION");
	ui.StopMeasBtn->setEnabled(s == "IN_USE_BY_APPLICATION");
    ui.darkRef->setEnabled(s == "IN_USE_BY_APPLICATION");
    ui.whiteRef->setEnabled(s == "IN_USE_BY_APPLICATION");

}

void Qtdemo_64::on_ReadEepromBtn_clicked()
{
	DeviceConfigType*  l_pDeviceData = NULL;
    unsigned int       l_Size;
	extern long m_DeviceHandle;

    int l_Res = AVS_GetParameter(m_DeviceHandle, 0, &l_Size, l_pDeviceData);

    if ( l_Res == ERR_INVALID_SIZE)
    {
        l_pDeviceData = (DeviceConfigType*)new char[l_Size];
    }
    l_Res = AVS_GetParameter(m_DeviceHandle, l_Size, &l_Size, l_pDeviceData);
    if (ERR_SUCCESS != l_Res)
    {
        QMessageBox::critical(this, tr("QT4 Demo"),
            tr("AVS_GetParameter failed, code %1").arg(l_Res),
            QMessageBox::Ok, QMessageBox::Ok);
        delete [] l_pDeviceData;
        return;
    }

    //show measurement settings
	ui.StartPixelEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_StartPixel));
    ui.StopPixelEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_StopPixel));
	ui.IntTimeEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_IntegrationTime,7,'f',2));
    unsigned int l_FPGAClkCycles = l_pDeviceData->m_StandAlone.m_Meas.m_IntegrationDelay;
    double l_NanoSec = 125.0*(l_FPGAClkCycles-1.0)/6.0;
	ui.IntDelayEdt->setText(QString("%1").arg(l_NanoSec,7,'f',0));
	ui.AvgEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_NrAverages));
	ui.SatDetEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_SaturationDetection));
	ui.HardwareTriggerRBtn->setChecked(l_pDeviceData->m_StandAlone.m_Meas.m_Trigger.m_Mode == 1);
	ui.SoftwareTriggerRBtn->setChecked(l_pDeviceData->m_StandAlone.m_Meas.m_Trigger.m_Mode == 0);
	ui.ExternalTriggerRbtn->setChecked(l_pDeviceData->m_StandAlone.m_Meas.m_Trigger.m_Source == 0);
	ui.SynchTriggerRBtn->setChecked(l_pDeviceData->m_StandAlone.m_Meas.m_Trigger.m_Source == 1);
	ui.EdgeTriggerRBtn->setChecked(l_pDeviceData->m_StandAlone.m_Meas.m_Trigger.m_SourceType == 0);
	ui.LevelTriggerRBtn->setChecked(l_pDeviceData->m_StandAlone.m_Meas.m_Trigger.m_SourceType == 1);
	ui.DarkCorrChk->setChecked(l_pDeviceData->m_StandAlone.m_Meas.m_CorDynDark.m_Enable == 1);
	ui.DarkCorrPercEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_CorDynDark.m_ForgetPercentage));
	ui.SmoothModelEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_Smoothing.m_SmoothModel));
	ui.SmoothNrPixelsEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_Smoothing.m_SmoothPix));
	ui.FlashesPerScanEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_Control.m_StrobeControl));
    l_FPGAClkCycles = l_pDeviceData->m_StandAlone.m_Meas.m_Control.m_LaserDelay;
    l_NanoSec = 125.0*(l_FPGAClkCycles)/6.0;
	ui.LaserDelayEdt->setText(QString("%1").arg(l_NanoSec,7,'f',0));
    l_FPGAClkCycles = l_pDeviceData->m_StandAlone.m_Meas.m_Control.m_LaserWidth;
    l_NanoSec = 125.0*(l_FPGAClkCycles)/6.0;
	ui.LaserWidthEdt->setText(QString("%1").arg(l_NanoSec,7,'f',0));
	ui.LaserWavEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_Control.m_LaserWaveLength,7,'f',3));
	ui.StoreToRamEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_Control.m_StoreToRam));
	ui.NrMeasEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Nmsr));

    delete [] l_pDeviceData;
}

void Qtdemo_64::on_DeactivateBtn_clicked()
{
	extern long m_DeviceHandle; 
	AVS_Deactivate(m_DeviceHandle);
	m_DeviceHandle  = INVALID_AVS_HANDLE_VALUE;
	on_UpdateListBtn_clicked();
	DisconnectGui();
}

void Qtdemo_64::on_DisableGraphChk_stateChanged(int)
{
	extern bool m_GraphicsDisabled;
	m_GraphicsDisabled = ui.DisableGraphChk->isChecked();
}

void Qtdemo_64::on_WriteEepromBtn_clicked()
{
    DeviceConfigType* l_pDeviceData = NULL;
    unsigned int l_Size;
    extern long m_DeviceHandle;
    bool ok;

    int l_Res = AVS_GetParameter(m_DeviceHandle, 0, &l_Size, l_pDeviceData);

    if ( l_Res == ERR_INVALID_SIZE)
    {
        l_pDeviceData = (DeviceConfigType*)new char[l_Size];
    }
    l_Res = AVS_GetParameter(m_DeviceHandle, l_Size, &l_Size, l_pDeviceData);
    if (ERR_SUCCESS != l_Res)
    {
        QMessageBox::critical(this, tr("QT4 Demo"),
            tr("AVS_GetParameter failed, code %1").arg(l_Res),
            QMessageBox::Ok, QMessageBox::Ok);
        delete [] l_pDeviceData;
        return;
    }
    l_pDeviceData->m_StandAlone.m_Meas.m_StartPixel = QString(ui.StartPixelEdt->text()).toInt(&ok);
    l_pDeviceData->m_StandAlone.m_Meas.m_StopPixel =  QString(ui.StopPixelEdt->text()).toInt(&ok);
    l_pDeviceData->m_StandAlone.m_Meas.m_IntegrationTime = QString(ui.IntTimeEdt->text()).toDouble(&ok);
    double l_NanoSec = QString(ui.IntDelayEdt->text()).toInt(&ok);
    l_pDeviceData->m_StandAlone.m_Meas.m_IntegrationDelay = (unsigned int)(6.0*(l_NanoSec+20.84)/125.0);
    l_pDeviceData->m_StandAlone.m_Meas.m_NrAverages = QString(ui.AvgEdt->text()).toInt(&ok);
    l_pDeviceData->m_StandAlone.m_Meas.m_Trigger.m_Mode = ui.HardwareTriggerRBtn->isChecked();
    l_pDeviceData->m_StandAlone.m_Meas.m_Trigger.m_Source = ui.SynchTriggerRBtn->isChecked();
    l_pDeviceData->m_StandAlone.m_Meas.m_Trigger.m_SourceType = ui.LevelTriggerRBtn->isChecked();
    l_pDeviceData->m_StandAlone.m_Meas.m_SaturationDetection = QString(ui.SatDetEdt->text()).toInt(&ok);
    l_pDeviceData->m_StandAlone.m_Meas.m_CorDynDark.m_Enable = ui.DarkCorrChk->isChecked(); 
    l_pDeviceData->m_StandAlone.m_Meas.m_CorDynDark.m_ForgetPercentage = QString(ui.DarkCorrPercEdt->text()).toInt(&ok);
    l_pDeviceData->m_StandAlone.m_Meas.m_Smoothing.m_SmoothPix = QString(ui.SmoothNrPixelsEdt->text()).toInt(&ok);
    l_pDeviceData->m_StandAlone.m_Meas.m_Smoothing.m_SmoothModel = QString(ui.SmoothModelEdt->text()).toInt(&ok);
    l_pDeviceData->m_StandAlone.m_Meas.m_Control.m_StrobeControl = QString(ui.FlashesPerScanEdt->text()).toInt(&ok);
    l_NanoSec = QString(ui.LaserDelayEdt->text()).toDouble(&ok);
    l_pDeviceData->m_StandAlone.m_Meas.m_Control.m_LaserDelay = (unsigned int)(6.0*l_NanoSec/125.0);
    l_NanoSec = QString(ui.LaserWidthEdt->text()).toDouble(&ok);
    l_pDeviceData->m_StandAlone.m_Meas.m_Control.m_LaserWidth = (unsigned int)(6.0*l_NanoSec/125.0);
    l_pDeviceData->m_StandAlone.m_Meas.m_Control.m_LaserWaveLength = QString(ui.LaserWavEdt->text()).toDouble(&ok);
    l_pDeviceData->m_StandAlone.m_Meas.m_Control.m_StoreToRam = QString(ui.StoreToRamEdt->text()).toInt(&ok);
    l_pDeviceData->m_StandAlone.m_Nmsr = QString(ui.NrMeasEdt->text()).toInt(&ok);

    //Write measurement parameters
    l_Res = AVS_SetParameter(m_DeviceHandle, l_pDeviceData);
    if (ERR_SUCCESS != l_Res)
    {
        QMessageBox::critical(this, tr("QT4 Demo"),
            tr("AVS_SetParameter failed, code %1").arg(l_Res),
            QMessageBox::Ok, QMessageBox::Ok);
    }
    delete [] l_pDeviceData;
}

void Qtdemo_64::on_AnalogIoBtn_clicked()
{
	analog_io w3;
	w3.exec();
	w3.activateWindow();
	w3.raise();
}

void Qtdemo_64::on_DigitalIoBtn_clicked()
{
	digital_io w4;
	w4.exec();
	w4.activateWindow();
	w4.raise();
}



void Qtdemo_64::keyPressEvent(QKeyEvent *ev)
{
    ui.myLabel->setText("You Pressed Key " + ev->text());
}

void Qtdemo_64::keyReleaseEvent(QKeyEvent *ev)
{
    ui.myLabel->setText("You Release Key " + ev->text());
}

void Qtdemo_64::readyReade()
{
    QHostAddress clientIPAddr; //declare variable to store received datagram's IP address
    quint16 clientPort;        //declare variable to store received datagram's port number
    QStringList stringList1;   //declare variable for list of items in datagram

    QString myDatagram;
    myDatagram = "done!";

    if (mSocket->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(mSocket->pendingDatagramSize());
        mSocket->readDatagram(datagram.data(),datagram.size(),&clientIPAddr,&clientPort);
        g_clientIP = clientIPAddr; // assign obtained IP address to corresponding global variable
        g_clientPort = clientPort; // assign obtained port number to corresponding global variable

        ui.listWidget->addItem(QString(datagram)); //listing down received datagram
        stringList1 = QString(datagram).split(',');
        if (stringList1[0] == "com"){
            switch(stringList1[1].toInt())
        {
        case 1:
            on_OpenCommBtn_clicked();
            break;
        case 2:
            on_UpdateListBtn_clicked();
            break;
        case 3:
            on_ActivateBtn_clicked();
            break;
        case 4:
            on_DeactivateBtn_clicked();
            break;
        case 5:
            on_StartMeasBtn_clicked();
            break;
        case 6:
            on_StopMeasBtn_clicked();
            break;
        case 7:
             on_darkRef_clicked();
             break;
         case 8:
             on_whiteRef_clicked();
             break;
        default:
            break;
        }
    }
    else if (stringList1[0] =="val")
    {

            ui.StartPixelEdt->setText(stringList1[1]);

            ui.StopPixelEdt->setText(stringList1[2]);

            ui.IntTimeEdt->setText(stringList1[3]);

            ui.IntDelayEdt->setText(stringList1[4]);

            ui.AvgEdt->setText(stringList1[5]);

            ui.DarkCorrChk->setChecked(stringList1[6].toInt());

            ui.DarkCorrPercEdt->setText(stringList1[7]);

            ui.SmoothModelEdt->setText(stringList1[8]);

            ui.SmoothNrPixelsEdt->setText(stringList1[9]);

            ui.FlashesPerScanEdt->setText(stringList1[10]);

            ui.LaserDelayEdt->setText(stringList1[11]);

            ui.LaserWidthEdt->setText(stringList1[12]);

            ui.LaserWavEdt->setText(stringList1[13]);

            ui.StoreToRamEdt->setText(stringList1[14]);

            ui.NrMeasEdt->setText(stringList1[14]);

    }
        else if (stringList1[0] =="val1")
        {
            //Integration time
            ui.IntTimeEdt->setText(stringList1[1]);
            //Integration delay [ns]
            ui.IntDelayEdt->setText(stringList1[2]);
            //number of Averages
            ui.AvgEdt->setText(stringList1[3]);
            //Nr of scans
            //ui.NrMeasEdt->setText(stringList1[4]);
        }
        else if (stringList1[0] =="val2")
        {
            //Integration time
            ui.IntTimeEdt->setText(stringList1[1]);
            //Integration delay [ns]
            ui.IntDelayEdt->setText(stringList1[2]);
            //number of Averages
            ui.AvgEdt->setText(stringList1[3]);
            //Nr of scans
            //ui.NrMeasEdt->setText(stringList1[4]);
        }

  }

}




void Qtdemo_64::on_darkRef_clicked()
{
    for(int i=0; i<=MAX_NR_PIXELS-1; i++)
    {
       g_buffer_dark[i]= 0.0;
    }
    darkRef = 1;

    ui.darkRef->setEnabled(false);
    ui.whiteRef->setEnabled(false);
    on_StartMeasBtn_clicked();

}


void Qtdemo_64::on_whiteRef_clicked()
{
    for(int i=0; i<=MAX_NR_PIXELS-1; i++)
    {
       g_buffer_white[i]= 0.0;
    }
    whiteRef = 1;
    ui.whiteRef->setEnabled(false);
    ui.darkRef->setEnabled(false);
    on_StartMeasBtn_clicked();
}
