# Settings for the Discovery STM32F746NG board.
#ifeq ($(TARGET),$(filter $(TARGET),disco_f746ng))   # original
ifneq ($(filter $(ARM), disco_f746ng),)

  micro_speech_MBED_PROJECT_FILES += \
    AUDIO_DISCO_F746NG.lib \
    BSP_DISCO_F746NG.lib \
    SDRAM_DISCO_F746NG.lib \
    LCD_DISCO_F746NG.lib

endif
