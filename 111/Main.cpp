//#define _CRT_SECURE_NO_WARNINGS
//
//#include<iostream>
//#include<algorithm>
//
//using namespace std;
//
//bool flag_invert = false;
//
//double Middle(int a[], int l) {
//    double mid;
//    if (l % 2 == 0) {
//        mid = (a[l / 2] + a[l / 2 - 1]) / 2.0;
//    }
//    else mid = a[l / 2];
//
//    //cout << mid << endl;
//    return mid;
//}
//
//void CopyArray(int a[], int a_copy[], int n, int m, int flag) {
//
//    if (flag == 1) {
//        int j = n / 2;
//        for (int i = 0; i < m; i++) {
//            a_copy[i] = a[j++];
//        }
//    }
//    else {
//        for (int i = 0; i < m; i++) {
//            a_copy[i] = a[i];
//        }
//    }
//
//}
//
//double FindMiddleNum(int a[], int b[], int n) {
//    if (n == 1)
//        return (a[0] + b[0]) / 2.0;
//    if (n == 2) {
//        int c[4];
//        c[0] = a[0];
//        c[1] = a[1];
//        c[2] = b[0];
//        c[3] = b[1];
//        int temp;
//        for (int i = 0; i < 3; i++) {
//            for (int j = 0; j < 3 - i; j++) {
//                if (c[j] > c[j + 1]) {
//                    temp = c[j];
//                    c[j] = c[j + 1];
//                    c[j + 1] = temp;
//                }
//            }
//        }
//        return (c[1] + c[2]) / 2.0;
//    }
//    double mid_a = Middle(a, n);
//    double mid_b = Middle(b, n);
//
//    int m = 0;
//    if (n % 2 == 0) {
//        m = n / 2;
//    }
//    else m = n / 2 + 1;
//
//
//    int* a_copy = (int*)malloc(m * sizeof(int));
//    int* b_copy = (int*)malloc(m * sizeof(int));
//
//    if (mid_a == mid_b)
//        return mid_a;
//    if (mid_a < mid_b) {
//        if (!flag_invert) {
//            CopyArray(a, a_copy, n, m, 1);
//            CopyArray(b, b_copy, n, m, 0);
//        }
//        else {
//            CopyArray(a, a_copy, n, m, 0);
//            CopyArray(b, b_copy, n, m, 1);
//        }
//
//        double w = FindMiddleNum(a_copy, b_copy, m);
//
//        delete[] a_copy;
//        delete[] b_copy;
//        return w;
//    }
//    else if (mid_a > mid_b) {
//        if (!flag_invert) {
//            CopyArray(a, a_copy, n, m, 0);
//            CopyArray(b, b_copy, n, m, 1);
//        }
//        else {
//            CopyArray(a, a_copy, n, m, 1);
//            CopyArray(b, b_copy, n, m, 0);
//        }
//
//        double w = FindMiddleNum(a_copy, b_copy, m);
//
//        delete[] a_copy;
//        delete[] b_copy;
//        return w;
//    }
//}
//
//int main() {
//    int n;
//    cin >> n;
//    int* a = (int*)malloc(n * sizeof(int));
//    int* b = (int*)malloc(n * sizeof(int));
//    for (int i = 0; i < n; i++) {
//        cin >> a[i];
//    }
//    for (int i = 0; i < n; i++) {
//        cin >> b[i];
//    }
//    if (n > 1) {
//        if (a[0] > a[1])
//            flag_invert = true;
//    }
//    double mid = FindMiddleNum(a, b, n);
//    cout << mid << endl;
//    return 0;
//}
//
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double getMedianSingle(const vector<int>& arr) {
    int n = arr.size();
    if (n % 2 == 0)
        return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
    else
        return arr[n / 2];
}

double findMedianUtil(const vector<int>& X, const vector<int>& Y, int n) {

    if (n == 0) return -1; 
    if (n == 1) return (X[0] + Y[0]) / 2.0;
    if (n == 2) return (max(X[0], Y[0]) + min(X[1], Y[1])) / 2.0;

    double m1 = getMedianSingle(X);
    double m2 = getMedianSingle(Y);

    if (m1 == m2) return m1;

    if (m1 < m2) {
        if (n % 2 == 0)
            return findMedianUtil(vector<int>(X.begin() + n / 2 - 1, X.end()),
                vector<int>(Y.begin(), Y.begin() + n / 2 + 1), n - n / 2 + 1);
        else
            return findMedianUtil(vector<int>(X.begin() + n / 2, X.end()),
                vector<int>(Y.begin(), Y.begin() + n / 2 + 1), n - n / 2);
    }

    else {
        if (n % 2 == 0)
            return findMedianUtil(vector<int>(X.begin(), X.begin() + n / 2 + 1),
                vector<int>(Y.begin() + n / 2 - 1, Y.end()), n - n / 2 + 1);
        else
            return findMedianUtil(vector<int>(X.begin(), X.begin() + n / 2 + 1),
                vector<int>(Y.begin() + n / 2, Y.end()), n - n / 2);
    }
}

double findMedianSortedArrays(const vector<int>& X, const vector<int>& Y) {
    int n = X.size();
    return findMedianUtil(X, Y, n);
}

int main() {
    int n;
    cin >> n;
    vector<int> X(n), Y(n);

    for (int i = 0; i < n; ++i)
        cin >> X[i];
    for (int i = 0; i < n; ++i)
        cin >> Y[i];

    double median = findMedianSortedArrays(X, Y);
    cout << median << endl;

    return 0;
}
