from rpi5_ws2812.ws2812 import Color, WS2812SpiDriver

LED_MAX_SIZE = 120
COLOR_BASE = Color(255, 255, 255)
COLOR_NONE = Color(0, 0, 0)

def color_wipe_forward(strip, color):
    for i in range(LED_MAX_SIZE):
        if i == 0:
            strip.set_pixel_color(LED_MAX_SIZE-1, COLOR_NONE)
        else:
            strip.set_pixel_color(i-1, COLOR_NONE)
        strip.set_pixel_color(i, color)
        strip.show()

def color_wipe_reverse(strip, color):
    for i in reversed(range(LED_MAX_SIZE)):
        if i == LED_MAX_SIZE-1:
            strip.set_pixel_color(0, COLOR_NONE)
        else:
            strip.set_pixel_color(i+1, COLOR_NONE)
        strip.set_pixel_color(i, color)
        strip.show()

if __name__ == "__main__":
    strip = WS2812SpiDriver(spi_bus=0, spi_device=0, led_count=LED_MAX_SIZE).get_strip()

    try:
        while True:
            color_wipe_forward(strip, COLOR_BASE)
            color_wipe_reverse(strip, COLOR_BASE)

    finally:
        strip.clear()
        strip.show()
