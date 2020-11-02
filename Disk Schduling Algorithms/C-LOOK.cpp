#include<iostream>

#include<stdlib.h>

using namespace std;

class clook_disk

{

int ref[100];

int ttrk,cur,size,prev;

int sort();

public:

void getdata();

void total_move();

};

int clook_disk::sort()

{

int temp;

for(int i=0;i<size-1;i++)

for(int y=0;y<size-1;y++)

if(ref[y]>ref[y+1])

{

temp=ref[y];

ref[y]=ref[y+1];

ref[y+1]=temp;

}

for(int i=0;i<size;i++)

if(ref[i]>cur)

return i;

return size;

}

void clook_disk::getdata()

{

cout<<"Enter total number of tracks : ";

cin>>ttrk;

ttrk--;

cout<<"Enter the current position of head : ";

cin>>cur;

cout<<"Enter previous position of head : ";

cin>>prev;

cout<<"Enter the size of queue : ";

cin>>size;

cout<<"Enter the request for tracks : ";

for(int i=0;i<size;i++)

cin>>ref[i];

}

void clook_disk::total_move()

{

int num=cur,move=0,ind,dir=cur-prev;

ind=sort();

if(dir>0)

{

for(int i=ind;i<size;i++)

{

move+=ref[i]-num;

num=ref[i];

}

if(ind!=0)

{

num=ref[0];

cout<<move<<" ";

for(int i=0;i<=ind-1;i++)

{

move+=ref[i]-num;

num=ref[i];

}

}

}

else

{

for(int i=ind-1;i>=0;i--)

{

move+=num-ref[i];

num=ref[i];

}

num=ref[size-1];

for(int i=size-2;i>=ind;i--)

{

move+=num-ref[i];

num=ref[i];

}

}

cout<<"Total head movements : "<<move;

}

int main()

{

clook_disk clook;

clook.getdata();

clook.total_move();

return 0;

}