#include <iostream>
#include <string>

using namespace std;

class Cat {    
public:
    int age;
    string nickname;
    
    
    Cat(int age, string nickname) : age(age), nickname(nickname) {
        
    }

    void operator[](int n) {
        if (n==0) {
            cout << nickname << endl;
        }
        if (n==1) {
            cout << age << endl;
        }
    }
};
    

