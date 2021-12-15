#include <iostream>
#include <random>
#include <cmath>
#include "simulation.h"

using namespace std;


void setSimulationParameters(int& sTime, int& numOfServers, int& transTime, int& tBetweenCArrival);
void runSimulation();

int main() 
{
  runSimulation();
}

void setSimulationParameters(int& sTime, int& numOfServers, int& transTime, int& tBetweenCArrival){
  
  cout << "Enter the simulation time: ";
  cin >> sTime;
  cout << endl;

  cout << "Enter the number of servers: ";
  cin >> numOfServers;
  cout << endl;

  cout << "Enter transaction time: ";
  cin >> transTime;
  cout << endl;

  cout << "Enter the time between customer arrivals: ";
  cin >> tBetweenCArrival;
  cout << endl;
}

void runSimulation(){
  int sTime = 0;
  int numOfServers = 0;
  int transTime = 0;
  int tBetweenCArrival = 0;
  setSimulationParameters(sTime,numOfServers,transTime,tBetweenCArrival);
  int cNumber = 1;
  int clock = 0;
  int tWaitTime = 0;
  int avgWaitTime = 0;
  int cServed = 0;
  int numLeftInQueue = 0;
  int numLeftWServer = 0;
  waitingCustomerQueueType queue(100);
  serverListType serverList(numOfServers);
/*
  customerType customer = queue.front();
  queue.deleteQueue();
  tWaitTime = tWaitTime + customer.getWaitingTime();
  serverList.setServerBusy(serverList.getFreeServerID(),customer, transTime);
*/
  for(clock = 1; clock < sTime; clock++){
    serverList.updateServers(cout);
    if(!queue.isEmptyQueue()){
        queue.updateWaitingQueue();
      }
    
    float lambda = 1.0/tBetweenCArrival;
    //cout << lambda;

    if((float) rand()/RAND_MAX > exp(-lambda)){              //my interpretation of the textbooks algo
      //cout << "hit" << endl; //CHECK OUTPUT TO SEE IT ITS WORKING
      queue.addQueue(customerType (cNumber, clock, 0, transTime));
      cout << "Customer number: " << cNumber << " arrived at time unit " << clock << endl;
      cNumber++;
    }
    
    int free = serverList.getFreeServerID();
    
    if(free != -1 && !queue.isEmptyQueue()){
      customerType cust = queue.front();
      queue.deleteQueue();
      tWaitTime = tWaitTime + cust.getWaitingTime();
      avgWaitTime = (avgWaitTime + cust.getWaitingTime())/2;
      serverList.setServerBusy(free, cust, transTime);
    }
    //else{

    //}
    //cout << endl;
  }

  int leftInQueue = 0;
  while(!queue.isEmptyQueue()){
    queue.deleteQueue();
    leftInQueue++;
  }
  int leftInServer = serverList.getNumberOfBusyServers();
  
  int cmpltTrans = cNumber - leftInQueue-1;

  cout << "This simulation ran: " << clock << " time units" << endl;
  cout << "Number of servers: " << numOfServers << endl;
  cout << "Average transaction time: " << transTime << endl;
  cout << "Average arrival time difference between customers: " << tBetweenCArrival << endl;
  cout << "Total waiting time: "<< tWaitTime << endl;
  cout << "Number of customers that completed the transaction: " << cmpltTrans << endl;
  cout << "Number of customers left in the servers: " << leftInServer << endl;
  cout << "The number of customers left in queue: " << leftInQueue << endl;
  cout << "Average waiting time: " << avgWaitTime << endl;
  cout << "*******************END SIMULATION*********************";
}