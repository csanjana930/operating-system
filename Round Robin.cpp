#include<iostream>
#include<string>
#include<queue>
#include<vector>
#include<utility>
using namespace std;

class Task{
    private:
        int id;
        int burstTime;
        int arrivingTime;
        
    public:
        Task(int id, int at, int rt){
            this->id = id;
            this->arrivingTime = at;
            this->burstTime = rt;
        }

        int getRemainingTime(){
            return this->burstTime;
        }

        int getId(){
            return this->id;
        }

        int getarrivingTime(){
            return this->arrivingTime;
        }

        void setArrivingTime(int time){
            this->burstTime = time;
        }
};

class RoundRobin{
    public:
        queue<Task> taskQueue;
        int timeQuantum;

        RoundRobin(int time){
            this->timeQuantum = time;
        }

        void enqueTask(Task t){
            taskQueue.push(t);
        }

        vector<int> completionTime(){
            vector<int> ans;
            int time = 0;

            while(!taskQueue.empty()){
                Task temp = taskQueue.front();
                taskQueue.pop();

                int exectime = min(temp.getRemainingTime() , timeQuantum);
                temp.setArrivingTime(temp.getRemainingTime() - exectime);

                time += exectime;

                if(temp.getRemainingTime() == 0){
                    int tat = time - temp.getarrivingTime();
                    ans.push_back(tat);
                    ans[temp.getId()-1] = tat;
                    // cout<<temp.getId()-1<<endl;
                }

                if(temp.getRemainingTime() > 0){
                    taskQueue.push(temp);
                }
            }
            return ans;
        }

};

int main()
{
    Task *t1 = new Task(1, 1, 2);
    Task *t2 = new Task(2, 3, 2);
    Task *t3 = new Task(3, 2, 2);
    Task *t4 = new Task(4, 5, 2);
    Task *t5 = new Task(5, 4, 2);

    int timeQuantum = 2;

    RoundRobin *process = new RoundRobin(timeQuantum);

    process->enqueTask(*t1);
    process->enqueTask(*t2);
    process->enqueTask(*t3);
    process->enqueTask(*t4);
    process->enqueTask(*t5);
    
    vector<int> completionTime = process->completionTime();

    cout<<"Turn around time for each task is : \n";
    for (int i=0; i<completionTime.size(); i++)
    {
        cout<<"Task t"<<i+1<<" : "<<completionTime[i]<<endl;
    }

return 0;
}
