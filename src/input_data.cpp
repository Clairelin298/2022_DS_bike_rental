/*
This is a file for input data from testcases
input data:
**bike_info.txt
**bike.txt
**map.txt
**user.txt
*/

#include "./nthu_bike.h"
#include <iostream>
#include <typeinfo>
#include <fstream>
#include <string>

using namespace std;

/*---------------
**bike_info.txt**
---------------*/

int read_bike_info(string selectedCase, int *bike_type_num, int *count_limit, float *decedant_rate, int *Bike_Price)
{

    ifstream file;
    string buffer;
    string path = "testcases/" + selectedCase + "/bike_info.txt";

    file.open(path, ios::out);
    // cout << "openning the file";

    if (!file)
    {
        // cout << "Failed to open file.\n";
        return 1; // EXIT_FAILURE
    }

    getline(file, buffer);
    *decedant_rate = stof(buffer);

    getline(file, buffer);
    *count_limit = stoi(buffer);

    int i = 0;
    string index, price;

    while (!file.eof())
    {
        file >> index >> price; // the price of the price

        if (index == "")
        {
            break;
        } // last line of the file is '\n'

        Bike_Price[i++] = stoi(price); // conver string to the int
                                       // //cout << stoi(buffer) << " ";
    }

    file.close();
    *bike_type_num = i;
    return 0;
}

/*----------
**bike.txt**
----------*/

int read_bike(string selectedCase, StationBike *station_bike_list)
{
    // VectorClass<int> bike_price;
    ifstream file;
    string buffer;
    string path = "testcases/" + selectedCase + "/bike.txt";

    file.open(path, ios::out);

    if (!file)
    {
        cout << "Failed to open file.\n";
        return 1; // EXIT_FAILURE
    }
    BikeType tmp;
    // //cout << decedant_rate << " " << count_limit << endl;
    int i = 0;
    while (!file.eof())
    {
        string bike_type, bike_index, bike_station, bike_price, bike_rent;
        file >> bike_type >> bike_index >> bike_station >> bike_price >> bike_rent;

        if (bike_type == "")
            break;

        // store the info of the bike
        tmp.type = stoi(bike_type.substr(1));       // store the type of the bike: B0
        tmp.station = stoi(bike_station.substr(1)); // the station of the bike: S1
        tmp.price = stof(bike_price);               // the price of the bike
        tmp.index = stoi(bike_index);               // the count of the bike
        tmp.count = stoi(bike_rent);

        station_bike_list[tmp.station].bike_heap[tmp.type].insertKey(tmp);
    }

    file.close();

    return 0;
}

/*----------
**map.txt**
----------*/

int read_map(string selectedCase, BikeMap &Map)
{
    ifstream file;
    string buffer;
    string path = "testcases/" + selectedCase + "/map.txt";

    file.open(path, ios::out);

    if (!file)
    {
        cout << "Failed to open file.\n";
        return 1; // EXIT_FAILURE
    }

    while (!file.eof())
    {
        string s1, s2, dis;
        file >> s1 >> s2 >> dis;

        if (s1 == "") // the last line is empty
            break;

        Map.adjacent_matrix[stoi(s1.substr(1))][stoi(s2.substr(1))] = stoi(dis);
        Map.adjacent_matrix[stoi(s2.substr(1))][stoi(s1.substr(1))] = stoi(dis);

        int big;
        if (stoi(s1.substr(1)) > stoi(s2.substr(1)))
        {
            big = stoi(s1.substr(1));
        }
        else
        {
            big = stoi(s2.substr(1));
        }
        if (big >= Map.station_num)
        {
            Map.station_num = big;
        }
    }

    Map.station_num += 1;

    file.close();

    return 0;
}

/*----------
**user.txt**
----------*/

int read_user(string selectedCase, UserInfo *user_list)
{
    ifstream file;
    string buffer;
    string path = "testcases/" + selectedCase + "/user.txt";

    file.open(path, ios::out);

    if (!file)
    {
        cout << "Failed to open file.\n";
        return 1; // EXIT_FAILURE
    }

    int user_num = 0;
    while (!file.eof())
    {

        string user_id, bike_list, a_time, d_time, a_station, d_station;
        file >> user_id >> bike_list >> a_time >> d_time >> a_station >> d_station;

        if (user_id == "")
        {
            break; // the last line is empty
        }

        UserInfo tmp;
        user_num++;

        tmp.user_index = stoi(user_id.substr(1));
        tmp.user_bike = split(bike_list, ',', tmp.bike_num);
        tmp.arr_time = stoi(a_time);
        tmp.des_time = stoi(d_time);
        tmp.arr_station = stoi(a_station.substr(1));
        tmp.des_station = stoi(d_station.substr(1));

        user_list[user_num - 1] = tmp;
    }

    file.close();

    return user_num;
}

// create custom split() function for user's bike list
int *split(string str, char seperator, int &num)
{
    int *tmp = new int[MAX_BIKE_TYPE];
    int currIndex = 0, i = 0;
    int startIndex = 0, endIndex = 0;
    int k = 0;
    while (i <= str.length())
    {
        if (str[i] == seperator || i == str.length())
        {
            endIndex = i;
            string subStr = "";
            subStr.append(str, startIndex, endIndex - startIndex);
            tmp[k++] = stoi(subStr.substr(1));
            currIndex += 1;
            startIndex = endIndex + 1;
        }
        i++;
    }
    num = k;
    return tmp;
}
