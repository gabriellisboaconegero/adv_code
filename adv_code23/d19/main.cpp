#include <bits/stdc++.h>
#define u64 uint64_t
#define i64 int64_t
using namespace std;

#define S 0
#define A 1
#define M 2
#define X 3
#define DEFAULT 4
map<char, int> cate_map = {
    {'x', X},
    {'m', M},
    {'a', A},
    {'s', S}
};
struct piece_t {
    i64 categories[4];
};

struct rule_t {
    char op;
    char var;
    i64 val;
    string next_rule;

    rule_t(){
        op = '\0';
        val = 0;
        next_rule = string();
    }
};

i64 index_of(string s){
    i64 id = 0;

    if (s[0] == 'A')
        return 26*26*26;
    if (s[0] == 'R')
        return 26*26*26+1;

    for (auto c : s)
        id = id * 26 + c - 'a';
    return id;
}

bool aply_rule(struct rule_t r, struct piece_t p){
    switch (r.op){
        case '#': return true;
        case '>': return p.categories[cate_map[r.var]] > r.val;
        case '<': return p.categories[cate_map[r.var]] < r.val;
        default: return false;
    }
}

string aply_workflow(vector<struct rule_t> workflow, struct piece_t p){
    for (size_t i = 0; i < DEFAULT; i++){
        if (aply_rule(workflow[i], p))
            return workflow[i].next_rule;
    }

    // never happening
    return workflow[DEFAULT].next_rule;
}

void part1(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;

    string line;
    vector<vector<struct rule_t>> workflows(26*26*26+2, vector<struct rule_t>());
    while (getline(file, line)){
        if (line.empty())
            break;
        auto f = line.find("{");
        string work_name = line.substr(0, f);
        line.erase(line.begin(), line.begin()+f+1);

        while ((f = line.find(",")) != string::npos){
            struct rule_t r;
            r.var = line[0];
            line.erase(0, 1);

            r.op = line[0];
            line.erase(0, 1);

            f = line.find(":");
            r.val = stoi(line.substr(0, f));
            line.erase(line.begin(), line.begin()+f+1);

            f = line.find(",");
            r.next_rule = line.substr(0, f);
            line.erase(line.begin(), line.begin()+f+1);
            workflows[index_of(work_name)].push_back(r);
        }
        struct rule_t r;
        r.next_rule = line.substr(0, line.size()-1);
        r.op = '#';
        workflows[index_of(work_name)].push_back(r);
    }

    vector<struct piece_t> pieces;
    while (getline(file, line)){
        struct piece_t p;
        char c, x, h;
        istringstream iss(line);
        iss >> c >> x >> h >> p.categories[X];
        iss >> c >> x >> h >> p.categories[M];
        iss >> c >> x >> h >> p.categories[A];
        iss >> c >> x >> h >> p.categories[S];
        pieces.push_back(p);
    }
    file.close();

    i64 res = 0;
    for (auto p : pieces){
        i64 workflow = index_of("in");
        //cout << p.categories[0] << ": " << "in";
        while (workflow != index_of("A") && workflow != index_of("R")){
            string nw = aply_workflow(workflows[workflow], p);
            //cout << " -> " << nw;
            workflow = index_of(nw);
        }
        if (workflow == index_of("A")){
            res += p.categories[X];
            res += p.categories[M];
            res += p.categories[A];
            res += p.categories[S];
        }
        //cout << endl;
    }

    cout << "Part1: " << res << endl;
}

struct range_t {
    u64 lo;
    u64 up;

    u64 size(){
        return up-lo+1;
    }
};

struct hyperplane_4d_t {
    struct range_t cate[4];
};

u64 traverse_tree(string workflow, struct hyperplane_4d_t v, vector<vector<struct rule_t>> &workflows){
    if (workflow == "A")
        return v.cate[X].size() * v.cate[M].size() * v.cate[A].size() * v.cate[S].size();
    if (workflow == "R")
        return 0;

    u64 r = 0;
    struct hyperplane_4d_t cv;
    for (auto rule : workflows[index_of(workflow)]){
        cv = v;
        switch(rule.op){
            case '<':
                cv.cate[cate_map[rule.var]].up = rule.val-1;
                r += traverse_tree(rule.next_rule, cv, workflows);
                v.cate[cate_map[rule.var]].lo = rule.val;
                break;
            case '>':
                cv.cate[cate_map[rule.var]].lo = rule.val+1;
                r += traverse_tree(rule.next_rule, cv, workflows);
                v.cate[cate_map[rule.var]].up = rule.val;
                break;
            case '#':
                r += traverse_tree(rule.next_rule, cv, workflows);
                break;
        }
    }

    return r;
}

void part2(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;

    string line;
    vector<vector<struct rule_t>> workflows(26*26*26+2, vector<struct rule_t>());
    while (getline(file, line)){
        if (line.empty())
            break;
        auto f = line.find("{");
        string work_name = line.substr(0, f);
        line.erase(line.begin(), line.begin()+f+1);

        while ((f = line.find(",")) != string::npos){
            struct rule_t r;
            r.var = line[0];
            line.erase(0, 1);

            r.op = line[0];
            line.erase(0, 1);

            f = line.find(":");
            r.val = stoi(line.substr(0, f));
            line.erase(line.begin(), line.begin()+f+1);

            f = line.find(",");
            r.next_rule = line.substr(0, f);
            line.erase(line.begin(), line.begin()+f+1);
            workflows[index_of(work_name)].push_back(r);
        }
        struct rule_t r;
        r.next_rule = line.substr(0, line.size()-1);
        r.op = '#';
        workflows[index_of(work_name)].push_back(r);
    }

    file.close();

    struct hyperplane_4d_t v;
    v.cate[X] = {1, 4000};
    v.cate[M] = {1, 4000};
    v.cate[A] = {1, 4000};
    v.cate[S] = {1, 4000};
    u64 res = traverse_tree("in", v, workflows);

    cout << "Part2: " << res << endl;
}

int main(int argc, char **argv){
    part1(argv[1]);
    part2(argv[1]);

    return 0;
}
