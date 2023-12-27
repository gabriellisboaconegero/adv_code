#include <bits/stdc++.h>
using namespace std;

#define u64 uint64_t
#define i64 int64_t

struct record_t {
    string springs;
    vector<int> group_damaged;
};

bool can_be(int group, string &s, int i){
    return s[i] != '#' &&
           s[i+group+1] != '#' &&
           all_of(s.begin()+i+1, s.begin()+i+group+1, [](char c){return c != '.';});
}

bool is_continuous(string &s, int begin, int end){
    return all_of(s.begin()+begin, s.begin()+end, [](char c){return c != '#';});
}

void part1(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;

    string line;
    vector<struct record_t> records;
    while (getline(file, line)){
        istringstream iss(line);
        string aux;
        char lixo;
        size_t seq;

        struct record_t r;

        iss >> aux;
        r.springs = "." + aux + ".";
        
        iss >> seq;
        do {
            r.group_damaged.push_back(seq);
        } while (iss >> lixo >> seq);
        records.push_back(r);
    }

    u64 res = 0;
    for (auto rec : records){
        int group = rec.group_damaged.front();
        vector<u64> dp1 = vector<u64>(rec.springs.size(), 0);
        vector<u64> dp2 = vector<u64>(rec.springs.size(), 0);

        int menor = -1;
        int maior = -1;
        for (size_t i = 0; i < dp2.size(); i++){
            if (can_be(group, rec.springs, i)){
                menor = menor == -1 ? i : menor;
                maior = i;
                dp2[i]++;
            }else if (rec.springs[i] == '#')
                break;
        }

        for (size_t i = 1; i < rec.group_damaged.size()-1; i++){
            dp2.swap(dp1);
            group = rec.group_damaged[i];
            int prev_group = rec.group_damaged[i-1];
            fill(dp2.begin(), dp2.end(), 0);

            int start = menor + prev_group + 1;
            menor = -1;
            int new_maior = -1;
            for (size_t j = start; j < dp2.size() - (group + 1); j++){
                if (can_be(group, rec.springs, j)){
                    menor = menor == -1 ? j : menor;
                    new_maior = j;
                    for (size_t k = 0; k < j - prev_group; k++){
                        if (is_continuous(rec.springs, k+prev_group+1, j))
                            dp2[j] += dp1[k];
                    }
                }else if (rec.springs[j] == '#' && j > maior + prev_group)
                    break;
            }
            maior = new_maior;
        }
        size_t i = rec.group_damaged.size()-1;
        dp2.swap(dp1);
        group = rec.group_damaged[i];
        int prev_group = rec.group_damaged[i-1];
        fill(dp2.begin(), dp2.end(), 0);

        int start = menor + prev_group + 1;
        menor = -1;
        int new_maior = -1;
        for (size_t j = start; j < dp2.size() - (group + 1); j++){
            if (can_be(group, rec.springs, j)){
                menor = menor == -1 ? j : menor;
                new_maior = j;
                for (size_t k = 0; k < j - prev_group; k++){
                    if (is_continuous(rec.springs, k+prev_group+1, j) &&
                        is_continuous(rec.springs, j+group+1, rec.springs.size()-1))
                        dp2[j] += dp1[k];
                }
            }else if (rec.springs[j] == '#' && j > maior + prev_group)
                break;
        }

        for (auto &i : dp2)
            res += i;
    }

    file.close();
    cout << "Part1: " << res << endl;
}

void part2(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;

    string line;
    vector<struct record_t> records;
    while (getline(file, line)){
        istringstream iss(line);
        string aux;
        char lixo;
        size_t seq;

        struct record_t r;

        iss >> aux;
        r.springs += ".";;
        r.springs += aux + "?";
        r.springs += aux + "?";
        r.springs += aux + "?";
        r.springs += aux + "?";
        r.springs += aux + ".";
        
        vector<int> tmp;
        iss >> seq;
        do {
            tmp.push_back(seq);
        } while (iss >> lixo >> seq);
        for (int i = 0; i < 5; i++)
            r.group_damaged.insert(r.group_damaged.end(), tmp.begin(), tmp.end());
        records.push_back(r);
    }

    u64 res = 0;
    for (auto rec : records){
        int group = rec.group_damaged.front();
        vector<u64> dp1 = vector<u64>(rec.springs.size(), 0);
        vector<u64> dp2 = vector<u64>(rec.springs.size(), 0);

        int menor = -1;
        int maior = -1;
        for (size_t i = 0; i < dp2.size(); i++){
            if (can_be(group, rec.springs, i)){
                menor = menor == -1 ? i : menor;
                maior = i;
                dp2[i]++;
            }else if (rec.springs[i] == '#')
                break;
        }

        for (size_t i = 1; i < rec.group_damaged.size()-1; i++){
            dp2.swap(dp1);
            group = rec.group_damaged[i];
            int prev_group = rec.group_damaged[i-1];
            fill(dp2.begin(), dp2.end(), 0);

            int start = menor + prev_group + 1;
            menor = -1;
            int new_maior = -1;
            for (size_t j = start; j < dp2.size() - (group + 1); j++){
                if (can_be(group, rec.springs, j)){
                    menor = menor == -1 ? j : menor;
                    new_maior = j;
                    for (size_t k = 0; k < j - prev_group; k++){
                        if (is_continuous(rec.springs, k+prev_group+1, j))
                            dp2[j] += dp1[k];
                    }
                }else if (rec.springs[j] == '#' && j > maior + prev_group)
                    break;
            }
            maior = new_maior;
        }
        size_t i = rec.group_damaged.size()-1;
        dp2.swap(dp1);
        group = rec.group_damaged[i];
        int prev_group = rec.group_damaged[i-1];
        fill(dp2.begin(), dp2.end(), 0);

        int start = menor + prev_group + 1;
        menor = -1;
        int new_maior = -1;
        for (size_t j = start; j < dp2.size() - (group + 1); j++){
            if (can_be(group, rec.springs, j)){
                menor = menor == -1 ? j : menor;
                new_maior = j;
                for (size_t k = 0; k < j - prev_group; k++){
                    if (is_continuous(rec.springs, k+prev_group+1, j) &&
                        is_continuous(rec.springs, j+group+1, rec.springs.size()-1))
                        dp2[j] += dp1[k];
                }
            }else if (rec.springs[j] == '#' && j > maior + prev_group)
                break;
        }

        for (auto &i : dp2)
            res += i;
    }

    file.close();
    cout << "Part2: " << res << endl;
}

int main(int argc, char **argv){
    part1(argv[1]);
    part2(argv[1]);

    return 0;
}
