
#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include <QUdpSocket> // Include the QUdpSocket header for UDP communication
#include <QHostAddress> // Include the QHostAddress header for handling IP 
#include <QTcpSocket> // Include the QTcpSocket header for TCP connection

#include <QCloseEvent> // Full definition of QCloseEvent, needed to call event->accept()
#include <QTimer> // Needed for the alarm banner's blinking behavior

class GCSMainWindow : public QWidget
{
	//Macro to enable Qt's meta-object features, such as signals and slots
	Q_OBJECT

public:
	GCSMainWindow(QWidget* Parent = nullptr);

protected:

	void closeEvent(QCloseEvent* CloseEvent) override;

private:

	//Titles for the window
	QLabel* TitleLabel = nullptr;
	QLabel* SubtitleLabel = nullptr;

	//TODO: Connection badges (depends on the connection)

	//Banners
	QLabel* MissionBanner = nullptr;
	QLabel* AlarmBanner = nullptr;

	//Drives the blinking of alarmBanner while the alarm is active
	//and not yet acknowledged by the operator.
	QTimer* alarmBlinkTimer = nullptr;
	bool alarmBlinkOn = false;        // current blink phase
	bool alarmAcknowledged = false;   // true once RTL is pressed, until battery recovers

	//Telemetry labels
	//TODO: Move all these labels into a new QWidget for modularity
	/*
	    Position position;
    Attitude attitude;
    Velocity velocity;
    BatteryState battery;

    float groundSpeed;
    float airSpeed;

    bool gpsValid;
	*/
};