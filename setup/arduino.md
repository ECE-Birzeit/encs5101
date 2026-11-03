---
title: Arduino IDE
description: Install the Arduino IDE, select the Mega 2560, upload a sketch, use the Serial Monitor and install libraries.
---

# Arduino IDE

Experiment 3 onward runs on the **Arduino Mega 2560**. The Arduino IDE runs on Windows, macOS and Linux, and the lab PCs already have it.

## 1. Install the Arduino IDE

1. Download **Arduino IDE 2** from [arduino.cc/en/software](https://www.arduino.cc/en/software) and install it with the defaults. On Windows, accept the USB driver prompts.
2. Plug the Mega in with its USB cable. The green **ON** LED lights.
3. Pick the board and port from the drop-down at the top of the window, or from the **Tools** menu:
   - **Tools → Board → Arduino AVR Boards → Arduino Mega or Mega 2560**
   - **Tools → Port →** the port labelled *Arduino Mega or Mega 2560* (`COMx` on Windows, `/dev/cu.usbmodem…` on macOS)

<Screenshot src="arduino/board-port.png" alt="Choosing the board and port">
Arduino IDE 2 with the board/port drop-down open and "Arduino Mega or Mega 2560" on COMx selected.
</Screenshot>

## 2. Upload a sketch

| Action | Button | Shortcut |
| --- | --- | --- |
| Verify (compile only) | ✓ | <kbd>Ctrl</kbd>+<kbd>R</kbd> |
| Upload to the board | → | <kbd>Ctrl</kbd>+<kbd>U</kbd> |
| Serial Monitor | magnifier, top right | <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>M</kbd> |

**File → New Sketch** opens an empty sketch with `setup()` and `loop()`. Paste your code over it, then **Upload**. The output pane ends with *Done uploading* and the board starts running the new sketch at once. It keeps running it, even after a power cycle, until you upload something else.

**Serial Monitor** shows what the sketch sends with `Serial.print()`. Set the baud rate in its drop-down to the same number as `Serial.begin()` in your code, normally 9600.

<Screenshot src="arduino/upload-serial.png" alt="Upload output and the Serial Monitor">
A sketch after a successful upload: "Done uploading" in the output pane, Serial Monitor open at the bottom set to 9600 baud and showing printed lines.
</Screenshot>

## 3. Install a library

Some experiments use libraries that do not come with the IDE. Open the **Library Manager** (the books icon on the left, or **Sketch → Include Library → Manage Libraries…**), search for the name the experiment gives, and click **Install**.

## Troubleshooting

| Symptom | Cause and fix |
| --- | --- |
| Upload fails with `avrdude: stk500v2_getsync(): timeout communicating with programmer` | Wrong board or port. Re-select both in **Tools**. Unplug anything wired to pins 0 and 1, which share the USB serial line. |
| No port appears | Try another cable, since some are power-only. On Windows, check *Device Manager* for an unknown device and reinstall the IDE's drivers. |
| Serial Monitor shows garbage | The baud rate in the monitor does not match `Serial.begin()`. |
| `fatal error: Keypad.h: No such file or directory` | The library is not installed. See [Install a library](#_3-install-a-library). |
