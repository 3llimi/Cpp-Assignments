#include <iostream>
using namespace std;
 
 
//Function to calculate the sum of the integers in the array from index 'a' to index 'b' (inclusive)
void sum(int *arr, int a, int b) {
    int sum = 0;
    for (int i = a; i <= b; ++i) {
        sum += *(arr + i);
    }
    cout<<sum<<endl; //Output the sum
}
 
//Function to set the value of an element at a given index in the array
void set(int *arr, int &index, int &value) {
    *(arr + index) = value;
}
 
//Function to print the elements of the array
void printArray(const int *arr, int size) {
    const int *ptr = arr;
    const int *endPtr = arr + size;
 
    //Loop through the array and print each element
    while (ptr < endPtr) {
        cout << *ptr << " "; //Output the current element
        ptr++; //Move to the next element
    }
    cout <<endl;
}
 
 
int main() {
    int n, m,a,b;
    string op;
    cin >> n >> m; //Input the size of the array 'n' and the number of operations 'm'
    int *arr = new int[n]; //Dynamic allocation of memory for the array
 
    //Input the elements of the array
    for (int i = 0; i < n; ++i) {
        cin >> *(arr + i);
    }
 
    //Perform operations based on the input
    for (int i = 0; i < m; ++i) {
        cin>>op>>a>>b; //Input the operation type and its parameters
        if(op == "sum"){
            sum(arr,a,b); //Call the 'sum' function
        } else{
            set(arr, a, b); //Call the 'set' function
        }
    }
    
    printArray(arr, n); //Print the array
 
    delete[] arr;
    return 0;
}