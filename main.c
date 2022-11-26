int main() {

  // オンチップLEDを2回点滅
  const uint LED_PIN = PICO_DEFAULT_LED_PIN;
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  gpio_put(LED_PIN, 1);
  sleep_ms(250);
  gpio_put(LED_PIN, 0);
  sleep_ms(250);
  gpio_put(LED_PIN, 1);
  sleep_ms(250);
  gpio_put(LED_PIN, 0);
  sleep_ms(250);

  // 8x8 matrix LED x 2個
  gpio_init(CS);
  gpio_set_dir(CS, GPIO_OUT);
  gpio_put(CS, 1);

  spi_init(SPI_PORT, 1000 * 1000);

  spi_set_format(SPI_PORT,
    8,
    1,
    1,
    SPI_MSB_FIRST);

  gpio_set_function(SCK, GPIO_FUNC_SPI);
  gpio_set_function(MOSI, GPIO_FUNC_SPI);
  
  sleep_ms(10);

  max7219_write(REG_DIGIT0, 0x00);
  max7219_write(REG_DIGIT1, 0x00);
  max7219_write(REG_DIGIT2, 0x00);
  max7219_write(REG_DIGIT3, 0x00);
  max7219_write(REG_DIGIT4, 0x00);
  max7219_write(REG_DIGIT5, 0x00);
  max7219_write(REG_DIGIT6, 0x00);
  max7219_write(REG_DIGIT7, 0x00);

  max7219_write(REG_DECODE_MODE,  0x00);
  max7219_write(REG_INTENSITY,    0x04);
  max7219_write(REG_SCAN_LIMIT,   0x07);
  max7219_write(REG_SHUTDOWN,     0x01);
  max7219_write(REG_DISPLAY_TEST, 0x00);

  sleep_ms(10);

  while (true) {
    display_eye_pattern(eyes_sleep, sizeof(eyes_sleep));
    sleep_ms(100);
    display_eye_pattern(eyes_open, sizeof(eyes_open));
    sleep_ms(100);
    display_eye_pattern(eyes_C,  sizeof(eyes_C));
    sleep_ms(100);
    display_eye_pattern(eyes_CL, sizeof(eyes_CL));
    sleep_ms(100);
    display_eye_pattern(eyes_L,  sizeof(eyes_L));
    sleep_ms(100);
    display_eye_pattern(eyes_LL, sizeof(eyes_LL));
    sleep_ms(100);
    display_eye_pattern(eyes_L,  sizeof(eyes_L));
    sleep_ms(100);
    display_eye_pattern(eyes_CL, sizeof(eyes_CL));
    sleep_ms(100);
    display_eye_pattern(eyes_C,  sizeof(eyes_C));
    sleep_ms(100);
    display_eye_pattern(eyes_CR, sizeof(eyes_CR));
    sleep_ms(100);
    display_eye_pattern(eyes_R,  sizeof(eyes_R));
    sleep_ms(100);
    display_eye_pattern(eyes_RR, sizeof(eyes_RR));
    sleep_ms(100);
    display_eye_pattern(eyes_R,  sizeof(eyes_R));
    sleep_ms(100);
    display_eye_pattern(eyes_CR, sizeof(eyes_CR));
    sleep_ms(100);
    display_eye_pattern(eyes_C,  sizeof(eyes_C));
    sleep_ms(100);
    display_eye_pattern(eyes_close, sizeof(eyes_close));
  }
}

