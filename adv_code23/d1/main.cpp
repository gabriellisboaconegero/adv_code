#include <bits/stdc++.h>
using namespace std;

void part1(){
    string line;
    int sum = 0;
    while (getline(cin, line)){
        sum += (line[line.find_first_of("0123456789")]-'0')*10 + (line[line.find_last_of("0123456789")]-'0');
    }
    cout << "part1: " << sum << endl;
}

size_t convert_to_num(string &str, size_t pos){
    if ('0' <= str[pos] && str[pos] <= '9')
        return  str[pos]-'0';

    if (str[pos] == 'o')
        return 1;
    if (str[pos] == 't'){
        if (str[pos+1] == 'w')
            return 2;
        return 3;
    }
    if (str[pos] == 'f'){
        if (str[pos+1] == 'o')
            return 4;
        return 5;
    }
    if (str[pos] == 's'){
        if (str[pos+1] == 'i')
            return 6;
        return 7;
    }
    if (str[pos] == 'e')
        return 8;
    return 9;
}

size_t first_spelled(string &str){
    string nums[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    size_t pos[9] = {0};
    for (int i = 0; i < 9; i++)
        pos[i] = str.find(nums[i]);

    return *min_element(pos, pos+9);
}

size_t last_spelled(string &str){
    string nums[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    size_t pos[9] = {0};
    size_t found;
    for (int i = 0; i < 9; i++){
        found = str.rfind(nums[i]);
        pos[i] = found != string::npos ? found : 0;
    }

    return *max_element(pos, pos+9);
}

void part2(){
    string line;
    size_t sum = 0;
    size_t first, last;
    size_t first_pos, last_pos, found;
    
    while(getline(cin, line)){
        first_pos = min(line.find_first_of("0123456789"), first_spelled(line));
        first = convert_to_num(line, first_pos);

        found = line.find_last_of("0123456789");
        found = found != string::npos ? found : 0;
        last_pos = max(found, last_spelled(line));
        last = convert_to_num(line, last_pos);
        
        sum += first*10 + last;
    }
    cout << "part2: " << sum << endl;
}

int main(){
    part1();
    // Resetar cin pois getline coloca ponteiro no fim após pegar tudo.
    cin.clear();
    cin.seekg(0);
    part2();
    return 0;
}
