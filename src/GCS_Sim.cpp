// GCS_Sim.cpp : Defines the entry point for the application.
//

#include "GCS_Sim.h"


using namespace std;

int main(int argc, char* argv[])
{
	GCSLog::GetInstance().AddPrinter<GCSLogPrinter>();
	//GCSLog::GetInstance().AddPrinter<LogFileWriter>();
	//Create the application object
	GCSLog::GetInstance().Log(ELogLevel::Info, "Initialize GCS app");
	QApplication QtApp(argc, argv);
	//Initialize the ground control window
	GCSMainWindow GCSWindow = GCSMainWindow(nullptr);
	GCSWindow.StartUAVTelemetry();
	GCSWindow.show();

	int result = QtApp.exec();

	return result;
}
