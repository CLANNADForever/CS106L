
using namespace std;

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        vector<bool> isVisited(n, false);
        dfs(edges, source, isVisited);
        return isVisited[destination];
    }

    void dfs(vector<vector<int>>& edges, int source, vector<bool>& isVisited) {
        if (isVisited[int])
        vector<int> neighbor = getNeighbor(source, edges);
        for ()
    }

    vector<int> getNeighbor(int vertex, vector<vector<int>>& edges) {
        vector<int> result;
        for (const auto& v : edges) {
            if (v[0] == vertex) {
                result.push_back(v[1]);
            } else if (v[1] == vertex) {
                result.push_back(v[0]);
            }
        }
        return result;
    }
}