// https://www.spoj.com/problems/PIE/

#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<cmath>
#include<iomanip>
using namespace std;

double circle_area(double r) {
	const double PI = acos(-1.0);
	return PI * r * r;
}

bool onePeiceForEachOne(vector<double> &pie_volume, int people, double area)
{
	int people_count = 0;

	for (int i = 0; i < (int) pie_volume.size(); i++) {
		people_count += floor(pie_volume[i] / area);
		if (people_count >= people)
			return true;
	}
	return false;
}

double largest_area(vector<double> &pie_radius, int people) {

	vector<double> pie_volume(pie_radius.size());
	for (int i = 0; i < (int) pie_volume.size(); i++)
		pie_volume[i] = circle_area(pie_radius[i]);
	auto it = max_element(pie_volume.begin(), pie_volume.end());
	double start = 0, end = (double) *it;
	double mid;
	for (int i = 0; i < 100; i++) {
		mid = start + (end - start) / 2.0f;
        if (onePeiceForEachOne(pie_volume, people, mid))
            start = mid;
        else 
            end = mid;
	}

	return mid;
}

int main() {
	int cases, n, f;
	cin >> cases;

	while (cases--) {
		cin >> n >> f;
		vector<double> pie_radius(n);

		for (int i = 0; i < n; i++)
			cin >> pie_radius[i];

		double area = largest_area(pie_radius, f + 1);	// +1 for the host person

		cout << fixed;
		cout << setprecision(4) << area << "\n";
	}
	return 0;
}
