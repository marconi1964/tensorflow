/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "tensorflow/lite/micro/examples/hello_world/output_handler.h"
#include "tensorflow/lite/micro/examples/hello_world/constants.h"

// added by Marconi
#include "mbed.h"

// Track whether the function has run at least once
bool initialized = false;
int counter = 0;
int led_status = 0;

// Animates a dot across the screen to represent the current x and y values
void HandleOutput(tflite::ErrorReporter* error_reporter, float x_value,
                  float y_value) {
  // Do this only once
  if (!initialized) {
    PwmOut LED_PWM(PB_4);
    LED_PWM.period(1);
    LED_PWM.write(0);
    initialized = true;
  }

  // Log the current X and Y values
  TF_LITE_REPORT_ERROR(error_reporter, "x_value: %f, y_value: %f\n", x_value,
                       y_value);

  if (counter < 10000) {
    counter++;
    LED_PWM.write(led_status)
  //  LED_PWM.write((y_value+1.0)/2.0);
  } else {
    counter = 0;
    led_status = 1 - led_status;
  }

  TF_LITE_REPORT_ERROR(error_reporter, "counter : %d, led_status: %d\n", counter,
                       led_status);

}
