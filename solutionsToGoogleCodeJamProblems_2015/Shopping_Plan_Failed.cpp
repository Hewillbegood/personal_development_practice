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
	bool operator == (const ItemToBuy& c) const
	{
		return this->name == c.name;
	}
};

struct ItemToSell {
	double price;
	string name;
	bool operator == (const ItemToSell& c) const
	{
		return this->name == c.name;
	}
};

struct Store {
	double x;
	double y;
	vector<ItemToSell> itemsToSell;
};

double MinCost(int iCurrLoc, vector<int> iCurrItems, vector<int> iItemsBought,
	vector<int> iStoresUsed, ItemToBuy* allItemsToBuy, Store* allStores,
	int cItemsToBuy, int cStores, double gasPrice, double** distX) {
	// -__- thing A figured out by me.

	double currCost = INT_MAX;

	if (iCurrLoc == cStores) {
		// current position is the home.
		assert(iCurrItems.size() == 0);	// A handled over home position.
		if (iItemsBought.size() == 0) {
			// the beginning home position.
			return 0;
		}
		else {
			// the final home position.
			for (int i = 0; i < cStores; i++) {

				vector<int> iItemsToBe;
				for (int j = 0; j < allStores[i].itemsToSell.size(); j++) {

					int forCmp;
					for (int k = 0; k < cItemsToBuy; k++) {
						if (allItemsToBuy[k].name == allStores[i].itemsToSell[j].name) forCmp = k;
					}
					iItemsToBe.push_back(forCmp);
				}

				// items assigned to a previous store simutaneously.  -__- combination scale.
				double tmpCost = 0;
				tmpCost += double(gasPrice) * (distX[iCurrLoc][i]);
				// cout << "tmpCost1 == " << tmpCost << endl;
				double mc = MinCost(i, iItemsToBe, iItemsBought, iStoresUsed, allItemsToBuy, allStores,
					cItemsToBuy, cStores, gasPrice, distX);
				if (mc >= 0) {
					tmpCost += mc;
					// cout << "tmpCost3 == " << fixed << setprecision(7) << tmpCost << endl;
					if (tmpCost < currCost) currCost = tmpCost;
				}
				else {
					cout << "-1 present.\n";
				}
			}
		}
	}
	else {
		// current position is some store.
		double payment = 0;

		// common.
		for (int i = 0; i < iCurrItems.size(); i++) {
			ItemToSell forCmp;
			forCmp.name = allItemsToBuy[iCurrItems[i]].name;
			forCmp.price = 0;
			vector<ItemToSell>::iterator iFindToSell = find(allStores[iCurrLoc].itemsToSell.begin(),
				allStores[iCurrLoc].itemsToSell.end(), forCmp);
			if (iFindToSell != allStores[iCurrLoc].itemsToSell.end())
				payment += (*iFindToSell).price;

			vector<int>::iterator iFindBought = find(iItemsBought.begin(), iItemsBought.end(), iCurrItems[i]);
			if (iFindBought != iItemsBought.end()) iItemsBought.erase(iFindBought);
		}

		iStoresUsed.push_back(iCurrLoc);

		if (iItemsBought.size() == 0) {
			// initial home-to-store.
			double tmpCost = 0;
			tmpCost += double(gasPrice) * (distX[iCurrLoc][cStores]);
			// cout << "tmpCost 1 == " << tmpCost << endl;
			tmpCost += payment;
			// cout << "tmpCost2 == " << tmpCost << endl;

			vector<int> tmpV;
			double mc = MinCost(cStores, tmpV, iItemsBought, iStoresUsed, allItemsToBuy, allStores, cItemsToBuy, cStores,
				gasPrice, distX);
			if (mc >= 0) {
				tmpCost += mc;
				// cout << "tmpCost3 == " << fixed << setprecision(7) << tmpCost << endl;
				if (tmpCost < currCost) currCost = tmpCost;
			}
			else {
				cout << "-1 present.\n";
			}
		}
		else if (iStoresUsed.size() == cStores) {
			cout << "return -1.\n";
			return -1;
		}
		else {
			// store to store.
			for (int i = 0; i < cStores; i++) {
				vector<int>::iterator iFindStore = find(iStoresUsed.begin(), iStoresUsed.end(), i);
				if (iFindStore != iStoresUsed.end()) continue;

				vector<int> iItemsToBe;
				bool pevishableFound = false;
				for (int j = 0; j < allStores[i].itemsToSell.size(); j++) {

					int forCmp;
					for (int k = 0; k < cItemsToBuy; k++) {
						if (allItemsToBuy[k].name == allStores[i].itemsToSell[j].name) forCmp = k;
					}

					vector<int>::iterator iFindBought = find(iItemsBought.begin(), iItemsBought.end(), forCmp);
					if (iFindBought != iItemsBought.end()) {
						if (allItemsToBuy[forCmp].isPevishable) pevishableFound = true;
						iItemsToBe.push_back(forCmp);
					}
				}

				if (iItemsToBe.size() == 0) continue;

				// items assigned to a previous store simutaneously.  -__- combination scale.
				double tmpCost = 0;
				if (pevishableFound) {
					tmpCost += double(gasPrice) * (distX[iCurrLoc][cStores] + distX[cStores][i]);
				}
				else {
					tmpCost += double(gasPrice) * (distX[iCurrLoc][i]);
				}
				// cout << "tmpCost1 == " << tmpCost << endl;
				tmpCost += payment;
				// cout << "tmpCost2 == " << tmpCost << endl;
				double mc = MinCost(i, iItemsToBe, iItemsBought, iStoresUsed, allItemsToBuy, allStores,
					cItemsToBuy, cStores, gasPrice, distX);
				if (mc >= 0) {
					tmpCost += mc;
					// cout << "tmpCost3 == " << fixed << setprecision(7) << tmpCost << endl;
					if (tmpCost < currCost) currCost = tmpCost;
				}
				else {
					cout << "-1 present.\n";
				}
			}
		}
	}

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

				stores[i].itemsToSell.push_back(item);
			}
		}

		cout << "Case #" << iCase << ":";
		for (int i = 0; i < cItems; i++) {
			cout << " " << itemsToBuy[i].isPevishable << ":" << itemsToBuy[i].name;
		}
		cout << endl;
		for (int i = 0; i < cStores; i++) {
			cout << stores[i].x << " " << stores[i].y;
			for (int j = 0; j < stores[i].itemsToSell.size(); j++) {
				cout << " " << stores[i].itemsToSell[j].name << ":" << stores[i].itemsToSell[j].price;
			}
			cout << endl;
		}
		cout << endl;

		//
		// process.
		//

		// distance matrix.
		double** distX = new double*[cStores + 1];
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
		distX[cStores][cStores] = 0;
		for (int i = 0; i < cStores + 1; i++) {
			for (int j = 0; j < cStores + 1; j++) {
				cout << fixed << setw(10) << setprecision(3) << distX[i][j];
			}
			cout << endl;
		}
		cout << endl;

		vector<int> iFinalCurrItems;
		vector<int> iFinalItemsBought;
		vector<int> iFinalStoresUsed;
		for (int i = 0; i < cItems; i++) {
			iFinalItemsBought.push_back(i);
		}

		// recursive procedure.
		double cost = MinCost(cStores, iFinalCurrItems, iFinalItemsBought, iFinalStoresUsed,
			itemsToBuy, stores, cItems, cStores, gasPrice, distX);

		//
		// output.
		//

		cout << fixed << setprecision(7) << cost << endl << endl << endl;
		outfile << "Case #" << iCase << ": " << fixed << setprecision(7) << cost << endl;

		delete[] stores;
		delete[] itemsToBuy;
	}

	infile.close();
	outfile.close();
	system("pause");
	return 0;
}