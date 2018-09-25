#ifndef View_h
#define View_h
#include <LockerCluster.h>
#include <Locker.h>

class TapHandler {
  public:
    virtual void onPressLocker(uint8_t row, uint8_t column);
    virtual void onPressQRCode();
    virtual void onPressClaimLocker();
};

const uint8_t LOCKERS_PAGE = 0;
const uint8_t QRCODE_PAGE = 1;
const uint8_t SUCCESS_PAGE = 2;
const uint8_t INITIAL_PAGE = 3;

class View {
  public:
    View();
    int16_t lcdScreenWidth;
    int16_t lcdScreenHeight;
    uint8_t cameraX = 0;
    uint8_t cameraY = 0;
    void setup();
    void loop();
    void drawLockerCluster(bool clearScreen, LockerCluster *lockerCluster);
    void drawLockerQRCode(Locker *locker);
    void drawInitialPage();
    void drawSuccess();
    void setCameraX(int x);
    void setCameraY(int y);

    void setTapHandler(TapHandler *tapHandler);
    uint8_t getCurrentPage();
  private:
    Locker *_selectedLocker;
    TapHandler *_tapHandler;
    uint8_t _currentPage;

    void handleLockersPageTouch(uint16_t t_x, uint16_t t_y);
    void handleQRCodePageTouch(uint16_t t_x, uint16_t t_y);
    void handleInitialPageTouch(uint16_t t_x, uint16_t t_y);
};
#endif