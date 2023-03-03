#include "./nthu_bike.h"
// #include "./vector_class.h"
using namespace std;

void basic(string selectedCase)
{

    cout << "start my basic version of data structure final from here!" << endl;

    int count_limit = 0;
    int bike_type_num = 0;
    float decedant_rate = 0.0;
    int *Bike_Price = new int[MAX_BIKE];
    read_bike_info(selectedCase, &bike_type_num, &count_limit, &decedant_rate, Bike_Price);

    // cout << "reading map:" << endl;
    BikeMap Map;
    read_map(selectedCase, Map);

    // cout << "station num:" << Map.station_num;
    int **dist_matrix = floydWarshall(Map.adjacent_matrix, Map.station_num);

    // cout << "reading user:" << endl;
    UserInfo *user_list = new UserInfo[MAX_USER];
    int user_num = read_user(selectedCase, user_list);

    sort_by_arr_time(user_list, 0, user_num - 1);

    // //cout << "reading bike:" << endl;

    StationBike *station_bike_list = new StationBike[Map.station_num];
    int all_bike_num = 0;
    read_bike(selectedCase, station_bike_list);

    // for (int i = 0; i < user_num; i++)
    // {
    //     cout << i << " ";
    //     cout << user_list[i].user_index << " ";

    //     // cout << " ";
    //     cout << user_list[i].arr_time << " ";
    //     cout << user_list[i].des_time << " ";
    //     cout << user_list[i].arr_station << " ";
    //     cout << user_list[i].des_station << " ";
    //     for (int j = 0; j < user_list[i].bike_num; j++)
    //         cout << user_list[i].user_bike[j] << ",";
    //     cout << endl;
    // }

    user_request_basic(dist_matrix, user_list, user_num,
                       station_bike_list, count_limit, decedant_rate);

    sort_by_index(user_list, 0, user_num - 1);

    out_transfer_log(selectedCase, user_list, user_num);
    out_user_result(selectedCase, user_list, user_num);
    out_station_status(selectedCase, station_bike_list, Map.station_num, bike_type_num);
 }