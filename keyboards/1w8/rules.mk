# Build Options
#   change yes to no to disable
#
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
CUSTOM_MATRIX = lite
LTO_ENABLE = no

SRC += matrix.c
I2C_DRIVER_REQUIRED = no
