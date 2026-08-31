
#pragma once

struct Position
{
    float latitude;
    float longitude;
    float altitude;
};

struct Attitude
{
    float roll;
    float pitch;
    float yaw;
};

struct Velocity
{
    float north;
    float east;
    float down;
};

struct BatteryState
{
    float voltage;
    float current;
    float percentage;
};

struct UAVState
{
    Position position;
    Attitude attitude;
    Velocity velocity;
    BatteryState battery;

    float groundSpeed;
    float airSpeed;

    bool gpsValid;
};