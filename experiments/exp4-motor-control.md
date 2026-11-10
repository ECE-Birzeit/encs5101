---
title: DC Motor and Stepper Control
description: Drive a DC motor through an L298N H-bridge, setting its speed with PWM and its direction with two pins, then turn a stepper motor by exact angles with the Stepper library.
short: "Motor Control"
manual: "/ENCS5101-Manual.pdf#page=67"
---

# DC Motor and Stepper Control

A motor needs far more current than an Arduino pin can give, so the board never drives it directly. It sends low-current control signals to a **driver**, which switches the motor's own supply. You use two drivers: an **L298N H-bridge** to set a DC motor's speed and direction, and a **ULN2003** to turn a stepper motor by exact steps.

## Objectives

- Explain why a motor needs a driver, and wire one with a shared ground.
- Set a DC motor's speed with PWM (`analogWrite()`) and its direction with an H-bridge.
- Read a number typed on the Serial Monitor and reject values out of range.
- Turn a stepper motor by a given angle with the `Stepper` library.

::: tip Before the lab
Finish [Experiment 3](./exp3-arduino-intro). This experiment reuses `analogWrite()`, `millis()` and the Serial Monitor from it.
:::

## Background

### Why a motor needs a driver

| | Arduino pin | Small DC motor | 28BYJ-48 stepper |
| --- | --- | --- | --- |
| Current | 20 mA, 40 mA max | 100–500 mA, more when starting | about 240 mA |

A motor connected straight to a pin would overload it, and the voltage spike a motor coil makes when switched off can destroy the chip. A driver takes the pin's signal as a command and switches the motor's own supply. Flyback diodes across its outputs absorb the spikes; both boards you use have them built in.

::: warning Shared ground
The motor supply and the Arduino must have their **GND connected together**. Without a common ground the driver cannot see the Arduino's signals, and the motor does nothing or twitches.
:::

### PWM: speed

`analogWrite(pin, value)` on a `~` pin does not output a voltage between 0 and 5 V. It switches the pin fully on and off about 490 times a second. The fraction of each period the pin is `HIGH` is the **duty cycle**:

**duty = T<sub>on</sub> / (T<sub>on</sub> + T<sub>off</sub>) = value / 255**

| `value` | 0 | 64 | 127 | 191 | 255 |
| --- | --- | --- | --- | --- | --- |
| Duty cycle | 0 % | 25 % | 50 % | 75 % | 100 % |
| Average voltage at 5 V | 0 V | 1.25 V | 2.5 V | 3.75 V | 5 V |

The motor is too slow to follow each pulse, so it responds to the **average**: higher duty, higher speed. Below some duty the motor only hums, because the average is too low to overcome friction. [Example 2](#example-2-find-the-starting-duty) finds that point.

If a value can leave the range 0–255, clamp it with `constrain(x, 0, 255)`, or rescale it with `map(x, fromLow, fromHigh, 0, 255)`.

### The H-bridge: direction

A DC motor reverses when the current through it reverses. An **H-bridge** is four switches around the motor, shaped like an H. Closing one diagonal pair sends current one way; closing the other pair sends it back:

![H-bridge: closing S1 and S4 drives the motor forward; closing S2 and S3 drives it in reverse](/images/exp4/h-bridge.svg)

The **L298N** holds two H-bridges, A and B, so it can drive two motors. For motor A, `IN1` and `IN2` choose which pair closes, and `ENA` turns the bridge on. Put PWM on `ENA` and it sets the speed too:

| `ENA` | `IN1` | `IN2` | Motor |
| --- | --- | --- | --- |
| PWM | `HIGH` | `LOW` | Forward, at the PWM speed |
| PWM | `LOW` | `HIGH` | Reverse, at the PWM speed |
| PWM | equal | equal | Brake: stops quickly |
| 0 | any | any | Coast: power off, spins down |

::: warning The ENA jumper
The L298N module ships with a jumper on `ENA`, which holds the bridge on at full speed. Pull the jumper off and wire `ENA` to a PWM pin, or `analogWrite()` changes nothing.
:::

### Stepper motors

A stepper does not spin freely. Its coils are energized one pattern at a time, and each new pattern pulls the rotor one **step** further. Count the steps and you know the angle, with no sensor.

The **28BYJ-48** has a gearbox, so one turn of its shaft takes **2048 steps** (0.18° each). Its **ULN2003** board is four transistor switches, one per coil, with an LED on each to show the pattern. The `Stepper` library, built into the Arduino IDE, sends the patterns for you:

| Function | Effect |
| --- | --- |
| `Stepper motor(2048, 8, 10, 9, 11)` | A stepper on the board's IN1..IN4 = pins 8..11. Note the order: IN1, IN3, IN2, IN4. |
| `motor.setSpeed(rpm)` | Speed for later moves; up to about 15 rpm for the 28BYJ-48 |
| `motor.step(n)` | Move `n` steps; negative reverses. **Blocks** until done. |

To turn by an angle, convert it to steps: `steps = angle × 2048 / 360`. A move of `n` steps at `rpm` takes `n × 60 / (2048 × rpm)` seconds.

### Reading a number from the Serial Monitor

Text typed in the Serial Monitor arrives one character at a time. With the line ending set to **Newline**, read a whole line and convert it:

```cpp
if (Serial.available() > 0) {               // something has arrived
  String line = Serial.readStringUntil('\n');
  line.trim();                              // drop spaces and '\r'
  int value = line.toInt();                 // 0 if the text is not a number
  // ... check the range before you use it ...
}
```

`toInt()` returns 0 for text that is not a number, so test `line == "0"` if you need to tell a real 0 from bad input.

## Materials

- Arduino Mega 2560 and USB cable
- L298N motor driver module
- Small 6 V DC motor
- 28BYJ-48 stepper motor with its ULN2003 driver board
- External supply for the DC motor, 6–9 V (battery pack or bench supply)
- Jumper wires

## Examples

### Example 1: forward, stop, reverse

Wire the L298N, with its `ENA` jumper removed:

| L298N | To |
| --- | --- |
| `ENA` | Pin 10 |
| `IN1` | Pin 8 |
| `IN2` | Pin 9 |
| `OUT1`, `OUT2` | The motor's two leads |
| `12V` | External supply + |
| `GND` | External supply − **and** an Arduino GND |

<<< @/snippets/exp4/hbridge.ino{cpp}

The motor runs one way for 2 s, stops, then runs the other way. `setMotor()` takes a signed speed and works out the three pins from it, so the rest of your code never touches `IN1` and `IN2` again. Reuse it in the lab work.

::: tip Which way is forward?
That depends only on which lead you put on `OUT1`. Swap the two motor leads and forward and reverse swap too.
:::

### Example 2: find the starting duty

Same wiring. Open the Serial Monitor at 9600 baud.

<<< @/snippets/exp4/ramp.ino{cpp}

The PWM value climbs by 15 every second. Note the value at which the motor starts to turn: below it the motor only hums. Each motor is different, so your lab work should never ask for a speed below this.

### Example 3: stepper, one turn each way

Plug the 28BYJ-48 into the ULN2003 board's socket, then wire the board:

| ULN2003 board | To |
| --- | --- |
| `IN1`, `IN2`, `IN3`, `IN4` | Pins 8, 9, 10, 11 |
| `+` (5–12 V) | Arduino 5V |
| `−` | Arduino GND |

The DC motor circuit can stay on the breadboard, but unplug `IN1` and `IN2` of the L298N from pins 8 and 9.

<<< @/snippets/exp4/stepper.ino{cpp}

The shaft makes exactly one turn, then turns back. The four LEDs on the board show the coil pattern; lower the speed to 1 rpm to watch them step.

## Lab work

### Lab work 1: Serial motor console

Control the DC motor from the Serial Monitor, using the Example 1 circuit. Each line typed is one command:

| Command | Effect |
| --- | --- |
| A number from −255 to 255 | Run at that speed; negative is reverse, 0 stops |
| `b` | Brake |
| Anything else, or a number out of range | Print an error and keep the current speed |

After every accepted command, print the speed and direction, for example `Forward at 180 (71 %)`.

::: tip Hints
- Start from [Reading a number](#reading-a-number-from-the-serial-monitor) and `setMotor()` from Example 1.
- Brake is `IN1` = `IN2` with `ENA` high, which `setMotor()` cannot express. Write a small `brake()` for it.
- Reversing at full speed makes a current spike. Stop for about 200 ms before changing direction.
:::

### Lab work 2: stepper to an angle

Make the stepper point the shaft at an angle typed on the Serial Monitor, from 0 to 359. The angle is **absolute**: typing `90` twice moves the first time and not the second. Take 0 as wherever the shaft is at reset.

1. Keep the current position, in steps, in a variable.
2. For each angle typed, work out the target in steps and move by the difference.
3. Print the new angle when the move is done.

::: tip Hints
- `target = angle * 2048L / 360`. The `L` keeps the product from overflowing an `int`, which holds at most 32767.
- Going from 350° to 10° by the short way means 20° forward, not 340° back. Get the long way working first, then fix it.
:::

## Common problems

| Symptom | Cause and fix |
| --- | --- |
| The DC motor never turns | No common ground: join the supply's − to an Arduino GND. Or the supply is off. |
| The motor always runs at full speed | The `ENA` jumper is still on, or `ENA` is on a pin without `~`. |
| The motor hums but does not turn | The PWM value is below the starting duty of [Example 2](#example-2-find-the-starting-duty), or the supply is too weak. |
| The motor turns slowly even at 255 | The L298N drops about 2 V. Use a supply about 2 V above the motor's rating. |
| The Arduino resets when the motor starts | The motor is powered from the Arduino. Give it the external supply. |
| The stepper vibrates but does not turn | The pin order is wrong. It must be `Stepper(2048, 8, 10, 9, 11)` for IN1..IN4 on 8..11. Or the speed is above about 15 rpm. |
| Buttons and Serial input are ignored while the stepper moves | `step()` blocks. Move in small chunks if you need to react mid-move. |
| Each Serial command takes a second to act | The Serial Monitor's line ending is **No line ending**, so `readStringUntil('\n')` waits for its 1 s timeout. Set it to **Newline**. |

## Things to try

- Wire a second motor to bridge B (`ENB`, `IN3`, `IN4`, `OUT3`, `OUT4`) and drive both, like a two-wheeled robot: same direction to go straight, opposite to spin.
- Ramp speed changes smoothly with `millis()` instead of jumping, so the motor never jerks.
- Run the stepper in the manual's sequence: 5 rpm for 2 s, reverse for 3 s, 3 rpm for 4 s, stop for 2 s. Work out each step count from the time.
- Drive a DC motor with a single PN2222 transistor and a flyback diode (manual Part 1). It sets speed, but can it reverse?
