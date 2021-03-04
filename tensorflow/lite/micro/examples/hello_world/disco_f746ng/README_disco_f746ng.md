# Hello World Example (中文版 - STM32 DISCO_F746NG)

參考 tensorflow/tensorflow/lite/micro/examples/hello_world/README.md, 擷取並修改 STM32F746 部份內容

This example is designed to demonstrate the absolute basics of using [TensorFlow Lite for Microcontrollers](https://www.tensorflow.org/lite/microcontrollers).
It includes the full end-to-end workflow of training a model, converting it for
use with TensorFlow Lite for Microcontrollers for running inference on a
microcontroller.

The model is trained to replicate a `sine` function and generates a pattern of
data to either blink LEDs or control an animation, depending on the capabilities of the device.

![Animation on STM32F746](../images/animation_on_STM32F746.gif)

## Table of contents

-   [Deploy to STM32F746](#deploy-to-STM32F746)
-   [Run the tests on a development machine](#run-the-tests-on-a-development-machine)
-   [Train your own model](#train-your-own-model)


## Deploy to STM32F746

The following instructions will help you build and deploy the sample to the
[STM32F7 discovery kit](https://os.mbed.com/platforms/ST-Discovery-F746NG/)
using [ARM Mbed](https://github.com/ARMmbed/mbed-cli).

![Animation on STM32F746](../images/animation_on_STM32F746.gif)

我們之前在 Windows 10 上安裝了 VMWare 跟 Ubuntu, 以及相關的套件如下：

- STM32F7 discovery kit board
- Mini-USB cable
- ARM Mbed CLI ([installation instructions](https://os.mbed.com/docs/mbed-os/v5.12/tools/installation-and-setup.html))
- Python 2.7 and pip

接下來, 我們再確定一次是否已經下載 tensorflow

```
$ git clone -b example --depth 1 https://github.com/marconi1964/tensorflow.git

# 說明：
# -b example 下載我修改 tensorflow 後的 example 分支 (branch)
# --depth 1 只下載最新的版本, 不下載歷史修改資料, 以節省下載時間
```

Mbed 針對開發案需要特別的檔案結構安排, 所以需要執行 make 指令來建立子目錄及所需的目錄結構及原始檔案

```
$ cd tensforflow

# 以下是 tensorflow 原始指令, 但是新版已經拿掉 TAGS 參數支援, 以下指令會產生錯誤訊息
$ make -f tensorflow/lite/micro/tools/make/Makefile TARGET=mbed TAGS="CMSIS disco_f746ng" generate_hello_world_mbed_project

# 修改如下, 將 TAGS 參數拿掉, 我自行增加另一個參數 (ARM）來帶入 disco_f746ng 的 lib, 關於 ARM 參數的帶入, 請參考檔案 examples/hello_world/disco_f746ng/Makefile.inc  
$ make -f tensorflow/lite/micro/tools/make/Makefile TARGET=mbed ARM=disco_f746ng generate_hello_world_mbed_project
```

make 指令會建立新的目錄:

```
tensorflow/lite/micro/tools/make/gen/mbed_cortex-m4_default/prj/hello_world/mbed

# 舊版的資料上其中一個目錄 mbed_cortex-m4 已經被 mbed_cortex-m4_default 取代
tensorflow/lite/micro/tools/make/gen/mbed_cortex-m4/prj/hello_world/mbed

```

這目錄下包含所有示範程式的正確檔案結構, 讓 Mbed 可以 'build'

Change into the directory and run the following commands, making sure you are
using Python 2.7.15.

First, tell Mbed that the current directory is the root of an Mbed project:

```
$ cd tensorflow/lite/micro/tools/make/gen/mbed_cortex-m4_default/prj/hello_world/mbed
$ mbed config root .
```

Next, tell Mbed to download the dependencies and prepare to build:

```
$ mbed deploy
```

以下這段已經不適用新版程式, 可以跳過
By default, Mbed will build the project using C++98. However, TensorFlow Lite
requires C++11. Run the following Python snippet to modify the Mbed
configuration files so that it uses C++11:

```
python -c 'import fileinput, glob;
for filename in glob.glob("mbed-os/tools/profiles/*.json"):
  for line in fileinput.input(filename, inplace=True):
    print line.replace("\"-std=gnu++98\"","\"-std=c++11\", \"-fpermissive\"")'

```

最後, 執行以下指令來 compile: 

```
$ mbed compile -m DISCO_F746NG -t GCC_ARM
```

執行 mbed compile 會在以下目錄下產生二進位檔案 mbed.bin:

```
# 在 tensorflow/lite/micro/tools/make/gen/mbed_cortex-m4_default/prj/hello_world/mbed 之下

./BUILD/DISCO_F746NG/GCC_ARM/mbed.bin
```

To deploy, plug in your STM board and copy the file to it. On MacOS, you can do
this with the following command:
或是直接在檔案管理員, 將 mbed.bin 檔案搬到 DIS_F746NG

```
cp ./BUILD/DISCO_F746NG/GCC_ARM/mbed.bin /Volumes/DIS_F746NG/
```

copy 檔案會啟動板子的韌體燒錄, 可以看到板子上的 LED 會紅/綠閃爍. 當燒錄完成後, 可以在 LCD 螢幕上看到程式開始執行的動畫. 

我們不用以下的 screen 這指令, 我們使用 coolterm 這程式, 按 connect 來連結 disco_f746ng 這板子

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

