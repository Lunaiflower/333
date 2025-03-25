#include<iostream>
using namespace std;

int main() {
	int x, y, z;
	cin >> x >> y >> z;
	while (true) {
		if (x + y > z) {
			cout << "Hello World!" << endl;
			break;
		}
		if (x + y < z) {
			cout << "I like study!" << endl;
			break;
		}
		cout << "Circulate" << endl;
	}
	return 0;
}