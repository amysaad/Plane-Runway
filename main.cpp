/* Name: Amy Saad
 * Files: main.cpp
 *
 * Program: Program to keep planes from crashing into one another on a runway, used for
 * both landing and take off.
 *
 * Input: Menu driven program, with possible inputs of ct (clear takeoff),
 * cl (clear landing), qt (queue takeoff), ql (queue landing), and s! (stop program).
 * The input of anything other than the many options results in an error message and displays
 * the menu again.
 *
 * Output: After each input, the screen displays the runway with the current status, landing
 * queue, takeoff queue, and the menu displayed again.
 *
 *
*/

#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;

class Runway {
public:
    virtual void showQueue() = 0;                               //shows the queue
    virtual void clearFlight() = 0;                             //clears flight from queue
    virtual void QueueFlight(const string& flightNumber) = 0;   //queues a flight
    virtual const string& GetFront() = 0;                       //gets first item in queue
    virtual bool IsQueueEmpty() = 0;                            //checks if queue is empty

};

class Landing : public Runway {
private:
    queue<string> LandingQueue;                                                //landing queue

    void DisplayQueue(const queue<string>& queue) {                            //displays queue with numbering format
        std::queue<string> TempQueue = queue;                                  //queue
        int count = 1;                                                         //counter for output
        while (!TempQueue.empty()) {                                           //while the temporary queue is not empty
            cout << setw(3) << count << ". " << TempQueue.front() << endl;  //queue format
            TempQueue.pop();                                                   //pops first element in temporary queue
            count++;                                                           //counter incremented for next number in queue
        }
    }

public:
    void showQueue() override {                         //shows landing queue
        cout << "-------- Runway 6A --------" << endl;
        cout << "Landing queue:" << endl;
        DisplayQueue(LandingQueue);              //displays landing queue
        cout << endl;
    }

    void clearFlight() override {                       //clears flight from queue
        if (!LandingQueue.empty()) {                    //checks if landing queue isn't empty
            LandingQueue.pop();                         //pops top element in queue
        }
    }

    void QueueFlight(const string& flightNumber) override {   //queues a flight
        LandingQueue.push(flightNumber);                   //pushes flight onto landing queue
    }


    const string& GetFront() override {                 //gets first item in queue
        return LandingQueue.front();                    //returns front of queue
    }

    bool IsQueueEmpty() override {                      //checks if queue is empty
        return LandingQueue.empty();                    //returns empty queue
    }

};

class Takeoff : public Runway {
private:
    queue<string> TakeoffQueue;                                                  //takeoff queue

    void DisplayQueue(const queue<string>& queue) {                              //displays queue with numbering format
        std::queue<string> TempQueue = queue;                                    //takeoff queue
        int count = 1;                                                           //counter for output
        while (!TempQueue.empty()) {                                             //while the temporary queue is not empty
            cout << setw(3) << count << ". " << TempQueue.front() << endl;    //queue format
            TempQueue.pop();                                                     //pops first element in temporary queue
            count++;                                                             //counter incremented for next number in queue
        }
    }

public:
    void showQueue() override {                         //shows queue
        cout << "Takeoff queue:" << endl;
        DisplayQueue(TakeoffQueue);              //displays takeoff queue
        cout << endl;
    }

    void clearFlight() override {                       //clears flight from queue
        if (!TakeoffQueue.empty()) {                    //checks if takeoff queue isn't empty
            TakeoffQueue.pop();                         //pops top element in takeoff queue
        }
    }

    void QueueFlight(const string& flight) override {   //queues a flight
        TakeoffQueue.push(flight);                   //pushes flight onto takeoff queue
    }


    const string& GetFront() override {                 //gets first item in queue
        return TakeoffQueue.front();                    //returns front of takeoff queue
    }

    bool IsQueueEmpty() override {                      //checks if queue is empty
        return TakeoffQueue.empty();                    //returns empty queue
    }

};

int main() {
    string userInput, flightNumber;  //string to store user input and flight number
    Takeoff takeoff;                 //instance for takeoff clas
    Landing landing;                 //instance for landing class

    while (true) {
        landing.showQueue();         //landing queue status
        takeoff.showQueue();         //takeoff queue status

        cout << "Menu:" << endl;                             //menu
        cout << "ct - clear flight for takeoff" << endl;
        cout << "cl - clear flight for landing" << endl;
        cout << "qt - queue flight for takeoff" << endl;
        cout << "ql - queue flight for landing" << endl;
        cout << "s! - stop the program" << endl;
        cout << endl;

        cout << "Enter your choice: ";
        cin >> userInput;

        if (userInput == "s!") {
            break;                      //stops program

        } else if (userInput == "ct") {
            if (!takeoff.IsQueueEmpty()) {                                          //checks if takeoff queue isn't empty
                cout << "Status: " << takeoff.GetFront() << " taking off" << endl;  //prints flight taking off
                takeoff.clearFlight();                                              //clears flight
            } else {
                cout << "Status: clear" << endl;                                    //displays clear status if queue is empty
            }

        } else if (userInput == "cl") {
            if (!landing.IsQueueEmpty()) {                                          //checks if landing queue isn't empty
                cout << "Status: " << landing.GetFront() << " landing" << endl;     //prints flight landing
                landing.clearFlight();                                              //clears flight
            } else {
                cout << "Status: clear" << endl;                                    //displays clear status if queue is empty
            }

        } else if (userInput == "qt") {
            cout << "Enter the flight number: ";
            cin >> flightNumber;                        //user input for flight number
            takeoff.QueueFlight(flightNumber);    //adds flight to takeoff queue
            cout << "Status: clear" << endl;

        } else if (userInput == "ql") {
            cout << "Enter the flight number: ";
            cin >> flightNumber;                        //user input for flight number
            landing.QueueFlight(flightNumber);          //adds flight to landing queue
            cout << "Status: clear" << endl;

        } else {
            cout << "Hmm.. that's not a menu option. Try again:" << endl;  //error message for invalid  input
        }
    }

    return 0;
}
