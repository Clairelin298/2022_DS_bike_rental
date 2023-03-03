#include "./nthu_bike.h"
#include <fstream>
#include <string>

using namespace std;

// this is a file handling user request based on their arr_time

// the user_request for basic function
void user_request_basic(int **dist_matrix, UserInfo *user_list, int user_num,
                        StationBike *station_bike_list, int const count_limit, float const decedant_rate)
{
    string tmp;
    for (int i = 0; i < user_num; i++) // for every user
    {
        int arr_station = user_list[i].arr_station; // user's arr station
        int des_station = user_list[i].des_station;
        int distance = dist_matrix[arr_station][des_station];

        // cout << i << " user id:" << user_list[i].user_index << " ";
        // cout << "arrive at " << user_list[i].arr_station << ", " << user_list[i].arr_time;
        // cout << " dis: " << distance << " ";

        // if the user can get to the des_station at time
        if (user_list[i].arr_time + distance < user_list[i].des_time)
        {
            BikeType highest;
            bool flag = false;

            // check user's every wanted bikes types
            for (int j = 0; j < user_list[i].bike_num; j++)
            {
                int want_bike = user_list[i].user_bike[j];

                BikeType first_bike;
                MaxHeap unreturn_bike; // to store the unreturn bike

                while (station_bike_list[arr_station].bike_heap[want_bike].get_size() > 0) // if there's still bike
                {

                    first_bike = station_bike_list[arr_station].bike_heap[want_bike].extractMax(); // check every single bike of wanted type

                    if (first_bike.return_time > user_list[i].arr_time) // bike's not return yet
                    {

                        unreturn_bike.insertKey(first_bike); // keep the bike in another heap

                        first_bike.index = -1;
                        continue;
                    }
                    if (first_bike.count >= count_limit) // the bike is too old
                    {
                        unreturn_bike.insertKey(first_bike);
                        first_bike.index = -1;
                        continue;
                    }

                    // the bike can be rented
                    if (first_bike.index != -1 && first_bike.return_time <= user_list[i].arr_time && first_bike.count < count_limit)
                    {
                        break; // break the while
                    }

                } // end of while

                // push back the unreturn bike
                while (unreturn_bike.get_size() > 0)
                {
                    station_bike_list[arr_station].bike_heap[want_bike].insertKey(unreturn_bike.extractMax());
                }
                // check the highest price bike
                if (first_bike.index != -1)
                {

                    if (flag == false) // if no highest bike is choosen
                    {
                        highest = first_bike;
                        flag = true;
                    }
                    // it is the highest
                    else if (first_bike.price > highest.price || (first_bike.price == highest.price && first_bike.index < highest.index))
                    {
                        station_bike_list[arr_station].bike_heap[highest.type].insertKey(highest);
                        highest = first_bike;
                    }
                    // not the highest bike, push it back
                    else
                    {
                        station_bike_list[arr_station].bike_heap[first_bike.type].insertKey(first_bike);
                    }

                } // end of if
            }     // end of for

            // find the bike for user
            if (flag && highest.index != -1)
            {
                // update user status
                user_list[i].accepted = true;
                user_list[i].bike_id = highest.index;
                user_list[i].bike_start = user_list[i].arr_time;
                user_list[i].bike_end = user_list[i].arr_time + distance;
                user_list[i].revenue = (int)distance * highest.price;

                // update bike status
                highest.count++;
                highest.price -= decedant_rate;
                highest.return_time = user_list[i].bike_end;
                highest.station = des_station;

                // insert the bike to the des_station
                station_bike_list[des_station].bike_heap[highest.type].insertKey(highest);

                user_list[i].log = to_string(highest.index) + " S" + to_string(user_list[i].arr_station) + " S" + 
                to_string(user_list[i].des_station) + " " + to_string(user_list[i].bike_start) + " " + to_string(user_list[i].bike_end) + " U" + to_string(user_list[i].user_index) + "\n";
            }
        } // end of if
    }
}

// the user_request for advance function
void user_request_advanced(int **dist_matrix, UserInfo *user_list, int &user_num,
                           StationBike *station_bike_list, int const count_limit, float const decedant_rate, int station_num)
{
    string tmp;
    for (int i = 0; i < user_num; i++) // for every user
    {
        int arr_station = user_list[i].arr_station; // user's arr station
        int des_station = user_list[i].des_station;
        int distance = dist_matrix[arr_station][des_station];
        // if user can wait
        int wait_time = user_list[i].des_time - (user_list[i].arr_time + distance) - 1;

        // cout << i << " user id:" << user_list[i].user_index << " ";
        // cout << "arrive at " << user_list[i].arr_station << ", " << user_list[i].arr_time;
        // cout << " dis: " << distance << " ";

        // if the user can get to the des_station at time
        if (wait_time + 1 > 0)
        {
            // check user's every wanted bikes types
            BikeType highest;
            bool flag = false;

            for (int j = 0; j < user_list[i].bike_num; j++)
            {
                int want_bike = user_list[i].user_bike[j];

                BikeType first_bike;
                MaxHeap unreturn_bike;

                while (station_bike_list[arr_station].bike_heap[want_bike].get_size() > 0) // if there's still bike
                {
                    first_bike = station_bike_list[arr_station].bike_heap[want_bike].extractMax(); // check every single bike of wanted type

                    if (first_bike.return_time > user_list[i].arr_time + wait_time) // bike's not return yet
                    {

                        unreturn_bike.insertKey(first_bike); // keep the bike in another heap
                        first_bike.index = -1;
                        continue;
                    }
                    if (first_bike.count >= count_limit) // the bike is too old
                    {
                        unreturn_bike.insertKey(first_bike);
                        first_bike.index = -1;
                        continue;
                    }
                    // the bike can be rented
                    if (first_bike.index != -1 && (first_bike.return_time <= user_list[i].arr_time + wait_time) && (first_bike.count < count_limit))
                    {
                        break;
                    }
                } // end of while

                // push back the unreturn bike
                while (unreturn_bike.get_size() > 0)
                {
                    station_bike_list[arr_station].bike_heap[want_bike].insertKey(unreturn_bike.extractMax());
                }
                // check the highest price bike
                if (first_bike.index != -1)
                {

                    if (flag == false)
                    {
                        highest = first_bike;
                        flag = true;
                    }
                    // it is the highest
                    else if (first_bike.price > highest.price || (first_bike.price == highest.price && first_bike.index < highest.index))
                    {
                        station_bike_list[arr_station].bike_heap[highest.type].insertKey(highest);
                        highest = first_bike;
                    }

                    else // not the highest bike, push it back
                    {
                        station_bike_list[arr_station].bike_heap[first_bike.type].insertKey(first_bike);
                    }

                } // end of if
            }     // end of for

            if (flag && highest.index != -1)
            {
                // update user status
                user_list[i].accepted = true;
                user_list[i].bike_id = highest.index;

                if (user_list[i].arr_time < highest.return_time)
                    user_list[i].bike_start = highest.return_time;
                else
                    user_list[i].bike_start = user_list[i].arr_time;

                user_list[i].bike_end = user_list[i].bike_start + distance;
                user_list[i].revenue = (int)distance * highest.price;

                // update bike status
                highest.count++;
                highest.price -= decedant_rate;
                highest.return_time = user_list[i].bike_end;
                highest.station = des_station;

                // insert the bike to the des_station
                station_bike_list[des_station].bike_heap[highest.type].insertKey(highest);

                user_list[i].log = to_string(highest.index) + " S" + to_string(user_list[i].arr_station) + " S" + to_string(user_list[i].des_station) + " " + to_string(user_list[i].bike_start) + " " + to_string(user_list[i].bike_end) + " U" + to_string(user_list[i].user_index) + "\n";
                // cout << user_list[i].log;
            }
        } // end of if
    }
}

int max(int a, int b)
{
    if (a >= b)
        return a;
    return b;
}
