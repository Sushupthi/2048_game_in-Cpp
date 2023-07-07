/******************************************************************************

An interactive 2048 game which makes use of the standard template library

******************************************************************************/
#include <bits/stdc++.h>
using namespace std;

/*
    Parameters and seed values for the random-number generator
*/
const int M = (1 << 16) | 1;
const int A = 75;
const int C = 74;
int Xn = 0;

/*
    Return: returns a random (pseudo-random) number
*/
int generateRandomNumber()
{
    Xn = ((A * Xn) + C) % M;
    return Xn;
}

/*
    Arguments: take in a list of (x, y) coordinates of all the empty cells
    Return: returns a value (80% : 2, 20% : 4) along with a Randomly (Pseudo) 
    selected cell out of the empty cells
    pair<int, pair<int, int>> --> <value, <x, y>>
*/

pair<int, pair<int, int>> getRandomEmptyCellAndValue(vector<pair<int, int>> &emptyCells)
{
    int mini = 0, maxi = (int)emptyCells.size() - 1;
    int pos = (generateRandomNumber() % (maxi - mini + 1)) + mini;

    sort(emptyCells.begin(), emptyCells.end());  // O(N*logN)  time complexity where N is 16

    mini = 1, maxi = 10;
    int value = (generateRandomNumber() % (maxi - mini + 1)) + mini;

    if (value <= 8)
        return make_pair(2, emptyCells[pos]);
    
    return make_pair(4, emptyCells[pos]);
}


/*
    Print the current configuration of the board
*/
void printBoard(map<pair<int,int>,int>&filled) // O(N^2) time complexity 
{
	for(int i=4;i>=1;i--)  // O(N^2) time complexity where N is 4
    {
        for(int j=1;j<=4;j++)
        {
            if(filled.find(make_pair(j,i))!=filled.end())
            {
                cout<<filled[make_pair(j,i)]<<"\t";
            }
            else
            {
                cout<<"-"<<"\t";
            }
        }
        cout<<"\n";
    }
}

/*
    Arguments: takes in the direction of the move {1: left, 2: down, 3: right, 4: up}
    Return: after applying the move to the board, returns if the move was successful 
    in changing the board or not
*/
bool move(int direction,map<pair<int,int>,int>&filled,vector<pair<int,int>>&emptyCells,int &maxy) // O(N^2)  time complexity
{
    pair<int,int>emp,fill;
    int change =0;
    if(direction==1)
    {
        for(int i=4;i>=1;i--) // O(N^2) time complexity where N is 4
        {
            fill=make_pair(1,i);
            for(int j=1;j<=4;j++)
            {
                int merge=0;
                if(filled.find(make_pair(j,i))!=filled.end())
                {
                    filled[fill]=filled[make_pair(j,i)];
                    if(fill!=make_pair(j,i))
                    {
                        filled.erase(make_pair(j,i));
                        emptyCells.push_back(make_pair(j,i));
                        auto it1 = remove(emptyCells.begin(), emptyCells.end(), fill);
                        emptyCells.erase(it1,emptyCells.end());
                        change=1;
                    }
                    
                    if(fill.first - 1 >=1 && filled[fill]==filled[make_pair(fill.first - 1,fill.second)])
                    {
                        filled[make_pair(fill.first - 1,fill.second)]=2*filled[make_pair(fill.first - 1,fill.second)];
                        maxy=max(maxy,filled[make_pair(fill.first - 1,fill.second)]);
                        filled.erase(fill);
                        emptyCells.push_back(fill);
                        merge=1;
                        change=1;
                    }
                    
                    if(merge!=1)
                    {
                        fill=make_pair(fill.first+1,i);
                    }
                }
            }
        }
    }
    else if(direction==3)
    {
        for(int i=4;i>=1;i--) // O(N^2) time complexity where N is 4
        {
            fill=make_pair(4,i);
            for(int j=4;j>=1;j--)
            {
                int merge=0;
                if(filled.find(make_pair(j,i))!=filled.end())
                {
                    filled[fill]=filled[make_pair(j,i)];
                    if(fill!=make_pair(j,i))
                    {
                        filled.erase(make_pair(j,i));
                        emptyCells.push_back(make_pair(j,i));
                        auto it1 = remove(emptyCells.begin(), emptyCells.end(), fill);
                        emptyCells.erase(it1,emptyCells.end());
                        change=1;
                    }
                    
                    if(fill.first + 1 <=4 && filled[fill]==filled[make_pair(fill.first + 1,fill.second)])
                    {
                        filled[make_pair(fill.first + 1,fill.second)]=2*filled[make_pair(fill.first + 1,fill.second)];
                        maxy=max(maxy,filled[make_pair(fill.first + 1,fill.second)]);
                        filled.erase(fill);
                        emptyCells.push_back(fill);
                        merge=1;
                        change=1;
                    }
                    
                    if(merge!=1)
                    {
                        fill=make_pair(fill.first-1,i);
                    }
                }
            }
        }
    }
    else if(direction==2)
    {
        for(int i=1;i<=4;i++) // O(N^2) time complexity where N is 4
        {
            fill=make_pair(i,1);
            for(int j=1;j<=4;j++)
            {
                int merge=0;
                if(filled.find(make_pair(i,j))!=filled.end())
                {
                    filled[fill]=filled[make_pair(i,j)];
                    if(fill!=make_pair(i,j))
                    {
                        filled.erase(make_pair(i,j));
                        emptyCells.push_back(make_pair(i,j));
                        auto it1 = remove(emptyCells.begin(), emptyCells.end(), fill);
                        emptyCells.erase(it1,emptyCells.end());
                        change=1;
                    }
                    
                    if(fill.second - 1 >= 1 && filled[fill]==filled[make_pair(fill.first,fill.second - 1)])
                    {
                        filled[make_pair(fill.first,fill.second - 1)]=2*filled[make_pair(fill.first,fill.second - 1)];
                        maxy=max(maxy,filled[make_pair(fill.first,fill.second - 1)]);
                        filled.erase(fill);
                        emptyCells.push_back(fill);
                        merge=1;
                        change=1;
                    }
                    
                    if(merge!=1)
                    {
                        fill=make_pair(i,fill.second+1);
                    }
                }
            }
        }
    }
    else
    {
        for(int i=1;i<=4;i++) // O(N^2) time complexity where N is 4
        {
            fill=make_pair(i,4);
            for(int j=4;j>=1;j--)
            {
                int merge=0;
                if(filled.find(make_pair(i,j))!=filled.end())
                {
                    filled[fill]=filled[make_pair(i,j)];
                    if(fill!=make_pair(i,j))
                    {
                        filled.erase(make_pair(i,j));
                        emptyCells.push_back(make_pair(i,j));
                        auto it1 = remove(emptyCells.begin(), emptyCells.end(), fill);
                        emptyCells.erase(it1,emptyCells.end());
                        change=1;
                    }
                    
                    if(fill.second + 1 <=4  && filled[fill]==filled[make_pair(fill.first,fill.second + 1)])
                    {
                        filled[make_pair(fill.first,fill.second + 1)]=2*filled[make_pair(fill.first,fill.second + 1)];
                        maxy=max(maxy,filled[make_pair(fill.first,fill.second + 1)]);
                        filled.erase(fill);
                        emptyCells.push_back(fill);
                        merge=1;
                        change=1;
                    }
                    
                    if(merge!=1)
                    {
                        fill=make_pair(i,fill.second-1);
                    }
                }
            }
        }
    }
    return change;
}

/*
    Randomly selects a cell (using getRandomEmptyCellAndValue() function) and 
    assigns a value to it
*/
void populateRandomCell(vector<pair<int,int>>&emptyCells,map<pair<int,int>,int>&filled) // worst case O(N*logN)+O(N)
{
	pair<int,pair<int,int>>prandom;
    pair<int,int>p1;
    prandom=getRandomEmptyCellAndValue(emptyCells);
    p1=prandom.second;
    filled[p1]=prandom.first;
    auto it1 = remove(emptyCells.begin(), emptyCells.end(), p1); //worst case O(N) where N is 16
    emptyCells.erase(it1,emptyCells.end());
}

/*
    Return: returns the current status of the game
    {
        0: Game Over (You lose / No more possible moves left)
        1: Game Over (You win / Target Achieved)
        2: Game still in progress (Valid moves left)
    }
*/
int checkGameStatus(vector<pair<int,int>>&emptyCells,int &maxy) // O(1) time complexity
{
	if(emptyCells.size()==0)
    {
        return 0;
    }
    else
    {
        if(maxy==2048)
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }
}

/*
    Used to Initialize the Board and other values required by the game
*/
void initialize(vector<pair<int,int>>&emptyCells) // O(N^2) time complexity where N
{
	for(int i=1;i<=4;i++) // O(N^2) time complexity where N is 4
    {
        for(int j=1;j<=4;j++)
        {
            emptyCells.push_back(make_pair(i,j));
        }
    }
}

int main()
{
    // Read inputs here and perform actions on the board
    int n,x;
    
    vector<pair<int,int>>emptyCells;
    map<pair<int,int>,int>filled;
    
    initialize(emptyCells);
    
    populateRandomCell(emptyCells,filled);
    populateRandomCell(emptyCells,filled);
    cout<<"GAME BOARD:"<<"\n";
    printBoard(filled);
    cout<<"ENTER THE NUMBER OF MOVES YOU WANNA PLAY"<<"\n";
    int maxy=0;
    cin>>n;
    while(n)
    {
        cout<<"ENTER 1 FOR LEFT; 2 FOR DOWN; 3 FOR RIGHT; 4 FOR UP"<<"\n";
        cin>>x;
        if(move(x,filled,emptyCells,maxy))
        {
            populateRandomCell(emptyCells,filled);
            cout<<"GAME BOARD:"<<"\n";
            printBoard(filled);
            if(checkGameStatus(emptyCells,maxy)==1)
            {
                cout<<"Game Over, You Win"<<"\n";
                break;
            }
        }
        else
        {
            if(checkGameStatus(emptyCells,maxy)==0)
            {
                cout<<"Game Over, You Lose"<<"\n";
                break;
            }
            else if(checkGameStatus(emptyCells,maxy)==2)
            {
                cout<<"Invalid Move"<<"\n";
            }
        }
        n--;
    }
    return 0;
}