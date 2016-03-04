#include <iostream>
#include <string>
#include <istream>
#include <stdio.h>
#include <sstream>

using namespace std;

int getSkyscrapers(int buildings[], int &amtBuildings) {
	int ctr = 0;
	int indexStack = 0;
	int indexCountStack = 0;
	int stack[amtBuildings];
	int countStack[amtBuildings];

	if (amtBuildings > 1) {
		stack[0] = buildings[0];
		for (int index = 1; index < amtBuildings; ++index) {
			if (buildings[index] <= stack[indexStack]) {
				stack[++indexStack] = buildings[index];
			// } else if (buildings[i] == stack[indexStack]) {
			// 	stack[++indexStack] = buildings[i];
			} else {
				while ((indexStack > -1) && (buildings[index] > stack[indexStack])) {
					int currHeight = stack[indexStack--];
					countStack[indexCountStack++] = currHeight;
					while (stack[indexStack] == currHeight) {
						countStack[indexCountStack++] = currHeight;
						--indexStack;
					}
					if (indexStack > -1) {
						ctr += (indexCountStack * (indexCountStack - 1)) / 2;
					}
					indexCountStack = 0;
				}
				stack[++indexStack] = buildings[index];
			}
		}
		while (indexStack > -1) {
			int currHeight = stack[indexStack--];
			countStack[indexCountStack++] = currHeight;
			while (stack[indexStack] == currHeight) {
				countStack[indexCountStack++] = currHeight;
				--indexStack;
			}
			ctr += (indexCountStack * (indexCountStack - 1)) / 2;
			indexCountStack = 0;
		}
	}
	return (2 * ctr);
}

int main() {
	int numBuilding;
	if (!(cin >> numBuilding) || (numBuilding < 1) || 
		(numBuilding > 300000)) {
		cerr << "Error: Input must be in range [1:300000]\n";
		return 1;
	}
	int buildingHeights[numBuilding];
	int index = 0;
	string strHeights;
	cin.ignore();
	getline(cin, strHeights);
	int start_pos = 0, end_pos = 0;
	int height;
	while ((end_pos = strHeights.find(" ", start_pos)) != string::npos) 
	{
		string currHeight = strHeights.substr(start_pos, end_pos - start_pos);
		istringstream iss(currHeight);
		if (!(iss >> height) || height < 0 || height > 1000000) {
			return 1;
		}
		buildingHeights[index++] = height;
		start_pos = end_pos + 1;
	}
	istringstream iss(strHeights.substr(start_pos, end_pos));
	if (!(iss >> height) || height < 0 || height > 1000000) {
		return 1;
	}
	buildingHeights[index++] = height;
	if (index != numBuilding) {
		cerr << "Amount not equal to amount heights\n";
		return 1;
	}
	cout << getSkyscrapers(buildingHeights, numBuilding) << "\n";
	return 0;
}