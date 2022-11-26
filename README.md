# pico_max7219

## 概要
Raspberry Pi Picoと8x8 matrix LED(MAX7219)を2つを接続して点灯させる

## 使用環境
Raspberry Pi Pico C/C++ SDK

[参考URL](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html)

## 接続
|Picoピン名|Picoピン番号|MAX7219|
|---|---|---|
|3V3|36|Vcc|
|GND|38|GND|
|SPI0 CSn|22|CS|
|SPI0 SCK|24|CLK|
|SPI0 TX|25|DIN|

## 使い方
1. ソースをクローンしたディレクトリに行く
2. 以下実行
```
mkdir build
cd build
cmake ..
make
```
eyes.uf2をPicoに書く
