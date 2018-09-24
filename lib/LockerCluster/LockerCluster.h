#ifndef LockerCluster_h
#define LockerCluster_h

#include <Locker.h>

class LockerCluster {
  public:
    LockerCluster();
    void addLocker(int row, int column, Locker *locker);
    Locker* lockers[10][10];
  private:
    
};
#endif