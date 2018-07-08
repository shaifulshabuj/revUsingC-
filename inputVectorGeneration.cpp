#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
using namespace std;

int maximum(int arrayName[], int index, int len);
int nextMaximum(int arrayName[], int index, int len, int maxFit);

main()
{
    int i,j,k,d=0,p,m;

    int wire,gate,col;
    int gNo=0;
    cout<< "enter the num of wire:";
    cin >> wire;
    cout<< "enter the num of gate:";
    cin >> gate;

    col = 2*gate + 1;

    int circuit[wire][col] ;        //circuit
    int temp[wire+1];
    int testCand[gate];             //

    int cromosomeLength;            //genetic algorithm
    int populationSize;
    cromosomeLength = wire;
    populationSize = ceil(0.2*(pow(2,wire)));


//  int cromosome[cromosomeLength];
    int population[populationSize][cromosomeLength];    //initialization of population randomly.
    int fitness[populationSize];


    for(i=0;i<populationSize;i++)
    {
        for(j=0;j<cromosomeLength;j++)
        {
            population[i][j] = rand() % 2;
        }
    }

    for(i=0;i<populationSize;i++)
    {
        fitness[i]=0;
    }



    for(i=0;i<gate;i++)
    {
        testCand[i]=0;
    }


    for(int i=0; i<col; i++)        //gates and input/output initialization.
    {
        if(i%2!=0)
        {
            cout<<"Gate No"<<++gNo<<" : ";
            for(int j=0; j<wire; j++)       //for gates
            {
                cin >> circuit[j][i];
            }
        }
        else
        {
            for(int j=0; j<wire; j++)       //for input-output
            {
                circuit[j][i]=4;
            }

        }

    }
    printf("\n");

    for(int i=0; i<wire; i++)
    {
        for(int j=0; j<col; j++)
        {
            cout << circuit[i][j]<<" ";
        }
        printf("\n");
    }


    for(m=0;m<populationSize;m++)
    {
        cout<<"\nInput vector "<<m+1<<" :";

        for(int i=0;i<wire;i++)
        {
            circuit[i][0]=population[m][i];
        }


/*
        for(int i=0; i<wire; i++)
        {
            for(int j=0; j<col; j++)
            {
                cout << circuit[i][j]<<" ";
            }
            printf("\n");
        } */

        cout << "\n";


        for(int i=0;i<col;i++)
        {
            if(i%2!=0)
            {
                for(int j=0;j<wire;j++)
                {
                    if(circuit[j][i]==0)            //temp initialization for negative control
                    {
                        if(circuit[j][i-1]==0)
                        {
                            temp[j]=1;
                        }
                        else if(circuit[j][i-1]==1)
                        {
                            temp[j]=0;
                        }
                    }
                    else if(circuit[j][i]==1)       //temp initialization for positive control
                    {
                        if(circuit[j][i-1]==0)
                        {
                            temp[j]=0;
                        }
                        else if(circuit[j][i-1]==1)
                        {
                            temp[j]=1;
                        }
                    }
                    else if(circuit[j][i]==2)
                    {
                        temp[j]=circuit[j][i-1];
                    }

                }

                int c=0;

                for(j=0;j<wire;j++)         //simulation part
                {
                    if(circuit[j][i]==2)
                    {
                        for(k=0;k<wire;k++)
                        {
                            if(k!=j && circuit[k][i]==3)
                            {
                                c++;
                            }

                            if(c!=(wire-1))
                            {
                                if(k!=j && circuit[k][i]!=3)
                                {
                                    temp[wire]=temp[k];

                                    for(p=0;p<wire;p++)
                                    {
                                        if(p!=j && p!=k && circuit[p][i]!=3)
                                        {
                                            temp[wire]=temp[wire]&temp[p];
                                        }
                                    }
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }

                        if(c!=(wire-1))
                        {
                            temp[j]=temp[j]^temp[wire];
                            circuit[j][i+1]=temp[j];
                        }
                        else{
                            if(circuit[j][i-1]==0)
                            {
                                circuit[j][i+1]=1;
                            }
                            else{
                                circuit[j][i+1]=0;
                            }
                        }

                    }
                }

                for(int j=0;j<wire;j++)
                {
                    if(circuit[j][i]==0)            //check negative control
                    {
                        if(circuit[j][i-1]==0)
                        {
                            circuit[j][i+1]=0;
                        }
                        else if(circuit[j][i-1]==1)
                        {
                            circuit[j][i+1]=1;
                        }
                    }
                    else if(circuit[j][i]==1)       //check positive control
                    {
                        if(circuit[j][i-1]==1)
                        {
                            circuit[j][i+1]=1;
                        }
                        else if(circuit[j][i-1]==0)
                        {
                            circuit[j][i+1]=0;
                        }

                    }
                    else if(circuit[j][i]==3)       //check no control and no target
                    {
                        circuit[j][i+1]=circuit[j][i-1];
                    }
                }
            }
        }



        for(int i=0; i<wire; i++)           //result after simulation
        {
            for(int j=0; j<col; j++)
            {
                cout << circuit[i][j]<<" ";
            }
            printf("\n");
        }

        bool change;                  //control change flag.
        for(int i=0;i<col;i++)              //test Candidate gates finder.
        {
            if(i%2!=0)
            {
                change=false;
                for(int j=0;j<wire;j++)
                {
                    if(circuit[j][i]!=2 && circuit[j][i]!=circuit[j][i-1] && circuit[j][i]!=3)
                    {
                        change=true;
                        break;
                    }
                }
                if(change==false)
                {
                    testCand[d++]=i;
                }
            }

        }

        fitness[m]=d;

        cout << "Fitness is "<<fitness[m]<<"\n";


        d=0;

    }


    //parent Selection Part

    int maxFitIndex,nextMaxFitIndex;

    maxFitIndex = maximum(fitness,0,populationSize);

    nextMaxFitIndex = nextMaximum(fitness,0,populationSize,maxFitIndex);

//    cout << "\n" << fitness[maxFitIndex]<<"\n";
//    cout << fitness[nextMaxFitIndex]<<"\n";

    int parentCromosome[2][cromosomeLength];

    for(i=0;i<2;i++)
    {
        if(i==0)
        {
            for(j=0;j<cromosomeLength;j++)
            {
                parentCromosome[i][j]=population[maxFitIndex][j];
            }
        }
        else{
            for(j=0;j<cromosomeLength;j++)
            {
                parentCromosome[i][j]=population[nextMaxFitIndex][j];
            }
        }
    }

    for(i=0;i<2;i++)
    {
        for(j=0;j<cromosomeLength;j++)
        {
            cout << parentCromosome[i][j] <<" ";
        }
        cout << "\n";
    }



    main();

    return 0;

}



int maximum(int arrayName[], int index, int len)
{
    int maxFit;

    if(index >= len-2)
        return (arrayName[index] > arrayName[index + 1])
                    ? index
                    : index + 1;

    maxFit = maximum(arrayName, index + 1, len);

    return (arrayName[index] > arrayName[maxFit])
                ? index
                : maxFit;
}

int nextMaximum(int arrayName[], int index, int len, int maxFit)
{
    int nextMaxFit;

    if(index >= len-2)
        return (arrayName[index] > arrayName[index + 1] && arrayName[index]!=arrayName[maxFit] && arrayName[index+1]!= arrayName[maxFit])
                    ? index
                    : index + 1;

    nextMaxFit = nextMaximum(arrayName, index + 1, len, maxFit);

    return (arrayName[index] > arrayName[nextMaxFit] && arrayName[index]!=arrayName[maxFit] && arrayName[nextMaxFit]!= arrayName[maxFit])
                ? index
                : nextMaxFit;
}



