#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
 
using namespace std;

int dp[100][100];

// Function that builds the DP matrix using Top Down Approach from lcs.cpp
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

// Returns a string which is there in s1 but not in s2 (like s1 - s2) (length of s1 > length of s2)
string find_diff(string s1, string s2){
    string res;
    int m = s1.length();
    int n = s2.length();

    if(m < n)   return "Invalid arguments";

    int i = 0, j = 0;

    while(j < n){
        if(s1[i] == s2[j]){
            i++;
            j++;
        }else{
            res.push_back(s1[i]);
            i++;
        }
    }

    while(i < m){
        res.push_back(s1[i]);
        i++;
    }

    return res;
}

// Main function returning the final result
string diff(string s1, string s2){
    string res;
    char lcslenstr[21];
    int m = s1.length();
    int n = s2.length();
    
    int lcslen = buildDPMemoized(s1, s2, m, n);

    string lcs = findLCSfromDP(s2, m, n);

    string diffprev = find_diff(s1, lcs);

    string diffnew = find_diff(s2, lcs);

    res =  "Deleted (-): \"" + diffprev + "\" \nAdded   (+): \"" + diffnew + "\"";

    return res;
}

int main(){
    string s1 = "Let’s meet at 10am";
    string s2 = "Let’s meet at 3pm or after"; 
 
    memset(dp, -1, sizeof(dp)); 

    cout << diff(s1, s2);

    return 0;
}