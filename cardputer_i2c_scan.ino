/**
 * @file ir_nec.ino
 * @author Felix Mann (djflix@gmail.com)
 * @brief M5Cardputer I2C scanner
 * @version 1.0.0
 * @date 2024-05-19
 *
 * @Hardwares: M5Cardputer
 * @Platform Version: Arduino M5Stack Board Manager v2.0.7
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 */
 
#include <Wire.h>
#include "M5Cardputer.h"
#define DEV_COUNT_X_OFFSET 72
#define DEV_COUNT_Y_OFFSET 0
#define ADDRESS_WIDTH_PIXELS 24
#define ADDRESS_Y_OFFSET_PX 10

void setup() {
  auto cfg = M5.config();
  M5.begin();
  Wire.begin(G2, G1);
  M5Cardputer.begin(cfg, true);
  M5Cardputer.Display.setRotation(1);
  M5Cardputer.Display.setTextColor(MAGENTA);
  M5Cardputer.Display.setTextFont(1);
  M5Cardputer.Display.setTextSize(1);
}

struct addrPos {
  int x;
  int y;
};

addrPos getAddressPrintPosition(int deviceCount);

addrPos getAddressPrintPosition(int deviceCount) {
  int x = (ADDRESS_WIDTH_PIXELS * deviceCount) % M5Cardputer.Display.width();
  if (x < ADDRESS_WIDTH_PIXELS) {
    x = 0;
  }
  int y = 10 * (((ADDRESS_WIDTH_PIXELS * deviceCount) - x) / M5Cardputer.Display.width());
  return { x, y + ADDRESS_Y_OFFSET_PX };
};

void loop() {
  M5Cardputer.update();
  int deviceCount = 0;
  delay(2500);

  M5Cardputer.Display.clear();
  M5Cardputer.Display.drawString("I2C Scanner", 0, 0);

  byte error, address;
  for (address = 0x01; address < 0x7f; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      addrPos pos = getAddressPrintPosition(deviceCount++);
      M5Cardputer.Display.drawString(String(address, HEX), pos.x, pos.y);
    }
  }

  M5Cardputer.Display.drawString("total: " + String(deviceCount) + " I2C devices", DEV_COUNT_X_OFFSET, DEV_COUNT_Y_OFFSET);
}