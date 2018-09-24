#include <View.h>
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include "qrcode.h"

#include <LockerCluster.h>

#define M_SIZE 1.3333
#define TFT_GREY 0x5AEB

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library


const int16_t rectWidth = 40;
const int16_t rectHeight = 20;


QRCode qrcode;

const uint8_t QRCODE_SIZE = 200;

void drawQRCode(int32_t x, int32_t y, int32_t s, const char *data, uint32_t color) {
  uint8_t qrcodeData[qrcode_getBufferSize(2)];
  qrcode_initText(&qrcode, qrcodeData, 2, ECC_LOW, data);
  uint8_t moduleSize = s / qrcode.size;

  tft.fillRect(x, y, s, s, TFT_WHITE);
  for (uint8_t i = 0; i < qrcode.size; i++) {
    for (uint8_t j = 0; j < qrcode.size; j++) {
      bool module = qrcode_getModule(&qrcode, i, j);
      if (module) {
        tft.fillRect(
          x + (j * moduleSize),
          y + (i * moduleSize), 
          moduleSize,
          moduleSize, 
          color
        );
      }
    }
  }
}



uint8_t visibleColumns = 2;
uint8_t visibleRows = 2;

void extractViewFromGrid (Locker* grid[10][10], uint8_t columns, uint8_t rows, uint8_t cX, uint8_t cY, Locker* subgrid[10][10]) {
  for (uint8_t i = 0; i < rows; i++) {
    for (uint8_t j = 0; j < columns; j++) {
      subgrid[i][j] = grid[cY + i][cX + j];
    }
  }
}

#define RENDER_CALLBACK_SIGNATURE std::function<void(uint32_t x, uint32_t y, uint32_t w, uint32_t h, Locker *locker)> render

void drawLockerGrid (Locker* grid[10][10], size_t columns, size_t rows, int32_t x, int32_t y, int32_t w, int32_t h, RENDER_CALLBACK_SIGNATURE) {
  int cellWidth = w / columns;
  int cellHeight = h / rows;

  for (uint8_t i = 0; i < rows; i++) {
    for (uint8_t j = 0; j < columns; j++) {
      Locker *locker = grid[i][j];

      render(
        x + (j * cellWidth),
        y + (i * cellHeight),
        cellWidth,
        cellHeight,
        locker
      );
    }
  }
}


uint8_t padding = 10;

void drawLocker (uint32_t x, uint32_t y, uint32_t w, uint32_t h, Locker *locker) {
  tft.fillRect(
    x + padding,
    y + padding,
    w - (padding * 2),
    h - (padding * 2),
    locker->isBusy() ? TFT_GREY: TFT_DARKGREEN
  );

  tft.setCursor(x + (w / 2) - 20, y + (h / 2) - 20);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(4);
  tft.setTextWrap(false);
  tft.print(locker->id);
}

void View::drawLockerCluster() {
  Locker* subgrid[10][10];
  extractViewFromGrid(this->_lockerCluster->lockers, visibleColumns, visibleRows, this->cameraX, this->cameraY, subgrid);
  drawLockerGrid(subgrid, visibleColumns, visibleRows, 0, 0, this->lcdScreenWidth, this->lcdScreenHeight, drawLocker);
}

View::View(LockerCluster *lockerCluster) {
  _lockerCluster = lockerCluster;
}

void View::setCameraX(int x) {
  this->cameraX = x;
  this->drawLockerCluster();
}

void View::setCameraY(int y) {
  this->cameraY = y;
  this->drawLockerCluster();

}
void View::setup() {
  tft.init();
  tft.setRotation(1);
  this->lcdScreenWidth = tft.width();
  this->lcdScreenHeight = tft.height();
  tft.fillScreen(TFT_WHITE);

  // drawLockerCluster(
  //   0,
  //   0,
  //   width,
  //   height
  // );
  // drawQRCode(
  //   (width / 2) - (QRCODE_SIZE / 2),
  //   (height / 2) - (QRCODE_SIZE / 2),
  //   QRCODE_SIZE,
  //   "cjmdtr3q3000s0a5842xwqcy1",
  //   TFT_BLACK
  // );
}