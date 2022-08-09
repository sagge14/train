#include <iostream>
#include <thread>
#include <mutex>
#include <limits>
using namespace std;

mutex m;
template<typename T>
void enterValue(T &n, T min, T max);
void foo(int time, char c);

int main() {

    cout << "---Trains---" << endl;
    int time[3];

    cout << "---Train A---" << endl;
    cout << "Enter travel time to the train station:";
    enterValue(time[0],5,100);
    system("cls");
    cout << "---Train B---" << endl;
    cout << "Enter travel time to the train station:";
    enterValue(time[1],5,100);
    system("cls");
    cout << "---Train C---" << endl;
    cout << "Enter travel time to the train station:";
    enterValue(time[2],5,100);
    system("cls");

    thread train1(foo, time[0], 'A');
    thread train2(foo, time[1], 'B');
    thread train3(foo, time[2], 'C');
    train1.join();
    train2.join();
    train3.join();

    cout << "---Bye, bye---" << endl;
    system("pause");

    return 0;
}

template<typename T>
void enterValue(T &n, T min, T max)
{
    n = max / 2;
    do
    {
        if(!cin || (n < min || n > max))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "-------------------Error----------------\n";
            cout << min << " < number diapason < " << max;
            cout << "\n-----------------------------------------\n";
            cout << "Repeat enter:";
        }

        cin>>n;
    }
    while(!cin || (n < min || n > max));
}
void foo(int time, char c)
{
    m.lock();
    cout << "Train '" << c << "' in way!" << endl;
    m.unlock();

    string command = "-";
    std::this_thread::sleep_for(std::chrono::seconds(time));
    cout << "Train '" << c << "' coming..." << endl;

    m.lock();
    cout << "Train '" << c << "' arrived at the train station" << endl;
    while (command != "depart")
    {
        cout << "Enter the command:" << endl;
        cin >> command;
    }
    cout << "Train '" << c << "' departed!" << endl;
    m.unlock();
}