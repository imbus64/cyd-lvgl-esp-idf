# CYD-LVGL-esp-idf

Cheap Yellow Display (ESP32-2432S028R)

- ESP-WROOM-32 [datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32e_esp32-wroom-32ue_datasheet_en.pdf)
- Uses ILI9341 display [datasheet](https://cdn-shop.adafruit.com/datasheets/ILI9341.pdf)

# Building

1. Install the ESP-IDF toolchain (See: [Toolchain section](#toolchain]))
2. Source the environment `source ~/esp/esp-idf/export.sh`
3. idf.py build
4. idf.py flash

## Toolchain

See: [Standard Toolchain Setup for Linux](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/linux-macos-setup.html)

From the official docs, essentially:
```sh
mkdir -p ~/esp
cd ~/esp
git clone -b v5.4.2 --recursive https://github.com/espressif/esp-idf.git
cd ~/esp/esp-idf
./install.sh esp32 # This is the arch for our mcu (esp-wroom-32)
```

## Help and Resources

- Espressif docs on the ESP-IDF build system: [Build System](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/build-system.html)
- Dependencies/packages found here: [ESP Registry](https://components.espressif.com/)
- Custon FreeRTOS to better facilitate the ESP: [ESP-IDF FreeRTOS](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/system/freertos.html)
- Vanilla FreeRTOS docs [FreeRTOS Documentation](https://www.freertos.org/Documentation/00-Overview)
- LVGL docs: [LVGL](https://docs.lvgl.io/master/index.html)

- https://components.espressif.com/components/atanisoft/esp_lcd_touch_xpt2046/versions/1.0.6
- https://components.espressif.com/components/espressif/esp_lcd_ili9341/versions/2.0.0
- https://components.espressif.com/components/lvgl/lvgl_esp32_drivers/versions/0.0.3

---
