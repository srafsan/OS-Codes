#include <bits/stdc++.h>

using namespace std;

const int process = 5;
const int resource = 3;

void getNeed(int need[process][resource], int mx[process][resource], int allocation[process][resource])
{
    for (int i = 0; i < process; i++)
        for (int j = 0; j < resource; j++)
            need[i][j] = mx[i][j] - allocation[i][j];
}

void outPut(bool found, int safeSeq[], int requestProcessNo, int processRequest[])
{
    if (!found)
    {
        cout << "\nSystem is not in safe state" << endl;
        cout << "Request --> P" << requestProcessNo << " {";
        for(int i=0;i<resource;i++)
        {
            if(i >= 1)
                cout << ", ";
            cout << processRequest[i];
        }

        cout << "} is not satisfied" << endl;

        return;
    }

    cout << "System is in safe state." << endl;
    cout << "Safe sequence: {";

    for (int i = 0; i < process; i++)
    {
        if(i >= 1)
            cout << " --> ";
        cout << "P" << safeSeq[i];
    }

    cout << "}" << endl;
    cout << "Request --> P" << requestProcessNo << " {";

    for(int i=0; i<resource; i++)
    {
        if(i >= 1)
            cout << ", ";
        cout << processRequest[i];
    }
    cout << "} is satisfied" << endl;
}

void safeState(int processes[], int available[], int mx[][resource], int allocation[][resource], int givenResourceInstances[], int requestProcessNo, int processRequest[])
{
    int need[process][resource];

    getNeed(need, mx, allocation);

    int safeSeq[process], work[resource];
    bool finish[process] = {false};
    
    for (int i = 0; i < resource; i++)
        work[i] = available[i];
    
    int cnt = 0;
    
    while (cnt < process)
    {
        bool found = false, invalid = false;

        for (int p = 0; p < process; p++)
        {
            if (finish[p] == 0)
            {
                int j = 0;
                cout << "P" << p << " --> ";

                while(j < resource)
                {
                    if (need[p][j] > work[j])break;
                    j++;
                }

                if (j == resource)
                {
                    for(int i=0; i<resource;i++)
                        cout<<need[p][i]<<" ";
                    cout<<" <= ";

                    for (int k = 0; k < resource; k++)
                    {
                        work[k] += allocation[p][k];
                        cout << work[k] << " ";
                    }
                    cout<<endl;
                    
                    for(int k = 0; k < resource; k++)
                    {
                        if(work[k] > givenResourceInstances[k])
                        {
                            for(int i=0;i<resource;i++)
                                cout << work[i] << " ";
                            cout << " > ";

                            for(int i=0;i<resource;i++)
                                cout << givenResourceInstances[i] << " ";
                            cout << "--> Invalid Condition. --> break" << endl;

                            found = false;
                            invalid = true;
                            break;
                        }
                    }

                    if(invalid)
                        break;
                    
                    safeSeq[cnt++] = p;
                    finish[p] = 1;
                    found = true;
                }
                else
                {
                    for(int i=0; i<resource;i++)
                        cout << need[p][i] << " ";
                    cout<<" > ";

                    for(int i=0; i<resource;i++)
                        cout << work[i] << " ";
                    cout << "--> Go " << endl;
                }

                cout << "Current Sequence: {";

                for(int i=0;i<cnt;i++)
                {
                    if(i >= 1)
                    cout << " --> ";
                    cout << "P" << safeSeq[i];
                }
                cout << "}" << endl << endl;
            }
        }

        if (!found)
        {
            outPut(found, safeSeq, requestProcessNo, processRequest);
            return;
        }
    }

    outPut(true, safeSeq, requestProcessNo, processRequest);
    return;
}

int main()
{
    int processes[] = {0, 1, 2, 3, 4};
    int available[] = {3, 3, 2};
    int givenResourceInstances[] = {10, 5, 7};

    int requestProcessNo = 3;
    int processRequest[] = {0, 1, 0};

    int mx[][resource] = {
                        {7, 5, 3},
                        {3, 2, 2},
                        {9, 0, 2},
                        {2, 2, 2},
                        {4, 3, 3}
                    };

    int allocation[][resource] = {
                        {0, 1, 0},
                        {2, 0, 0},
                        {3, 0, 2},
                        {2, 1, 1},
                        {0, 2, 2}
                    };

    safeState(processes, available, mx, allocation, givenResourceInstances, requestProcessNo, processRequest);

    return 0;
}