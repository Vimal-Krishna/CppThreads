#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
using namespace std;

class Maintenance {
private:    
    mutex M;
    condition_variable CV;
public:
    int operator()(int interval) {
        while (true) {
            cout << "Do maintenance" << endl;            
            cout << "Sleep" << endl;
            unique_lock<mutex> lck(M);
            CV.wait_for(lck, chrono::milliseconds(interval));            
            cout << "Wake up" << endl;
        }
        return 0;
    }
};

int main() {
    Maintenance maint;
    thread maint_thread(ref(maint), 2000);
    
    // Perform multi-threaded magic without being disturbed for maintenance activities   
    
    // Wait for the maintenance thread
    maint_thread.join();
    return 0;
}
