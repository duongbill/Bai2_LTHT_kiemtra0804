#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <windows.h>  

using namespace std;

float* arr = nullptr;
int size = 0;
int capacity = 10;

bool task1_done = false;
mutex mtx;
condition_variable cv;

void inputArray() {
    arr = new float[capacity];

    float num;
    

    while (true) {
       	cout << "Nhap cac so thuc (-1 de ket thuc): ";
        cin >> num;
        if (num == -1) break;

        unique_lock<mutex> lock(mtx);

        if (size >= capacity) {
            capacity *= 2;
            float* newArr = new float[capacity];
            for (int i = 0; i < size; i++) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }

        arr[size++] = num;
    }

    {
        unique_lock<mutex> lock(mtx);
        task1_done = true;
    }
    cv.notify_one();
}

void sumPositiveNumbers() {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [] { return task1_done; });

    float sum = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i] > 0) {
            sum += arr[i];
        }
    }

    cout << "\nTong cac so duong: " << sum << endl;
    Beep(750, 300);  // Âm thanh thông báo
}

int main() {
    thread t1(inputArray);
    thread t2(sumPositiveNumbers);

    t1.join();
    t2.join();

    delete[] arr;
    return 0;
}

