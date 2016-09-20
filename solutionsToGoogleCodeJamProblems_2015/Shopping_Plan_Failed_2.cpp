#include <fstream>
#include <iostream>
#include <assert.h>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

struct ItemToBuy {
	string name;
	bool isPevishable;
};

struct ItemToSell {
	double price;
	string name;
	int iToBuy;	// the index of this item in the array of itemsToBuy
};

struct Store {
	double x;
	double y;
	vector<ItemToSell> itemsToSell;
};

double MinCost(int iCurrLoc, /*this value is the index of stores, specially, value "cStores" means the home*/
	bool* itemRem, int cItemsRem, /*bool array serving as a mask, true for remaining(need to buy)*/
	/*the following parameters are all constant ones*/
	ItemToBuy* allItemsToBuy,
	Store* allStores, int cItemsToBuy, int cStores, double gasPrice, double** distX) {

	double currCost = INT_MAX;

	// to make a copy of array itemRem for further usage.
	bool* thisItemRem = new bool[cItemsToBuy];
	for (int i = 0; i < cItemsToBuy; i++) {
		thisItemRem[i] = itemRem[i];
	}

	if (iCurrLoc == cStores) { // the current position is the home.
		if (cItemsRem == 0) {
			return 0;
		}
		else {
			for (int i = 0; i < cStores; i++) {
				double localCost = 0;
				localCost += gasPrice * distX[iCurrLoc][i];
				double mc = MinCost(i, thisItemRem, cItemsRem, allItemsToBuy, allStores, cItemsToBuy,
					cStores, gasPrice, distX);
				if (mc > -0.0000001F) { // if stores[i] doesn't contain any item in the itemRem list, ignore this route.
					localCost += mc;
					if (localCost < currCost) currCost = localCost;
				}
			}
		}
	}
	else {	// the current position is one of the stores.
		bool needHome = false;
		bool returnM1 = true;		// if this store doesn't contain any item in the itemRem list, return -1 which <= -0.0000001F

		double localCost = 0;
		for (int i = 0; i < allStores[iCurrLoc].itemsToSell.size(); i++) {
			ItemToSell* currItem = &allStores[iCurrLoc].itemsToSell[i];
			if (thisItemRem[currItem->iToBuy]) {
				if (allItemsToBuy[currItem->iToBuy].isPevishable) needHome = true;
				returnM1 = false;
				localCost += currItem->price;
				thisItemRem[currItem->iToBuy] = false;
				cItemsRem--;
			}
		}

		if (needHome || cItemsRem == 0) { // the next position is the home.
			localCost += gasPrice * distX[iCurrLoc][cStores];
			localCost += MinCost(cStores, thisItemRem, cItemsRem, allItemsToBuy, allStores,
				cItemsToBuy, cStores, gasPrice, distX);
			if (localCost < currCost) currCost = localCost;
		}
		else if (returnM1) {
			return -1;
		}
		else {	// the next position is one of the stores.
			for (int i = 0; i < cStores; i++) {
				localCost += gasPrice * distX[iCurrLoc][i];
				double mc = MinCost(i, thisItemRem, cItemsRem, allItemsToBuy, allStores, cItemsToBuy,
					cStores, gasPrice, distX);
				if (mc > -0.0000001F) {
					localCost += mc;
					if (localCost < currCost) currCost = localCost;
				}
			}
		}
	}
	delete[] thisItemRem;
	return currCost;
}

int main() {

	int cCases = 0;
	ifstream infile("D-small-practice.in");
	ofstream outfile("outfile.out");
	infile >> cCases;

	for (int iCase = 1; iCase <= cCases; iCase++) {
		//
		// input.
		//

		int cItems = 0, cStores = 0;
		double gasPrice = 0;
		infile >> cItems >> cStores >> gasPrice;

		// information of items to buy is kept in the array itemsToBuy.
		ItemToBuy* itemsToBuy = new ItemToBuy[cItems];
		for (int i = 0; i < cItems; i++) {
			string tmp;
			infile >> tmp;
			if (tmp[tmp.size() - 1] == '!') {
				itemsToBuy[i].name = tmp.substr(0, tmp.size() - 1);
				itemsToBuy[i].isPevishable = true;
			}
			else {
				itemsToBuy[i].name = tmp;
				itemsToBuy[i].isPevishable = false;
			}
		}

		// information of stores is kept in the array stores.
		Store* stores = new Store[cStores];
		infile.get();
		for (int i = 0; i < cStores; i++) {
			string tmpStr;
			getline(infile, tmpStr);

			stringstream ss;
			ss << tmpStr;

			ss >> stores[i].x;
			ss >> stores[i].y;

			while (!ss.eof()) {
				string oneItemToSell;
				ss >> oneItemToSell;
				int idxColon = oneItemToSell.find(':');
				ItemToSell item;
				item.name = oneItemToSell.substr(0, idxColon);

				stringstream stoiSS;
				stoiSS << oneItemToSell.substr(idxColon + 1, oneItemToSell.size() - idxColon - 1);
				stoiSS >> item.price;

				for (int j = 0; j < cItems; j++) {
					if (item.name == itemsToBuy[j].name) {
						item.iToBuy = j;
						break;
					}
				}

				stores[i].itemsToSell.push_back(item);
			}
		}

		// output the information of items and stores to check out if the input procedure is correct.
		cout << "Case #" << iCase << ":";
		for (int i = 0; i < cItems; i++) {
			cout << " " << itemsToBuy[i].isPevishable << ":" << itemsToBuy[i].name;
		}
		cout << endl;
		for (int i = 0; i < cStores; i++) {
			cout << stores[i].x << " " << stores[i].y;
			for (int j = 0; j < stores[i].itemsToSell.size(); j++) {
				cout << " " << stores[i].itemsToSell[j].name << ":" << stores[i].itemsToSell[j].price
					<< "(" << stores[i].itemsToSell[j].iToBuy << ")";
			}
			cout << endl;
		}
		cout << endl;

		//
		// process.
		//

		// distance matrix.
		double** distX = new double*[cStores + 1];	// the index "cStores" represents the home.
		for (int i = 0; i < cStores + 1; i++) {
			distX[i] = new double[cStores + 1];
		}
		for (int i = 0; i < cStores; i++) {
			double horiX = stores[i].x;
			double horiY = stores[i].y;
			for (int j = 0; j < cStores; j++) {
				double vertX = stores[j].x;
				double vertY = stores[j].y;

				distX[i][j] = sqrt(abs(horiX - vertX) * abs(horiX - vertX) + abs(horiY - vertY) * abs(horiY - vertY));
			}
		}
		for (int i = 0; i < cStores; i++) {
			double x = stores[i].x;
			double y = stores[i].y;
			distX[cStores][i] = sqrt(x * x + y * y);
			distX[i][cStores] = distX[cStores][i];
		}
		// output the distance matrix to validate.
		distX[cStores][cStores] = 0;
		for (int i = 0; i < cStores + 1; i++) {
			for (int j = 0; j < cStores + 1; j++) {
				cout << fixed << setw(10) << setprecision(3) << distX[i][j];
			}
			cout << endl;
		}
		cout << endl;

		// main job.
		bool* itemRem = new bool[cItems];
		for (int i = 0; i < cItems; i++) { // make all items remaining.
			itemRem[i] = true;
		}
		double cost = MinCost(cStores, itemRem, cItems, itemsToBuy, stores, cItems, cStores,
			gasPrice, distX);

		//
		// output.
		//

		cout << fixed << setprecision(7) << cost << endl << endl << endl;
		outfile << "Case #" << iCase << ": " << fixed << setprecision(7) << cost << endl;

		delete[] itemRem;
		delete[] stores;
		delete[] itemsToBuy;
	}

	infile.close();
	outfile.close();
	system("pause");
	return 0;
}