#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// 52. N-Queens II==========================================================
int Rows = 0;
int Cols = 0;
int Diag = 0;
int Adiag = 0;
int Nqueen_01(int idx, int n, int m, int qsf)
{
    if (qsf == 0)
        return 1;

    int count = 0;
    for (int i = idx; i < n * m; i++)
    {
        int x = i / m;
        int y = i % m;

        if ((Rows & (1 << x)) == 0 && (Cols & (1 << y)) == 0 && (Diag & (1 << (x + y))) == 0 && (Adiag & (1 << (x - y + m - 1))) == 0)
        {
            Rows ^= (1 << x);
            Cols ^= (1 << y);
            Diag ^= (1 << (x + y));
            Adiag ^= (1 << (x - y + m - 1));
            count += Nqueen_01(i + 1, n, m, qsf - 1);
            Rows ^= (1 << x);
            Cols ^= (1 << y);
            Diag ^= (1 << (x + y));
            Adiag ^= (1 << (x - y + m - 1));
        }
    }

    return count;
}

int totalNQueens(int n)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return Nqueen_01(0, n, n, n);
}

// 37. Sudoku Solver============================================================
//without bitmasking
bool isValid(vector<vector<char>> &board, int r, int c, int num)
{
    //row
    for (int i = 0; i < 9; i++)
    {
        if (board[r][i] - '0' == num)
            return false;
    }

    //col
    for (int i = 0; i < 9; i++)
    {
        if (board[i][c] - '0' == num)
            return false;
    }

    //3x3 grid
    int x = (r / 3) * 3;
    int y = (c / 3) * 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[x + i][y + j] - '0' == num)
                return false;
        }
    }

    return true;
}
bool solveSudoku_01(vector<vector<char>> &board, vector<int> &calls, int idx)
{
    if (idx == calls.size())
        return true;

    int r = calls[idx] / 9;
    int c = calls[idx] % 9;
    for (int num = 1; num <= 9; num++)
    {
        if (isValid(board, r, c, num))
        {
            board[r][c] = (char)(num + '0');
            if (solveSudoku_01(board, calls, idx + 1))
                return true;
            board[r][c] = '.';
        }
    }

    return false;
}
void solveSudoku(vector<vector<char>> &board)
{
    vector<int> calls;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] == '.')
            {
                calls.push_back(i * 9 + j);
            }
        }
    }

    solveSudoku_01(board, calls, 0);
}

//with bitmasking
vector<int> row;
vector<int> col;
vector<vector<int>> mat;
bool solveSudoku_01(vector<vector<char>> &board, vector<int> &calls, int idx)
{
    if (idx == calls.size())
        return true;

    int r = calls[idx] / 9;
    int c = calls[idx] % 9;
    for (int num = 1; num <= 9; num++)
    {
        int mask = (1 << num);
        if ((row[r] & mask) == 0 && (col[c] & mask) == 0 && (mat[r / 3][c / 3] & mask) == 0)
        {
            board[r][c] = (char)(num + '0');
            row[r] ^= mask;
            col[c] ^= mask;
            mat[r / 3][c / 3] ^= mask;
            if (solveSudoku_01(board, calls, idx + 1))
                return true;
            board[r][c] = '.';
            row[r] ^= mask;
            col[c] ^= mask;
            mat[r / 3][c / 3] ^= mask;
        }
    }
    return false;
}
void solveSudoku(vector<vector<char>> &board)
{
    row.resize(9, 0);
    col.resize(9, 0);
    mat.resize(3, vector<int>(3, 0));

    vector<int> calls;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == '.')
            {
                calls.push_back(i * 9 + j);
            }
            else
            {
                int num = board[i][j] - '0';
                int mask = 1 << num;
                row[i] ^= mask;
                col[j] ^= mask;
                mat[i / 3][j / 3] ^= mask;
            }
        }
    }
    solveSudoku_01(board, calls, 0);
}

// 139. Word Break=========================================================
//Recursion-TLE
bool wordBreak_01(string &s, unordered_set<string> &dict, int idx)
{
    if (idx >= s.size())
        return true;

    for (int i = idx; i < s.size(); i++)
    {
        string word = s.substr(idx, i - idx + 1);
        if (dict.find(word) != dict.end())
        {
            if (wordBreak_01(s, dict, i + 1))
                return true;
        }
    }

    return false;
}
//Memoization
int wordBreak_01(string &s, unordered_set<string> &dict, vector<int> &dp, int idx)
{
    if (idx >= s.size())
        return dp[idx] = 1;

    if (dp[idx] != -1)
        return dp[idx];

    for (int i = idx; i < s.size(); i++)
    {
        string word = s.substr(idx, i - idx + 1);
        if (dict.find(word) != dict.end())
        {
            if (wordBreak_01(s, dict, dp, i + 1) == 1)
                return dp[idx] = 1;
        }
    }

    return dp[idx] = 0;
}
//Tabulation
int wordBreak_DP(string &s, unordered_set<string> &dict, vector<int> &dp, int idx)
{
    for (int idx = s.size(); idx >= 0; idx--)
    {
        int flag = 0;
        if (idx == s.size())
        {
            dp[idx] = 1;
            continue;
        }

        for (int i = idx; i < s.size(); i++)
        {
            string word = s.substr(idx, i - idx + 1);
            if (dict.find(word) != dict.end())
            {
                if (dp[i + 1] == 1)
                {
                    dp[idx] = 1;
                    flag = 1;
                    break;
                }
            }
        }
        if (flag == 1)
            continue;
        dp[idx] = 0;
    }
    return dp[0];
}
bool wordBreak(string s, vector<string> &wordDict)
{
    unordered_set<string> dict;
    vector<int> dp(s.size() + 1, -1);
    for (string s : wordDict)
        dict.insert(s);
    return wordBreak_01(s, dict, dp, 0);
    // return wordBreak_01(s, dict, 0);
}

// 140. Word Break II=======================================================
//Recursion-TLE
typedef pair<int, vector<string>> pr;
pr wordBreak_02(string &s, unordered_set<string> &dict, int idx)
{
    if (idx >= s.size())
    {
        return {1, {""}};
    }

    int res = 0;
    vector<string> myWords;

    for (int i = idx; i < s.size(); i++)
    {
        string word = s.substr(idx, i - idx + 1);
        if (dict.find(word) != dict.end())
        {
            pr smallAns = wordBreak_02(s, dict, i + 1);
            int res = smallAns.first;
            vector<string> words = smallAns.second;
            if (i >= s.size() - 1)
            {
                for (string str : words)
                    myWords.push_back(word + str);
            }
            else
            {
                for (string str : words)
                    myWords.push_back(word + " " + str);
            }
        }
    }

    return {res, myWords};
}
//Memoization
pr wordBreak_03(string &s, unordered_set<string> &dict, int idx, vector<pr> &dp)
{
    if (idx >= s.size())
    {
        return dp[idx] = {1, {""}};
    }

    if (dp[idx].first != -1)
        return dp[idx];

    int res = 0;
    vector<string> myWords;

    for (int i = idx; i < s.size(); i++)
    {
        string word = s.substr(idx, i - idx + 1);
        if (dict.find(word) != dict.end())
        {
            pr smallAns = wordBreak_03(s, dict, i + 1, dp);
            int res = smallAns.first;
            vector<string> words = smallAns.second;
            if (i >= s.size() - 1)
            {
                for (string str : words)
                    myWords.push_back(word + str);
            }
            else
            {
                for (string str : words)
                    myWords.push_back(word + " " + str);
            }
        }
    }

    return dp[idx] = {res, myWords};
}
vector<string> wordBreak_ques(string s, vector<string> &wordDict)
{
    unordered_set<string> dict;
    for (string s : wordDict)
        dict.insert(s);
    vector<pr> dp(s.size() + 1, {-1, {}});
    return wordBreak_03(s, dict, 0, dp).second;
}

void solve()
{
}
int main()
{
    solve();
    return 0;
}