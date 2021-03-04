<!-- mdformat off(b/169948621#comment2) -->

# Hello World Example

Reference from tensorflow/tensorflow/lite/micro/examples/hello_world/README.md

This example is designed to demonstrate the absolute basics of using [TensorFlow
Lite for Microcontrollers](https://www.tensorflow.org/lite/microcontrollers).
It includes the full end-to-end workflow of training a model, converting it for
use with TensorFlow Lite for Microcontrollers for running inference on a
microcontroller.

The model is trained to replicate a `sine` function and generates a pattern of
data to either blink LEDs or control an animation, depending on the capabilities
of the device.

![Animation on STM32F746](../images/animation_on_STM32F746.gif)

## Table of contents

-   [Deploy to STM32F746](#deploy-to-STM32F746)
-   [Run the tests on a development machine](#run-the-tests-on-a-development-machine)
-   [Train your own model](#train-your-own-model)


## Deploy to STM32F746

The following instructions will help you build and deploy the sample to the
[STM32F7 discovery kit](https://os.mbed.com/platforms/ST-Discovery-F746NG/)
using [ARM Mbed](https://github.com/ARMmbed/mbed-cli).

![Animation on STM32F746](images/animation_on_STM32F746.gif)

Before we begin, you'll need the following:

- STM32F7 discovery kit board
- Mini-USB cable
- ARM Mbed CLI ([installation instructions](https://os.mbed.com/docs/mbed-os/v5.12/tools/installation-and-setup.html))
- Python 2.7 and pip

Since Mbed requires a special folder structure for projects, we'll first run a
command to generate a subfolder containing the required source files in this
structure:

```
make -f tensorflow/lite/micro/tools/make/Makefile TARGET=mbed TAGS="CMSIS disco_f746ng" generate_hello_world_mbed_project
```

This will result in the creation of a new folder:

```
tensorflow/lite/micro/tools/make/gen/mbed_cortex-m4/prj/hello_world/mbed
```

This folder contains all of the example's dependencies structured in the correct
way for Mbed to be able to build it.

Change into the directory and run the following commands, making sure you are
using Python 2.7.15.

First, tell Mbed that the current directory is the root of an Mbed project:

```
mbed config root .
```

Next, tell Mbed to download the dependencies and prepare to build:

```
mbed deploy
```

By default, Mbed will build the project using C++98. However, TensorFlow Lite
requires C++11. Run the following Python snippet to modify the Mbed
configuration files so that it uses C++11:

```
python -c 'import fileinput, glob;
for filename in glob.glob("mbed-os/tools/profiles/*.json"):
  for line in fileinput.input(filename, inplace=True):
    print line.replace("\"-std=gnu++98\"","\"-std=c++11\", \"-fpermissive\"")'

```

Finally, run the following command to compile:

```
mbed compile -m DISCO_F746NG -t GCC_ARM
```

This should result in a binary at the following path:

```
./BUILD/DISCO_F746NG/GCC_ARM/mbed.bin
```

To deploy, plug in your STM board and copy the file to it. On MacOS, you can do
this with the following command:

```
cp ./BUILD/DISCO_F746NG/GCC_ARM/mbed.bin /Volumes/DIS_F746NG/
```

Copying the file will initiate the flashing process. Once this is complete, you
should see an animation on the device's screen.


```
screen /dev/tty.usbmodem14403 9600
```

In addition to this animation, debug information is logged by the board while
the program is running. To view it, establish a serial connection to the board
using a baud rate of `9600`. On OSX and Linux, the following command should
work, replacing `/dev/tty.devicename` with the name of your device as it appears
in `/dev`:

```
screen /dev/tty.devicename 9600
```

You will see a lot of output flying past! To stop the scrolling, hit `Ctrl+A`,
immediately followed by `Esc`. You can then use the arrow keys to explore the
output, which will contain the results of running inference on various `x`
values:

```
x_value: 1.1843798*2^2, y_value: -1.9542645*2^-1
```

To stop viewing the debug output with `screen`, hit `Ctrl+A`, immediately
followed by the `K` key, then hit the `Y` key.

## Run the tests on a development machine

To compile and test this example on a desktop Linux or macOS machine, first
clone the TensorFlow repository from GitHub to a convenient place:

```bash
git clone --depth 1 https://github.com/tensorflow/tensorflow.git
```

Next, `cd` into the source directory from a terminal, and then run the following
command:

```bash
make -f tensorflow/lite/micro/tools/make/Makefile test_hello_world_test
```

This will take a few minutes, and downloads frameworks the code uses. Once the
process has finished, you should see a series of files get compiled, followed by
some logging output from a test, which should conclude with
`~~~ALL TESTS PASSED~~~`.

If you see this, it means that a small program has been built and run that loads
the trained TensorFlow model, runs some example inputs through it, and got the
expected outputs.

To understand how TensorFlow Lite does this, you can look at the source in
[hello_world_test.cc](hello_world_test.cc).
It's a fairly small amount of code that creates an interpreter, gets a handle to
a model that's been compiled into the program, and then invokes the interpreter
with the model and sample inputs.

## Train your own model

So far you have used an existing trained model to run inference on
microcontrollers. If you wish to train your own model, follow the instructions
given in the [train/](train/) directory.

