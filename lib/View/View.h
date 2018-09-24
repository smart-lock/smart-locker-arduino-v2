#ifndef View_h
#define View_h
#include <LockerCluster.h>
class View {
  public:
    View(LockerCluster *lockerCluster);
    int16_t lcdScreenWidth;
    int16_t lcdScreenHeight;
    uint8_t cameraX = 0;
    uint8_t cameraY = 0;
    void setup();
    void drawLockerCluster();
    void setCameraX(int x);
    void setCameraY(int y);
  private:
    LockerCluster *_lockerCluster;
};

#endif