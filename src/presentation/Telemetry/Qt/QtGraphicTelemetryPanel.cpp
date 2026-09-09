
#include "QtGraphicTelemetryPanel.h"
#include <QPainter>


QtGraphicTelemetryPanel::QtGraphicTelemetryPanel(QWidget* Parent/* = nullptr*/)
	: QOpenGLWidget(Parent)
	, m_UAVState({})
{
	setMinimumSize(600, 400); //TODO: No magic numbers
}

void QtGraphicTelemetryPanel::SetUAVState(const UAVState& State)
{
	m_UAVState = State;
}

void QtGraphicTelemetryPanel::initializeGL()
{
	initializeOpenGLFunctions();
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);//TODO: No magic numbers

}
void QtGraphicTelemetryPanel::resizeGL(int Width, int Height)
{
	glViewport(0, 0, Width, Height); //TODO: No magic numbers
}
void QtGraphicTelemetryPanel::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QPainter Painter(this);
    Painter.setPen(Qt::white);

    Painter.setFont(QFont("Consolas", 14));
    int Y = 30;

    Painter.drawText(20, Y, QString("UAV TELEMETRY"));
    Y += 40;
    Painter.drawText(20, Y, QString("Position:"));
    Y += 25;
    Painter.drawText(40, Y, QString("Latitude:  %1").arg(m_UAVState.position.latitude));
    Y += 25;
    Painter.drawText(40, Y,QString("Longitude: %1").arg(m_UAVState.position.longitude));
    Y += 25;
    Painter.drawText(40, Y, QString("Altitude:  %1 m").arg(m_UAVState.position.altitude));
    Y += 40;

    Painter.drawText(20, Y, QString("Attitude:"));
    Y += 25;
    Painter.drawText(40, Y, QString("Roll:  %1 deg").arg(m_UAVState.attitude.roll));
    Y += 25;
    Painter.drawText(40, Y, QString("Pitch: %1 deg").arg(m_UAVState.attitude.pitch));
    Y += 25;
    Painter.drawText(40, Y, QString("Yaw:   %1 deg").arg(m_UAVState.attitude.yaw));
    Y += 40;

    Painter.drawText(20,Y,QString("Velocity:"));
    Y += 25;
    Painter.drawText(40, Y, QString("North: %1 m/s").arg(m_UAVState.velocity.north));
    Y += 25;
    Painter.drawText(40, Y,QString("East:  %1 m/s").arg(m_UAVState.velocity.east));
    Y += 25;
    Painter.drawText(40, Y, QString("Down:  %1 m/s").arg(m_UAVState.velocity.down));
    Y += 40;

    Painter.drawText(20, Y, QString("Battery: %1 %").arg(m_UAVState.battery.percentage));
    Y += 25;

    Painter.drawText(20, Y, QString("Ground Speed: %1 m/s").arg(m_UAVState.groundSpeed));
    Y += 25;
    Painter.drawText(20, Y, QString("Air Speed: %1 m/s").arg(m_UAVState.airSpeed));
    Y += 25;
    Painter.drawText(20, Y, QString("GPS: %1").arg(m_UAVState.gpsValid ? "VALID" : "INVALID"));
    Painter.end();
}