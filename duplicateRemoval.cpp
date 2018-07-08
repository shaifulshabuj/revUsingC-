#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
using namespace std;


int main()
{
    int populationSize,cromosomeLength,i,j;
    cin >> populationSize;
    cin >> cromosomeLength;
    int population[populationSize][cromosomeLength];
    int dupMov[populationSize][cromosomeLength];

    for(int i=0;i<populationSize;i++)
    {
        for(int j=0;j<cromosomeLength;j++)
        {
            cin >> population[i][j];
        }
    }

    for(int i=0;i<populationSize;i++)
    {
        for(int j=0;j<cromosomeLength;j++)
        {
            dupMov[i][j]=5;
        }
    }

    //duplicate removal part

    int countSame=0;
    for(int i=0;i<populationSize;i++)
    {
        if(population[i][0]!=5)
        {
            for(int j=0;j<cromosomeLength;j++)
            {
                dupMov[i][j]=population[i][j];
                population[i][j]=5;
            }

            for(int m=0;m<populationSize;m++)
            {
                if(population[m][0]!=5)
                {
                    for(int n=0;n<cromosomeLength;n++)
                    {
                        if(population[m][n]==dupMov[i][n])
                        {
                            countSame++;
                        }
                    }
                    if(countSame==cromosomeLength)
                    {
                        population[m][0]=5;
                    }
                }
                countSame =0;
            }
        }
    }

    for(int i=0;i<populationSize;i++)
    {
        for(int j=0;j<cromosomeLength;j++)
        {
            population[i][j]=dupMov[i][j];
        }
    }

    cout << "\n";

    for(int i=0;i<populationSize;i++)
    {
        for(int j=0;j<cromosomeLength;j++)
        {
            cout << population[i][j]<<" ";
        }
        cout << "\n";
    }

    return 0;

}

