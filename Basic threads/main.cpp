#include <iostream>
#include <thread>

using namespace std;

void print_numbers(int start, int end);

int main() {
    int start,end;
    cout << "Enter begging and end of numeric line" << endl;
    cin >> start >> end;
    thread t1(print_numbers,start,end);

    if(t1.joinable()){
        t1.join();
    }

    return 0;
}

void print_numbers(int start, int end){
    for (int i = start; i <= end; ++i) {
        cout << i << " ";
    }

}