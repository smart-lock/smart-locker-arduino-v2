#ifndef View_h
#define View_h
#include <LockerCluster.h>
class View {
  public:
    View();
    int16_t lcdScreenWidth;
    int16_t lcdScreenHeight;
    uint8_t cameraX = 0;
    uint8_t cameraY = 0;
    void setup();
    void drawLockerCluster(bool clearScreen, LockerCluster *lockerCluster);
    void drawLockerQRCode(Locker *locker);
    void drawSuccess();
    void setCameraX(int x);
    void setCameraY(int y);

    void selectLocker(Locker* locker);
  private:
    LockerCluster *_lockerCluster;
    Locker *_selectedLocker;
};

#endif