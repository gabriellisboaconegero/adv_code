#include <bits/stdc++.h>
#define u64 uint64_t
#define i64 int64_t
using namespace std;

#define FF 0
#define CONJ 1
#define BROD 2

#define LOW false
#define HIGH true

struct module_t {
    int type;
    bool output;
    vector<string> inputs;
    vector<string> outputs;
    bool state;

    bool operator<(struct module_t &a){
        return type < a.type;
    }
};

void part1(char *input){
    ifstream file;
    file.open(input);
    if (!file.is_open())
        return;

    string line;
    map<string, struct module_t> graph;
    while (getline(file, line)){
        struct module_t m;
        m.output = LOW;
        m.state = false;
        istringstream iss(line);
        string mod_name, lixo;

        iss >> mod_name >> lixo;
        if (mod_name.front() == '%'){
            m.type = FF;
            mod_name.erase(0, 1);
        }else if (mod_name.front() == '&'){
            m.type = CONJ;
            mod_name.erase(0, 1);
        }else{
            m.type = BROD;
        }

        auto p = graph.insert({mod_name, m});
        auto &nm = p.first->second;
        if (!p.second){
            nm.type = m.type;
        }

        while (iss >> mod_name){
            if (mod_name.back() == ',')
                mod_name.erase(mod_name.end()-1);

            nm.outputs.push_back(mod_name);
            auto np = graph.insert({mod_name, m});
            np.first->second.inputs.push_back(p.first->first);
        }
    }

    file.close();

    u64 conts[2] = {0};
    queue<pair<bool, string>> qq;

    for (size_t i = 0; i < 1000; i++){
        conts[LOW]++;
        auto brod = graph["broadcaster"];
        for (auto m_ : brod.outputs){
            conts[brod.output]++;
            qq.push(make_pair(brod.output, m_));
        }
        while (!qq.empty()){
            auto p = qq.front();
            string m_name = p.second;
            bool input = p.first;
            qq.pop();
            struct module_t &m = graph[m_name];
            switch (m.type){
                case FF:
                    if (input == LOW){
                        m.state = !m.state;
                        m.output = m.state;
                        for (auto m_ : m.outputs){
                            conts[m.output]++;
                            qq.push(make_pair(m.output, m_));
                        }
                    }
                    break;
                case CONJ:
                    m.output = LOW;
                    for (auto m_ : m.inputs){
                        if (graph[m_].output == LOW){
                            m.output = HIGH;
                            break;
                        }
                    }
                    for (auto m_ : m.outputs){
                        conts[m.output]++;
                        qq.push(make_pair(m.output, m_));
                    }
                    break;
            }
        }
    }

    cout << "Part1: " << conts[LOW] << ", " << conts[HIGH] << ": " << conts[LOW]*conts[HIGH] << endl;
}

int main(int argc, char **argv){
    part1(argv[1]);
    return 0;
}
