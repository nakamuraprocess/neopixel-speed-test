# neopixel-speed-test

## Raspberry Pi 4

### 仮想環境の作成
```
python3 -m venv .venv
```
### 仮想環境の実行
```
source .venv/bin/activate
```
### パッケージインストール
```
pip install rpi_ws281x
```
### 仮想環境の終了
```
deactivate
```
### 実行
```
sudo .venv/bin/python3 speed_test_single.py
```
```
sudo .venv/bin/python3 speed_test_multi.py
```
### 使用PIN
```
strip_1 DIN = GPIO18
strip_2 DIN = GPIO21
```

## Raspberry Pi 5

### 仮想環境の作成
```
python3 -m venv .venv
```
### 仮想環境の実行
```
source .venv/bin/activate
```
### パッケージインストール
```
pip install rpi5-ws2812
```
### 仮想環境の終了
```
deactivate
```
### 実行
```
sudo .venv/bin/python3 speed_test_single.py
```
```
sudo .venv/bin/python3 speed_test_multi.py
```
### 使用PIN
```
strip_1 DIN = GPIO10 (19)
strip_2 DIN = GPIO20 (38) 
```

#### ※2チャンネルのLEDストリップを使う場合は下記を追記
```
sudo nano /boot/firmware/config.txt
```
```
dtoverlay=spi0-1cs
dtoverlay=spi1-1cs
```

#### ※NumPyが見つからないエラーが出る場合
```
sudo apt update
```
```
sudo apt install libopenblas-dev
```

## Raspberry Pi Pico / Pico 2
1. Arduino IDE に Raspberry Pi Pico（RP2040）を追加
* Arduino IDE を開き、ファイル → 環境設定を開く。
* 「追加のボードマネージャURL」に以下を追加：
```
https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
```
2. ボードをインストール
* ツール → ボード → ボードマネージャ
* 検索欄で「rp2040」または「pico」
* 「Raspberry Pi Pico/RP2040 by Earle Philhower」をインストール
3. Adafruit NeoPixel ライブラリをインストール
* スケッチ → ライブラリをインクルード → ライブラリを管理
* 「Adafruit NeoPixel」で検索
* インストール

### 実行
```
speed_test_single.ino
```
```
speed_test_multi.ino
```
### 使用PIN
```
strip_1 DIN = GPIO2
strip_2 DIN = GPIO3
```
## Freenove ESP32 WROOM

1. Arduino IDE に ESP32 ボードを追加
* Arduino IDE を開き、ファイル → 環境設定を開く。
* 「追加のボードマネージャURL」に以下を追加：
```
https://dl.espressif.com/dl/package_esp32_index.json
```
2. ボードをインストール
* ツール → ボード → ボードマネージャ
* 検索欄で「esp32 dev module」
* 「ESP32 Dev Module」をインストール
3. Adafruit NeoPixel ライブラリをインストール
* スケッチ → ライブラリをインクルード → ライブラリを管理
* 「Adafruit NeoPixel」で検索
* インストール
### 実行
```
speed_test_single.ino
```
```
speed_test_multi.ino
```
### 使用PIN
```
strip_1 DIN = GPIO5
strip_2 DIN = GPIO15
```
## PJRC Teensy 4.0

1. Arduino IDE に Teensy ボードを追加
* Arduino IDE を開き、ファイル → 環境設定を開く。
* 「追加のボードマネージャURL」に以下を追加：
```
https://www.pjrc.com/teensy/package_teensy_index.json
```
2. ボードをインストール
* ツール → ボード → ボードマネージャ
* 検索欄で「teensy 4.0」
* 「Teensy 4.0」をインストール
3. Teensy for Arduinoをインストール
* ボードマネージャで
* 「teensy」で検索
* 「Teensy(for Arduino IDE 2.0.4 or later)」をインストール
4. Adafruit NeoPixel ライブラリをインストール
* スケッチ → ライブラリをインクルード → ライブラリを管理
* 「Adafruit NeoPixel」で検索
* インストール
### 実行
```
speed_test_single.ino
```
```
speed_test_multi.ino
```
### 使用PIN
```
strip_1 DIN = GPIO1
strip_2 DIN = GPIO6
```
## 速度計測結果

|               | Pi 4   | Pi 5   | Pico   | Pico 2 | ESP32  | T 4.0  | T 4.1 |
|---------------|--------|--------|--------|--------|--------|--------|-------|
| 1 strip (sec) | 0.58s  | 0.47s  | 0.55s  | 0.55s  | 0.48s  | 0.56s  |-------|
| 2 strip (sec) | 1.13s  | 0.47s  | 0.55s  | 0.55s  | 1.21s  | 1.75s  |-------|
|  price (yen)  | 10,980 | 12,900 | 1,470  | 2,080  | 1,680  | 6,980  | 8,604 |

#### ※T = Teensy
#### ※priceはAmazonでの実売価格（2025年11月）