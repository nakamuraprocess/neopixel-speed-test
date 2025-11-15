from rpi5_ws2812.ws2812 import Color, WS2812SpiDriver
import threading
import time

LED_MAX_SIZE = 120
COLOR_BASE = Color(255, 255, 255)
COLOR_NONE = Color(0, 0, 0)

thread_1_loop = True
thread_2_loop = True

def color_wipe_forward(strip):
    for i in range(LED_MAX_SIZE):
        if i == 0:
            strip.set_pixel_color(LED_MAX_SIZE-1, COLOR_NONE)
        else:
            strip.set_pixel_color(i-1, COLOR_NONE)
        strip.set_pixel_color(i, COLOR_BASE)
        strip.show()

def color_wipe_reverse(strip):
    for i in reversed(range(LED_MAX_SIZE)):
        if i == LED_MAX_SIZE-1:
            strip.set_pixel_color(0, COLOR_NONE)
        else:
            strip.set_pixel_color(i+1, COLOR_NONE)
        strip.set_pixel_color(i, COLOR_BASE)
        strip.show()

def thread_strip_1():
    while thread_1_loop:
        color_wipe_forward(strip_1)
        color_wipe_reverse(strip_1)

def thread_strip_2():
    while thread_2_loop:
        color_wipe_forward(strip_2)
        color_wipe_reverse(strip_2)

if __name__ == "__main__":
    strip_1 = WS2812SpiDriver(spi_bus=0, spi_device=0, led_count=LED_MAX_SIZE).get_strip()
    strip_2 = WS2812SpiDriver(spi_bus=1, spi_device=0, led_count=LED_MAX_SIZE).get_strip()

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
        strip_1.clear()
        strip_1.show()
        strip_2.clear()
        strip_2.show()