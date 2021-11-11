# Multithreaded Sorting Application

## Description
Write a multithreaded sorting program that works as follows: A list of integers is divided into two smaller lists of equal size. Two separate threads (which we will term sorting threads) sort each sublist using a sorting algorithm of your choice. The two sublists are then merged by a third thread — a merging thread — which merges the two sublists into a single sorted list.

## Basic Idea
First divide the array into two subarrays or 2 parts, each of which is then sorted by an individual thread. Create Another thread to merge the 2 sorted parts to make one complete sorted array.

## Details

### Sorting 1st Part
Gets input as an array of integers, size = length of 1st part of the full array. Uses Bubble sort technique to sort the array.
```
// Sort the 1st part of the array
void* partoflist1(int arr[]){
    //sleep(1);

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
```
### Sorting 2nd Part
Gets input as an array of integers, size = length of 2nd part of the full array. Uses Bubble sort technique to sort the array.
```
// sort the 2nd part of the array
void* partoflist2(int arr[]){
    //sleep(2);

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
```
### Merging the 2 Sorted Parts
Takes input as array into which we have to store the sorted list. Uses 2 pointer approach to combine the 2 sorted lists.
```
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
```
### Main Function
In the main function, we take input of an array of some length n.
```
int main(){

    // initialize variables
    int n,i,j=0,k=0;

    // Get the array from the console
    printf("Enter size of array:");
    scanf("%d",&n);
    printf("Now Enter the Array: ");
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
```
We divide this array into 2 equal parts (if length is odd then one array has an extra element).
```
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
```

Then we declare threads and create them. We wait for them to complete before terminating the main function. When all of our threads terminate, our job is done and we return from the main function
```
    // declare threads...
    // pthread_t is a data-type
    pthread_t th1,th2,th3;
    
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
```

## Result
```
Enter size of array:10 
Now Enter the Array: 17 26 0 9 7 14 45 13 13 0
First array:- 17 26 0 9 7 
Second array:- 14 45 13 13 0 
Sorted Part 1 of the list :- 0 7 9 17 26 
Sorted Part 2 of the list :- 0 13 13 14 45 
Completely Sorted List :- 0 0 7 9 13 13 14 17 26 45
```

## Credits
[https://github.com/forestLoop/Learning-EI338](https://github.com/forestLoop/Learning-EI338)

[https://github.com/sarmadhashmi/multithreaded-sudoku-validator](https://github.com/sarmadhashmi/multithreaded-sudoku-validator)
