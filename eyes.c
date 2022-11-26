#include "pico/stdlib.h"
#include <hardware/spi.h>

#include "eyes.h"

const uint MOSI_PIN = 19;
const uint SCK_PIN  = 18;
const uint CS_PIN   = 17;

#define SPI_PORT spi0

const int CHAIN_LEN = 2;

static inline void cs_select() {
  asm volatile("nop \n nop \n nop");
  gpio_put(CS_PIN, 0);
  asm volatile("nop \n nop \n nop");
  // Active low
}

static inline void cs_deselect() {
  asm volatile("nop \n nop \n nop");
  gpio_put(CS_PIN, 1);
  asm volatile("nop \n nop \n nop");
}

static void max7219_write(uint8_t reg, uint8_t data) {
  int i;
  uint8_t buf[2];

  buf[0] = 0x00 | reg;
  buf[1] = data;

  cs_select();
  for (i = 0; i < CHAIN_LEN; i++) {
    spi_write_blocking(SPI_PORT, buf, 2);
  }
  cs_deselect();
}

void display_eye_pattern(const uint8_t* pattern, int size) {

  for (int i = 0; i < size / 8; i++) {
    uint8_t addr = 0x01;
    for (int j = 0; j < 8; j++) {
      max7219_write(addr, pattern[i * 8 + j]);
      addr++;
    }
    sleep_ms(10);
  }
}

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
  gpio_init(CS_PIN);
  gpio_set_dir(CS_PIN, GPIO_OUT);
  gpio_put(CS_PIN, 1);

  spi_init(SPI_PORT, 1000 * 1000);

  spi_set_format(SPI_PORT,
    8,
    1,
    1,
    SPI_MSB_FIRST);

  gpio_set_function(SCK_PIN,  GPIO_FUNC_SPI);
  gpio_set_function(MOSI_PIN, GPIO_FUNC_SPI);
  
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

  display_eye_pattern(eyes_sleep, sizeof(eyes_sleep));
  sleep_ms(1000);
  while (true) {
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
    sleep_ms(100);
  }
}
