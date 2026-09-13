
#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include "domain/UAV_Types.h"

/*
* @brief OpenGL graphic window version for the telemetry panel
* which inherits from QOpenGLWidget. Documentation: https://doc.qt.io/qt-6/qopenglwidget.html
*/
class QtGraphicTelemetryPanel
	: public QOpenGLWidget
	, protected QOpenGLFunctions //Allows us to call gl functions directly
{
	Q_OBJECT

public:

	QtGraphicTelemetryPanel(QWidget* Parent = nullptr);

	void SetUAVState(const UAVState& State);

protected:

	/*
	* @brief Sets up the OpenGL resources and state.
	* Gets called once before the first time resizeGL() or paintGL() is called.
	*/
	void initializeGL() override;
	/*
	* @brief Sets up the OpenGL viewport, projection, etc.
	* Gets called whenever the widget has been resized
	* (and also when it is shown for the first time because all newly created widgets get a resize event automatically).
	*/
	void resizeGL(int Width, int Height) override;

	/*
	* @brief Renders the OpenGL scene. Gets called whenever
	* the widget needs to be updated.
	*/
	void paintGL() override;

private:

	UAVState m_UAVState;
};