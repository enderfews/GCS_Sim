#include "QtTelemetryPanel.h"
#include <QVBoxLayout>
#include <QNetworkDatagram>// Include the QNetworkDatagram header for handling incoming UDP datagrams
#include <QHBoxLayout> //Allow to desing better IU 
#include <QGroupBox>

QtUAVTelemetryPanel::QtUAVTelemetryPanel(QWidget* Parent)
    : QWidget(Parent)
    , m_LatitudeLabel(nullptr)
    , m_LongitudeLabel(nullptr)
    , m_AltitudeLabel(nullptr)
    , m_RollLabel(nullptr)
    , m_PitchLabel(nullptr)
    , m_YawLabel(nullptr)
    , m_NorthVelocityLabel(nullptr)
    , m_EastVelocityLabel(nullptr)
    , m_DownVelocityLabel(nullptr)
    , m_BatteryVoltageLabel(nullptr)
    , m_BatteryCurrentLabel(nullptr)
    , m_BatteryPercentageLabel(nullptr)
    , m_GroundSpeedLabel(nullptr)
    , m_AirSpeedLabel(nullptr)
    , m_GPSStatusLabel(nullptr)
{
    CreateUI();
}

void QtUAVTelemetryPanel::SetUAVState(const UAVState& State)
{
    UpdatePosition(State.position);
    UpdateAttitude(State.attitude);
    UpdateVelocity(State.velocity);
    UpdateBattery(State.battery);
    UpdateSpeed(State.groundSpeed, State.airSpeed);
    UpdateGPS(State.gpsValid);
}
void QtUAVTelemetryPanel::closeEvent(QCloseEvent* CloseEvent)
{
	CloseEvent->accept();
}

void QtUAVTelemetryPanel::CreateUI()
{
    auto* MainLayout = new QVBoxLayout(this);

    // =========================================
    // Position
    // =========================================

    auto* PositionGroup = new QGroupBox("Position", this);

    auto* PositionLayout = new QGridLayout(PositionGroup);
    PositionLayout->setContentsMargins(10, 20, 10, 10);
    PositionLayout->setVerticalSpacing(6);
    PositionLayout->addWidget(new QLabel("Roll:", PositionGroup), 0, 0);
    PositionLayout->addWidget(new QLabel("Latitude:", PositionGroup),0, 0);

    m_LatitudeLabel = new QLabel("--", PositionGroup);
    PositionLayout->addWidget(m_LatitudeLabel,0, 1);
    PositionLayout->addWidget(new QLabel("Longitude:", PositionGroup), 1, 0);

    m_LongitudeLabel = new QLabel("--", PositionGroup);

    PositionLayout->addWidget(m_LongitudeLabel, 1, 1);
    PositionLayout->addWidget(new QLabel("Altitude:", PositionGroup), 2, 0);

    m_AltitudeLabel = new QLabel("--", PositionGroup);
    PositionLayout->addWidget(m_AltitudeLabel, 2, 1);

    MainLayout->addWidget(PositionGroup);


    // =========================================
    // Attitude
    // =========================================

    auto* AttitudeGroup = new QGroupBox("Attitude", this);

    auto* AttitudeLayout = new QGridLayout(AttitudeGroup);
    AttitudeLayout->setContentsMargins(10, 20, 10, 10);
    AttitudeLayout->setVerticalSpacing(6);
    AttitudeLayout->addWidget(new QLabel("Roll:", AttitudeGroup),0, 0);

    m_RollLabel = new QLabel("--", AttitudeGroup);

    AttitudeLayout->addWidget(
        m_RollLabel,
        0, 1
    );

    AttitudeLayout->addWidget(
        new QLabel("Pitch:", AttitudeGroup),
        1, 0
    );

    m_PitchLabel = new QLabel("--", AttitudeGroup);

    AttitudeLayout->addWidget(
        m_PitchLabel,
        1, 1
    );

    AttitudeLayout->addWidget(
        new QLabel("Yaw:", AttitudeGroup),
        2, 0
    );

    m_YawLabel = new QLabel("--", AttitudeGroup);

    AttitudeLayout->addWidget(
        m_YawLabel,
        2, 1
    );

    MainLayout->addWidget(AttitudeGroup);


    // =========================================
    // Velocity
    // =========================================

    auto* VelocityGroup = new QGroupBox("Velocity", this);

    auto* VelocityLayout = new QGridLayout(VelocityGroup);
    VelocityLayout->setContentsMargins(10, 20, 10, 10);
    VelocityLayout->setVerticalSpacing(6);
    VelocityLayout->addWidget(
        new QLabel("North:", VelocityGroup),
        0, 0
    );

    m_NorthVelocityLabel = new QLabel("--", VelocityGroup);

    VelocityLayout->addWidget(
        m_NorthVelocityLabel,
        0, 1
    );

    VelocityLayout->addWidget(
        new QLabel("East:", VelocityGroup),
        1, 0
    );

    m_EastVelocityLabel = new QLabel("--", VelocityGroup);

    VelocityLayout->addWidget(
        m_EastVelocityLabel,
        1, 1
    );

    VelocityLayout->addWidget(
        new QLabel("Down:", VelocityGroup),
        2, 0
    );

    m_DownVelocityLabel = new QLabel("--", VelocityGroup);

    VelocityLayout->addWidget(
        m_DownVelocityLabel,
        2, 1
    );

    MainLayout->addWidget(VelocityGroup);


    // =========================================
    // Battery
    // =========================================

    auto* BatteryGroup = new QGroupBox("Battery", this);

    auto* BatteryLayout = new QGridLayout(BatteryGroup);
    BatteryLayout->setContentsMargins(10, 20, 10, 10);
    BatteryLayout->setVerticalSpacing(6);
    BatteryLayout->addWidget(
        new QLabel("Voltage:", BatteryGroup),
        0, 0
    );

    m_BatteryVoltageLabel = new QLabel("--", BatteryGroup);

    BatteryLayout->addWidget(
        m_BatteryVoltageLabel,
        0, 1
    );

    BatteryLayout->addWidget(
        new QLabel("Current:", BatteryGroup),
        1, 0
    );

    m_BatteryCurrentLabel = new QLabel("--", BatteryGroup);

    BatteryLayout->addWidget(
        m_BatteryCurrentLabel,
        1, 1
    );

    BatteryLayout->addWidget(
        new QLabel("Battery:", BatteryGroup),
        2, 0
    );

    m_BatteryPercentageLabel = new QLabel("--", BatteryGroup);

    BatteryLayout->addWidget(
        m_BatteryPercentageLabel,
        2, 1
    );

    MainLayout->addWidget(BatteryGroup);


    // =========================================
    // Speed
    // =========================================

    auto* SpeedGroup = new QGroupBox("Speed", this);

    auto* SpeedLayout = new QGridLayout(SpeedGroup);
    SpeedLayout->setContentsMargins(10, 20, 10, 10);
    SpeedLayout->setVerticalSpacing(6);
    SpeedLayout->addWidget(
        new QLabel("Ground:", SpeedGroup),
        0, 0
    );

    m_GroundSpeedLabel = new QLabel("--", SpeedGroup);

    SpeedLayout->addWidget(
        m_GroundSpeedLabel,
        0, 1
    );

    SpeedLayout->addWidget(
        new QLabel("Air:", SpeedGroup),
        1, 0
    );

    m_AirSpeedLabel = new QLabel("--", SpeedGroup);

    SpeedLayout->addWidget(
        m_AirSpeedLabel,
        1, 1
    );

    MainLayout->addWidget(SpeedGroup);


    // =========================================
    // GPS
    // =========================================

    auto* GPSGroup = new QGroupBox("GPS", this);

    auto* GPSLayout = new QGridLayout(GPSGroup);
    GPSLayout->setContentsMargins(10, 20, 10, 10);
    GPSLayout->setVerticalSpacing(6);
    GPSLayout->addWidget(
        new QLabel("Status:", GPSGroup),
        0, 0
    );

    m_GPSStatusLabel = new QLabel("INVALID", GPSGroup);

    GPSLayout->addWidget(
        m_GPSStatusLabel,
        0, 1
    );

    MainLayout->addWidget(GPSGroup);

    MainLayout->addStretch();
}

void QtUAVTelemetryPanel::UpdatePosition(const Position& Position)
{
    m_LatitudeLabel->setText(
        QString::number(Position.latitude, 'f', 6)
    );

    m_LongitudeLabel->setText(
        QString::number(Position.longitude, 'f', 6)
    );

    m_AltitudeLabel->setText(
        QString::number(Position.altitude, 'f', 2) + " m"
    );
}

void QtUAVTelemetryPanel::UpdateAttitude(const Attitude& Attitude)
{
    m_RollLabel->setText(
        QString::number(Attitude.roll, 'f', 2) + " °"
    );

    m_PitchLabel->setText(
        QString::number(Attitude.pitch, 'f', 2) + " °"
    );

    m_YawLabel->setText(
        QString::number(Attitude.yaw, 'f', 2) + " °"
    );
}

void QtUAVTelemetryPanel::UpdateVelocity(const Velocity& Velocity)
{
    m_NorthVelocityLabel->setText(
        QString::number(Velocity.north, 'f', 2) + " m/s"
    );

    m_EastVelocityLabel->setText(
        QString::number(Velocity.east, 'f', 2) + " m/s"
    );

    m_DownVelocityLabel->setText(
        QString::number(Velocity.down, 'f', 2) + " m/s"
    );
}

void QtUAVTelemetryPanel::UpdateBattery(const BatteryState& Battery)
{
    m_BatteryVoltageLabel->setText(
        QString::number(Battery.voltage, 'f', 2) + " V"
    );

    m_BatteryCurrentLabel->setText(
        QString::number(Battery.current, 'f', 2) + " A"
    );

    m_BatteryPercentageLabel->setText(
        QString::number(Battery.percentage, 'f', 1) + " %"
    );
}

void QtUAVTelemetryPanel::UpdateSpeed(float GroundSpeed, float AirSpeed)
{
    m_GroundSpeedLabel->setText(
        QString::number(GroundSpeed, 'f', 2) + " m/s"
    );

    m_AirSpeedLabel->setText(
        QString::number(AirSpeed, 'f', 2) + " m/s"
    );
}

void QtUAVTelemetryPanel::UpdateGPS(bool GPSValid)
{
    m_GPSStatusLabel->setText(
        GPSValid ? "VALID" : "INVALID"
    );
}
