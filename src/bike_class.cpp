#include <iostream>
#include "./nthu_bike.h"

using namespace std;

// this file contain implementation of two classes, BikeType and BikeMap

/* ------BikeType------*/
// a class to store every single bike's attribute

BikeType::BikeType(int t, int s, float p, int i, int c, int rt, int st)
{
    type = t;
    station = s;
    price = p;
    index = i;
    count = c;
    return_time = rt;
    station = st;
}
BikeType::BikeType()
{
    type = 0;
    station = 0;
    price = 0;
    index = -1;
    count = 0;
    return_time = 0;
}

/* ------BikeMap------*/
// a class to store the distance of stations

BikeMap::BikeMap()
{
    // station number default to 0
    station_num = 0;

    // all the distace between stations default to infinity
    for (int i = 0; i < MAX_STATION; i++)
    {
        for (int j = 0; j < MAX_STATION; j++)
        {
            if (i == j)
                adjacent_matrix[i][j] = 0; // distance to itself
            else
                adjacent_matrix[i][j] = IFINITY;
        }
    }
}

void BikeMap::print_matrix()
{
    for (int i = 0; i < station_num; i++)
    {
        for (int j = 0; j < station_num; j++)
        {
            if (adjacent_matrix[i][j] == 2147483647)
                cout << "# ";
            else
                cout << adjacent_matrix[i][j] << " ";
        }
        // cout << endl;
    }
}
