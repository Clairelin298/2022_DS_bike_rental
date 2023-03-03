#include "./nthu_bike.h"
#include <iostream>
#include <typeinfo>
#include <fstream>
#include <string>

using namespace std;

// this is a file of 2 sorting fuctions for UserInfo array
// using Quick Sort

// sort by UserInfo.arrive_time
void sort_by_arr_time(UserInfo *user_list, int start, int end)
{
    if (start >= end)
        return;
    int p = partition_arr(user_list, start, end);

    // Sorting the left part
    sort_by_arr_time(user_list, start, p - 1);

    // Sorting the right part
    sort_by_arr_time(user_list, p + 1, end);
}

int partition_arr(UserInfo *user_list, int start, int end)
{

    int pivot = start;

    int count = 0;
    for (int i = start + 1; i <= end; i++)
    {
        if (user_list[i].arr_time < user_list[pivot].arr_time || ((user_list[i].arr_time == user_list[pivot].arr_time) 
        && (user_list[i].user_index < user_list[pivot].user_index)))
        {
            count++;
        }
    }

    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap_by_index(user_list, pivotIndex, start);

    // Sorting left and right parts of the pivot element
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex)
    {
        while (user_list[i].arr_time < user_list[pivotIndex].arr_time || (user_list[i].arr_time == user_list[pivotIndex].arr_time 
        && user_list[i].user_index < user_list[pivotIndex].user_index))
        {
            i++;
        }

        while (user_list[j].arr_time > user_list[pivotIndex].arr_time || (user_list[j].arr_time == user_list[pivotIndex].arr_time 
        && user_list[j].user_index > user_list[pivotIndex].user_index))
        {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex)
        {
            // //cout << "Hiiii" << endl;
            swap_by_index(user_list, i++, j--);
        }
    }

    return pivotIndex;
}

// sort by UserInfo.index
void sort_by_index(UserInfo *user_list, int start, int end)
{
    if (start >= end)
        return;
    int p = partition_index(user_list, start, end);

    // Sorting the left part
    sort_by_index(user_list, start, p - 1);

    // Sorting the right part
    sort_by_index(user_list, p + 1, end);
}

int partition_index(UserInfo *user_list, int start, int end)
{

    int pivot = user_list[start].user_index;

    int count = 0;
    for (int i = start + 1; i <= end; i++)
    {
        if (user_list[i].user_index <= pivot)
            count++;
    }

    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap_by_index(user_list, pivotIndex, start);

    // Sorting left and right parts of the pivot element
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex)
    {
        while (user_list[i].user_index <= pivot)
        {
            i++;
        }

        while (user_list[j].user_index > pivot)
        {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex)
        {
            // //cout << "Hiiii" << endl;
            swap_by_index(user_list, i++, j--);
        }
    }

    return pivotIndex;
}

void swap_by_index(UserInfo *user_list, int a_id, int b_id)
{
    // //cout << "calling userinfo constructor" << endl;

    UserInfo tmp(user_list[a_id].log,
                 user_list[a_id].user_index, user_list[a_id].arr_time, user_list[a_id].des_time, user_list[a_id].arr_station,
                 user_list[a_id].des_station, user_list[a_id].user_bike, user_list[a_id].bike_num, user_list[a_id].accepted,
                 user_list[a_id].bike_id, user_list[a_id].bike_start, user_list[a_id].bike_end, user_list[a_id].revenue);

    user_list[a_id] = user_list[b_id];
    user_list[b_id] = tmp;
}