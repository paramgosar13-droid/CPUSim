#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

struct Task{
    public:
    string id;
    int burst;
    vector<string> mem_requests;
    size_t current_mem_index = 0;
};

class Cache{
    private:
    size_t capacity;
    vector<string> memory;

    public:
    Cache(size_t cap): capacity(cap){}

    bool contains(const string &block){
       return find(memory.begin(), memory.end(), block) != memory.end();
    }

    string insert(const string &block){
        if(block.empty() || contains(block)) return "";
        string evicted = "";
        if(memory.size()>=capacity){
            evicted = memory.front();
            memory.erase(memory.begin());
        }
        memory.push_back(block);
        return evicted;
    }
    void print(){
        cout<<"[";
        for(size_t i=0; i<memory.size(); i++){
            cout<<memory[i];
            if(i<memory.size()-1) cout<<", ";
        }
        cout<<"]"<<endl;
    }
};

class MemorySystem{
    public:
    Cache L1{32};
    Cache L2{128};
    Cache L3{512};
    int ram_access = 0;

    int access(const string &block){
        if (L1.contains(block)) {
            cout << " -> HIT L1 (4 cycles)"<<endl;
            return 4;
        }
        cout << " >> MISS L1";

        if (L2.contains(block)) {
            cout << " >> HIT L2 (12 cycles)"<<endl;
            string evicted = L1.insert(block);
            L2.insert(evicted);
            return 12;
        }
        cout << " >> MISS L2";

        if (L3.contains(block)) {
            cout << " >> HIT L3 (40 cycles)"<<endl;
            string evicted1 = L1.insert(block);
            string evicted2 = L2.insert(evicted1);
            L3.insert(evicted2);
            return 40;
        }
        cout << " >> MISS L3";

        cout << " -> Fetching from RAM (200 cycles)";
        ram_access++;
        string evicted1 = L1.insert(block);
        string evicted2 = L2.insert(evicted1);
        string evicted3 = L3.insert(evicted2);
        if (!evicted3.empty()) {
            cout << " ( evicted from L3: " << evicted3 << ")";
        }
        cout << endl;
        return 200;
    }

    void printState(){
        cout << "  L1: "; L1.print();
        cout << "  L2: "; L2.print();
        cout << "  L3: "; L3.print();
        cout << endl;
    }
};

int main(){
    ifstream file("input_task2.txt");
    if(!file.is_open()){
        cout<<"Error: Could not open the file!"<<endl;
        return 1;
    }

    queue<Task> tasks;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream line_ss(line);
        string token, id;
        int burst;

        if(!(line_ss >> token >> id >> token >> burst >> token)) continue;

        Task t;
        t.id = id;
        t.burst = burst;

        string mem_block;
        while (line_ss >> mem_block) {
            t.mem_requests.push_back(mem_block);
        }
        tasks.push(t);
    }
    file.close();

    MemorySystem mem_system;
    int global_cycle = 1;
    int tasks_completed = 0;

    cout << "=== Starting Simulation ===" << endl;

    // Round Robin Loop
     while(!tasks.empty()){
        Task task = tasks.front();
        tasks.pop();
        int active_burst = task.burst;

        for(int i=0; i<3; i++) {
            cout << "Cycle " << global_cycle << " - Running: " << task.id;

            if (task.current_mem_index < task.mem_requests.size()) {
                string current_req = task.mem_requests[task.current_mem_index];
                cout << " Requesting: " << current_req;
                int penalty = mem_system.access(current_req);
                task.current_mem_index++;
                global_cycle += penalty;
            }
            else {
                cout << " Core Processing..." << endl;
                global_cycle++;
            }

            mem_system.printState();
            cout << "------------------------------------------------" << endl;
            active_burst--;
        }
        task.burst = active_burst;
        if(task.burst>0){
            tasks.push(task);
        }
        else{
            tasks_completed++;
        }
        
    }

    cout << "\n=== Final Results ===" << endl;
    cout << "Total Cycles: " << global_cycle - 1 << endl;
    cout << "Tasks Completed: " << tasks_completed << endl;
    cout << "Scheduler: Round Robin (quantum = 3)" << endl;
    cout << "RAM Accesses: " << mem_system.ram_access << endl;

    return 0;
}