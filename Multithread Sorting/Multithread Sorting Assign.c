// Multithread Sorting

// Header files:- 
// 1) standard input output file
// 2) POSIX pthread library
#include<stdio.h>
#include<pthread.h>

// Define some max size for the array of numbers
#define MaxSize 1000

// Globally Declared arrays  
// 1) a stores the initial unsorted full array
// 2) b stores the 1st part after dividing the array
// 3) c stores the 2nd part after dividing the array
// 4) d stores the complete sorted array after merging 2 individual arrays b and c
int a[MaxSize],b[(MaxSize)/2],c[MaxSize/2],d[MaxSize];

// size of part 1 of the full array:- ps1
// size of part 2 of the full array:- ps2
int ps1,ps2;

// Sort the 1st part of the array
void* partoflist1(int arr[]){
    sleep(1);

    // bubble sort algorithm to sort an array
    for(int i=0;i<ps1;i++){
        for(int j=0;j<ps1-i-1;j++){
            if(arr[j]>arr[j+1]){
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }

    // Print the sorted part of the list
    printf("Sorted Part 1 of the list :- ");
    for(int i=0;i<ps1;i++){
        b[i]=arr[i];
        printf("%d ",arr[i]);
    }
    printf("\n");
    pthread_exit(NULL);
}

// sort the 2nd part of the array
void* partoflist2(int arr[]){
    sleep(2);

    // bubble sort algorithm to sort an array
    for(int i=0;i<ps2;i++){
        for(int j=0;j<ps2-i-1;j++){
            if(arr[j]>arr[j+1]){
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }

    // Print the sorted part of the list
    printf("Sorted Part 2 of the list :- ");
    for(int i=0;i<ps2;i++){
        c[i]=arr[i];
        printf("%d ",arr[i]);
    }
    printf("\n");
    pthread_exit(NULL);

}

// merge the sorted array into one full sorted array
void* merge(int arr[]){
    // sleep(3);

    // variables/pointers to go through each sorted array
    int pb=0,pc=0;

    // merging 2 arrays using 2 pointer approach.
    for(int i=0;i<ps1+ps2;i++){
        if(b[pb]<=c[pc]){
            if(pb<ps1){
                arr[i]=b[pb];
                pb++;
            }
            else{
                arr[i]=c[pc];
                pc++;
            }
        }
        else if(c[pc]<=b[pb]){
            if(pc<ps2){
                arr[i]=c[pc];
                pc++;
            }
            else{
                arr[i]=b[pb];
                pb++;
            }
        }
    }

    // Printing the complete sorted list
    printf("Completely Sorted List :- ");
    for(int i=0;i<ps1+ps2;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    pthread_exit(NULL);

}

// driver function
int main(){

    // initialize variables
    int n,i,j=0,k=0;

    // declare threads...
    // pthread_t is a data-type
    pthread_t th1,th2,th3;

    // Get the array from the console
    printf("Enter size of array:");
    scanf("%d",&n);
    printf("Now Enter the Array: ");
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }

    // divide the array into 2 parts
    // part 1 stored in global array b
    // part 2 stored in global array c
    for(i=0;i<n/2;i++)
    {
        b[j]=a[i];
        j++;
    }
    
    ps1= j; // size of 1st part of the array
    for(i=n/2;i<n;i++)
    {
        c[k]=a[i];
        k++;
    }
    ps2=k; // size of 2nd part of the array
    
    // Print the divided parts as it is (unsorted)
    printf("First array:- ");
    for(i=0;i<n/2;i++)
    {
        printf("%d ",b[i]);
    }
    printf("\n");
    printf("Second array:- ");
    for(i=n/2;i<n;i++)
    {
        printf("%d ",c[i-n/2]);
    }
    printf("\n");

    // Create threads with default attributes for first sorting the 2 parts of the array :- 
    // 1) th1 to sort 1st part
    // 2) th2 to sort 2nd part
    pthread_create(&th1,NULL,partoflist1,&b);
    pthread_create(&th2,NULL,partoflist2,&c);
    

    // using pthread_join to wait for the target threads to complete first.
    pthread_join(th1,NULL); // block main function till thread 1 terminates
    pthread_join(th2,NULL); // block main function till thread 2 terminates

    // Create thread for the merging the 2 sorted arrays :-
    pthread_create(&th3,NULL,merge,&d);
    
    pthread_join(th3,NULL); // block main function till thread 3 terminates
    
    // Our job is complete, hence return and exit the program
    return 0;
}