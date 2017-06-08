#include <iostream>
#include <vector>
using namespace std;

vector <int> sons[1000];

int mytimein[1000];
int mytimeout[1000];
int mytime;
void DFS(int v)
{
	mytimein[v] = mytime++;
	for(int i=0; i < sons[v].size(); i++)
	{
		DFS(sons[v][i]);
	}
	mytimeout[v] = mytime++;
	
}

int main() {
	mytime = 0;
	int n;
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int p, a;
		cin >> p >> a;
		sons[p].push_back(a);
	}
	DFS(0);
	

	

	return 0;
}
