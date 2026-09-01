// GCS_Sim.cpp : Defines the entry point for the application.
//

#include "GCS_Sim.h"
#include <QApplication>
#include "presentation/MainWindow.h"

//Testing services and ports
#include "application/TelemetryService.h"
#include "Infraestructure/Qt/QtUdpTelemetryInput.h"
#include "Infraestructure/Qt/QtUtf8TelemetryDecoder.h"

using namespace std;

int main(int argc, char* argv[])
{
	cout << "Initialize GCS app." << endl;

	//Create the application object
	QApplication QTApp(argc, argv);

	//Initialize the ground control window
	GCSMainWindow GCSWindow = GCSMainWindow(nullptr);

	//Testing
	QtUdpTelemetryInput TelemetryInput;
	QtUtf8TelemetryDecoder TelemetryDecoder;
	TelemetryService Service(TelemetryInput, TelemetryDecoder);
	Service.SetTelemetryServiceCallback([](UAVState& State)
		{
			system("cls");

			qDebug() << "========================================";
			qDebug() << "             UAV TELEMETRY";
			qDebug() << "========================================";

			qDebug() << "[Position]";
			qDebug() << "  Latitude:  " << State.position.latitude;
			qDebug() << "  Longitude: " << State.position.longitude;
			qDebug() << "  Altitude:  " << State.position.altitude;

			qDebug() << "[Attitude]";
			qDebug() << "  Roll:      " << State.attitude.roll;
			qDebug() << "  Pitch:     " << State.attitude.pitch;
			qDebug() << "  Yaw:       " << State.attitude.yaw;

			qDebug() << "[Velocity]";
			qDebug() << "  North:     " << State.velocity.north;
			qDebug() << "  East:      " << State.velocity.east;
			qDebug() << "  Down:      " << State.velocity.down;

			qDebug() << "[Battery]";
			qDebug() << "  Voltage:   " << State.battery.voltage;
			qDebug() << "  Current:   " << State.battery.current;
			qDebug() << "  Percentage:" << State.battery.percentage;

			qDebug() << "[Speed]";
			qDebug() << "  Ground:    " << State.groundSpeed;
			qDebug() << "  Air:       " << State.airSpeed;

			qDebug() << "[GPS]";
			qDebug() << "  Valid:     " << State.gpsValid;

			qDebug() << "========================================";
		});
	//End testing
	Service.Start();

	//Display the window
	GCSWindow.show();

	int result = QTApp.exec();

	return result;
}
