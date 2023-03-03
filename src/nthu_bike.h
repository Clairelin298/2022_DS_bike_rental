#ifndef NTHU_BIKE_H
#define NTHU_BIKE_H

#include <iostream>

#define MAX_STATION 1001
#define MAX_BIKE 10001
#define MAX_USER 100001
#define MAX_BIKE_TYPE 50
#define IFINITY 2147483647

using namespace std;

// basic.cpp
void basic(string selectedCase);

// advanced.cpp
void advanced(string selectedCase);

/*----Self-defined data structures----*/

// bike_class.cpp
class BikeType
{
public:
    int type;    // the type of the bike
    int station; // the station of the bike
    float price; // the price of the bike
    int index;   // how many times bike can be rent out
    int count;   // how many time it is out
    int return_time;

    BikeType(int t, int s, float p, int i, int c, int rt, int st);
    BikeType();
    ~BikeType(){};
};

// bike_class.cpp
class BikeMap
{
public:
    int adjacent_matrix[MAX_STATION][MAX_STATION]; // to store the distance between the nodes
    int station_num;

    BikeMap();
    ~BikeMap(){};

    void print_matrix();
};

// user_info.cpp
class UserInfo
{
public:
    int *user_bike;
    int user_index;
    int bike_num;
    int arr_time;
    int des_time;
    int arr_station;
    int des_station;
    bool accepted;
    int bike_id;
    int bike_start; // the bike start time
    int bike_end;   // the bike end time
    int revenue;
    string log; // to store the transfer log a user made

    UserInfo();
    UserInfo(string log, int id, int a_time, int d_time,
             int a_station, int d_station, int *bike_list, int bike_no,
             bool acc, int b_id, int b_start, int b_end, int r);
    ~UserInfo(){};
};

// heap.cpp
class MaxHeap
{
public:
    BikeType *harr; // pointer to array of elements in heap
    int capacity;   // maximum possible size of min heap
    int heap_size;  // Current number of elements in min heap

    MaxHeap();
    int get_size();
    void MaxHeapify(int i); // to heapify a subtree with the root at given index
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }
    BikeType extractMax(); // to extract the root which is the max element
    BikeType getMax();
    void insertKey(BikeType k);
};
void swap(BikeType *harr, int x, int y);

// station_bike.cpp
class StationBike
{
public:
    MaxHeap *bike_heap;
    StationBike();
};

/*---- Other functions----*/

// input_data.cpp
int read_bike_info(string selectedCase, int *bike_type_num, int *count_limit, float *decedant_rate, int *Bike_Price);
int read_bike(string selectedCase, StationBike *station_bike_list); // implement in input_data.cpp
int read_map(string selectedCase, BikeMap &Map);
int read_user(string selectedCase, UserInfo *user_list);
int *split(string str, char seperator, int &num);

// sort.cpp
void swap_by_index(UserInfo *user_list, int a_id, int b_id);
int partition_arr(UserInfo *user_list, int start, int end);
void sort_by_arr_time(UserInfo *user_list, int start, int end); // sort by UserInfo.arr_time

int partition_index(UserInfo *user_list, int start, int end);
void sort_by_index(UserInfo *user_list, int start, int end); // sort by UserInfo.index

// floyd_washall.cpp
int **floydWarshall(int dist[][MAX_STATION], int V);

void user_request_basic(int **dist_matrix, UserInfo *user_list, int user_num,
                        StationBike *station_bike_list, int const count_limit, float const decedant_rate);
void user_request_advanced(int **dist_matrix, UserInfo *user_list, int &user_num,
                           StationBike *station_bike_list, int const count_limit, float const decedant_rate, int station_num);
void user_request_advanced_0(int **dist_matrix, UserInfo *user_list, int &user_num,
                             StationBike *station_bike_list, int const count_limit, float const decedant_rate, int station_num);
int max(int a, int b);

int out_user_result(UserInfo *user_list, int user_num);

void out_user_result(string selectedCase, UserInfo *user_list, int user_num);
void out_station_status(string selectedCase, StationBike *station_bike_list, int station_num, int bike_type_num);
void out_transfer_log(string selectedCase, UserInfo *user_list, int user_num);

#endif
