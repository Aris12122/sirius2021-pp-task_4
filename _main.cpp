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

int current_time = 0, current_floor = 1, move_count = 0;
bool go_up = true, go_down = false;
set<int> query_floor;


void simulate(int t){
    while(current_time < t){ 
        query_floor.erase(current_floor);

        if(go_down && go_up){
            early_exit("Fatal Error\nPlease write \"miha.tropin@gmail.com\" to update version");

        }else if(go_down && current_floor > 1){
            current_floor--;
            move_count++;

        }else{
            go_up = false, go_down = true;
            for(int floor:query_floor){
                if(floor > current_floor){
                    go_up = true, go_down = false;
                }
            }
            if(go_up){
                current_floor++;
                move_count++;
            }

        }
        current_time++;
    }
}//simulation of lift moves

int call_count[H];


int main(){
    freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);
    stringstream answer;
    int h; cin >> h;
    
    for(char type;cin >> type;){
        int t; cin >> t;
        if(!format_ok(t,current_time,T - 1)) early_exit("Wrong Value of time\n" + er_text);

        if(type == '?'){
            simulate(t);
            answer << t << ' ' << current_floor << '\n';

        }else if(type == '!'){
            int floor; cin >> floor;
            if(!format_ok(floor,2,h)) early_exit("Wrong Value of floor\n" + er_text);

            query_floor.insert(floor);
            call_count[floor]++;

            simulate(t);
        }else{
            early_exit("Data input format Error\n" + er_text);
        }
    }simulate(T);
    cout << answer.str();
    
    cout << h << '\n';
    for(int i=2;i <= h;i++){
        cout << i << ' ' << call_count[i] << '\n';
    }

    cout << move_count;
    return 0;
}