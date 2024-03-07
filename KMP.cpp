class Solution {
public:
    int strStr(string s, string p) {
        int n = s.size(), m = p.size();
        if(m == 0) return 0;
        if(n == 0) return -1;
        vector<int> suffix = longestSuffixAlsoPrefix(p);
        vector<int> dp(n, 0);
        dp[0] = (s[0] == p[0]);
        if(m == 1 && dp[0] == 1) return 0;

        for(int i = 1; i < n; ++i){
            int j = dp[i-1];
            while(j > 0 && s[i] != p[j]){
                j = suffix[j-1];
            }
            dp[i] = j+(s[i] == p[j]);
            if(dp[i] == m) return i-m+1;
        }
        return -1;
    }
    vector<int> longestSuffixAlsoPrefix(string s){
        int n = s.size();
        vector<int> dp(n, 0);
        for(int i = 1; i < n; ++i){
            int j = dp[i-1];
            while(j > 0 && s[i] != s[j]){
                j = dp[j-1];
            }
            dp[i] = j+(s[i] == s[j]);
        }
        return dp;
    }
};
