#include <iostream>
#include <stack>
#include <fstream>
#include <cmath>
using namespace std;

int main()
{
    //Vars
    stack<int> partitions;
    int problems, t, n;
    
    ofstream outStream("output.txt", ofstream::out);
    ifstream inputStr("input.txt", ifstream::in);
    inputStr >> problems;
    
    //
    //Iteritive solution for each problem
    // This for loop iterates for each problem, so we
    // don't consider it in the time complexity analysis
    // Same for all code above this line.
    for (int k = 0; k < problems; k++)
    {
        //Local vars
        int minSum = 0, minCol = 0;
        int r = 0, c = 0;

        //Fill array
	inputStr >> n;
        inputStr >> t;

        int *data = new int[n];
        int **dpArr;
        dpArr = new int*[n];
	
	// complexity up to here --- Theta(1)
	
	// for loop:: Theta(n)
        for (int i = 0; i < n; i++)
        {
            int in;
            inputStr >> in;
	    data[i] = in;

            //Init dpArr to 0
            dpArr[i] = new int[n]();
        }

        //Find min inequality
	//for loop: Theta(n^2)
	// only the for loop within  this for loop brings any real complexity
        for (int i = 0; i < n; i++)
        {
            int sum = 0;

            //Get min of prev col
            if (i == 0)
            {

            }
            else
            {
                minCol = 99999;
		//for loop: Theta(n)
                for (int row = 0; row < n; row++)
                {
                    if (minCol > dpArr[row][i - 1] && dpArr[row][i - 1] != 0)
                    {
                        minCol = dpArr[row][i - 1];
                    }
                }
	    }

            //Fill dpArr
	    //for loop: Theta(n)
            for (int j = i; j < n; j++)
            {
                sum += data[j];

                if (sum <= t)
                {
                    dpArr[i][j] = minCol + ((t - sum) * (t - sum));
                }
                else
                {
                    break;
                }
            }
	    
	    //if statement: for loop: Theta(n)
            if (i == n - 1)
            {
                minCol = 99999;
                for (int row = 0; row < n; row++)
                {
                    if (minCol > dpArr[row][i] && dpArr[row][i] != 0)
                    {
                        minCol = dpArr[row][i];
                        r = row;
                        c = i;
                    }
                }

                //cout << minCol << endl;
            }
        }

        //Fill out stack to be printed
	//while loop: Theta(n^2)
        while (c >= 0)
        {
            partitions.push(c-r + 1);
            c = r - 1;
            minCol = 99999;
            for (int row = 0; row < n; row++)
            {
                if (minCol > dpArr[row][c] && dpArr[row][c] != 0)
                {
                    minCol = dpArr[row][c];
                    r = row;
                    c = c;
                }
            }
        }

        outStream << partitions.size() << " ";
	//while loop: Theta(n)
        while (partitions.size() != 0)
        {
            outStream << partitions.top() << " ";
            partitions.pop();
        }
	outStream << endl;

        //prints out the dparray
        /*for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << dpArr[i][j] << ' ';
            }
            cout << endl;
        }*/

        //Free memory after each problem
	//while loop: Theta(n)
        for (int i = 0; i < n; ++i) 
        {
            delete[] dpArr[i];
        }
        delete[] dpArr; 
        delete[] data;
    }

    return 0;
}


// Total complexity = Theta(n^2)
