#include <bits/stdc++.h>

using namespace std;

int main()
{
    int frameSize;
    string pageString;

    cout << "Number of Page Frames: ";
    cin  >> frameSize;

    cout << "Enter Page String: ";
    cin  >> pageString;

    unordered_set<char> us;
    unordered_map<char, int> um;

    char displayArr[frameSize+1][pageString.size()+1];
    int pageFaults = 0;

    for(int i=0; i<pageString.size(); i++)
    {
        bool pageFaultsHappen = false;

        if(us.size() != frameSize && us.find(pageString[i]) == us.end())
        {
            us.insert(pageString[i]);
            pageFaults++;
            pageFaultsHappen = true;
        }
        else
        {
            bool pagePresent = (us.find(pageString[i]) != us.end());

            if(!pagePresent)
            {
                int idx = INT_MAX, val;

                for(auto it=us.begin();it!=us.end();it++)
                {
                    if(um[*it] < idx)
                    {
                        idx = um[*it];
                        val = *it;
                    }
                }

                us.erase(val);
                us.insert(pageString[i]);
                pageFaults++;
                pageFaultsHappen = true;
            }
        }

        um[pageString[i]] = i;
    }

    cout << "Page Faults: " << pageFaults << endl;
    
    return 0;
}
