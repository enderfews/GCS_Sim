// GCS_Sim.cpp : Defines the entry point for the application.
//

#include "GCS_Sim.h"
#include <QApplication>
#include "presentation/MainWindow.h"

using namespace std;

int main(int argc, char* argv[])
{
	cout << "Initialize GCS app." << endl;

	//Create the application object
	QApplication QTApp(argc, argv);

	//Initialize the ground control window
	GCSMainWindow GCSWindow = GCSMainWindow(nullptr);

	//Display the window
	GCSWindow.show();

	int result = QTApp.exec();

	return result;
}
