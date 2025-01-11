# Play a sound when door is opened;
# using Digoo Door Window Alarm Sensor 
# DG_HAMA 433 MHz SKU A84932

import string

def door_rule(value, trigger, msg)
  var received_string = string.format("%s", msg)
  print("Received RF data:", received_string)
  
  if string.find(received_string, "0x86953") != -1
    print("Door opened! Playing gong sound.")
    tasmota.cmd("Backlog I2SGain 100; I2SPlay attention.mp3 ; Delay 20; I2SGain 10")
  elif string.find(received_string, "0x86959") != -1
    print("Door closed.")
  end
end

tasmota.add_rule("RfReceived#Data", door_rule)

print("Door monitoring script loaded and active.")
