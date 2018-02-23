#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

vector<long long int> calculate(long int sequence_copy[],int n,int pat,int win_size) {

    int k = win_size;
    vector<long long int> v;
    list<long int> window;
    list<long int> :: iterator it;
    long int sequence[n];
    long int temp = 0;
    for (int i = 0; i < n; i++) {
        if (sequence_copy[i] == pat || sequence_copy[i] == 0){
            sequence[i] = 1;
        }
        else{
            sequence[i] = 0;
        }
    }

    long int sum = 0;
    long long int total = 0;
    long long int left_sum = 0;
    long long int right_sum = 0;
    for (int i = 0; i < k; i++) {
        if (sequence[i] == 1){
            sum += 1;
        }
        else{
            if (sum != 0) {
                window.push_back(sum);
            }
            sum = 0;
        }
    }
    if (sum != 0){
        window.push_back(sum);
    }
    total = 0;
    for (it = window.begin(); it != window.end(); it++){
        temp = *it + 1;
        total = total + (temp*(temp-1))/2;
    }
    v.push_back(total);

    for (int i = k; i < n; i++) {
        left_sum = 0;
        right_sum = 0;
        if (window.size() == 0 ){
            if (sequence[i] == 1){
                window.push_back(1);
                right_sum += 1;
            }
        }
        else if (window.size() >= 1) {
            if (sequence[i] == 1 ){
                if (sequence[i-1] == 0){
                        right_sum += 1;
                        window.push_back(1);
                }
                else{
                    it = window.end();
                    it--;
                    temp = *it;
                    right_sum = temp + 1;
                    *it = temp + 1;
                }
            }
            if (sequence[i-k] == 1){
                it = window.begin();
                temp = *it;
                left_sum -= temp;
                temp -= 1;
                *it = temp;
                if (temp == 0 ){
                    window.pop_front();
                }
            }
        }
        total += left_sum + right_sum;
        v.push_back(total);
    }
    return v;
}

int main(){
    int n,k = 0;
    cin >> n >> k;
    long int array[n];
    long int sequence[n-1];
    for (int i = 0; i < n; i++) {
        cin >> array[i];
    }
    if (k == 1){
        for (int i = 0; i < n; i++) {
            cout << 0 << endl;
        }
    }
    else{
        for (int i = 0; i < n-1; i++) {
            sequence[i] = 0;
        }
        for (int i = 0; i < n-1; i++) {
            if (array[i] < array[i+1]) {
                sequence[i] = 1;
            }
            else if ( array[i] > array[i+1]) {
                sequence[i] = -1;
            }
            else {
                sequence[i] = 0;
            }
        }
        vector<long long int> count_non_increasing;
        vector<long long int> count_non_decreasing;

        count_non_increasing = calculate(sequence,n-1,1,k-1);
        count_non_decreasing = calculate(sequence,n-1,-1,k-1);

        int len_range = count_non_increasing.size();

        for (int i = 0; i < len_range; i++) {
            cout << count_non_increasing[i] - count_non_decreasing[i] << endl;
        }
    }
    return 0;
}
