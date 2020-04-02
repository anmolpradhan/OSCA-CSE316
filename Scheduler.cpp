#include <iostream>
using namespace std;
class Scheduler{
	private:
		int processNo, currentTime, remainingProcess, indicator = 0, wait = 0, turnAroundTime = 0, arrivalTime[10], burstTime[10], remainingTime[10], x = 1;
	public:
		void process(int n){
			remainingProcess = n;
			for (processNo = 0; processNo < n; processNo++)
			{
				cout<<"\nEnter Arrival time and Burst time for Process P"<<processNo + 1<<"\n";
				cin>>arrivalTime[processNo];
				cin>>burstTime[processNo];
				remainingTime[processNo] = burstTime[processNo];
			}
			cout<<"Time quantum for first round is 6.\n";
			int timeQuantum = 6;
			currentTime = 0;
			for (processNo = 0; remainingProcess != 0;)
			{
				if (remainingTime[processNo] <= timeQuantum && remainingTime[processNo] > 0)
				{
					currentTime += remainingTime[processNo];
					remainingTime[processNo] = 0;
					indicator = 1;
				}
				else if (remainingTime[processNo] > 0)
				{
					remainingTime[processNo] -= timeQuantum;
					currentTime += timeQuantum;
				}
				else if (remainingTime[processNo] == 0 && indicator == 1)
				{
					cout<<"Process:"<<processNo;
					remainingProcess--;
					cout<<"P "<<processNo + 1;
					cout<<"\t\t\t"<<currentTime - arrivalTime[processNo];
					cout<<"\t\t\t"<< currentTime - burstTime[processNo] - arrivalTime[processNo]<<"\n";
					wait += currentTime - arrivalTime[processNo] - burstTime[processNo];
					turnAroundTime += currentTime - arrivalTime[processNo];
					indicator = 0;
				}
				if (processNo == n - 1)
				{
					x++;
					if (x == 2)
					{
						processNo = 0;
						timeQuantum = 10;
						cout<<"Time quantum for second round is 10. \n";
					}
					else
					{
						break;
					}
				}
				else if (currentTime >= arrivalTime[processNo + 1])
				{
					processNo++;
				}
				else
				{
					processNo = 0;
				}
			}

			thirdIteration(n, remainingTime, currentTime, arrivalTime);
		}
		void thirdIteration(int n, int remainingTime[10], int currenttime, int arrivalTime[10])
		{
			float averageWait, averageTurnAround;
			int bTime[20], processNo[20], waitingTime[20], turnAroundTime[20];
			for (int i = 0; i < n; i++)
			{
				bTime[i] = remainingTime[i];
				waitingTime[i] = currenttime - arrivalTime[i] - bTime[i];
				processNo[i] = i + 1;
			}
			int loc = 0, total;
			for (int i = 0; i < n; i++)
			{
				loc = i;
				for (int j = i + 1; j < n; j++)
				{
					if (bTime[j] < bTime[loc])
					{
						loc = j;
					}
				}
				int temp = bTime[i];
				bTime[i] = bTime[loc];
				bTime[loc] = temp;
				temp = processNo[i];
				processNo[i] = processNo[loc];
				processNo[loc] = temp;
			}

			for (int i = 1; i < n; i++)
			{
				for (int j = 0; j < i; j++)
				{
					waitingTime[i] += bTime[j];
				}
				total += waitingTime[i];
			}
			averageWait = (float)total / n;
			total = 0;
			cout<<"\nProcess\t\tBurst time\t\twaiting time\t\tTurn Around Time";
			for (int i = 0; i < n; i++)
			{
				turnAroundTime[i] = bTime[i] + waitingTime[i];
				total = total + turnAroundTime[i];
				cout << "\nP0" << processNo[i] << "\t\t\t" << bTime[i] << "\t\t\t" << waitingTime[i] << "\t\t\t" << turnAroundTime[i];
			}
			averageTurnAround = (float)total / n;
			cout<<"\nAverage Waiting Time:"<<averageWait<<"\nAverage Turn Around Time:"<<averageTurnAround<<"\n";
		}
};

int main()
{
	cout << "Enter the no. of processes:";
	int n;
	cin >> n;
	Scheduler s;
	s.process(n);
	return 0;
}

