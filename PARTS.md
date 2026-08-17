# Parts List — Motorized DIY Cable Cam

## Electronics
 
| Component | Description | Notes |
|-----------|-------------|-------|
| Arduino Nano | Microcontroller | Any V3 clone works |
| BTS7960 IBT-2 | 43A H-bridge motor driver | Handles direction + PWM speed control |
| JGY-370 | 12V worm gear motor, 40RPM | 90° output shaft, self-locking |
| LM2596 buck converter | Step-down 12V → 5V | Powers Arduino and BTS7960 logic |
| 11.1V 3S LiPo | Main battery | 2000mAh recommended |
| B10K potentiometer | Speed control | Linear taper, 10kΩ |
| Microswitch (x2) | End stop limit switches | Wired as NO (Normally Open) |

## Wiring

| Component | Notes |
|-----------|-------|
| Jumper wires | For connecting components |
| Perfboard or PCB | For permanent mounting |
| Terminal blocks | Optional, for motor and power connections |

## Mechanical

| Component | Notes |
|-----------|-------|
| Paracord | 2–3mm diameter, length as needed |
| Chicago Screw | For carriage to ride on cable. I used 5x30mm |
| 3D printed carriage | Custom designed |
| 3D printed pulley | Custom designed |
| Clamps for endstops | Adjustable end stop triggers on cable. Bag clips works pretty well but I will 3D-print alternatives |
| M2/M3 screws and nuts of different lengths | For assembly |
| Washers in various sizes | For assembly |


## Camera

| Component | Notes |
|-----------|-------|
| Insta360 aluminum cage | To hold the camera |
| SmallRig Camera Cold Shoe - Ballhead-1/4" | For mounting the cage to the carriage |

## Notes

- The pulley diameter determines speed range. A 2cm pulley gives ~0.5–3 m/min at 12V. A 10cm pulley gives ~2.5–15 m/min.
- The worm gear motor is self-locking, meaning the carriage will not drift when the motor is stopped.
- The BTS7960 can handle motors up to 43A stall current, making it suitable for much larger motors if needed in the future.
- Always use a LiPo balance charger for the 3S battery.