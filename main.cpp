#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
vector<int> w;
vector<int> v;
vector<int> bestChoose;
int bestV;

void ShowX(vector<int> x)
{
	string allX = "";
	for (int i = 0; i < 100; i++)
	{
		if (i % 10 == 0)
			allX = allX + "\n";
		string kk = to_string(x[i]);
		allX = allX + kk;
	}
	cout << allX;
}

void GetCost(vector<int> x, int& totalW, int& totalV)
{
	totalV = 0;
	totalW = 0;
	for (int i = 0; i < 100; i++)
	{
		totalV = totalV + v[i] * x[i];
		totalW = totalW + w[i] * x[i];
	}
}

vector<int> GetNext(vector<int> x)
{
	vector<int> newX = x;

	int rule = rand() % 3;;
	if (rule == 0)
	{
		int len = x.size();
		int n1 = rand() % len;
		int n2 = rand() % len;
		newX[n1] = x[n2];
		newX[n2] = x[n1];
	}
	else if (rule == 1)
	{
		int len = x.size();
		int n1 = rand() % len;
		newX[n1] = 1;
	}
	else //if (rule == 2)
	{
		int len = x.size();
		int n1 = rand() % len;
		newX[n1] = 0;
	}
	return newX;
}
void erase(int pos, vector<int> x) {
	for (int i = pos; i < x.size(); i++) {
		x[i] = 0;
	}
}
void enumerate(int pos, vector<int> x) {

	if (pos >= x.size())
		return;

	int totalW = 0, totalV = 0;

	x[pos] = 0;
	GetCost(x, totalW, totalV);
	if (totalW <= 500) {
		if (totalV > bestV) {
			bestV = totalV;
			bestChoose = x;
			cout << "總重量=" + to_string(totalW) << endl;
			cout << "總價格=" + to_string(totalV) << endl;
		}
		enumerate(pos + 1, x);
	}
	erase(pos, x);

	x[pos] = 1;
	GetCost(x, totalW, totalV);
	if (totalW <= 500) {
		if (totalV > bestV) {
			bestV = totalV;
			bestChoose = x;
			cout << "總重量=" + to_string(totalW) << endl;
			cout << "總價格=" + to_string(totalV) << endl;
		}
		enumerate(pos + 1, x);
	}
	erase(pos, x);
}

void SA()
{
	double T = 100;
	double k = 1;
	vector<int> x;
	for (int i = 0; i < 100; i++)
	{
		x.push_back(0);
	}

	int bestV = 0;
	int totalW = 0, totalV = 0;
	GetCost(w, totalW, totalV);
	cout << "總重量=" + to_string(totalW) << endl;
	cout << "總價格=" + to_string(totalV) << endl;
	ShowX(x);

	enumerate(0,x);

	while (T > 10)
	{
		int reject = 0;
		while (reject < 100)
		{
			//int[] newX = new int[100];
			vector<int>newX;
			newX = GetNext(x);
			int newW = 0, newV = 0;
			GetCost(w, v, newX, newW, newV);
			if (newW > 500) continue;

			if (newV > totalV)
			{
				x = newX;

				totalW = newW;
				totalV = newV;
				cout << "總重量=" + to_string(totalW) << endl;
				cout << "總價格=" + to_string(totalV) << endl;
				//ShowX(x);
				if (newV > bestV) bestV = newV;
			}
			else
			{
				double delta = totalV - newV;
				double rrr1 = exp(-delta * k / T);
				double rrr2 = (double)rand() / RAND_MAX;
				if (rrr2 < rrr1)
				{
					x = newX;
					totalW = newW;
					totalV = newV;
					cout << "總重量=" + to_string(totalW) << endl;
					cout << "總價格=" + to_string(totalV) << endl;
					//ShowX(x);
					if (newV > bestV) bestV = newV;
				}
				else
				{
					reject++;
				}
			}
			cout << bestV << " ,T=" << T << ",reject=" << reject;
		}
		T = T * 0.9;
	}
	cout << "end" << endl;
}

int main() {
	
	for (int i = 0; i < 100; i++)
		bestChoose.push_back(0);

	ifstream infile("input100.csv");  // 讀取 input.csv 檔案
	string line;

	// 逐行讀取檔案
	while (getline(infile, line)) {
		istringstream ss(line);
		string token;

		// 逐欄讀取每一行的資料，將 weight 和 value 分別儲存在 w 和 v 陣列中
		getline(ss, token, ',');
		w.push_back(stoi(token));

		getline(ss, token, ',');
		v.push_back(stoi(token));
	}

	// 印出 w 和 v 陣列中的所有元素
	cout << "w array: ";
	for (int i = 0; i < w.size(); i++) {
		cout << w[i] << " ";
	}
	cout << endl;

	cout << "v array: ";
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;

	SA();
	system("pause");
	return 0;
}
