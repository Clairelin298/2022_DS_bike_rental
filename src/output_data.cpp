#include "./nthu_bike.h"
#include <fstream>
#include <string>

using namespace std;

// this is a file for output files to reuslt directory

// fuction for output user_reuslt
void out_user_result(string selectedCase, UserInfo *user_list, int user_num)
{

    string path = "result/" + selectedCase + "/user_result.txt";

    ofstream MyFile(path);

    for (int i = 0; i < user_num; i++)
    {
        MyFile << "U" << user_list[i].user_index << " "
               << user_list[i].accepted
               << " "
               << user_list[i].bike_id
               << " "
               << user_list[i].bike_start
               << " "
               << user_list[i].bike_end
               << " "
               << user_list[i].revenue
               << endl;
    }
}

// fuction for output station_status
void out_station_status(string selectedCase, StationBike *station_bike_list, int station_num, int bike_type_num)
{

    string path = "result/" + selectedCase + "/station_status.txt";

    ofstream MyFile(path);

    for (int i = 0; i < station_num; i++)
    {
        BikeType *all_bikes = new BikeType[10000];
        MaxHeap back;

        for (int j = 0; j < bike_type_num; j++)
        {
            while (station_bike_list[i].bike_heap[j].get_size() > 0)
            {
                BikeType tmp = station_bike_list[i].bike_heap[j].extractMax();
                all_bikes[tmp.index] = tmp;
                back.insertKey(tmp);
            }
            while (back.get_size() > 0)
            {
                station_bike_list[i].bike_heap[j].insertKey(back.extractMax());
            }
        }
        for (int j = 0; j < 10000; j++)
        {
            if (all_bikes[j].index != -1)
            {
                MyFile << "S" << i << " "
                       << all_bikes[j].index
                       << " "
                       << "B" << all_bikes[j].type
                       << " "
                       << (float)((int)(all_bikes[j].price * 10 + .5)) / 10
                       << " "
                       << all_bikes[j].count
                       << endl;
            }
        }
        delete[] all_bikes;
    }
}

// fuction for output transfer_log
void out_transfer_log(string selectedCase, UserInfo *user_list, int user_num)
{

    string path = "result/" + selectedCase + "/transfer_log.txt";

    ofstream MyFile(path);
    for (int i = 0; i < user_num; i++)
    {
        MyFile << user_list[i].log;
    }
}
