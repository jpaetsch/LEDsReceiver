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
Download .ino Arduino file onto the Arduino board with a HC-05 Bluetooth module. Parse for new instructions while the lights are set to one of many possible pattern options.

## Potential Improvements
Just getting started on this project; will update the REAME eventually with what can be improved on.

## Technologies
* MEGA2560 (not official Arduino but same hardware) board
* HC-05 Bluetooth module
* WS2812B LED lights
* C code (Arduino style)
* Power supply and a bunch of wiring to combat voltage drop
* FastLED library

## Inspiration
Wanted to set up a lightstrip and have it controllable by an app I program from my phone (will set up a controller repository).  Also want to eventually connect to the Spotify API to automatically set the lights depending on songs, genres, etc and have 'smart, responsive' patterns.

## Sources
Online resources used extensively.  Code examples derived from to figure out the FastLED library.
