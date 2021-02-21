# Settings for the Discovery STM32F746NG board.
ifeq ($(TARGET),$(filter $(TARGET),disco_f746ng))

  micro_speech_MBED_PROJECT_FILES += \
    AUDIO_DISCO_F746NG.lib \
    BSP_DISCO_F746NG.lib \
    SDRAM_DISCO_F746NG.lib \
    LCD_DISCO_F746NG.lib
  MICRO_SPEECH_SRCS += \
	tensorflow/lite/micro/examples/micro_speech/mbed/audio_provider.cc \
	tensorflow/lite/micro/examples/micro_speech/mbed/command_responder.cc \
	tensorflow/lite/micro/examples/micro_speech/mbed/timer.cc

endif
