# Custom Tasmota [![Build Status](../../actions/workflows/build.yml/badge.svg)](../../actions/workflows/build.yml)

Builds https://github.com/arendst/Tasmota but with different compile-time configurations and hosts the builds on GitHub Releases so that OTA can be performed from there.

Can be flashed using 

- [X] ESP32 and variants
- [ ] ESP8266 - OTA fails (due to size and/or HTTPS and/or redirects?)

Known good boards:

* S2 mini (with PSRAM if you want to play mp3) using `tasmota32s2cdc.bin`
