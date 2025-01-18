#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

// QUESTION: How can we do without hardcoding this?
// #define TASMOTA_VARIANT "tasmota32s2cdc"
// #define OTA_URL "https://github.com/probonopd/custom-tasmota/releases/download/continuous" TASMOTA_VARIANT ".bin"

// Disable webcam support and advanced display GUIs (seems to be in tasmota32s3-qio_opi by otherwise)
#undef USE_WEBCAM
#undef USE_LVGL
#undef USE_LVGL_OPENHASP
#undef FIRMWARE_LVGL

// Enable RTC support; but DS1302 is not supported yet since it does not use I2C
#ifndef USE_RTC_CHIPS
#define USE_RTC_CHIPS
#endif
#ifndef USE_DS3231
#define USE_DS3231
#endif

// Enable 16x2 LCD support
#ifndef USE_DISPLAY
#define USE_DISPLAY
#endif

// SH1106 OLED displays
// is now supported by the universal display driver, but it needs to be configured using a descriptor file in the filesystem
// https://tasmota.github.io/docs/Universal-Display-Driver/
// Also need to set an unused pin to "Option A" and select "3"; why do we have to waste a pin for this?
// Only then can we set "DisplayModel 17" in the console
// Also need to have a file data/display.ini with the content matching the display, and need to build a filesystem image and upload it to the device on ESP8266;
// on ESP32, it is not necessary to build a filesystem image, but the file still needs to be uploaded to the device via the web interface
// Apparently one can also use Rule3 for this, https://github.com/arendst/Tasmota/discussions/21121 but it does not seem to work for me
# ifndef USE_DISPLAY_SH1106
# define USE_DISPLAY_SH1106
# endif
#ifndef USE_UNIVERSAL_DISPLAY
#define USE_UNIVERSAL_DISPLAY
#endif

// Enable I2S support
#ifndef USE_I2S_ALL
#define USE_I2S_ALL
#endif

// HLK-LD2410 human presence sensor
#ifndef USE_LD2410
#define USE_LD2410
#endif

// Enable mDNS support by default
// so that one doesn't have to manually enable it in the console after flashing using
// SetOption55 1
#ifndef USE_DISCOVERY
#define USE_DISCOVERY
#endif
#define MDNS_ENABLED           true

// Use bright mode for the web UI
// WebColor {"WebColor":["#000","#fff","#f2f2f2","#000","#fff","#000","#fff","#f00","#008000","#fff","#1fa3ec","#0e70a4","#d43535","#931f1f","#47c266","#5aaf6f","#fff","#999","#000","#08405e"]}
#define COLOR_TEXT                  "#000"       // [WebColor1] Global text color - Black
#define COLOR_BACKGROUND            "#fff"       // [WebColor2] Global background color - White
#define COLOR_FORM                  "#f2f2f2"    // [WebColor3] Form background color - Greyish
#define COLOR_INPUT_TEXT            "#000"       // [WebColor4] Input text color - Black
#define COLOR_INPUT                 "#fff"       // [WebColor5] Input background color - White
#define COLOR_CONSOLE_TEXT          "#000"       // [WebColor6] Console text color - Black
#define COLOR_CONSOLE               "#fff"       // [WebColor7] Console background color - White
#define COLOR_TEXT_WARNING          "#f00"       // [WebColor8] Warning text color - Red
#define COLOR_TEXT_SUCCESS          "#008000"    // [WebColor9] Success text color - Dark lime green
#define COLOR_BUTTON_TEXT           "#fff"       // [WebColor10] Button text color - White
#define COLOR_BUTTON                "#1fa3ec"    // [WebColor11] Button color - Vivid blue
#define COLOR_BUTTON_HOVER          "#0e70a4"    // [WebColor12] Button color when hovered over - Dark blue
#define COLOR_BUTTON_RESET          "#d43535"    // [WebColor13] Restart/Reset/Delete button color - Strong red
#define COLOR_BUTTON_RESET_HOVER    "#931f1f"    // [WebColor14] Restart/Reset/Delete button color when hovered over - Dark red
#define COLOR_BUTTON_SAVE           "#47c266"    // [WebColor15] Save button color - Moderate lime green
#define COLOR_BUTTON_SAVE_HOVER     "#5aaf6f"    // [WebColor16] Save button color when hovered over - Dark moderate lime green
#define COLOR_TIMER_TAB_TEXT        "#fff"       // [WebColor17] Config timer tab text color - White
#define COLOR_TIMER_TAB_BACKGROUND  "#999"       // [WebColor18] Config timer tab background color - Dark gray
#define COLOR_TITLE_TEXT            "#000"       // [WebColor19] Title text color - Whiteish
#define COLOR_BUTTON_OFF            "#a1d9f7"    // [WebColor20] Button color when off - Light blue

// Enable also for the ESP8266; by default, it is only enabled for the ESP32
#define USE_IPV6                true
// NOTE: For ESP8266 you need to compile with -DPIO_FRAMEWORK_ARDUINO_LWIP2_IPV6_HIGHER_BANDWIDTH option in platform.ini instead of -DPIO_FRAMEWORK_ARDUINO_LWIP2_HIGHER_BANDWIDTH_LOW_FLASH, and set -DUSE_IPV6.

// MQTT fingerprint auto-learn; so that no certificates can expire
// https://tasmota.github.io/docs/TLS/#option-1-fingerprint-auto-learn
#define MQTT_FINGERPRINT1      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

// Enable TLS for MQTT connection
#ifndef USE_MQTT_TLS 
#define USE_MQTT_TLS                             // Use TLS for MQTT connection (+34.5k code, +7.0k mem and +4.8k additional during connection handshake)
#define MQTT_TLS_ENABLED       true              // [SetOption103] Enable TLS mode (requires TLS version)
#define MQTT_PORT              8883              // [MqttPort] MQTT port (default 8883 for TLS)
#endif

// Ensure that for the environment you have selected, lib/lib_ssl is included on platformio_tasmota_env.ini :~
// lib_extra_dirs          = lib/lib_ssl

// Need to change footer in /tasmota/tasmota_xdrv_driver/xdrv_01_9_webserver.ino
// const char HTTP_END[] PROGMEM =
// ...

// Long strings that can be replaced with sed after compiling
// #define STA_SSID1         "SSIDSTRINGWITH128CHARACTERSSSIDSTRINGWITH128CHARACTERSSSIDSTRINGWITH128CHARACTERSSSIDSTRINGWITH128CHARACTERSSSIDSTRINGWITH128CHA"     // [Ssid1] Wifi SSID
// #define STA_PASS1         "PASSWORDSTRINGWITH128CHARACTERSPASSWORDSTRINGWITH128CHARACTERSPASSWORDSTRINGWITH128CHARACTERSPASSWORDSTRINGWITH128CHARACTERSPASS"     // [Password1] Wifi password
// #define USER_BACKLOG      "WebGetConfig http://myserver:8000/%id%.dmp"
// #define USE_WEBGETCONFIG

/*

Once flashed, use the serial console to:

- Set the WiFi credentials, hostname for mDNS, and enable mDNS
Backlog SSId1 XXXXXXXXX; Password1 XXXXXXXXX; hostname XXXXXXXXX; SetOption55 1

- Set the MQTT credentials
Backlog MqttHost XXXXXXXXX; MqttPort 8883; MqttUser XXXXXXXXX; MqttPassword XXXXXXXXX; SetOption103 1

# The following could then already be done via MQTT

- Set the device name (note that apparently the device name nor the friendly are being advertised via mDNS as of Tasmota 14.4.1)
Backlog DeviceName XXXXXXXXX; FriendlyName XXXXXXXXX

- Set German timezone (could also send this to "tasmotas" group topic so that all devices in the group get the same settings), https://tasmota.github.io/docs/Timezone-Table/
Backlog Timezone 99; TimeStd 0,0,10,1,3,60; TimeDst 0,0,3,1,2,120

I2SWr http://liveradio.swr.de/sw282p3/swr3/play.mp3 ## WORKS!!!! :))) but https does not. maybe due to cert checking
But sounds is crackling, maybe due to buffer size or CPU load?
After a short while, it says OFFLINE over MQTT, but the stream is still playing. And cannot be stopped anymore.

I2SWr http://sc8.radiocaroline.net/; # No issues with this one, which is lower bitrate (32 bit)
I2SWr http://playerservices.streamtheworld.com/api/livestream-redirect/WUAL_HD3.mp3 (96 bit; I think I hear some crackling but not as much as with SWR3)
I2SWr http://iheart.wnyc.org/wnycfm # Completely crashes it
15:11:21.921 I2S: updateClockConfig i2s_channel_disable err=0x0000
15:11:21.923 I2S: updateClockConfig i2s_channel_reconfig_std_clock err=0x0000
15:11:21.925 I2S: updateClockConfig i2s_channel_enable err=0x0000


Sleep 100; CpuFrequency 240; I2SWr http://playerservices.streamtheworld.com/api/livestream-redirect/WUAL_HD3.mp3
*/

#endif  // _USER_CONFIG_OVERRIDE_H_
