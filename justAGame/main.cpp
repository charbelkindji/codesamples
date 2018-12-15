#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int main()
{
    int score1(1), score2(0);
    vector <int>scores;

    do
    {
        do
        {
            scanf("%d %d", &score1, &score2);
        }while(score1 > 10 || score2 > 10);

        if(score1 == -1 || score2 == -2)
        {
            break;
        }

        scores.push_back(score1);
        scores.push_back(score2);

    }while(score1 != -1 && score2 != -1);

    for(int i(0); i < scores.size(); i+=2)
    {
        if(scores[i] == 1 || scores[i+1] == 1)
        {
            cout << scores[i] << "+" << scores[i+1] << "=" << scores[i]+scores[i+1] << endl;
        }else
        {
            cout << scores[i] << "+" << scores[i+1] << "!=" << scores[i]+scores[i+1] << endl;
        }
    }

    return 0;
}
