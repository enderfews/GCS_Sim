
import socket
import struct
import random
import time
import os

UDP_IP = "127.0.0.1"
UDP_PORT = 5000

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)


def generate_uav_state():

    latitude = random.uniform(37.0, 38.0)
    longitude = random.uniform(-6.0, -5.0)
    altitude = random.uniform(50.0, 500.0)

    roll = random.uniform(-30.0, 30.0)
    pitch = random.uniform(-20.0, 20.0)
    yaw = random.uniform(0.0, 360.0)

    north = random.uniform(-20.0, 20.0)
    east = random.uniform(-20.0, 20.0)
    down = random.uniform(-5.0, 5.0)

    voltage = random.uniform(20.0, 25.2)
    current = random.uniform(0.0, 30.0)
    percentage = random.uniform(10.0, 100.0)

    ground_speed = random.uniform(0.0, 40.0)
    air_speed = random.uniform(0.0, 45.0)

    gps_valid = random.choice([True, True, True, False])

    return (
        latitude,
        longitude,
        altitude,

        roll,
        pitch,
        yaw,

        north,
        east,
        down,

        voltage,
        current,
        percentage,

        ground_speed,
        air_speed,

        gps_valid
    )

def print_uav_state(state):

    os.system("cls")

    print("========================================")
    print("             UAV TELEMETRY")
    print("========================================")

    print()
    print("[Position]")
    print(f"  Latitude:   {state[0]:.6f}")
    print(f"  Longitude:  {state[1]:.6f}")
    print(f"  Altitude:   {state[2]:.3f}")

    print()
    print("[Attitude]")
    print(f"  Roll:       {state[3]:.3f}")
    print(f"  Pitch:      {state[4]:.3f}")
    print(f"  Yaw:        {state[5]:.3f}")

    print()
    print("[Velocity]")
    print(f"  North:      {state[6]:.3f}")
    print(f"  East:       {state[7]:.3f}")
    print(f"  Down:       {state[8]:.3f}")

    print()
    print("[Battery]")
    print(f"  Voltage:    {state[9]:.3f}")
    print(f"  Current:    {state[10]:.3f}")
    print(f"  Percentage: {state[11]:.3f}")

    print()
    print("[Speed]")
    print(f"  Ground:     {state[12]:.3f}")
    print(f"  Air:        {state[13]:.3f}")

    print()
    print("[GPS]")
    print(f"  Valid:      {state[14]}")

    print()
    print(f"Packet size: 57 bytes")
    print("========================================")


print(f"UAV simulator started")
print(f"Sending UDP telemetry to {UDP_IP}:{UDP_PORT}")
print()

def encode_uav_state(state):

    return struct.pack(
        "<14f?",
        *state
    )


print(f"UAV simulator started")
print(f"Sending UDP telemetry to {UDP_IP}:{UDP_PORT}")

while True:

    state = generate_uav_state()

    packet = encode_uav_state(state)

    sock.sendto(packet, (UDP_IP, UDP_PORT))

    print_uav_state(state)

    time.sleep(1.1)