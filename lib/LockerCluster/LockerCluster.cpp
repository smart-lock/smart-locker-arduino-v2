#include <LockerCluster.h>


LockerCluster::LockerCluster() {

}

void LockerCluster::addLocker(int row, int column, Locker *locker) {
  lockers[row][column] = locker;
}
