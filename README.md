# *DEPRECATED*
* Final commit backtracked to the last working version in conjunction with the LEDsController repository.
* Working on a new, private project repository; includes improved hardware, architecture design, and tech stack

# LED Receiver - Bluetooth App -> Arduino-controlled LED lightstrip

## Table of Contents
* [Summary](#summary)
* [Setup & Usage](#setup-&-usage)
* [Technologies](#technologies)
* [Inspiration](#inspiration)
* [Sources](#sources)

## Summary
The Arduino receiver half of the code for an LED lights project. Receives instructions via Bluetooth and sets up the lightstrip pattern accordingly.

## Setup & Usage
Download .ino Arduino file onto the Arduino board with a HC-05 Bluetooth module. Connect via Bluetooth with a phone with the app installed to control the LED lightstrip.

## Potential Improvements
Just getting started on this project; will update the README eventually with what can be improved on.

## Technologies
* API 28: Android 9.0 (Pie)
* MEGA2560 (not official Arduino but same hardware) board
* HC-05 Bluetooth module
* WS2812B LED lights
* C code (Arduino style)
* Power supply and a bunch of wiring to combat voltage drop
* FastLED library

## Inspiration
Wanted to set up a lightstrip and have it controllable by an app I program from my phone (also see the controller app repository).  Also want to eventually connect to the Spotify API to automatically set the lights depending on songs, genres, etc and have 'smart, responsive' patterns.

## Sources
Online resources used extensively.  Code examples derived from to figure out the FastLED library and program Bluetooth functionality in Android.
