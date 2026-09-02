// GCS_Sim.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "domain/UAV_Types.h"
#include "presentation/MainWindow.h"
#include <iostream>
#include <QApplication>
#include "application/Logs/LogManager.h"
#include "Infraestructure/Logs/GCSLogPrinter.h"

//Testing services and ports
#include "application/TelemetryService.h"
#include "Infraestructure/Qt/QtUdpTelemetryInput.h"
#include "Infraestructure/Qt/QtUtf8TelemetryDecoder.h"
// TODO: Reference additional headers your program requires here.
