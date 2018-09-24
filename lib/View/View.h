#ifndef View_h
#define View_h
#include <LockerCluster.h>
class View {
  public:
    View();
    int16_t lcdScreenWidth;
    int16_t lcdScreenHeight;
    void setup();
};
void drawLockerCluster(LockerCluster *lockerCluster, uint32_t x, uint32_t y, uint32_t w, uint32_t h);

#endif