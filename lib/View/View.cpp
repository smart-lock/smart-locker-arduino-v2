#include <View.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "qrcode.h"
#include <LockerCluster.h>
#include "FS.h"


#define TFT_GREY 0x5AEB


TFT_eSPI tft = TFT_eSPI();       // Invoke custom library


QRCode qrcode;
const uint8_t QRCODE_SIZE = 200;
const uint8_t visibleColumns = 2;
const uint8_t visibleRows = 2;

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
  tft.print(locker->idInCluster);
}

View::View() {
  _tapHandler = NULL;
}

void View::drawLockerCluster(bool clearScreen, LockerCluster *lockerCluster) {
  _currentPage = LOCKERS_PAGE;
  if (clearScreen) {
    tft.fillScreen(TFT_WHITE);
  }

  Locker* subgrid[10][10];
  extractViewFromGrid(lockerCluster->lockers, visibleColumns, visibleRows, this->cameraX, this->cameraY, subgrid);
  drawLockerGrid(subgrid, visibleColumns, visibleRows, 0, 0, this->lcdScreenWidth, this->lcdScreenHeight, drawLocker);
}

void View::drawLockerQRCode(Locker *locker) {
  _currentPage = QRCODE_PAGE;
  tft.fillScreen(TFT_WHITE);
  drawQRCode(
    (this->lcdScreenWidth / 2) - (QRCODE_SIZE / 2),
    (this->lcdScreenHeight / 2) - (QRCODE_SIZE / 2),
    QRCODE_SIZE,
    locker->idAsString.c_str(),
    TFT_BLACK
  );
}


void View::drawSuccess() {
  _currentPage = SUCCESS_PAGE;
  tft.fillScreen(TFT_DARKGREEN);
  tft.setCursor((this->lcdScreenWidth / 2) - 25, (this->lcdScreenHeight / 2) - 25);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(5);
  tft.setTextWrap(false);
  tft.print("OK !");
}

void View::setCameraX(int x) {
  this->cameraX = x;
}

void View::setCameraY(int y) {
  this->cameraY = y;
}

void View::setup() {
  tft.init();
  tft.setRotation(1);
  this->lcdScreenWidth = tft.width();
  this->lcdScreenHeight = tft.height();
}

TFT_eSPI_Button key[15];

void View::setTapHandler(TapHandler *tapHandler) {
  _tapHandler = tapHandler;
}

void View::handleLockersPageTouch(uint16_t t_x, uint16_t t_y) {
  bool left = t_x < this->lcdScreenWidth / 2;
  bool top = t_y < this->lcdScreenHeight / 2;
  uint8_t xOffset = !left;
  uint8_t yOffset = !top;
  _tapHandler->onPressLocker(this->cameraX + xOffset, this->cameraY + yOffset);
}

void View::handleQRCodePageTouch(uint16_t t_x, uint16_t t_y) {
  _tapHandler->onPressQRCode();
}
void View::loop() {
  uint16_t t_x = 0, t_y = 0; // To store the touch coordinates

  // Pressed will be set true is there is a valid touch on the screen
  if (_tapHandler == NULL) {
    return;
  }

  if (tft.getTouch(&t_x, &t_y)) {
    Serial.println(String(t_x) + ", " + String(t_y));
    switch (_currentPage) {
      case INITIAL_PAGE:
        this->handleInitialPageTouch(t_x, t_y);
        break;
      case LOCKERS_PAGE: 
        this->handleLockersPageTouch(t_x, t_y);
        break;
      case QRCODE_PAGE:
        this->handleQRCodePageTouch(t_x, t_y);
        break;
    }  
  }
}

void View::handleInitialPageTouch(uint16_t t_x, uint16_t t_y) {
  _tapHandler->onPressClaimLocker();
}


const uint16_t characterWidth = 5;
const uint16_t characterHeight = 5;
void drawCenteredText(int16_t x, int16_t y, int16_t color, uint8_t size, const char *s) {
  uint16_t textWidth = size * strlen(s) * characterWidth;
  uint16_t textHeight = characterHeight * size;

  tft.setCursor(x - textWidth / 2, y - textHeight / 2);
  tft.setTextColor(color);
  tft.setTextSize(size);
  tft.setTextWrap(false);
  tft.print("ALUGAR");
}

void View::drawInitialPage() {
  _currentPage = INITIAL_PAGE;
  tft.fillScreen(TFT_ORANGE);
  drawCenteredText(this->lcdScreenWidth / 2, this->lcdScreenHeight / 2, TFT_WHITE, 5, "ALUGAR");
}

uint8_t View::getCurrentPage() {
  return this->_currentPage;
}