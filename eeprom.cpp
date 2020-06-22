#include <QtGui>
#include <QApplication>
#include <QPushButton>
#include "eeprom.h"
#include "libavs/as5216.h"
//#include "as5216.h"
#include "application.h"
#include <QMessageBox>

uint8 const SENSOR_OFFSET = 1;

eeprom::eeprom(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updatetime()));
	timer->setInterval(1000);  // interval is 1000 msec
}

eeprom::~eeprom()
{

}

void eeprom::showEvent(QShowEvent * /* event */)
{
	DeviceConfigType* l_pDeviceData = NULL;
	unsigned int l_Size;
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
	// show parameters
	ui.StrucLengthEdt->setText(QString("%1").arg(l_pDeviceData->m_Len));
	ui.StrucVersionEdt->setText(QString("%1").arg(l_pDeviceData->m_ConfigVersion));
	ui.FriendlyEdt->setText(QString("%1").arg(l_pDeviceData->m_aUserFriendlyId));
	// show detectortype parameters
	ui.SensorComboBox->clear();
	ui.SensorComboBox->addItem("HAMS8378-256", QRegExp::FixedString);
	ui.SensorComboBox->addItem("HAMS8378-1024", QRegExp::FixedString);
	ui.SensorComboBox->addItem("ILX554", QRegExp::FixedString);
	ui.SensorComboBox->addItem("HAMS9201", QRegExp::FixedString);
	ui.SensorComboBox->addItem("TCD1304", QRegExp::FixedString);
	ui.SensorComboBox->addItem("TSL1301", QRegExp::FixedString);
	ui.SensorComboBox->addItem("TSL1401", QRegExp::FixedString);
	ui.SensorComboBox->addItem("HAMS8378-512", QRegExp::FixedString);
	ui.SensorComboBox->addItem("HAMS9840", QRegExp::FixedString);
	ui.SensorComboBox->addItem("ILX511", QRegExp::FixedString);
	ui.SensorComboBox->addItem("HAMS10420_2048X64", QRegExp::FixedString);
	ui.SensorComboBox->addItem("HAMS11071_2048X64", QRegExp::FixedString);
	ui.SensorComboBox->addItem("HAMS7031_1024X122", QRegExp::FixedString);
	ui.SensorComboBox->addItem("HAMS7031_1024X58", QRegExp::FixedString);
	ui.SensorComboBox->addItem("HAMS11071_2048X16", QRegExp::FixedString);
	ui.SensorComboBox->setCurrentIndex(l_pDeviceData->m_Detector.m_SensorType - SENSOR_OFFSET);
	ui.NrPixelsEdt->setText(QString("%1").arg(l_pDeviceData->m_Detector.m_NrPixels));
	ui.WavCalInterceptEdt->setText(QString("%1").arg(l_pDeviceData->m_Detector.m_aFit[0],8,'E',6));
	ui.WavCalX1Edt->setText(QString("%1").arg(l_pDeviceData->m_Detector.m_aFit[1],8,'E',6));
	ui.WavCalX2Edt->setText(QString("%1").arg(l_pDeviceData->m_Detector.m_aFit[2],8,'E',6));
	ui.WavCalX3Edt->setText(QString("%1").arg(l_pDeviceData->m_Detector.m_aFit[3],8,'E',6));
	ui.WavCalX4Edt->setText(QString("%1").arg(l_pDeviceData->m_Detector.m_aFit[4],8,'E',6));
	ui.Gain1Edt->setText(QString("%1").arg(l_pDeviceData->m_Detector.m_Gain[0],7,'f',2));
	ui.Gain2Edt->setText(QString("%1").arg(l_pDeviceData->m_Detector.m_Gain[1],7,'f',2));
	ui.Offset1Edt->setText(QString("%1").arg(l_pDeviceData->m_Detector.m_Offset[0],7,'f',2));
	ui.Offset2Edt->setText(QString("%1").arg(l_pDeviceData->m_Detector.m_Offset[1],7,'f',2));
	ui.ExtOffsetEdt->setText(QString("%1").arg(l_pDeviceData->m_Detector.m_ExtOffset,7,'f',2));
	ui.NonLinInterceptEdt->setText(QString("%1").arg(l_pDeviceData->m_Detector.m_aNLCorrect[0],8,'E',6));
	ui.NonLinX1Edt->setText(QString("%1").arg(l_pDeviceData->m_Detector.m_aNLCorrect[1],8,'E',6));
	ui.NonLinX2Edt->setText(QString("%1").arg(l_pDeviceData->m_Detector.m_aNLCorrect[2],8,'E',6));
	ui.NonLinX3Edt->setText(QString("%1").arg(l_pDeviceData->m_Detector.m_aNLCorrect[3],8,'E',6));
	ui.NonLinX4Edt->setText(QString("%1").arg(l_pDeviceData->m_Detector.m_aNLCorrect[4],8,'E',6));
	ui.NonLinX5Edt->setText(QString("%1").arg(l_pDeviceData->m_Detector.m_aNLCorrect[5],8,'E',6));
	ui.NonLinX6Edt->setText(QString("%1").arg(l_pDeviceData->m_Detector.m_aNLCorrect[6],8,'E',6));
	ui.NonLinX7Edt->setText(QString("%1").arg(l_pDeviceData->m_Detector.m_aNLCorrect[7],8,'E',6));
	ui.LoCountsEdt->setText(QString("%1").arg(l_pDeviceData->m_Detector.m_aLowNLCounts,8,'E',6));
	ui.HiCountsEdt->setText(QString("%1").arg(l_pDeviceData->m_Detector.m_aHighNLCounts,8,'E',6));
	ui.NonLinEnableChk->setChecked(l_pDeviceData->m_Detector.m_NLEnable);
	ui.DefectEdt->clear();
	for (unsigned short i = 0; i < NR_DEFECTIVE_PIXELS; i++)
	{
		ui.DefectEdt->append(QString("%1").arg(l_pDeviceData->m_Detector.m_DefectivePixels[i]));
	}
	// show standalone parameters
	ui.EnableStandAloneChk->setChecked(l_pDeviceData->m_StandAlone.m_Enable);
	ui.StartPixelEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_StartPixel));
	ui.StopPixelEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_StopPixel));
	ui.IntTimeEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_IntegrationTime,7,'f',2));
    unsigned int l_FPGAClkCycles = l_pDeviceData->m_StandAlone.m_Meas.m_IntegrationDelay;
    double l_NanoSec = 125.0*(l_FPGAClkCycles-1.0)/6.0;
	ui.IntDelayEdt->setText(QString("%1").arg(l_NanoSec,7,'f',0));
	ui.NrAveragesEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_NrAverages));
	ui.SatDetectEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_SaturationDetection));
	ui.HardwareTriggerRBtn->setChecked(l_pDeviceData->m_StandAlone.m_Meas.m_Trigger.m_Mode == 1);
	ui.SoftwareTriggerRBtn->setChecked(l_pDeviceData->m_StandAlone.m_Meas.m_Trigger.m_Mode == 0);
	ui.ExternalTriggerRbtn->setChecked(l_pDeviceData->m_StandAlone.m_Meas.m_Trigger.m_Source == 0);
	ui.SynchTriggerRBtn->setChecked(l_pDeviceData->m_StandAlone.m_Meas.m_Trigger.m_Source == 1);
	ui.EdgeTriggerRBtn->setChecked(l_pDeviceData->m_StandAlone.m_Meas.m_Trigger.m_SourceType == 0);
	ui.LevelTriggerRBtn->setChecked(l_pDeviceData->m_StandAlone.m_Meas.m_Trigger.m_SourceType == 1);
	ui.DarkCorrEnableChk->setChecked(l_pDeviceData->m_StandAlone.m_Meas.m_CorDynDark.m_Enable == 1);
	ui.DarkPercentageEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_CorDynDark.m_ForgetPercentage));
	ui.SmoothModelEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_Smoothing.m_SmoothModel));
	ui.SmoothPixelsEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_Smoothing.m_SmoothPix));
	ui.FlashesPerScanEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_Control.m_StrobeControl));
    l_FPGAClkCycles = l_pDeviceData->m_StandAlone.m_Meas.m_Control.m_LaserDelay;
    l_NanoSec = 125.0*(l_FPGAClkCycles)/6.0;
	ui.LaserDelayEdt->setText(QString("%1").arg(l_NanoSec,7,'f',0));
    l_FPGAClkCycles = l_pDeviceData->m_StandAlone.m_Meas.m_Control.m_LaserWidth;
    l_NanoSec = 125.0*(l_FPGAClkCycles)/6.0;
	ui.LaserWidtEdt->setText(QString("%1").arg(l_NanoSec,7,'f',0));
	ui.LaserWavEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_Control.m_LaserWaveLength,7,'f',3));
	ui.StoreToRamEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Meas.m_Control.m_StoreToRam));
	ui.NrMeasEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_Nmsr));
	ui.SDCardEnableChk->setChecked(l_pDeviceData->m_StandAlone.m_SDCard.m_Enable);
	ui.SpectrumTypeEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_SDCard.m_SpectrumType));
	ui.FileRootNameEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_SDCard.m_aFileRootName));
	ui.DateNrEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_SDCard.m_TimeStamp.m_Date));
    unsigned short l_Year = (l_pDeviceData->m_StandAlone.m_SDCard.m_TimeStamp.m_Date >> 9);
    unsigned short l_Month = (l_pDeviceData->m_StandAlone.m_SDCard.m_TimeStamp.m_Date)& (0x1FF);
    l_Month  >>= 5 ;
    unsigned short l_Day = (l_pDeviceData->m_StandAlone.m_SDCard.m_TimeStamp.m_Date)& (0x1F);
	ui.DayEdt->setText(QString("%1").arg(l_Day));
	ui.MonthEdt->setText(QString("%1").arg(l_Month));
	ui.YearEdt->setText(QString("%1").arg(l_Year));
	ui.TimeNrEdt->setText(QString("%1").arg(l_pDeviceData->m_StandAlone.m_SDCard.m_TimeStamp.m_Time));
    unsigned short l_Hour = (l_pDeviceData->m_StandAlone.m_SDCard.m_TimeStamp.m_Time >> 11);
    unsigned short l_Minute = (l_pDeviceData->m_StandAlone.m_SDCard.m_TimeStamp.m_Time)& (0x7FF);
    l_Minute  >>= 5 ;
    unsigned short l_Sec = (l_pDeviceData->m_StandAlone.m_SDCard.m_TimeStamp.m_Time)& (0x1F);
    ui.HourEdt->setText(QString("%1").arg(l_Hour));
	ui.MinEdt->setText(QString("%1").arg(l_Minute));
	ui.SecEdt->setText(QString("%1").arg(l_Sec));
	// show irradiance parameters
	ui.IrradianceSmoothModelEdt->setText(QString("%1").arg(l_pDeviceData->m_Irradiance.m_IntensityCalib.m_Smoothing.m_SmoothModel));
	ui.IrradianceSmoothPixelsEdt->setText(QString("%1").arg(l_pDeviceData->m_Irradiance.m_IntensityCalib.m_Smoothing.m_SmoothPix));
	ui.IrradianceIntTimeEdt->setText(QString("%1").arg(l_pDeviceData->m_Irradiance.m_IntensityCalib.m_CalInttime,7,'f',2));
    ui.IrradianceConvEdt->clear();
    for (unsigned short i = 0; i < MAX_NR_PIXELS; i++)
    {
		ui.IrradianceConvEdt->append(QString("%1").arg(l_pDeviceData->m_Irradiance.m_IntensityCalib.m_aCalibConvers[i],7,'E',5));
    }
	ui.IrradCalibrationTypeEdt->setText(QString("%1").arg(l_pDeviceData->m_Irradiance.m_CalibrationType));
	ui.IrradFiberDiameterEdt->setText(QString("%1").arg(l_pDeviceData->m_Irradiance.m_FiberDiameter));
	// show reflectance parameters
	ui.ReflectanceSmoothModelEdt->setText(QString("%1").arg(l_pDeviceData->m_Reflectance.m_Smoothing.m_SmoothModel));
	ui.ReflectanceSmoothPixelsEdt->setText(QString("%1").arg(l_pDeviceData->m_Reflectance.m_Smoothing.m_SmoothPix));
	ui.ReflectanceIntTimeEdt->setText(QString("%1").arg(l_pDeviceData->m_Reflectance.m_CalInttime,7,'f',2));
    ui.ReflectanceCorrEdt->clear();
    for (unsigned short i = 0; i < MAX_NR_PIXELS; i++)
    {
		ui.ReflectanceCorrEdt->append(QString("%1").arg(l_pDeviceData->m_Reflectance.m_aCalibConvers[i],7,'E',5));
    }
    // show correction parameters
	ui.SpectrumCorrEdt->clear();
    for (unsigned short i = 0; i < MAX_NR_PIXELS; i++)
    {
		ui.SpectrumCorrEdt->append(QString("%1").arg(l_pDeviceData->m_SpectrumCorrect.m_aSpectrumCorrect[i],7,'E',5));
    }
	// show thermistor parameters
	ui.NTC1X0Edt->setText(QString("%1").arg(l_pDeviceData->m_aTemperature[0].m_aFit[0],8,'E',6));
	ui.NTC1X1Edt->setText(QString("%1").arg(l_pDeviceData->m_aTemperature[0].m_aFit[1],8,'E',6));
	ui.NTC1X2Edt->setText(QString("%1").arg(l_pDeviceData->m_aTemperature[0].m_aFit[2],8,'E',6));
	ui.NTC1X3Edt->setText(QString("%1").arg(l_pDeviceData->m_aTemperature[0].m_aFit[3],8,'E',6));
	ui.NTC1X4Edt->setText(QString("%1").arg(l_pDeviceData->m_aTemperature[0].m_aFit[4],8,'E',6));

	ui.NTC2X0Edt->setText(QString("%1").arg(l_pDeviceData->m_aTemperature[1].m_aFit[0],8,'E',6));
	ui.NTC2X1Edt->setText(QString("%1").arg(l_pDeviceData->m_aTemperature[1].m_aFit[1],8,'E',6));
	ui.NTC2X2Edt->setText(QString("%1").arg(l_pDeviceData->m_aTemperature[1].m_aFit[2],8,'E',6));
	ui.NTC2X3Edt->setText(QString("%1").arg(l_pDeviceData->m_aTemperature[1].m_aFit[3],8,'E',6));
	ui.NTC2X4Edt->setText(QString("%1").arg(l_pDeviceData->m_aTemperature[1].m_aFit[4],8,'E',6));

	ui.ThermistorX0Edt->setText(QString("%1").arg(l_pDeviceData->m_aTemperature[2].m_aFit[0],8,'E',6));
	ui.ThermistorX1Edt->setText(QString("%1").arg(l_pDeviceData->m_aTemperature[2].m_aFit[1],8,'E',6));
	ui.ThermistorX2Edt->setText(QString("%1").arg(l_pDeviceData->m_aTemperature[2].m_aFit[2],8,'E',6));
	ui.ThermistorX3Edt->setText(QString("%1").arg(l_pDeviceData->m_aTemperature[2].m_aFit[3],8,'E',6));
	ui.ThermistorX4Edt->setText(QString("%1").arg(l_pDeviceData->m_aTemperature[2].m_aFit[4],8,'E',6));
	// show TEC Control parameters
	ui.TECEnableChk->setChecked(l_pDeviceData->m_TecControl.m_Enable);
	ui.SetPointEdt->setText(QString("%1").arg(l_pDeviceData->m_TecControl.m_Setpoint,7,'f',1));
	ui.TECX0Edt->setText(QString("%1").arg(l_pDeviceData->m_TecControl.m_aFit[0],7,'f',3));
	ui.TECX1Edt->setText(QString("%1").arg(l_pDeviceData->m_TecControl.m_aFit[1],7,'f',3));

	delete [] l_pDeviceData;
}

void eeprom::on_SaveEepromBtn_clicked()
{
    DeviceConfigType* l_pDeviceData = NULL;
    extern long m_DeviceHandle;
    unsigned int l_Size;
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
    // Get parameters
    l_pDeviceData->m_ConfigVersion =QString(ui.StrucVersionEdt->text()).toInt(&ok);

    QByteArray temp = QString(ui.FriendlyEdt->text()).toLatin1();
    for (int i = 0; i < USER_ID_LEN-1; i++)
    {
        l_pDeviceData->m_aUserFriendlyId[i] = temp[i];
    }
    l_pDeviceData->m_aUserFriendlyId[USER_ID_LEN-1] = 0;
    // Get detector parameters
    l_pDeviceData->m_Detector.m_SensorType = ui.SensorComboBox->currentIndex() + SENSOR_OFFSET;
    l_pDeviceData->m_Detector.m_NrPixels = QString(ui.NrPixelsEdt->text()).toInt(&ok);
    l_pDeviceData->m_Detector.m_aFit[0] = QString(ui.WavCalInterceptEdt->text()).toDouble(&ok);
    l_pDeviceData->m_Detector.m_aFit[1] = QString(ui.WavCalX1Edt->text()).toDouble(&ok);
    l_pDeviceData->m_Detector.m_aFit[2] = QString(ui.WavCalX2Edt->text()).toDouble(&ok);
    l_pDeviceData->m_Detector.m_aFit[3] = QString(ui.WavCalX3Edt->text()).toDouble(&ok);
    l_pDeviceData->m_Detector.m_aFit[4] = QString(ui.WavCalX4Edt->text()).toDouble(&ok);
    l_pDeviceData->m_Detector.m_Gain[0] = QString(ui.Gain1Edt->text()).toDouble(&ok);
    l_pDeviceData->m_Detector.m_Gain[1] = QString(ui.Gain2Edt->text()).toDouble(&ok);
    l_pDeviceData->m_Detector.m_Offset[0] = QString(ui.Offset1Edt->text()).toDouble(&ok);
    l_pDeviceData->m_Detector.m_Offset[1] = QString(ui.Offset2Edt->text()).toDouble(&ok);
    l_pDeviceData->m_Detector.m_ExtOffset = QString(ui.ExtOffsetEdt->text()).toDouble(&ok);
    l_pDeviceData->m_Detector.m_aNLCorrect[0] = QString(ui.NonLinInterceptEdt->text()).toDouble(&ok);
    l_pDeviceData->m_Detector.m_aNLCorrect[1] = QString(ui.NonLinX1Edt->text()).toDouble(&ok);
    l_pDeviceData->m_Detector.m_aNLCorrect[2] = QString(ui.NonLinX2Edt->text()).toDouble(&ok);
    l_pDeviceData->m_Detector.m_aNLCorrect[3] = QString(ui.NonLinX3Edt->text()).toDouble(&ok);
    l_pDeviceData->m_Detector.m_aNLCorrect[4] = QString(ui.NonLinX4Edt->text()).toDouble(&ok);
    l_pDeviceData->m_Detector.m_aNLCorrect[5] = QString(ui.NonLinX5Edt->text()).toDouble(&ok);
    l_pDeviceData->m_Detector.m_aNLCorrect[6] = QString(ui.NonLinX6Edt->text()).toDouble(&ok);
    l_pDeviceData->m_Detector.m_aNLCorrect[7] = QString(ui.NonLinX7Edt->text()).toDouble(&ok);
    l_pDeviceData->m_Detector.m_aLowNLCounts = QString(ui.LoCountsEdt->text()).toDouble(&ok);
    l_pDeviceData->m_Detector.m_aHighNLCounts = QString(ui.HiCountsEdt->text()).toDouble(&ok);
    l_pDeviceData->m_Detector.m_NLEnable = ui.NonLinEnableChk->isChecked();
    QStringList defecttext = ui.DefectEdt->toPlainText().split('\n');
    for (unsigned short i = 0; (i < NR_DEFECTIVE_PIXELS) && (i<defecttext.size()); i++)
    {
        l_pDeviceData->m_Detector.m_DefectivePixels[i] = defecttext.at(i).toInt();
    }
    // Get standalone parameters
    l_pDeviceData->m_StandAlone.m_Enable = ui.EnableStandAloneChk->isChecked();
    l_pDeviceData->m_StandAlone.m_Meas.m_StartPixel = QString(ui.StartPixelEdt->text()).toInt(&ok);
    l_pDeviceData->m_StandAlone.m_Meas.m_StopPixel =  QString(ui.StopPixelEdt->text()).toInt(&ok);
    l_pDeviceData->m_StandAlone.m_Meas.m_IntegrationTime = QString(ui.IntTimeEdt->text()).toDouble(&ok);
    double l_NanoSec = QString(ui.IntDelayEdt->text()).toDouble(&ok);
    unsigned int l_FPGAClkCycles = (unsigned int)(0.5+6.0*(l_NanoSec+20.84)/125.0);
    l_pDeviceData->m_StandAlone.m_Meas.m_IntegrationDelay = l_FPGAClkCycles;
    l_pDeviceData->m_StandAlone.m_Meas.m_NrAverages = QString(ui.NrAveragesEdt->text()).toInt(&ok);
    l_pDeviceData->m_StandAlone.m_Meas.m_Trigger.m_Mode = ui.HardwareTriggerRBtn->isChecked();
    l_pDeviceData->m_StandAlone.m_Meas.m_Trigger.m_Source = ui.SynchTriggerRBtn->isChecked();
    l_pDeviceData->m_StandAlone.m_Meas.m_Trigger.m_SourceType = ui.LevelTriggerRBtn->isChecked();
    l_pDeviceData->m_StandAlone.m_Meas.m_SaturationDetection = QString(ui.SatDetectEdt->text()).toInt(&ok);
    l_pDeviceData->m_StandAlone.m_Meas.m_CorDynDark.m_Enable = ui.DarkCorrEnableChk->isChecked();
    l_pDeviceData->m_StandAlone.m_Meas.m_CorDynDark.m_ForgetPercentage = QString(ui.DarkPercentageEdt->text()).toInt(&ok);
    l_pDeviceData->m_StandAlone.m_Meas.m_Smoothing.m_SmoothPix = QString(ui.SmoothPixelsEdt->text()).toInt(&ok);
    l_pDeviceData->m_StandAlone.m_Meas.m_Smoothing.m_SmoothModel = QString(ui.SmoothModelEdt->text()).toInt(&ok);
    l_pDeviceData->m_StandAlone.m_Meas.m_Control.m_StrobeControl = QString(ui.FlashesPerScanEdt->text()).toInt(&ok);
    l_NanoSec = QString(ui.LaserDelayEdt->text()).toDouble(&ok);
    l_FPGAClkCycles = (unsigned int)(6.0*l_NanoSec/125.0);
    l_pDeviceData->m_StandAlone.m_Meas.m_Control.m_LaserDelay = l_FPGAClkCycles;
    l_NanoSec = QString(ui.LaserWidtEdt->text()).toDouble(&ok);
    l_FPGAClkCycles = (unsigned int)(6.0*l_NanoSec/125.0);
    l_pDeviceData->m_StandAlone.m_Meas.m_Control.m_LaserWidth = l_FPGAClkCycles;
    l_pDeviceData->m_StandAlone.m_Meas.m_Control.m_LaserWaveLength = QString(ui.LaserWavEdt->text()).toDouble(&ok);
    l_pDeviceData->m_StandAlone.m_Meas.m_Control.m_StoreToRam = QString(ui.StoreToRamEdt->text()).toInt(&ok);
    l_pDeviceData->m_StandAlone.m_Nmsr =  QString(ui.NrMeasEdt->text()).toInt(&ok);
    l_pDeviceData->m_StandAlone.m_SDCard.m_Enable = ui.SDCardEnableChk->isChecked();
    l_pDeviceData->m_StandAlone.m_SDCard.m_SpectrumType = ui.SpectrumTypeEdt->text().toInt(&ok);
    temp = QString(ui.FileRootNameEdt->text()).toLatin1();
    for (int i = 0; i < ROOT_NAME_LEN-1; i++)
    {
        l_pDeviceData->m_StandAlone.m_SDCard.m_aFileRootName[i] = temp[i];
    }
    l_pDeviceData->m_StandAlone.m_SDCard.m_aFileRootName[ROOT_NAME_LEN-1] = 0;
    l_pDeviceData->m_StandAlone.m_SDCard.m_TimeStamp.m_Date = QString(ui.DateNrEdt->text()).toInt(&ok);
    l_pDeviceData->m_StandAlone.m_SDCard.m_TimeStamp.m_Time = QString(ui.TimeNrEdt->text()).toInt(&ok);
	// Get Irradiance parameters
    l_pDeviceData->m_Irradiance.m_IntensityCalib.m_Smoothing.m_SmoothModel = QString(ui.IrradianceSmoothModelEdt->text()).toInt(&ok);
    l_pDeviceData->m_Irradiance.m_IntensityCalib.m_Smoothing.m_SmoothPix = QString(ui.IrradianceSmoothPixelsEdt->text()).toInt(&ok);
    l_pDeviceData->m_Irradiance.m_IntensityCalib.m_CalInttime = QString(ui.IrradianceIntTimeEdt->text()).toDouble(&ok);
    QStringList irradiancetext = ui.IrradianceConvEdt->toPlainText().split('\n');
    for (unsigned short i = 0; (i < MAX_NR_PIXELS) && (i<irradiancetext.size()); i++)
    {
        l_pDeviceData->m_Irradiance.m_IntensityCalib.m_aCalibConvers[i] = irradiancetext.at(i).toInt();
    }
    l_pDeviceData->m_Irradiance.m_CalibrationType = QString(ui.IrradCalibrationTypeEdt->text()).toInt(&ok);
    l_pDeviceData->m_Irradiance.m_FiberDiameter = QString(ui.IrradFiberDiameterEdt->text()).toInt(&ok);
    // Get Reflectance parameters
    l_pDeviceData->m_Reflectance.m_Smoothing.m_SmoothModel = QString(ui.ReflectanceSmoothModelEdt->text()).toInt(&ok);
    l_pDeviceData->m_Reflectance.m_Smoothing.m_SmoothPix = QString(ui.ReflectanceSmoothPixelsEdt->text()).toInt(&ok);
    l_pDeviceData->m_Reflectance.m_CalInttime = QString(ui.ReflectanceIntTimeEdt->text()).toDouble(&ok);
    QStringList reflectancetext = ui.ReflectanceCorrEdt->toPlainText().split('\n');
    for (unsigned short i = 0; (i < MAX_NR_PIXELS) && (i<reflectancetext.size()); i++)
    {
        l_pDeviceData->m_Reflectance.m_aCalibConvers[i] = reflectancetext.at(i).toInt();
    }
    // Get Correction parameters
    QStringList correctiontext = ui.SpectrumCorrEdt->toPlainText().split('\n');
    for (unsigned short i = 0; (i < MAX_NR_PIXELS) && (i<correctiontext.size()); i++)
    {
        l_pDeviceData->m_SpectrumCorrect.m_aSpectrumCorrect[i] = correctiontext.at(i).toInt();
    }
    // Get Thermistor parameters
    l_pDeviceData->m_aTemperature[0].m_aFit[0] = QString(ui.NTC1X0Edt->text()).toDouble(&ok);
    l_pDeviceData->m_aTemperature[0].m_aFit[1] = QString(ui.NTC1X0Edt->text()).toDouble(&ok);
    l_pDeviceData->m_aTemperature[0].m_aFit[2] = QString(ui.NTC1X2Edt->text()).toDouble(&ok);
    l_pDeviceData->m_aTemperature[0].m_aFit[3] = QString(ui.NTC1X3Edt->text()).toDouble(&ok);
    l_pDeviceData->m_aTemperature[0].m_aFit[4] = QString(ui.NTC1X4Edt->text()).toDouble(&ok);
    l_pDeviceData->m_aTemperature[1].m_aFit[0] = QString(ui.NTC2X0Edt->text()).toDouble(&ok);
    l_pDeviceData->m_aTemperature[1].m_aFit[1] = QString(ui.NTC2X1Edt->text()).toDouble(&ok);
    l_pDeviceData->m_aTemperature[1].m_aFit[2] = QString(ui.NTC2X2Edt->text()).toDouble(&ok);
    l_pDeviceData->m_aTemperature[1].m_aFit[3] = QString(ui.NTC2X3Edt->text()).toDouble(&ok);
    l_pDeviceData->m_aTemperature[1].m_aFit[4] = QString(ui.NTC2X4Edt->text()).toDouble(&ok);
    l_pDeviceData->m_aTemperature[2].m_aFit[0] = QString(ui.ThermistorX0Edt->text()).toDouble(&ok);
    l_pDeviceData->m_aTemperature[2].m_aFit[1] = QString(ui.ThermistorX1Edt->text()).toDouble(&ok);
    l_pDeviceData->m_aTemperature[2].m_aFit[2] = QString(ui.ThermistorX2Edt->text()).toDouble(&ok);
    l_pDeviceData->m_aTemperature[2].m_aFit[3] = QString(ui.ThermistorX3Edt->text()).toDouble(&ok);
    l_pDeviceData->m_aTemperature[2].m_aFit[4] = QString(ui.ThermistorX4Edt->text()).toDouble(&ok);
    // Get Tec Control parameters
    l_pDeviceData->m_TecControl.m_Enable   = ui.TECEnableChk->isChecked() ;
    l_pDeviceData->m_TecControl.m_Setpoint = QString(ui.SetPointEdt->text()).toDouble(&ok) ;
    l_pDeviceData->m_TecControl.m_aFit[0]  = QString(ui.TECX0Edt->text()).toDouble(&ok) ;
    l_pDeviceData->m_TecControl.m_aFit[1]  = QString(ui.TECX1Edt->text()).toDouble(&ok) ;

    // Write parameters
    l_Res = AVS_SetParameter(m_DeviceHandle, l_pDeviceData);
    if (ERR_SUCCESS != l_Res)
    {
        QMessageBox::critical(this, tr("QT4 Demo"),
                     tr("AVS_SetParameter failed, code %1").arg(l_Res),
                     QMessageBox::Ok, QMessageBox::Ok);
    }
    delete [] l_pDeviceData;
}

void eeprom::updatetime()
{
	unsigned short Years, Months, Days, Hours, Minutes, Seconds, DateNr, TimeNr ;
    if (this->isVisible())
    {
		QDate DateNow;
		Years = DateNow.currentDate().year();
		Months = DateNow.currentDate().month();
		Days = DateNow.currentDate().day();
		ui.YearEdt->setText(QString("%1").arg(Years-1980));
		ui.MonthEdt->setText(QString("%1").arg(Months));
		ui.DayEdt->setText(QString("%1").arg(Days));
		DateNr = Days + (Months << 5) + ((Years-1980) << 9);
		ui.DateNrEdt->setText(QString("%1").arg(DateNr));

		QTime TimeNow; 
		Hours = TimeNow.currentTime().hour();
		Minutes = TimeNow.currentTime().minute();
		Seconds = TimeNow.currentTime().second();
		ui.SecEdt->setText(QString("%1").arg(Seconds/2));
		ui.MinEdt->setText(QString("%1").arg(Minutes));
		ui.HourEdt->setText(QString("%1").arg(Hours));
		TimeNr = (Seconds/2) + (Minutes << 5) + (Hours << 11);
		ui.TimeNrEdt->setText(QString("%1").arg(TimeNr));
	 }
}

void eeprom::on_GetTimeStampChk_stateChanged(int)
{
	if (ui.GetTimeStampChk->isChecked())
	{
		timer->start();
	}
	else
	{
		timer->stop();
	}
}

void eeprom::on_groupBox_8_toggled(bool)
{

}
