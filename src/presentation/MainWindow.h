
#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include <QUdpSocket> // Include the QUdpSocket header for UDP communication
#include <QHostAddress> // Include the QHostAddress header for handling IP 
#include <QTcpSocket> // Include the QTcpSocket header for TCP connection

#include <QCloseEvent> // Full definition of QCloseEvent, needed to call event->accept()
#include <QTimer> // Needed for the alarm banner's blinking behavior
#include "application/TelemetryService.h"
#include <memory>
class QtUAVTelemetryPanel;

using namespace std;

/*
* @brief The main window of the presentation layer for the GCS application.
* It's the root class and the mediator of all components of the UI. All services
* used are initialized and managed here.
*/
class GCSMainWindow : public QWidget
{
	//Macro to enable Qt's meta-object features, such as signals and slots
	Q_OBJECT

public:
	GCSMainWindow(QWidget* Parent = nullptr);

	void StartUAVTelemetry();
	void StopUAVTelemetry();

protected:

	void closeEvent(QCloseEvent* CloseEvent) override;

private:
	void OnTelemetryReceived(const struct UAVState& State);
	//Titles for the window
	QLabel* TitleLabel = nullptr;
	QLabel* SubtitleLabel = nullptr;
	QPushButton* buttonReconnet = nullptr;
	QtUAVTelemetryPanel* TelemetryPanel = nullptr;

	//App Services
	unique_ptr<TelemetryService> m_pUAVTelemetryService;

};