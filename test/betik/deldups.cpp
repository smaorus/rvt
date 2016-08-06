#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[]) {
	vector<string> latest;
	char line[65000];
	while (gets(line) != NULL) {
		string s(line);
		if (find(latest.begin(), latest.end(), s) == latest.end()) {
			puts(line);
			latest.push_back(s);
			if (latest.size() > 2)
				latest.erase(latest.begin());
		}
	}
	return 0;
}
