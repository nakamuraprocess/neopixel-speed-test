from rpi_ws281x import *
import threading
import time

# LED strip configuration:
LED_MAX_SIZE      = 120      # Number of LED pixels.
LED_PIN_1       = 18      # GPIO pin connected to the pixels (18 uses PWM!).
LED_PIN_2       = 21      # GPIO pin connected to the pixels (10 uses SPI /dev/spidev0.0).
LED_FREQ_HZ    = 800000  # LED signal frequency in hertz (usually 800khz)
LED_DMA        = 10      # DMA channel to use for generating signal (try 10)
LED_BRIGHTNESS = 65     # Set to 0 for darkest and 255 for brightest
LED_INVERT     = False   # True to invert the signal (when using NPN transistor level shift)
LED_CHANNEL    = 0      # set to '1' for GPIOs 13, 19, 41, 45 or 53

COLOR_BASE = Color(255, 255, 255)
COLOR_NONE = Color(0, 0, 0)

thread_1_loop = True
thread_2_loop = True

def color_wipe_forward(strip):
    for i in range(LED_MAX_SIZE):
        if i == 0:
            strip.setPixelColor(LED_MAX_SIZE-1, COLOR_NONE)
        else:
            strip.setPixelColor(i-1, COLOR_NONE)
        strip.setPixelColor(i, COLOR_BASE)
        strip.show()

def color_wipe_reverse(strip):
    for i in reversed(range(LED_MAX_SIZE)):
        if i == LED_MAX_SIZE-1:
            strip.setPixelColor(0, COLOR_NONE)
        else:
            strip.setPixelColor(i+1, COLOR_NONE)
        strip.setPixelColor(i, COLOR_BASE)
        strip.show()
    
def color_wipe_all(strip):
    for i in range(LED_MAX_SIZE):
        strip.setPixelColor(i, COLOR_NONE)
    strip.show()

def thread_strip_1():
    while thread_1_loop:
        color_wipe_forward(strip_1)
        color_wipe_reverse(strip_1)

def thread_strip_2():
    while thread_2_loop:
        color_wipe_forward(strip_2)
        color_wipe_reverse(strip_2)

if __name__ == '__main__':
    strip_1 = Adafruit_NeoPixel(LED_MAX_SIZE, LED_PIN_1, LED_FREQ_HZ, LED_DMA, LED_INVERT, LED_BRIGHTNESS, LED_CHANNEL)
    strip_1.begin()

    strip_2 = Adafruit_NeoPixel(LED_MAX_SIZE, LED_PIN_2, LED_FREQ_HZ, LED_DMA, LED_INVERT, LED_BRIGHTNESS, LED_CHANNEL)
    strip_2.begin()

    thread_1 = threading.Thread(target=thread_strip_1)
    thread_2 = threading.Thread(target=thread_strip_2)
    thread_1.start()
    thread_2.start()

    try:
        while True:
            time.sleep(1)
    
    except KeyboardInterrupt:
        print(">>> Ctrl + C detected! Stopping...")

    finally:
        print("Finaly")
        thread_1_loop = False
        thread_2_loop = False
        thread_1.join()
        thread_2.join()
        color_wipe_all(strip_1)
        color_wipe_all(strip_2)
