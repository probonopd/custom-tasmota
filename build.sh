#!/bin/sh

CONFIGS=$(cd custom-tasmota ; find configs/ -type f -maxdepth 1)
for CONFIG in $CONFIGS ; do
  echo $CONFIG
  NAME=$(echo $CONFIG | cut -d '/' -f 2)
  echo "Run PlatformIO for $NAME"
  cp custom-tasmota/"$CONFIG" ./tasmota/user_config_override.h
  platformio run -e tasmota
  mkdir -p ./out
  mv ./build_output/firmware/tasmota.bin.gz out/tasmota-$NAME-$(git rev-parse --short HEAD).bin.gz
  mv ./build_output/firmware/tasmota.bin out/tasmota-$NAME-$(git rev-parse --short HEAD).bin
  mv ./tasmota/user_config_override.h out/tasmota-$NAME-config_override.h
done
