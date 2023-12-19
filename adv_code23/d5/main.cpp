#include <bits/stdc++.h>
using namespace std;

struct Map_t {
    size_t src_start;
    size_t dest_start;
    size_t sz;
};

void part1(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;

    string line;
    size_t num;
    int id = -1;
    vector<size_t> seeds;
    vector<vector<struct Map_t>> maps(7);

    getline(file, line);
    istringstream iss(line.substr(line.find(":")+2));
    while (iss >> num)
        seeds.push_back(num);

    while (getline(file, line)){
        if (line.empty()){
            getline(file, line);
            getline(file, line);
            id++;
        }
        istringstream iline(line);
        struct Map_t m = {0};
        iline >> m.dest_start;
        iline >> m.src_start;
        iline >> m.sz;
        maps[id].push_back(m);
    }

    size_t min_ = string::npos;
    for (auto num : seeds){
        for (size_t i = 0; i < maps.size(); i++){
            for (size_t j = 0; j < maps[i].size(); j++){
                struct Map_t m = maps[i][j];
                if ((m.src_start <= num) && (num < m.src_start + m.sz)){
                    num = m.dest_start + (num - m.src_start);
                    break;
                }
            }
        }
        if (num < min_)
            min_ = num;
    }
    file.close();

    cout << "part1: " << min_ << endl;
}

struct Map_t intersec(struct Map_t a,
                      struct Map_t b,
                      struct Map_t *c,
                      struct Map_t *d
                      ){
    size_t s, e;
    // Casos:
    // Ref:    |--------------|
    //               |--------------|
    //     |--------------|
    //            |-------|
    //                         |-------|
    //     |--|
    //     |------------------------|
    // Ref:    |--------------|
    s = max(a.src_start, b.src_start);
    e = min(a.src_start + a.sz - 1, b.src_start + b.sz - 1);
    d->sz = c->sz = 0;
    if (e < s){
        c->src_start = a.src_start;
        c->sz = a.sz;
        return (struct Map_t){
            .src_start=s,
            .dest_start=0,
            .sz=0
        };
    }
    if (a.src_start < b.src_start){
        c->src_start = a.src_start;
        c->sz = b.src_start - a.src_start ;
    }
    if (a.src_start + a.sz - 1 > b.src_start + b.sz - 1){
        d->src_start = b.src_start + b.sz - 1;
        d->sz = (a.src_start + a.sz - 1) - d->src_start;
    }

    return (struct Map_t){
        .src_start=s,
        .dest_start=0,
        .sz=e - s + 1
    };
}


inline struct Map_t map_to(struct Map_t i, struct Map_t ma){
    return (struct Map_t){
        .src_start= ma.dest_start + (i.src_start - ma.src_start),
        .dest_start=0,
        .sz=i.sz
    };
}

void part2(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;

    string line;
    size_t num;
    int id = -1;
    vector<size_t> seeds;
    vector<vector<struct Map_t>> maps(7);

    getline(file, line);
    istringstream iss(line.substr(line.find(":")+2));
    while (iss >> num)
        seeds.push_back(num);

    while (getline(file, line)){
        if (line.empty()){
            getline(file, line);
            getline(file, line);
            id++;
        }
        istringstream iline(line);
        struct Map_t m = {0};
        iline >> m.dest_start;
        iline >> m.src_start;
        iline >> m.sz;
        maps[id].push_back(m);
    }

    size_t MIN_ = string::npos;

    for (size_t i = 0; i < seeds.size(); i+=2){
        queue<struct Map_t> inters;
        struct Map_t m;
        m.src_start = seeds[i];
        m.sz = seeds[i+1];
        inters.push(m);

        for (size_t i = 0; i < maps.size(); i++){
            queue<struct Map_t> inters2;
            for (size_t j = 0; j < maps[i].size(); j++){
                queue<struct Map_t> inters3;
                while (!inters.empty()){
                    struct Map_t inter = inters.front();
                    struct Map_t l, u;
                    inters.pop();
                    m = intersec(inter, maps[i][j], &l, &u);
                    if (m.sz != 0)
                        inters2.push(map_to(m, maps[i][j]));
                    if (l.sz != 0)
                        inters3.push(l);
                    if (u.sz != 0)
                        inters3.push(u);
                }
                while (!inters3.empty()){
                    inters.push(inters3.front());
                    inters3.pop();    
                }
            }
            while (!inters2.empty()){
                inters.push(inters2.front());
                inters2.pop();    
            }
        }

        size_t min_ = inters.front().src_start;
        while (!inters.empty()){
            struct Map_t i = inters.front();
            cout << i.src_start << " - " << i.src_start + i.sz - 1 << " , ";
            min_ = min(min_, inters.front().src_start);
            inters.pop();
        }
        cout << endl;
        if (min_ < MIN_)
            MIN_ = min_;
    }
    file.close();

    cout << "part2: " << MIN_ << endl;
}

void part2_alt(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;

    string line;
    size_t num;
    int id = -1;
    vector<size_t> seeds;
    vector<vector<struct Map_t>> maps(7);

    getline(file, line);
    istringstream iss(line.substr(line.find(":")+2));
    while (iss >> num)
        seeds.push_back(num);

    while (getline(file, line)){
        if (line.empty()){
            getline(file, line);
            getline(file, line);
            id++;
        }
        istringstream iline(line);
        struct Map_t m = {0};
        iline >> m.dest_start;
        iline >> m.src_start;
        iline >> m.sz;
        maps[id].push_back(m);
    }

    size_t min_ = string::npos;
    for (size_t k = 0; k < seeds.size(); k+=2){
        cout << seeds[k] << " - " << seeds[k] + seeds[k+1] - 1 << endl;
        for (size_t n = seeds[k]; n < (seeds[k] + seeds[k+1]); n++){
            size_t num = n;
            for (size_t i = 0; i < maps.size(); i++){
                for (size_t j = 0; j < maps[i].size(); j++){
                    struct Map_t m = maps[i][j];
                    if ((m.src_start <= num) && (num < m.src_start + m.sz)){
                        num = m.dest_start + (num - m.src_start);
                        break;
                    }
                }
            }
            if (num < min_){
                min_ = num;
                cout <<  "min = " << min_ << endl;
            }
        }
    }
    file.close();

    cout << "part2_alt: " << min_ << endl;
}

int main(int argc, char **argv){
    part1(argv[1]);
    part2_alt(argv[1]);
    return 0;
}
