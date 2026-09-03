import socket
import struct
import time
import random

GCS_IP = "192.168.1.100"
GCS_PORT = 5000

def generate_uav_state():

    latitude = random.uniform(36.0, 37.0)
    longitude = random.uniform(-6.0, -5.0)
    altitude = random.uniform(100.0, 5000.0)

    roll = random.uniform(-180.0, 180.0)
    pitch = random.uniform(-90.0, 90.0)
    yaw = random.uniform(0.0, 360.0)

    north = random.uniform(-50.0, 50.0)
    east = random.uniform(-50.0, 50.0)
    down = random.uniform(-10.0, 10.0)

    voltage = random.uniform(20.0, 25.2)
    current = random.uniform(0.0, 30.0)
    percentage = random.uniform(0.0, 100.0)

    ground_speed = random.uniform(0.0, 100.0)
    air_speed = random.uniform(0.0, 100.0)

    gps_valid = random.choice([True, False])

    return struct.pack(
        "!fffffffffffffffB",
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

        int(gps_valid)
    )

def send_uav_state(sock, payload):

    # 4-byte payload size
    header = struct.pack("!I", len(payload))

    sock.sendall(header + payload)

def main():

    print(f"Connecting to {GCS_IP}:{GCS_PORT}...")

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:

        sock.connect((GCS_IP, GCS_PORT))

        print("Connected.")

        while True:

            payload = generate_uav_state()

            send_uav_state(sock, payload)

            print(f"Sent {len(payload)} bytes")

            time.sleep(1.0)


if __name__ == "__main__":
    main()