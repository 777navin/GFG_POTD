🔹 1. Brute Force Approach
string removeSpaces(string s) {
    string ans = "";
    for (char c : s) {
        if (c != ' ') {
            ans += c;
        }
    }
    return ans;
} 


2. Optimized Approach (In-Place)
string removeSpaces(string s) {
    int j = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != ' ') {
            s[j++] = s[i];
        }
    }
    return s.substr(0, j);
}
