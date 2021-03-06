#include<bits/stdc++.h>

using namespace std;

void displayProcess(int totalProcess, vector<int> &p)
{
    cout << "Process ";

    for(int i=0; i<totalProcess; i++)
        cout << p[i] << " ";
    cout << endl;
}

void displayFrames(int pageSize, int totalProcess, vector<vector<int> > &a)
{
    for(int i=0; i<pageSize; i++)
    {
        cout << "Frame " << i << " ";

        for(int j=0; j<totalProcess; j++)
        {
            if(a[i][j] == -1)
                cout << "E ";
            else
                cout << a[i][j] << " ";
        }

        cout << endl;
    }
}

void displayHit(int totalProcess, vector<int> &hit)
{
    cout << "\t";
    for(int i=0; i<totalProcess; i++)
    {
        if(hit[i] == 0)
            cout << "f ";
        else
            cout << hit[i] << " ";
    }

    cout << endl << endl;
}

void displayHitAndFault(int totalProcess, int hit)
{
    int pageFault = totalProcess - hit;
    cout <<"Hit:        " << hit << endl;
    cout <<"Page Fault: " << pageFault << endl;

    double hitRate = (1.0 * hit * 100) / totalProcess;
    cout << fixed;
    cout << "Hit Rate:   " << setprecision(3) << hitRate << "%" << endl;

    double faultRate = (1.0 * pageFault * 100) / totalProcess;
    cout << fixed;
    cout << "Hit Rate:   " << setprecision(3) << faultRate << "%" << endl;
}

int main(){
    int pageSize, totalProcess, i, j, k, hit=0;

    cout << "Page Size: ";
    cin  >> pageSize;
    
    cout << "Number of process: ";
    cin  >>totalProcess;

    vector<int> p(totalProcess);
    vector<int> hi(totalProcess);
    cout<<"Enter processes: ";
    for(i=0; i<totalProcess; i++)
        cin >> p[i];

    vector<vector<int> > a(pageSize);
    for(i=0; i<pageSize; i++)
        a[i]=vector<int>(totalProcess,-1);

    map <int, int> mp;
    for(i=0; i<totalProcess; i++)
    {
        vector<pair<int,int>> c;
        for(auto q: mp)
            c.push_back({q.second,q.first});
        
        sort(c.begin(), c.end());

        bool hasrun = false;
        for(j = 0; j < pageSize; j++)
        {
            if(a[j][i] == p[i])
            {
                hasrun = true;
                hi[i] = 1;
                mp[p[i]] = 1;
                hit++;
                break;
            }

            if(a[j][i] == -1)
            {
                for(k = i; k < totalProcess; k++)
                    a[j][k] = p[i];
                hasrun = true;
                mp[p[i]]++;
                break;
            }
        }

        if(j == pageSize || hasrun == false)
        {
            for(j = 0; j < pageSize; j++)
            {
                if(a[j][i] == c[c.size()-1].second)
                {
                    mp.erase(a[j][i]);
                    for(k = i; k < totalProcess; k++)
                        a[j][k] = p[i];
                    mp[p[i]]++;
                    break;
                }
            }
        }

        for(auto q: mp){
            if(q.first != p[i]){
                mp[q.first]++;
            }
        }
    }

    displayProcess(totalProcess, p);
    displayFrames(pageSize, totalProcess, a);
    displayHit(totalProcess, hi);
    displayHitAndFault(totalProcess, hit);

    return 0;
}

/*
OUTPUT:

Page Size: 4
Number of process: 23
Enter processes: 1 2 4 8 6 7 4 6 8 6 7 9 7 6 5 4 6 9 3 1 8 5 6
Process 1 2 4 8 6 7 4 6 8 6 7 9 7 6 5 4 6 9 3 1 8 5 6
Frame 0 1 1 1 1 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 8 8 8
Frame 1 E 2 2 2 2 7 7 7 7 7 7 7 7 7 7 7 7 9 9 9 9 5 5
Frame 2 E E 4 4 4 4 4 4 4 4 4 9 9 9 9 4 4 4 4 1 1 1 1
Frame 3 E E E 8 8 8 8 8 8 8 8 8 8 8 5 5 5 5 3 3 3 3 6
        f f f f f f 1 1 1 1 1 f 1 1 f f 1 f f f f f f

Hit:        8
Page Fault: 15
Hit Rate:   34.783%
Hit Rate:   65.217%

*/
