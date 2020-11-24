#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
 
using namespace std;

int dp[100][100];

// Function that builds the DP matrix using Bottom Up Approach
int buildDPIterative(string s1, string s2){
    int m = s1.length();
    int n = s2.length();

    int i, j;

    for(i = 0; i<=m; i++){
        for(j=0; j<=n; j++){

            if(i == 0 || j == 0)
                dp[i][j] = 0;
            else if(s1[i-1] == s2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);

        }
    }

    return dp[m][n];
}

// Function that builds the DP matrix using Top Down Approach
int buildDPMemoized(string s1, string s2, int i, int j){
    if(i == 0 || j == 0){
        dp[i][j] = 0;
        return 0;
    }

    if(dp[i][j] != -1)
        return dp[i][j];

    int res;

    if(s1[i-1] == s2[j-1])
        res = 1 + buildDPMemoized(s1, s2, i-1, j-1);
    else
        res = max(buildDPMemoized(s1, s2, i-1, j), buildDPMemoized(s1, s2, i, j-1));

    dp[i][j] = res;
    return res;
}

// Find the LCS String by backtracking the given DP matrix
string findLCSfromDP(string s2, int m, int n){
    int i, j;
    string res;

    i = m;
    for(j = n; j > 0; j--){
        if(dp[i][j] == dp[i][j-1]){
            continue;
        }
        else{
            res.push_back(s2[j-1]);
            i--;
        }
    }
    
    reverse(res.begin(), res.end());

    return res;
}

string LCS(string s1, string s2){
    int m = s1.length();
    int n = s2.length();

    // int lcslen = buildDPIterative(s1, s2);
    
    int lcslen = buildDPMemoized(s1, s2, m, n);

    string lcs = findLCSfromDP(s2, m, n);

    string res;
    char lcslenstr[21];

    sprintf(lcslenstr, "%d", lcslen);

    res = "The LCS is \"" + lcs + "\" with length " + lcslenstr;

    return res;
}

int main(){
    string s1 = "Let’s meet at 10am";
    string s2 = "Let’s meet at 3pm or after"; 
 
    // string s1 = "cdgadfjanfkaxiabcij";    
    // string s2 = "abcdefghij";
 
    // string s1 = "bd";    
    // string s2 = "abcd";
 
    memset(dp, -1, sizeof(dp)); 

    cout << LCS(s1, s2);

    return 0;
}