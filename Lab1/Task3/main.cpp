#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    int arr[n];
    vector<int> vec;
    for(int i = 0; i < n; i ++) {
        int a;
        cin >> a;
        arr[i] = a;
        vec.push_back(a);
    }

    //solution for array
    bool used[1000000];
    int ans[n];
    for(int i = 0; i < 1000000; i ++) {
        used[i] = 0;
    }
    int j = 0;
    for(int i = 0; i < n; i ++) {
        if(!used[arr[i]]) {
            used[arr[i]] = 1;
            ans[j] = arr[i];
            j ++;
        }
    }
    cout << "solution by array:" << endl;
    for(int i = 0; i < j; i ++) {
        cout << ans[i] << " ";
    }
    cout << endl;

    //solution for vector
    sort(vec.begin(), vec.end());
    for(int i = 1; i < vec.size(); i ++) {
        if(vec[i] == vec[i-1]) {
            int temp = vec[i];
            erase(vec, vec[i]);
            vec.insert(vec.begin() + i-1, temp);
        }
    }
    cout << "solution by vector:" << endl;
    for(int i = 0; i < vec.size(); i ++){
        cout << vec[i] << " ";
    }
}
