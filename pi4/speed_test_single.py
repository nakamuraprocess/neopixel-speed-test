from rpi_ws281x import *
import time

# LED strip configuration:
LED_MAX_SIZE   = 120     # Number of LED pixels.
LED_PIN        = 18      # GPIO pin connected to the pixels (18 uses PWM!).
#LED_PIN        = 10     # GPIO pin connected to the pixels (10 uses SPI /dev/spidev0.0).
LED_FREQ_HZ    = 800000  # LED signal frequency in hertz (usually 800khz)
LED_DMA        = 10      # DMA channel to use for generating signal (try 10)
LED_BRIGHTNESS = 255     # Set to 0 for darkest and 255 for brightest
LED_INVERT     = False   # True to invert the signal (when using NPN transistor level shift)
LED_CHANNEL    = 0       # set to '1' for GPIOs 13, 19, 41, 45 or 53

COLOR_BASE = Color(255, 255, 255)
COLOR_NONE = Color(0, 0, 0)

time_start = 0.0
time_finish = 0.0

def color_wipe_forward(strip):
    global time_start
    for i in range(LED_MAX_SIZE):
        if i == 0:
            time_start = time.perf_counter()
            strip.setPixelColor(LED_MAX_SIZE-1, COLOR_NONE)
        else:
            strip.setPixelColor(i-1, COLOR_NONE)
        strip.setPixelColor(i, COLOR_BASE)
        strip.show()

def color_wipe_reverse(strip):
    global time_finish
    for i in reversed(range(LED_MAX_SIZE)):
        if i == LED_MAX_SIZE-1:
            time_finish = time.perf_counter()
            strip.setPixelColor(0, COLOR_NONE)
        else:
            strip.setPixelColor(i+1, COLOR_NONE)
        strip.setPixelColor(i, COLOR_BASE)
        strip.show()
    
def color_wipe_all(strip):
    for i in range(LED_MAX_SIZE):
        strip.setPixelColor(i, COLOR_NONE)
    strip.show()

if __name__ == '__main__':
    strip = Adafruit_NeoPixel(LED_MAX_SIZE, LED_PIN, LED_FREQ_HZ, LED_DMA, LED_INVERT, LED_BRIGHTNESS, LED_CHANNEL)
    strip.begin()

    try:
        color_wipe_forward(strip)
        color_wipe_reverse(strip)

    finally:
        print("FINALLY")
        color_wipe_all(strip)
        print(f"TIME: {time_finish - time_start} sec")
