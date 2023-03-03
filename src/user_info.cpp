#include <iostream>

#include "./nthu_bike.h"

using namespace std;

// this is a file for implementing UserInfo class
// to store every user's information

UserInfo::UserInfo()
{

    user_index = 0;
    bike_num = 0;
    arr_time = 0;
    des_time = 0;
    arr_station = 0;
    des_station = 0;
    accepted = false;
    bike_id = 0;
    bike_start = 0; // the bike start time
    bike_end = 0;
    revenue = 0;
}

UserInfo::UserInfo(string logg, int id, int a_time, int d_time,
                   int a_station, int d_station, int *bike_list, int bike_no,
                   bool acc, int b_id, int b_start, int b_end, int r)
{
    log = logg;
    user_index = id;
    arr_time = a_time;
    des_time = d_time;
    arr_station = a_station;
    des_station = d_station;
    user_bike = bike_list;
    bike_num = bike_no;
    accepted = acc;
    bike_id = b_id;
    bike_start = b_start; // the bike start time
    bike_end = b_end;
    revenue = r;
}
