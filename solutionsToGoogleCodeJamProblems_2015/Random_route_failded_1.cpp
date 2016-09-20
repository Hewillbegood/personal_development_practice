#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <assert.h>
#include <iomanip>
using namespace std;

struct SmallRoad {
	int len;
	double probability = 0.0;
	string start;
	string end;
};

struct CityInfo {
	int pathLen = 0;
	vector<vector<int>> paths;
	vector<vector<int>> paths1;
	CityInfo() {
		paths.reserve(20);
		paths1.reserve(20);
	}
};

int main() { // -__- paths clearing betraies following paths. I found a pointer solution.

	ifstream infile("C-small-practice.in");
	ofstream outfile("outfile.out");

	int cCase = 0;
	infile >> cCase;
	for (int iCase = 1; iCase <= cCase; iCase++) {
		
		cout << "Case #" << iCase << ":";
		int cSmalls = 0;
		infile >> cSmalls;
		string wholeStart;
		infile >> wholeStart;
		SmallRoad* smallRoads = new SmallRoad[cSmalls];
		for (int i = 0; i < cSmalls; i++) {
			infile >> smallRoads[i].start >> smallRoads[i].end >> smallRoads[i].len;
		}
		map<string, CityInfo> cities;

		cities.insert(pair<string, CityInfo>(wholeStart, CityInfo()));

		queue<int> smallRoadsTo;
		bool firstDone = false;
		int cLoop = 0;
		do {
			cLoop++;
			cout << " " << cLoop;
			if (firstDone) {
				int iSmall = smallRoadsTo.front();
				smallRoadsTo.pop();

				map<string, CityInfo>::iterator ite = cities.find(smallRoads[iSmall].end);
				map<string, CityInfo>::iterator its = cities.find(smallRoads[iSmall].start);
				assert(its != cities.end());
				if (ite != cities.end())  {// target exists.					
					int newPathLen = its->second.pathLen + smallRoads[iSmall].len;
					if (newPathLen < ite->second.pathLen) {// clear.				
						ite->second.paths.clear();
						ite->second.pathLen = newPathLen;
					}
					if (newPathLen <= ite->second.pathLen) {// add new.
						// longer path expelled from consideration.
						if (its->second.paths.size() == 0) {// no path in the starting city.						
							vector<int> tmpV;
							tmpV.reserve(50);
							tmpV.push_back(iSmall);
							ite->second.paths.push_back(tmpV);
						}
						else {// extend every path.
							for (int i = 0; i < its->second.paths.size(); i++) {
								ite->second.paths.push_back(its->second.paths[i]);
								ite->second.paths[ite->second.paths.size() - 1].push_back(iSmall);
							}
						}
					}
					if (its->second.paths1.size() == 0) {// no path in the starting city.						
						vector<int> tmpV;
						tmpV.reserve(50);
						tmpV.push_back(iSmall);
						ite->second.paths1.push_back(tmpV);
					}
					else {// extend every path.
						for (int i = 0; i < its->second.paths1.size(); i++) {
							ite->second.paths1.push_back(its->second.paths1[i]);
							ite->second.paths1[ite->second.paths1.size() - 1].push_back(iSmall);
						}
					}
				}
				else {// target is new.
					CityInfo newCity;
					newCity.pathLen = its->second.pathLen + smallRoads[iSmall].len;
					if (its->second.paths.size() == 0) {// no path in the starting city.						
						vector<int> tmpV;
						tmpV.reserve(50);
						tmpV.push_back(iSmall);
						newCity.paths.push_back(tmpV);
					}
					else {// extend every path.							
						for (int i = 0; i < its->second.paths.size(); i++) {
							newCity.paths.push_back(its->second.paths[i]);
							newCity.paths[newCity.paths.size() - 1].push_back(iSmall);
						}
					}
					if (its->second.paths1.size() == 0) {// no path in the starting city.						
						vector<int> tmpV;
						tmpV.reserve(50);
						tmpV.push_back(iSmall);
						newCity.paths1.push_back(tmpV);
					}
					else {// extend every path.							
						for (int i = 0; i < its->second.paths1.size(); i++) {
							newCity.paths1.push_back(its->second.paths1[i]);
							newCity.paths1[newCity.paths1.size() - 1].push_back(iSmall);
						}
					}
					cities.insert(pair<string, CityInfo>(smallRoads[iSmall].end, newCity));
				}

				// add new smalls to queue.
				for (int i = 0; i < cSmalls; i++) {
					/*if (smallRoads[i].start != smallRoads[iSmall].end
						|| smallRoads[i].end == smallRoads[iSmall].start) continue;*/
					if (smallRoads[i].start != smallRoads[iSmall].end) continue;
					bool stillCont = false;
					map<string, CityInfo>::iterator itee = cities.find(smallRoads[iSmall].end);
					assert(itee != cities.end());
					for (int j = 0; j < itee->second.paths1.size(); j++) {
						if (stillCont) break;
						for (int k = 0; k < itee->second.paths1[j].size(); k++) {
							if (stillCont) break;
							if (smallRoads[itee->second.paths1[j][k]].start == smallRoads[i].end) {
								stillCont = true;
							}
						}
					}
					if (stillCont) continue;

					smallRoadsTo.push(i);
				}
			}
			else {
				firstDone = true;
				for (int i = 0; i < cSmalls; i++) {
					if (smallRoads[i].start != wholeStart) continue;

					smallRoadsTo.push(i);
				}
			}

		} while (smallRoadsTo.size() > 0);
		//
		// output.
		//
		int cCities = cities.size() - 1;
		double outerProb = 1 / (double)cCities;
		for (map<string, CityInfo>::iterator it = cities.begin(); it != cities.end(); it++) {
			if (it->second.pathLen == 0) continue;
			int cPaths = it->second.paths.size();
			double innerProb = 1 / (double)cPaths;
			for (int i = 0; i < cPaths; i++) {
				for (int j = 0; j < it->second.paths[i].size(); j++) {
					smallRoads[it->second.paths[i][j]].probability += outerProb * innerProb;
				}
			}
		}
		outfile << "Case #" << iCase << ":";
		for (int i = 0; i < cSmalls; i++) {
			outfile << " " << setprecision(7) << fixed << smallRoads[i].probability;
		}
		outfile << endl;

		cout << endl;
		delete[] smallRoads;
	}

	infile.close();
	outfile.close();
	system("pause");
	return 0;
}