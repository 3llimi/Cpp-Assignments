#include <bits/stdc++.h>
using namespace std;
 
//Abstract class for a data structure
class DataStructure {
public:
    virtual void insert(int x) = 0;
    virtual void remove() = 0;
    virtual bool search(int x) = 0;
};
 
//Abstract class for a sequential data structure
class SequentialDataStructure : public DataStructure {
public:
    virtual void pushBack(int x) = 0;
    virtual void pushFront(int x) = 0;
    virtual void popBack() = 0;
    virtual void popFront() = 0;
};
 
//Abstract class for a dynamic data structure
class DynamicDataStructure : public DataStructure {
public:
    virtual void resize(int new_size) = 0;
    virtual void clear() = 0;
};
 
//Class List implementing both SequentialDataStructure and DynamicDataStructure
class List : public SequentialDataStructure, public DynamicDataStructure {
 
public:
    //Implementation of insert function
    void insert(int x) override {
        data.push_back(x); //Insert the integer at the back of the list
    }
 
    //Implementation of remove function
    void remove() override {
        if (!data.empty()) //Check if list is not empty
            data.pop_back(); //Remove the integer from the back of the list
    }
 
    //Implementation of search function
    bool search(int x) override {
        //Loop through the list
        for (int num : data) {
            if (num == x) //If the integer is found
                return true; //Return true
        }
        return false; //Else return false
    }
 
    //Implementation of pushBack function
    void pushBack(int x) override {
        data.push_back(x); //Insert the integer at the back of the list
    }
    //Implementation of pushFront function
    void pushFront(int x) override {
        data.insert(data.begin(), x); //Insert the integer at the front of the list
    }
 
    //Implementation of popBack function
    void popBack() override {
        if (!data.empty()) //Check if list is not empty
            data.pop_back(); //Remove the integer from the back of the list
    }
 
    //Implementation of popFront function
    void popFront() override {
        if (!data.empty()) //Check if list is not empty
            data.erase(data.begin()); //Remove the integer from the front of the list
    }
 
    //Implementation of resize function
    void resize(int new_size) override {
        data.resize(new_size); //Resize the list to the specified size
    }
    //Implementation of clear function
    void clear() override {
        data.clear(); //Clear all elements from the list
    }
    vector<int> data; //Vector to store the list elements
};
 
int main()
{
    int n;
    string order;
    List list; //Creation of an instance of List
    int k;
    cin>>n; //Input number of operations
    for (int i = 0; i < n; ++i) {
        cin>>order; //Input operation type
        if (order == "insert"){
            cin>>k;
            list.insert(k); //Insert value into the list
        }else if(order == "search"){
            cin>>k;
            //Search for value in the list
            if (list.search(k)){
                cout<<"YES"<<endl; //If value is found print YES
            }else{
                cout<<"NO"<<endl; //Else print NO
            }
        }else{ // else then we assume that  the operation is "remove"
            list.remove(); //Remove the last integer from the list
        }
    }
    //Loop through the list elements and print each element
    for (int num : list.data) {
        cout <<num<<" ";
    }
    return 0;
}