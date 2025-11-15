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
strip_1 DIN = GPIO10 (19)
strip_2 DIN = GPIO20 (38) 

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

### OSとパッケージインストール

1. CircuitPython for Raspberry Pi Picoをダウンロード
```
https://circuitpython.org/board/raspberry_pi_pico/
```
2. BOOTSEL で接続し、.uf2ファイルをドラッグしてインストール
3. 自動的に CIRCUITPY ドライブがマウントされる
4. adafruit-circuitpython-bundle をダウンロード（バージョンはCircuitPythonと合わせる）
```
https://circuitpython.org/libraries
```
5. /CIRCUITPY/lib に neopixel.mpy をコピー
6. 実行ソースコードは /CIRCUITPY/code.py に書いて保存

## Freenove ESP32 WROOM

Please wait...