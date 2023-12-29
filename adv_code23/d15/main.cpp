#include <bits/stdc++.h>
#define u64 uint64_t
#define i64 int64_t
using namespace std;

u64 my_hash(string &s){
    u64 res = 0;
    for (auto i : s){
        res += i;
        res *= 17;
        res %= 256;
    }

    return res;
}

void part1(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;

    string line;
    getline(file, line);
    file.close();

    size_t f = 0;
    vector<string> vals;
    while ((f = line.find(",")) != string::npos){
        vals.push_back(line.substr(0, f));
        line.erase(0, f+1);
    }
    vals.push_back(line.substr(0, f));

    u64 res = 0;
    for (auto i : vals)
        res += my_hash(i);

    cout << "Part1: " << res << endl;
}

pair<u64, size_t> my_hash2(string &s){
    u64 res = 0;
    size_t i;
    for (i = 0; i < s.size() && s[i] != '-' && s[i] != '='; i++){
        res += s[i];
        res *= 17;
        res %= 256;
    }

    return make_pair(res, i);
}

struct lens_t{
    string label;
    u64 val;
};

void part2(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;

    string line;
    getline(file, line);
    file.close();

    size_t f = 0;
    vector<string> vals;
    while ((f = line.find(",")) != string::npos){
        vals.push_back(line.substr(0, f));
        line.erase(0, f+1);
    }
    vals.push_back(line.substr(0, f));

    pair<u64, size_t> h;
    list<struct lens_t> boxes[256];
    for (auto i : vals){
        h = my_hash2(i);
        list<struct lens_t> &l = boxes[h.first];
        string label = i.substr(0, h.second);

        switch (i[h.second]){
            case '-':
                for (list<struct lens_t>::iterator it = l.begin(); it != l.end(); it++){
                    if (it->label == label){
                        l.erase(it);
                        break;
                    }
                }
                break;
            case '=':
                u64 val = stoi(i.substr(h.second+1, string::npos));
                bool flag = false;
                for (list<struct lens_t>::iterator it = l.begin(); it != l.end(); it++){
                    if (flag = (it->label == label)){
                        it->val = val;
                        break;
                    }
                }
                if (!flag)
                    l.push_back((struct lens_t){.label=label, .val=val});
                break;
        }
    }

    u64 res = 0;
    for (size_t i = 0; i < 256; i++){
        u64 s = 1;
        for (list<struct lens_t>::iterator it = boxes[i].begin(); it != boxes[i].end(); it++){
            u64 a = (i+1)*s*(it->val);
            res += a;
            s++;
        }
    }

    cout << "Part2: " << res << endl;
}

int main(int argc, char **argv){
    part1(argv[1]);
    part2(argv[1]);

    return 0;
}
