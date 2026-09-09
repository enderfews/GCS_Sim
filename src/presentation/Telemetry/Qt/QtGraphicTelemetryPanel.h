
#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include "domain/UAV_Types.h"

/*
* @brief OpenGL graphic window version for the telemetry panel
*/
class QtGraphicTelemetryPanel
	: public QOpenGLWidget
	, protected QOpenGLFunctions
{
	Q_OBJECT

public:

	QtGraphicTelemetryPanel(QWidget* Parent = nullptr);

	void SetUAVState(const UAVState& State);

protected:

	void initializeGL() override;
	void resizeGL(int Width, int Height) override;
	void paintGL() override;

private:

	UAVState m_UAVState;
};