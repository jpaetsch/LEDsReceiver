# LED Receiver

## Table of Contents
* [Summary](#summary)
* [Architecture](#architecture)
* [Setup & Usage](#setup-&-usage)
* [Technologies](#technologies)
* [Inspiration](#inspiration)
* [Sources](#sources)

## Summary
The ESP32 receiver half of the code for an LED lights project. Receives instructions via HTTP and sets up the lightstrip pattern accordingly.

## Architecture
![General Architecture Diagram](documentation/LEDs%20Project%20General%20Architecture.png)
[Edit Source Document](https://app.diagrams.net/?src=about#G1grlmBMnNhJxIqO1p9Py0KbEwqqTXZHo6)

## Setup & Usage
Download .ino Arduino file onto the ESP32 module. Connect via the same network as a phone with the app installed to control the LED lightstrip.

## Potential Improvements
Just getting started on this project; will update the README eventually with what can be improved on.

## Technologies
* ESP32 (TinyPICO Development Board v3)
* WS2812B LED lights
* C code and libraries (compiled and flashed using the Arduino IDE)
* Power supply and a bunch of wiring to combat voltage drop
* FastLED library

## Inspiration
Wanted to set up a lightstrip and have it controllable by an app I program from my phone (also see the controller app repository).  Also want to eventually connect to the Spotify API to automatically set the lights depending on songs, genres, etc and have 'smart, responsive' patterns.

## Sources
Online resources used extensively.  Code examples derived from to figure out the FastLED library and program Wifi functionality in Android.
