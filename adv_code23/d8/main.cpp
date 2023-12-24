#include <bits/stdc++.h>
#define u64 uint64_t
#define i64 int64_t
using namespace std;

int f(char a){
    return a-'A';
}

void part1(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;

    string moves;
    getline(file, moves);

    string line;
    getline(file, line);

    vector<pair<int, int>> graph(26*26*26, make_pair(0, 0));
    while (getline(file, line)){
        string node1, s;
        istringstream iss(line);

        iss >> node1;
        int id = f(node1[2]) + f(node1[1])*26 + f(node1[0])*26*26;

        iss >> s;

        iss >> s;
        graph[id].first = f(s[3]) + f(s[2])*26 + f(s[1])*26*26;
        iss >> s;
        graph[id].second = f(s[2]) + f(s[1])*26 + f(s[0])*26*26;
    }

    int i = 0;
    int j = 0;
    u64 cont = 0;
    while (i != 26*26*26 - 1){
        switch (moves[j]){
            case 'R': 
                i = graph[i].second;
                break;
            case 'L': 
                i = graph[i].first;
                break;
        }
        j = (j + 1) % moves.length();
        cont++;
    }

    file.close();
    cout << "part1: " << cont << endl;
}

void move(vector<int> &i_s, char move, vector<pair<int, int>> &graph){

    for (size_t i = 0; i < i_s.size(); i++){
        switch (move){
            case 'R': 
                i_s[i] = graph[i_s[i]].second;
                break;
            case 'L': 
                i_s[i] = graph[i_s[i]].first;
                break;
        }
    }
}

bool final_loc(vector<int> &i_s){
    for (auto i : i_s){
        if (i%26 != f('Z'))
            return false;
    }
    return true;
}

string rep(int i){
    char a[4] = {0};
    a[2] = i%26+'A';
    a[1] = (i/(26))%26+'A';
    a[0] = (i/(26*26))%26+'A';
    string res(a);

    return res;
}

void part2(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;

    string moves;
    getline(file, moves);

    string line;
    getline(file, line);

    vector<pair<int, int>> graph(26*26*26, make_pair(0, 0));
    vector<int> i_s;
    while (getline(file, line)){
        string node1, s;
        istringstream iss(line);

        iss >> node1;
        int id = f(node1[2]) + f(node1[1])*26 + f(node1[0])*26*26;
        if (id%26 == f('A'))
            i_s.push_back(id);

        iss >> s;

        iss >> s;
        graph[id].first = f(s[3]) + f(s[2])*26 + f(s[1])*26*26;
        iss >> s;
        graph[id].second = f(s[2]) + f(s[1])*26 + f(s[0])*26*26;
    }

    u64 res = 1;
    for ( auto i : i_s){
        int ii = i;
        int j = 0;
        u64 cont = 0;
        while (ii%26 != f('Z')){
            switch (moves[j]){
                case 'R': 
                    ii = graph[ii].second;
                    break;
                case 'L': 
                    ii = graph[ii].first;
                    break;
            }
            j = (j + 1) % moves.length();
            cont++;
        }
        res = __detail::__lcm(res, cont);
        cout << rep(i) << ": " << cont << ": " << rep(ii) << endl;
    }

    file.close();
    cout << "part2: " << res << endl;
}

int main(int argc, char **argv){
    part1(argv[1]);
    part2(argv[1]);
    return 0;
}
