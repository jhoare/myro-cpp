#include<Myro.h>
#include<MyroIO.h>
#include<iostream>
#include<vector>

using namespace std;

int main(){
    connect();
    for (int i = 0; i < 10; i++){
        vector<int> allir = robot.getIR();
        cout << "All: " << allir << endl;
        cout << "Left  (int) " << robot.getIRdir(0) << endl;
        cout << "Right (int) " << robot.getIRdir(1) << endl;
        cout << "Left  (string) " << robot.getIRdir("left") << endl;
        cout << "Right (string) " << robot.getIRdir("right") << endl << endl;
    }
    disconnect();
    return 0;
}
