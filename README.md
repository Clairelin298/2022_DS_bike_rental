# 2022_DS_bike_rental
 
## How to compile my program



3. The details of my Data Structures
A. Heap
I use max heap to store bike according to their rental price. Every bike type has 
their own heap, and every station contains multiple heap. Every time a user 
requests a bike, the heap will extract the bike with max price from the heap.
How I implement it:
Declaration:
Name: 林育萱
ID : 111065546
3
Important function implementation:
- Insert key:
Insert object of class BikeType and adjust the node according to bike’s price and 
index.
- Heapify
Maintain the max heap’s attribute, according to bike’s price and index.
4. The details of my Algorithm
A. Quick sort:
I use Quick sort to sort the user with their arrive time/user index respectively.
Name: 林育萱
ID : 111065546
4
Quick sort pseudo code:
-Sort:
If the array is bigger than zero:
find the partition index by Partition;
sort the array of left to partition index;
sort the array of right to partition index;
-Partition:
Find the position(index) of pivot;
pivot to the found position;
until all element right to the pivot is bigger and left to the pivot is smaller:
swap left and right element;
How I implement it:
Name: 林育萱
ID : 111065546
5
B. Floyd Washall Algorithm
I use Floyd Washall to calculate the shortest distance between all the station pair, 
and then store the calculate result in a 2D array.
Floyd Washall Pseudo code:
n = no of vertices
A = matrix of dimension n*n
for k = 1 to n
 for i = 1 to n
 for j = 1 to n
 Ak
[i, j] = min (Ak-1
[i, j], Ak-1
[i, k] + Ak-1
[k, j])
How I implement it:
Name: 林育萱
ID : 111065546
6
C. The user_request algorithm(self-design):
The flow chart :
(next page)
Name: 林育萱
ID : 111065546
7
Name: 林育萱
ID : 111065546
8
5. Feedback
A. I would like to suggest a few progress check during the semester.
B. Assignment Spec seemed to be modified too many times, if someone finished the 
work early, may not see those changes.
