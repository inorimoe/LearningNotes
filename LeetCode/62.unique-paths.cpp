class Solution {
public:
    int uniquePaths(int m, int n) {
        std::array<std::array<int, 100>, 100> mpRouteCount;
	    for (int i = 0; i < m; ++i) mpRouteCount[i][n-1] = 1;
	    for (int i = 0; i < n; ++i) mpRouteCount[m-1][i] = 1;
        
        for (int i = n - 2; i >= 0; --i) {
            for (int j = m - 2; j >= 0; --j) {
                mpRouteCount[j][i] = mpRouteCount[j + 1][i] + mpRouteCount[j][i + 1];
            }
        }
        return mpRouteCount[0][0];
    };
};

/*
 * Accepted
 * 63/63 cases passed (0 ms)
 * Your runtime beats 100 % of cpp submissions
 * Your memory usage beats 70.36 % of cpp submissions (6 MB)
 */