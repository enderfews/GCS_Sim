#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include <QUdpSocket> // Include the QUdpSocket header for UDP communication
#include <QHostAddress> // Include the QHostAddress header for handling IP 
#include <QTcpSocket> // Include the QTcpSocket header for TCP connection

#include <QCloseEvent> // Full definition of QCloseEvent, needed to call event->accept()
#include <QTimer> // Needed for the alarm banner's blinking behavior
#include "domain/UAV_Types.h"

class QLabel;

class QtUAVTelemetryPanel : public QWidget
{
    Q_OBJECT

public:

    QtUAVTelemetryPanel(QWidget* Parent = nullptr);

public slots:

    void SetUAVState(const UAVState& State);

protected:

    void closeEvent(QCloseEvent* CloseEvent) override;

private:

    void CreateUI();
    void UpdatePosition(const Position& Position);
    void UpdateAttitude(const Attitude& Attitude);
    void UpdateVelocity(const Velocity& Velocity);
    void UpdateBattery(const BatteryState& Battery);
    void UpdateSpeed(float GroundSpeed, float AirSpeed);
    void UpdateGPS(bool GPSValid);

private:

    // Position
    QLabel* m_LatitudeLabel;
    QLabel* m_LongitudeLabel;
    QLabel* m_AltitudeLabel;

    // Attitude
    QLabel* m_RollLabel;
    QLabel* m_PitchLabel;
    QLabel* m_YawLabel;

    // Velocity
    QLabel* m_NorthVelocityLabel;
    QLabel* m_EastVelocityLabel;
    QLabel* m_DownVelocityLabel;

    // Battery
    QLabel* m_BatteryVoltageLabel;
    QLabel* m_BatteryCurrentLabel;
    QLabel* m_BatteryPercentageLabel;

    // Speed
    QLabel* m_GroundSpeedLabel;
    QLabel* m_AirSpeedLabel;

    // GPS
    QLabel* m_GPSStatusLabel;
};