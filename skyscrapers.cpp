/*******************************************************************************
 * Name        : skyscrapers.cpp
 * Author      : Michael Curry and Justin Tsang
 * Version     : 1.0
 * Date        : 3/7/2016
 * Description : Print amount of variation can reach all skyscrapers
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <string>
#include <istream>
#include <stdio.h>
#include <sstream>

using namespace std;

// Get the number of skyscrapers can get to
long long getSkyscrapers(long buildings[], long &amtBuildings) {
	// Variable initialization
	long long ctr = 0;

	// If more than one building
	if (amtBuildings > 1) {
		long* stack = new long[amtBuildings];
		long indexStack = 0;
		long counterIndex = 1;
		stack[0] = buildings[0];
		// Iterate throughout array of building heights
		for (long index = 1; index < amtBuildings; ++index) {
			// If buidling height is equal or less than the value at top stack
			// push value to top of stack
			if (buildings[index] <= stack[indexStack]) {
				stack[++indexStack] = buildings[index];
			// If value is greater than the value at top of stack,
			// pop from stack until reach value that is equal or stack is empty
			// Count number of equal values at stack and add to ctr
			} else {
				while ((indexStack > -1) && (buildings[index] > stack[indexStack])) {
					long currHeight = stack[indexStack--];
					while ((indexStack > -1) && (stack[indexStack] == currHeight)) {
						++counterIndex;
						--indexStack;
					}
					ctr += counterIndex * (counterIndex - 1);
					counterIndex = 1;
				}
				stack[++indexStack] = buildings[index];
			}
		}
		// At completion of array iteration
		// If stack is not empty, pop and find matching values and keep count
		// Add the number of options from count
		while (indexStack > -1) {
			long currHeight = stack[indexStack--];
			while ((indexStack > -1) && (stack[indexStack] == currHeight)) {
				--indexStack;
				++counterIndex;
			}
			ctr += counterIndex * (counterIndex - 1);
			counterIndex = 1;
		}
		delete stack;
	}
	return ctr;
}

int main() {
	long numBuilding;
	// If not integer or numBuilding outside range [1:300000]
	if (!(cin >> numBuilding) || ((numBuilding < 1) || (numBuilding > 300000))) {
		cerr << "Error: Input must be in range [1:300000]. Received " <<
				numBuilding << ".\n";
		return 1;
	}
	cin.ignore();
	// Create array of amount
	long* buildingHeights = new long[numBuilding];
	long index = 0;
	string strHeights;
	// Take user input for height value
	getline(cin, strHeights);
	long start_pos = 0, end_pos = 0;
	long height;
	// Parse string for empty space and append to array
	while ((end_pos = strHeights.find(" ", start_pos)) != string::npos)
	{
		string currHeight = strHeights.substr(start_pos, end_pos - start_pos);
		istringstream iss(currHeight);
		// If the substring is not integer or outside range [1:1000000]
		if (!(iss >> height) || ((height < 1) || (height > 1000000))) {
			delete buildingHeights;
			cerr << "Error: Not valid integer [1:1000000]. Received " <<
					currHeight << ".\n";
			return 1;
		}
		buildingHeights[index++] = height;
		start_pos = end_pos + 1;
	}
	istringstream iss(strHeights.substr(start_pos, end_pos));
	// If the substring is not integer or outside range [1:1000000]
	if (!(iss >> height) || ((height < 1) || (height > 1000000))) {
		delete buildingHeights;
		cerr << "Error: Not valid integer [1:1000000]. Received " <<
				strHeights.substr(start_pos, end_pos) << ".\n";
		return 1;
	}
	buildingHeights[index++] = height;
	// Check if amount of heights given does not match numBuilding given
	if (index != numBuilding) {
		delete buildingHeights;
		cerr << "Error: Expecting " << numBuilding << " input. Received " <<
				 index << " input.\n";
		return 1;
	}
	// Perform the count of amount of variation of skyscraper travel
	cout << getSkyscrapers(buildingHeights, numBuilding) << "\n";
	delete buildingHeights;
	return 0;
}