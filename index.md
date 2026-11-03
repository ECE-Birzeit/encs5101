---
layout: home

hero:
  name: ENCS5101
  text: Microprocessor and Embedded Systems Laboratory
  tagline: Department of Electrical & Computer Engineering · Birzeit University
  actions:
    - theme: brand
      text: Explore Experiments
      link: /experiments/
    - theme: alt
      text: Download Full Manual
      # Relative on purpose: VitePress doesn't add `base` to non-page links in hero actions.
      link: ./ENCS5101-Manual.pdf
      target: _blank
    - theme: alt
      text: Setup Guide
      link: /setup/

features:
  - icon:
      src: /icons/arm.svg
      alt: Arm
      width: 28
      height: 28
      wrap: true
    title: ARM Assembly on Cortex-M
    details: Write assembly for an ARM Cortex-M4 in Keil uVision5, step through it in the simulator, and watch every register and flag change.
  - icon:
      src: /icons/arduino.svg
      alt: Arduino
      width: 28
      height: 28
      wrap: true
    title: Arduino from the Registers Up
    details: Move to real hardware with the Arduino. Drive GPIO and motors, write AVR assembly, then program the timers, interrupts and ADC directly.
  - icon:
      src: /icons/raspberrypi.svg
      alt: Raspberry Pi
      width: 28
      height: 28
      wrap: true
    title: Systems and Interfacing
    details: Connect boards over serial links, control hardware from LabVIEW, build an elevator controller, and finish on the Raspberry Pi.
---
