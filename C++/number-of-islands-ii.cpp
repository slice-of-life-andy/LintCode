// Time:  O(p), p is number of operators.
// Space: O(p)

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */

class Solution {
public:
    /**
     * @param n an integer
     * @param m an integer
     * @param operators an array of point
     * @return an integer array
     */
    vector<int> numIslands2(int n, int m, vector<Point>& operators) {
        vector<int> numbers;
        int number = 0;
        const vector<pair<int, int>> directions{{0, -1}, {0, 1},
                                                {-1, 0}, {1, 0}};
        unordered_map<int, int> set;
        for (const auto& oper : operators) {
            const auto& node = make_pair(oper.x, oper.y);
            set[node_id(node, m)] = node_id(node, m);

            // For each direction, count distinct islands.
            unordered_set<int> neighbors;
            for (const auto& d : directions) {
                const auto& neighbor = make_pair(oper.x + d.first,
                                                 oper.y + d.second);
                if (neighbor.first >= 0 && neighbor.first < n &&
                    neighbor.second >= 0 && neighbor.second < m &&
                    set.find(node_id(neighbor, m)) != set.end()) {
                    neighbors.emplace(find_set(node_id(neighbor, m), &set));
                }
            }

            number += 1 - neighbors.size();  // Merge neighbors into one island.
            numbers.emplace_back(number);

            // For each direction, find and union.
            for (const auto& d : directions) {
                const auto& neighbor = make_pair(oper.x + d.first,
                                                 oper.y + d.second);
                if (neighbor.first >= 0 && neighbor.first < n &&
                    neighbor.second >= 0 && neighbor.second < m &&
                    set.find(node_id(neighbor, m)) != set.end()) {
                    union_set(&set, node_id(node, m), node_id(neighbor, m));
                }
            }
        }
        return numbers;
    }

    int node_id(const pair<int, int>& node, const int m) {
        return node.first * m + node.second;
    }

    int find_set(int x, unordered_map<int, int> *set) {
       if ((*set)[x] != x) {
           (*set)[x] = find_set((*set)[x], set);  // path compression.
       }
       return (*set)[x];
    }

    void union_set(unordered_map<int, int> *set, const int x, const int y) {
        int x_root = find_set(x, set), y_root = find_set(y, set);
        (*set)[min(x_root, y_root)] = max(x_root, y_root);
    }
};
