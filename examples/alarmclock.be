# Alarm clock using a capacitive bed occupancy sensor
# attached to a pin configured as button_ts;
# the alarm will sound every second while the imaginary "relais 1" is ON

import string
import mqtt

class BedOccupancySensor
  var lr
  var is_occupied
  var last_number
  var threshold
  var initial_number
  var hysteresis
  var debounce_count
  var debounce_threshold
  var consecutive_readings
  var percentage  # New variable for threshold percentage

  def init()
    self.lr = tasmota_log_reader()
    self.is_occupied = false
    self.last_number = 0
    self.threshold = 0
    self.initial_number = 0
    self.hysteresis = 0.01  # 1% hysteresis
    self.debounce_count = 0
    self.debounce_threshold = 2  # Number of consecutive readings required to change state
    self.consecutive_readings = 0
    self.percentage = 0.05  # Default to 5%
    tasmota.cmd("TouchCal 1")
    # Wait for before calibration
    tasmota.delay(500)
    tasmota.delay(500)
    tasmota.delay(500)
  end

  def parse_log_line(line)
    var parts = string.split(line, ',')
    if size(parts) > 3
      var last_part = parts[1]
      self.last_number = number(last_part)
      # print("Last Number:", self.last_number)
      # print("Threshold:", self.threshold)

      if self.initial_number == 0
        self.initial_number = self.last_number
        self.threshold = self.initial_number * (1 + self.percentage)  # Use percentage for threshold calculation
        print("Initial number:", self.initial_number)
        print("Threshold:", self.threshold)
        tasmota.cmd("LedPower 1")
      end

      self.check_occupancy()
    end
  end

  def check_occupancy()
    var lower_threshold = self.threshold * (1 - self.hysteresis)
    var upper_threshold = self.threshold * (1 + self.hysteresis)

    if self.is_occupied
      if self.last_number < lower_threshold
        self.consecutive_readings += 1
      else
        self.consecutive_readings = 0
      end
    else
      if self.last_number > upper_threshold
        self.consecutive_readings += 1
      else
        self.consecutive_readings = 0
      end
    end

    if self.consecutive_readings >= self.debounce_threshold
      self.change_occupancy_state(!self.is_occupied)
      self.consecutive_readings = 0
    end
  end

  def change_occupancy_state(new_state)
    if new_state != self.is_occupied
      self.is_occupied = new_state
      if self.is_occupied
        print("Bed is now occupied")
        mqtt.publish("cmnd/tasmota_FF15F2/Backlog", "I2SPlay attention.mp3")
        tasmota.cmd("LedPower 0")
      else
        print("Bed is now vacant")
        mqtt.publish("cmnd/tasmota_FF15F2/Backlog", "I2SPlay attention.mp3")
        tasmota.cmd("LedPower 1")
      end
    end
  end

  def check_logs()
    var ret = self.lr.get_log(2)
    if ret != nil
      var lines = string.split(ret, '\n')
      for line: lines
        if string.find(line, "PLOT:") != -1
          self.parse_log_line(line)
        end
      end
    end
  end

  def every_50ms()
    self.check_logs()
  end

  def json_append()
    var msg = string.format(",\"BedSensor\":{\"Occupied\":%s,\"Value\":%d, \"Threshold\":%d}",
                            self.is_occupied ? "true" : "false", self.last_number, self.threshold)
    tasmota.response_append(msg)
  end

end

# Create an instance of the BedOccupancySensor with a custom percentage if needed.
bed_sensor = BedOccupancySensor()
print("Bed sensor created")

# Register the driver.
tasmota.add_driver(bed_sensor)
print("Bed sensor driver registered")

######

# NOTE: Use 2 timers to enable and disable an imaginary "Relais 1"
# to set the alarm time that way
def play_attention()
  if tasmota.get_power(0) && bed_sensor.is_occupied
    tasmota.cmd("Backlog I2SGain 80 ; I2SPlay1 attention.mp3")
  end
  tasmota.set_timer(1000, play_attention)
end

# Start the process
play_attention()
