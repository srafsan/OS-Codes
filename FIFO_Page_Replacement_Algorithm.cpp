#include <bits/stdc++.h>

using namespace std;

bool isPagePresent(queue<char> nq, char ch)
{
    bool found = false;

    while(!nq.empty())
    {
        if(ch == nq.front())
            found = true;
        nq.pop();
        if(found)
            break;
    }
    
    return found;
}

int main()
{
    int frameSize;
    string pageString;
    
    cout << "Number of Page Frames: ";
    cin  >> frameSize;
    
    cout << "Enter Page String: ";
    cin  >> pageString;

    char displayArr[frameSize+1][pageString.size()+1];
    int pageFaults = 0;
    queue<char> q, dq;

    for(int i=0;i<pageString.size();i++)
    {
        bool pageFaultsHappen = false;
        if(q.size() != frameSize && !isPagePresent(q, pageString[i]))
        {
            q.push(pageString[i]);
            pageFaults++;
            pageFaultsHappen = true;
        }
        else
        {
            bool pagePresent = isPagePresent(q, pageString[i]);

            if(!pagePresent)
            {
                q.pop();
                q.push(pageString[i]);
                pageFaults++;
                pageFaultsHappen = true;
            }
        }

        dq = q;

        for(int j=0; j<frameSize; j++)
        {
            if(dq.empty())
                displayArr[j][i] = 'E';
            else
            {
                displayArr[j][i] = dq.front();
                dq.pop();
            }
        }

        if(pageFaultsHappen)
            displayArr[frameSize][i] = 'f';
        else
            displayArr[frameSize][i] = 'n';
    }

    cout << "\nString : ";
    for(int i=0; i<pageString.size(); i++)
        cout << pageString[i] << " ";
    cout << endl;

    for(int i=0; i<=frameSize; i++)
    {
        if(i!=frameSize)
            cout << "Frame " << i << ": ";
        else
            cout<<"         ";

        for(int j=0; j<pageString.size(); j++)
            cout << displayArr[i][j]<<" ";
        cout << endl;
    }

    cout << "Page Faults: " << pageFaults << endl;
    
    return 0;
}