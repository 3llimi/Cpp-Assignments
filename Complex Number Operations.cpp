#include <bits/stdc++.h>
 
using namespace std;
 
//Function to perform addition of two complex numbers
void add(double a, double b, double c, double d) {
    double nat = a + c; //Calculate the real part of the result
    double img = b + d; //Calculate the imaginary part of the result
    if (img<0){ //If the imaginary part is negative
        img=img*(-1); //Multiply it by -1 to make it positive
        cout<<fixed<<setprecision(2); //Set output precision to 2 decimal places
        cout<<nat<<"-"<<img<<"i"<<endl; //Output the result in the format: a-bi
    }else{
        cout<<fixed<<setprecision(2);
        cout<<nat<<"+"<<img<<"i"<<endl; //Output the result in the format: a+bi
    }
}
 
//Function to perform subtraction of two complex numbers
void sub(double a, double b, double c, double d) {
    double nat = a - c; //Calculate the real part of the result
    double img = b - d; //Calculate the imaginary part of the result
    if (img<0){ //If the imaginary part is negative
        img=img*(-1); //Multiply it by -1 to make it positive
        cout<<fixed<<setprecision(2); //Set output precision to 2 decimal places
        cout<<nat<<"-"<<img<<"i"<<endl; //Output the result in the format: a-bi
    }else{
        cout<<fixed<<setprecision(2);
        cout<<nat<<"+"<<img<<"i"<<endl; //Output the result in the format: a+bi
    }
}
 
//Function to perform multiplication of two complex numbers
void mul(double a, double b, double c, double d) {
    double nat = a * c + ((b * d) * (-1)); //Calculate the real part of the result
    double img = (a * d) + (c * b); //Calculate the imaginary part of the result
    if (img<0){ //If the imaginary part is negative
        img=img*(-1); //Multiply it by -1 to make it positive
        cout<<fixed<<setprecision(2); //Set output precision to 2 decimal places
        cout<<nat<<"-"<<img<<"i"<<endl; //Output the result in the format: a-bi
    }else{
        cout<<fixed<<setprecision(2);
        cout<<nat<<"+"<<img<<"i"<<endl; //Output the result in the format: a+bi
    }
}
 
//Function to perform division of two complex numbers
void division(double a, double b, double c, double d) {
    double nat = (a * c + b * d) / (c * c + d * d); //Calculate the real part of the result
    double img = (b * c - a * d) / (c * c + d * d); //Calculate the imaginary part of the result
    if (img<0){ //If the imaginary part is negative
        img=img*(-1); //Multiply it by -1 to make it positive
        cout<<fixed<<setprecision(2); //Set output precision to 2 decimal places
        cout<<nat<<"-"<<img<<"i"<<endl; //Output the result in the format: a-bi
    }else{
        cout<<fixed<<setprecision(2);
        cout<<nat<<"+"<<img<<"i"<<endl; //Output the result in the format: a+bi
    }
}
 
//Function to check if two complex numbers are equal
string equal(double a, double b, double c, double d) {
    double nat = a - c; //Calculate the difference between the real parts
    double img = b - d; //Calculate the difference between the imaginary parts
    if (nat == 0 && img == 0){ //If both differences are zero
        return "true"; //Return true
    }else{
        return "false"; //Else return false
    }
}
 
int main() {
    int n;
    double a, b, c, d;
    char op;
    cin >> n; //Input the number of operations to perform
    for (int i = 0; i < n; ++i) { //Loop over each operation
        cin >> op >> a >> b >> c >> d; //Input the operation and operands
        switch (op) { //Check the operation
            case '+':
                add(a, b, c, d); //Perform addition
                break;
            case '-':
                sub(a, b, c, d); //Perform subtraction
                break;
            case '*':
                mul(a, b, c, d); //Perform multiplication
                break;
            case '/':
                division(a, b, c, d); //Perform division
                break;
            default:
                cout << equal(a, b, c, d) << endl; //Check equality
                break;
        }
    }
    return 0;
}