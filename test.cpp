#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;
const long long INF = 1e18;

struct Point {
	int x, y, h;
} points[MAXN];

vector<vector<int>> lines;
int n, m;

// Calculate Euclidean distance between two points (rounded up)
int dist(int i, int j) {
	long long dx = points[i].x - points[j].x;
	long long dy = points[i].y - points[j].y;
	return (int)ceil(sqrt(dx * dx + dy * dy));
}

// State for Dijkstra's algorithm
struct State {
	int node;
	long long happiness;
	bool operator<(const State& other) const {
		return happiness < other.happiness;
	}
};

// Modified Dijkstra's algorithm to find maximum happiness
vector<long long> findMaxHappiness(int start) {
	vector<long long> happiness(n + 1, -INF);
	priority_queue<State> pq;
	
	// Start with initial node's happiness
	happiness[start] = points[start].h;
	pq.push({start, happiness[start]});
	
	while (!pq.empty()) {
		State curr = pq.top();
		pq.pop();
		
		if (curr.happiness < happiness[curr.node]) continue;
		
		// Try each metro line
		for (const auto& line : lines) {
			for (int i = 0; i < line.size(); i++) {
				if (line[i] != curr.node) continue;
				
				// Try all possible destinations on this line after current station
				long long currHappiness = curr.happiness;
				for (int j = i + 1; j < line.size(); j++) {
					int next = line[j];
					// Calculate total distance cost for this segment
					long long distCost = 0;
					for (int k = i; k < j; k++) {
						distCost += dist(line[k], line[k + 1]);
					}
					
					// Calculate new happiness (including station happiness if we stop there)
					long long newHappiness = currHappiness - distCost + points[next].h;
					
					if (newHappiness > happiness[next]) {
						happiness[next] = newHappiness;
						pq.push({next, newHappiness});
					}
				}
			}
		}
	}
	
	return happiness;
}

int main() {
	freopen("metro.in", "r", stdin);
	freopen("metro.out", "w", stdout);
	
	cin >> n >> m;
	
	// Read points
	for (int i = 1; i <= n; i++) {
		cin >> points[i].x >> points[i].y >> points[i].h;
	}
	
	// Read metro lines
	for (int i = 0; i < m; i++) {
		int p;
		cin >> p;
		vector<int> line(p);
		for (int j = 0; j < p; j++) {
			cin >> line[j];
		}
		lines.push_back(line);
	}
	
	// Calculate maximum happiness for each pair of stations
	for (int i = 1; i <= n; i++) {
		vector<long long> maxHappiness = findMaxHappiness(i);
		for (int j = 1; j <= n; j++) {
			if (j > 1) cout << " ";
			cout << maxHappiness[j];
		}
		cout << "\n";
	}
	
	return 0;
}