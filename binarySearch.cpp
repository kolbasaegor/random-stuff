#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int binarySearch(vector <int> a,int size, int elem){
    int index = -1;
    int l = 0;
    int r = size - 1;
    int mid = (l+r) / 2;
    if(elem == a[l]) return l;
    if(elem == a[r]) return r;
    if(elem == a[mid]) return mid;

    while( l<=r && a[mid] != elem){
        mid =(l+r) / 2;
        //cout << l << " " << r << endl;
        if(a[mid] == elem){
            index = mid;
            break;
        }
        else{
            if(a[mid] > elem) r = mid - 1;
            else if (a[mid] < elem) l =mid + 1;
        }
    }

    return index;
}
