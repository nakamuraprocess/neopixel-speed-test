import time
import board
import neopixel

LED_MAX_SIZE = 120
COLOR_BASE = (255, 255, 255)
COLOR_NONE = (0, 0, 0)

pixels = neopixel.NeoPixel(board.GP0, LED_MAX_SIZE, brightness=0.3, auto_write=False)

def color_wipe_forward(pixels):
    for i in range(LED_MAX_SIZE):
        if i == 0:
            pixels[LED_MAX_SIZE-1] = COLOR_NONE
        else:
            pixels[i-1] = COLOR_NONE
        pixels[i] = COLOR_BASE
        pixels.show()

def color_wipe_reverse(strip):
    for i in reversed(range(LED_MAX_SIZE)):
        if i == LED_MAX_SIZE-1:
            pixels[0] = COLOR_NONE
        else:
            pixels[i+1] = COLOR_NONE
        pixels[i] = COLOR_BASE
        pixels.show()

while True:
    color_wipe_forward(pixels)
    color_wipe_reverse(pixels)
    