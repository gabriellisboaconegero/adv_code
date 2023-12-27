#include <bits/stdc++.h>
#define u64 uint64_t
#define i64 int64_t
using namespace std;

#define pattern_t vector<string>

bool is_reflect_hori(pattern_t &p, i64 l, i64 u){
    while (l < p.size() && u >= 0 && p[l] == p[u]){
        l++;
        u--;
    }

    return l >= p.size() || u < 0;
}

bool col_equal(pattern_t &p, i64 c1, i64 c2){
    return all_of(p.begin(), p.end(), [c1, c2](string s){return s[c1] == s[c2];});
}

bool is_reflect_vert(pattern_t &p, i64 d, i64 e){
    while (d < p[0].size() && e >= 0 && col_equal(p, e, d)){
        d++;
        e--;
    }

    return d >= p[0].size() || e < 0;
}

void part1(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;

    string line;
    vector<pattern_t> patterns(1, pattern_t());
    while (getline(file, line)){
        if (line.empty())
            patterns.push_back(pattern_t());
        else
            patterns.back().push_back(line);
    }

    u64 res = 0;
    for (auto p : patterns){
        i64 m = 0;

        for (i64 i = 1; i < p.size(); i++){
            if (is_reflect_hori(p, i, i-1)){
                m=i;
                break;
            }
        }
        res += 100*m;
        if (m)
            continue;

        m = 0;
        for (i64 i = 1; i < p[0].size(); i++){
            if (is_reflect_vert(p, i, i-1)){
                m=i;
                break;
            }
        }
        res += m;
    }
    cout << "Part1: " << res << endl;
}

int row_diff(pattern_t &p, i64 c1, i64 c2){
    int res = 0;
    for (size_t i = 0; i < p[c1].size(); i++)
        res += p[c1][i] != p[c2][i];
    return res;
}

int col_diff(pattern_t &p, i64 c1, i64 c2){
    int res = 0;
    for (size_t i = 0; i < p.size(); i++)
        res += p[i][c1] != p[i][c2];
    return res;
}

bool is_reflect_hori_smuge(pattern_t &p, i64 l, i64 u){
    int smuge = 0;
    while (l < p.size() && u >= 0 && (smuge += row_diff(p, l, u)) < 2){
        l++;
        u--;
    }

    return (l >= p.size() || u < 0) && smuge == 1;
}

bool is_reflect_vert_smuge(pattern_t &p, i64 d, i64 e){
    int smuge = 0;
    while (d < p[0].size() && e >= 0 && (smuge += col_diff(p, e, d)) < 2){
        d++;
        e--;
    }

    return (d >= p[0].size() || e < 0) && smuge == 1;
}
void part2(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;

    string line;
    vector<pattern_t> patterns(1, pattern_t());
    while (getline(file, line)){
        if (line.empty())
            patterns.push_back(pattern_t());
        else
            patterns.back().push_back(line);
    }

    u64 res = 0;
    for (auto p : patterns){
        i64 m = 0;

        for (i64 i = 1; i < p.size(); i++){
            if (is_reflect_hori_smuge(p, i, i-1)){
                m=i;
                break;
            }
        }
        res += 100*m;
        if (m)
            continue;

        m = 0;
        for (i64 i = 1; i < p[0].size(); i++){
            if (is_reflect_vert_smuge(p, i, i-1)){
                m=i;
                break;
            }
        }
        res += m;
    }
    cout << "Part2: " << res << endl;
}

int main(int argc, char **argv){
    part1(argv[1]);
    part2(argv[1]);
    return 0;
}
