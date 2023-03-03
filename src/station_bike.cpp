#include "./nthu_bike.h"
using namespace std;

// this is a file for a station's bike heaps
// every bike type is a heap in a staion

StationBike::StationBike()
{
    bike_heap = new MaxHeap[MAX_BIKE_TYPE];
}