//Write a c program to demonstrate the working of the following
//disk scheduling algorithms.
//a) SCAN
//b) CSCAN
//Reference queue sequence : 2,
//3,100,10,56,3,20,100,130,60,34,80,23,10,20,180
//Total cylinders 0-199. Current position of the armhead is
//30. Compare the performance of the algorithms. Show the
//results in the form of a table.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#define DISKNUM 10000
#define CYLINDERNUM 1000
int cylinders[CYLINDERNUM];
int comp (const void* a, const void* b){ // Comparing Integers For Sorting
int *x = (int*) a;
int *y = (int*) b;
return *x - *y;
}
void cylindersRequest(){ // Obtain Random Cylinder Requests
srand(time(NULL)); // Different Seed For Random Number Generator
for (int i = 0; i < CYLINDERNUM; i++){ // 1000 Cylinders Request
while(1){ // Loop To Make Sure Value Is Unique Before Moving On
bool found = false; // Assume Found Is False
int random = rand() % DISKNUM; // Random Number From 0 to 9999
for (int j = i -1 ; j > -1; j--
){ // Check To See If It was Entered Already
if(cylinders[j] == random){ // If It's Found, It's Not Unique, Break And
found = true; // If Found, Found = True and Reloop To Get NewRandom Value
break; // Break Out
}
}
if(found == false){ // Not Fount After Looping Through Array
//printf("%d- random: %d \n", i, random);
cylinders[i] = random; // Requesting From a Range From 0-9999
break; // Unique Is True So i++. Break.
}
}
}
}
int FCFS(int cylinders[],int head){ // First Come First Serve Algorithm
int sum = 0; // Sum is Zero

for(int i = 0; i < CYLINDERNUM; i++){ // Loop From 1st To End
sum += abs(head - cylinders[i]); // Get The Distance Traveled
head = cylinders[i]; // New Head Value
}
return sum; // Return Total Head Movement
}
int SSTF(int cylinders[],int head){ // Shortest Seek Time First Algorithm
int sum = 0; // Sum Is Zero
int storage[CYLINDERNUM]; // Used So cylinders[] Doesn't Get Modified
for(int i = 0; i < CYLINDERNUM; i++){ // Copy
storage[i] = cylinders[i]; // Copying
}
int count = CYLINDERNUM; // Used To Keep Count Of What's Left
while(count){ // While There's Still Something Left
int min = DISKNUM + 1; // High Min To Prevent Miscalculation
int index; // For Index Of Min
for(int i = 0; i < count; i++){ // Find Minimum Seek Time
if(abs(head -
storage[i]) < min){ // If Seek Time Is Lower Than Before
min = abs(head - storage[i]); // Replace Min With New Min
index = i; // Get Index Of Next Head
}
}
//printf("%d\n",min);
sum += abs(head-storage[index]); // Shortest Seek Time
head = storage[index]; // New Head Value
for(int i = index; i < count; i++){ // Remove Current Head Value
storage[i] = storage[i+1]; // Replace It With Everything Ahead
}
count--; // Subtract Count
}
return sum; // Return Total Head Movement
}
int SCAN(int cylinders[],int head){ // SCAN Algorithm
int sum = 0; // Sum Is Zero
int low = 0; // Amount of Values Less Than Head
int storeLow[CYLINDERNUM]; // Used To Store Values Less Than Current Head
int high = 0; // Amount of Values Higher Than
int storeHigh[CYLINDERNUM]; // Used To Store Values Higher Than Current Head
for(int i = 0; i < CYLINDERNUM; i++){ // Parse Array
if(cylinders[i] > head){ // Above Head Goes Here
storeHigh[high] = cylinders[i]; // Parse
high++; // Increase Size Of High

}
else{ // Below Or Equal To Head Goes Here
storeLow[low] = cylinders[i]; // Parse
low++; // Increase Size Of Low
}
}
qsort(storeLow, low, sizeof(*storeLow), comp); // Sort Low
qsort(storeHigh, high, sizeof(*storeHigh), comp); // Sort High
for(int i = low-1; i > -1; i--){ // Start To Descend From Head
//printf("head: %d \n", head);
sum += head - storeLow[i]; // Head Movement
head = storeLow[i]; // New Head Value
}
sum += head - 0; // To Zero
head = 0; // Head = 0
for(int i = 0; i < high; i++){ // Start To Ascend From Head
//printf("head: %d \n", head);
sum += storeHigh[i] - head; // Head Movement
head = storeHigh[i]; // New Head Value
}
//printf("head: %d \n", head);
return sum; // Return Total Head Movement
}
int CSCAN(int cylinders[],int head){ // CSCAN Algorithm
int sum = 0; // Sum Is Zero
int low = 0; // Amount of Values Less Than Head
int storeLow[CYLINDERNUM]; // Used To Store Values Less Than Current Head
int high = 0; // Amount of Values Higher Than
int storeHigh[CYLINDERNUM]; // Used To Store Values Higher Than Current Head
for(int i = 0; i < CYLINDERNUM; i++){ // Parse Array
if(cylinders[i] > head){ // Above Head Goes Here
storeHigh[high] = cylinders[i]; // Parse
high++; // Increase Size Of High
}
else{ // Below Or Equal To Head Goes Here
storeLow[low] = cylinders[i]; // Parse
low++; // Increase Size Of Low
}
}
qsort(storeLow, low, sizeof(*storeLow), comp); // Sort Low
qsort(storeHigh, high, sizeof(*storeHigh), comp); // Sort High
for(int i = low-1; i > -1; i--){ // Start To Descend From Head
//printf("head: %d \n", head);
sum += head - storeLow[i]; // Head Movement

head = storeLow[i]; // New Head Value
}
sum += head - 0; // To Zero
head = 0; // Head = 0
for(int i = high-1; i > -1; i--){ // Start To Descend From Head
//printf("head: %d \n", head);
if (i == high-1){
sum += storeHigh[i] - head; // Head Movement
}
else{
sum += head - storeHigh[i]; // Head Movement
}
head = storeHigh[i]; // New Head Value
}
//printf("head: %d \n", head);
return sum; // Return Total Head Movement
}
int LOOK(int cylinders[],int head){ // LOOK Algorithm
int sum = 0; // Sum Is Zero
int low = 0; // Amount of Values Less Than Head
int storeLow[CYLINDERNUM]; // Used To Store Values Less Than Current Head
int high = 0; // Amount of Values Higher Than
int storeHigh[CYLINDERNUM]; // Used To Store Values Higher Than Current Head
for(int i = 0; i < CYLINDERNUM; i++){ // Parse Array
if(cylinders[i] > head){ // Above Head Goes Here
storeHigh[high] = cylinders[i]; // Parse
high++; // Increase Size Of High
}
else{ // Below Or Equal To Head Goes Here
storeLow[low] = cylinders[i]; // Parse
low++; // Increase Size Of Low
}
}
qsort(storeLow, low, sizeof(*storeLow), comp); // Sort Low
qsort(storeHigh, high, sizeof(*storeHigh), comp); // Sort High
for(int i = low-1; i > -1; i--){ // Start To Descend From Head
//printf("head: %d \n", head);
sum += head - storeLow[i]; // Head Movement
head = storeLow[i]; // New Head Value
}
for(int i = 0; i < high; i++){ // Start To Ascend From Head
//printf("head: %d \n", head);
sum += storeHigh[i] - head; // Head Movement
head = storeHigh[i]; // New Head Value

}
//printf("head: %d \n", head);
return sum; // Return Total Head Movement
}
int CLOOK(int cylinders[],int head){ // CLOOK Algorithm
int sum = 0; // Sum Is Zero
int low = 0; // Amount of Values Less Than Head
int storeLow[CYLINDERNUM]; // Used To Store Values Less Than Current Head
int high = 0; // Amount of Values Higher Than
int storeHigh[CYLINDERNUM]; // Used To Store Values Higher Than Current Head
for(int i = 0; i < CYLINDERNUM; i++){ // Parse Array
if(cylinders[i] > head){ // Above Head Goes Here
storeHigh[high] = cylinders[i]; // Parse
high++; // Increase Size Of High
}
else{ // Below Or Equal To Head Goes Here
storeLow[low] = cylinders[i]; // Parse
low++; // Increase Size Of Low
}
}
qsort(storeLow, low, sizeof(*storeLow), comp); // Sort Low
qsort(storeHigh, high, sizeof(*storeHigh), comp); // Sort High
for(int i = low-1; i > -1; i--){ // Start To Descend From Head
//printf("head: %d \n", head);
sum += head - storeLow[i]; // Head Movement
head = storeLow[i]; // New Head Value
}
for(int i = high-1; i > -1; i--){ // Start To Descend From Head
//printf("head: %d \n", head);
if (i == high-1){
sum += storeHigh[i] - head; // Head Movement
}
else{
sum += head - storeHigh[i]; // Head Movement
}
head = storeHigh[i]; // New Head Value
}
//printf("head: %d \n", head);
return sum; // Return Total Head Movement
}
int main(){
cylindersRequest(); // Obtain a Random Series of 1000 Cylinders Requests
int input; // To Store Disk Head

printf("Insert Initial Position of the Disk Head Between 0 and %d: ", DISKNUM
- 1); // Print
scanf("%d", &input); // Obtain Initial Position of the Disk Head
while(input < 0 || input > DISKNUM - 1){ // Makes Sure Input Is Appropriate
printf("Incorrect Input. Input Has to be Between 0 and %d. You Inputted %d.\n", DISKNUM - 1, input); // Print
printf("Insert Initial Position of the Disk Head Between 0 and %d: ", DISKNUM -1); // Print
scanf("%d", &input); // Obtain Initial Position Of The Disk Head
}
int FCFS_SUM = FCFS(cylinders,input); // Store
int SSTF_SUM = SSTF(cylinders,input); // Store
int SCAN_SUM = SCAN(cylinders,input); // Store
int CSCAN_SUM = CSCAN(cylinders,input); // Store
int LOOK_SUM = LOOK(cylinders,input); // Store
int CLOOK_SUM = CLOOK(cylinders,input); // Store
printf("Algorithm\t|Total Head Movement\n"); // Print
printf("________________|___________________\n"); // Print
printf("FCFS\t\t|%d\n", FCFS_SUM); // Print
printf("SSTF\t\t|%d\n", SSTF_SUM); // Print
printf("SCAN\t\t|%d\n", SCAN_SUM); // Print
printf("CSCAN\t\t|%d\n", CSCAN_SUM); // Print
printf("LOOK\t\t|%d\n", LOOK_SUM); // Print
printf("CLOOK\t\t|%d\n", CLOOK_SUM); // Print
return 0;
}