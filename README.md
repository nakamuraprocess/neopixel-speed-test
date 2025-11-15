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

## Raspberry Pi Pico

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

## Freenove ESP32 WROOM

Please wait...