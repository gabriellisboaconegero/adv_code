#include <bits/stdc++.h>
#define u64 uint64_t
#define i64 int64_t
using namespace std;


void part1(char *input){
    ifstream file;
    file.open(input);
    i64 res = 0;
    if (!file.is_open())
        return;

    string line;
    while (getline(file, line)){
        istringstream iss(line);
        i64 num;
        vector<i64> v;
        while (iss >> num)
            v.push_back(num);

        vector<vector<i64>> mat(1, vector<i64>(v));

        int n = 0;
        while (mat[n].size() != 0 &&
               any_of(
                    mat[n].begin(),
                    mat[n].end(),
                    [](i64 a){return a!=0;}
               ))
        {
            mat.push_back(vector<i64>(mat[n].size()-1, 0));
            for (size_t i = 0; i < mat[n].size()-1; i++){
                i64 d = mat[n][i+1]-mat[n][i];
                mat[n+1][i] = d;
            }
            n++;
        }
        mat.back().push_back(0);
        for (i64 i = mat.size()-2; i >= 0; i--)
            mat[i].push_back(mat[i].back() + mat[i+1].back());
        res += mat[0].back();
    }

    file.close();
    cout << "Part1: " << res << endl;
}

void part2(char *input){
    ifstream file;
    file.open(input);
    i64 res = 0;
    if (!file.is_open())
        return;

    string line;
    while (getline(file, line)){
        istringstream iss(line);
        i64 num;
        vector<i64> v;
        while (iss >> num)
            v.push_back(num);

        vector<vector<i64>> mat(1, vector<i64>(v));

        int n = 0;
        while (mat[n].size() != 0 &&
               any_of(
                    mat[n].begin(),
                    mat[n].end(),
                    [](i64 a){return a!=0;}
               ))
        {
            mat.push_back(vector<i64>(mat[n].size()-1, 0));
            for (size_t i = 0; i < mat[n].size()-1; i++){
                i64 d = mat[n][i+1]-mat[n][i];
                mat[n+1][i] = d;
            }
            n++;
        }
        mat.back().insert(mat.back().begin(), 0);
        for (i64 i = mat.size()-2; i >= 0; i--)
            mat[i].insert(mat[i].begin(), mat[i].front() - mat[i+1].front());
        res += mat[0].front();
    }

    file.close();
    cout << "Part1: " << res << endl;
}

int main(int argc, char **argv){
    part1(argv[1]);
    part2(argv[1]);
    return 0;
}
