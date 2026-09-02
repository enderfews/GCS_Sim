// GCS_Sim.cpp : Defines the entry point for the application.
//

#include "GCS_Sim.h"


using namespace std;

int main(int argc, char* argv[])
{
	cout << "Initialize GCS app." << endl;
	GCSLog::GetInstance().AddPrinter<GCSLogPrinter>();
	//Create the application object
	QApplication QTApp(argc, argv);
	//Initialize the ground control window
	GCSMainWindow GCSWindow = GCSMainWindow(nullptr);
	GCSWindow.StartUAVTelemetry();
	GCSWindow.show();

	int result = QTApp.exec();

	return result;
}
