#include <iostream>
using namespace std;

int main(){
    class Int{
    public:
        int a, b;
        Int(int a, int b){
            this->a = a;
            this->b = b;
            cout << "Int(int,int)" << endl;
        }
        Int(){
            this->a = 1;
            this->b = 2;
            cout << "Int()" << endl;
        }
        ~Int(){
            cout << "~Int()" << endl;
        }
    };

    Int I{10,20};

    cout << I.a << " " << I.b << endl;

    return 0;
}
