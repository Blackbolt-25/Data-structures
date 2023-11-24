//Tower of hanoi probelm using stack
//Protocols:-
    //i)Only one disk can be move from one tower to another at a time.
    //ii)Larger disk cannot be placed on top of smaller disk
    //iii)no.of steps neeeded to transfer all the disks from source to the target destination is 2^n.
    //iv)With the hep of helper (Auxiliary) tower,we transfer all the disk from source to intended destination.

#include<stdio.h>

void towerofHanoi(int n,char from_rod,char to_rod,char aux_rod)
{ 
    if(n==0)
        return;
    towerofHanoi(n-1,from_rod,aux_rod,to_rod);
    printf("Shift rod %d from rod %c to rod %c\n",n,from_rod,to_rod);
    towerofHanoi(n-1,aux_rod,to_rod,from_rod);
}

int main()
{
    int n=3;
    towerofHanoi(n,'A','C','B');
    return(0);
}

