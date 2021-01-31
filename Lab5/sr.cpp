#include <bits/stdc++.h>
using namespace std;

int main(){
    int w, d, cnt=0; // w is window size, d is data size in number of pkts
    //cnt to keep the count of packets successfully sent
    cout << "Enter the number of packets to be sent\n";
    cin >> d;
    cout << "Enter the window size\n";
    cin>>w;
    queue<int> win, temp; //win queue is sent window
    // temp is the list of unacknowledged packets
    vector<int> RecBuf; //reciever side buffer or window
    while (cnt < d){
        // sending w packets
        for (int sn = 1; (sn <= d) and (win.size() < w); sn++){
            win.push(sn);
            temp.push(sn);
            cout << "Packet number " << sn << " sent\n";
        }
        cout << endl;
        //recieving w packets
        int tsize = temp.size();
        for (int i = 0; i < tsize; i++){
            int pseq = temp.front();
            temp.pop();
            if (((double)rand() / (RAND_MAX)) < 0.75){ //75% chance of recieving the packet case
                cout << "Ack received for packet " << pseq << endl;
                if (pseq == win.front()){ //Case when packet is in order
                    win.pop();
                    cnt++;
                }
                else RecBuf.push_back(pseq); //Case when packet is out of order
            }
            else{ //25% chance of packet loss case
                // timeout
                cout << "Timeout for packet number " << pseq << endl;
                cout << "Retransmitting packet number " << pseq << endl;
                temp.push(pseq);
            }
        }
        // retrieving the ordered data and sliding the window
        while(!RecBuf.empty()){
            bool flag = false;
            // Loop to find ordered packets
            for (int i = 0; i < RecBuf.size(); i++){
                if (win.front() == RecBuf[i]){
                    win.pop();
                    cnt++;
                    RecBuf.erase(RecBuf.begin() + i); //sliding the recieve window
                    flag = true; // to check the next value
                    break;
                }
            }
            if (!flag) break; 
        }
    }
}