#include <bits/stdc++.h>
using namespace std;

const int T = 86400, H = 100;
const string er_text = "Please read README.md";

void early_exit(const string &s){
    cout << s;
    exit(0);
}

bool format_ok(const int &num,const int &L,const int &R){
    return num >= L && num <= R;
}

int max_value(const set<int> &s){
    return s.empty() ? 0 : *(s.rbegin());
}

int current_time = 0, current_floor = 1, move_count = 0;
bool go_up = true, go_down = false;
set<int> query_floor;


void simulate(int t){
    while(current_time < t){ 
        query_floor.erase(current_floor);

        if(go_down == false || current_floor == 1){
            if(max_value(query_floor) > current_floor) go_up = true, go_down = false;
            else go_up = false, go_down = true;
        }

        if(go_down && go_up){
            early_exit("Fatal Error\nPlease write \"miha.tropin@gmail.com\" to update version");

        }else if(go_up){
            current_floor++;
            move_count++;

        }else if(go_down && current_floor > 1){
            current_floor--;
            move_count++;

        }
        current_time++;
    }
}//simulation of lift moves

int call_count[H];

struct query{
    char type;
    int t, floor;

    bool operator<(const query& s) const{
        return t < s.t || (t == s.t && type == '!');
    }
};


int main(){
    freopen("data.txt", "r", stdin), freopen("out.txt", "w", stdout);

    int h = 1; cin >> h;
    if(!format_ok(h, 2, H - 1)) early_exit("Wrong Height of building\n" + er_text);

    vector<query> querys;
    
    for(char type;cin >> type;){
        int t = T, floor = 1; cin >> t;
        if(!format_ok(t, current_time, T - 1)) early_exit("Wrong Value of time\n" + er_text);

        if(type == '!'){
            cin >> floor;
            if(!format_ok(floor, 2, h)) early_exit("Wrong Value of floor\n" + er_text);

        }else if(type != '?'){
            early_exit("Data input format Error\n" + er_text);
        }
        querys.emplace_back(query{type, t, floor});

    }sort(querys.begin(), querys.end());

    
    cout << "Elevator positions: \n";

    for(const query &v:querys){
        if(v.type == '?'){
            simulate(v.t);
            cout << "Second " << v.t << " Floor = " << current_floor << '\n';

        }else if(v.type == '!'){
            query_floor.insert(v.floor);
            call_count[v.floor]++;

            simulate(v.t);
        }
    }
    simulate(T);
    
    cout << "\nBuilding Height" << ' ' << h << '\n';
    for(int i=2;i <= h;i++){
        cout << "Floor " << i << ": Count of calls = " << call_count[i] << '\n';
    }

    cout << "\nSummary moves = " << move_count;
    return 0;
}