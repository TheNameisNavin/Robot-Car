# Robot-Car
It's a bluetooth controlled robot car.

This is a 2‑wheel robot car that you control over Bluetooth:

F = Forward
B = Backward
L = Turn Left (in‑place)
R = Turn Right (in‑place)
S = Stop
0–9 = Set speed (0 = stop, 9 = max)


# Components Used:

1) Arduino UNO
2) HC‑05 Bluetooth module
3) L298N motor driver (or L293D)
4) 2× DC gear motors + robot chassis + wheels
5) Battery pack for motors (e.g., 2S Li‑ion 7.4V or 6×AA NiMH)
6) Optionally a separate 5V power bank for Arduino (recommended for stability)
7) Jumper wires, switch, and 2 resistors for a voltage divider (e.g., 1kΩ + 2kΩ)


# Wiring:

1) HC‑05 → Arduino UNO (using SoftwareSerial)

| HC‑05 Pin | Arduino UNO |
| VCC       |    5V       |
| GND       |   GND       |
| TXD       |   D2 (RX)   |
| RXD       |   D3 (TX)   |


2) L298N Motor Driver (Assuming Left Motor = OUT1/OUT2 and Right Motor = OUT3/OUT4)

| L298N     | Connect To       |
| ENA       | D5 (PWM)         |



