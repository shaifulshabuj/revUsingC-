#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
using namespace std;

int binaryTournamentSelection(int arrayName[], int len);

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
        for(j=0;j<cromosomeLength;j++)
        {
            cout << population[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";

    /*

    //population sorting
    int countRow=0;
    int sortPopulation[populationSize][cromosomeLength];

    for(i=0;i<populationSize;i++)
    {
        for(j=0;j<cromosomeLength;j++)
        {
            sortPopulation[i][j] = 5;
        }
    }

    for(i=cromosomeLength-1;i>=0;i--)
    {
        for(j=0;j<populationSize;j++)
        {
            if(population[j][i]==0)
            {
                for(int k=0; k<cromosomeLength; k++)
                {
                    sortPopulation[countRow][k]=population[j][k];
                    countRow++;
                }
            }
        }
        for(int k=0;k<populationSize;k++)
        {
            for(j=0;j<cromosomeLength;j++)
            {
                cout << sortPopulation[k][j]<<" ";
            }
            cout << "\n";
        }
        cout << "wow\n";

        for(j=0;j<populationSize;j++)
        {
            if(population[j][i]==1)
            {
                for(int k=0; k<cromosomeLength; k++)
                {
                    sortPopulation[countRow][k]=population[j][k];
                    countRow++;
                }
            }
        }
        for(int k=0;k<populationSize;k++)
        {
            for(j=0;j<cromosomeLength;j++)
            {
                cout << sortPopulation[k][j]<<" ";
            }
            cout << "\n";
        }
        cout << "\n";

        for(int k=0;k<populationSize;k++)
        {
            for(j=0;j<cromosomeLength;j++)
            {
                population[k][j]=sortPopulation[k][j];
            }
        }

        for(int k=0;k<populationSize;k++)
        {
            for(j=0;j<cromosomeLength;j++)
            {
                cout << population[k][j]<<" ";
            }
            cout << "\n";
        }
        cout << "\n";
        cout << "\n";


    }
    */



    //fitness defaulting initialize

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

/*    for(int i=0; i<wire; i++)
    {
        for(int j=0; j<col; j++)
        {
            cout << circuit[i][j]<<" ";
        }
        printf("\n");
    }*/


    for(m=0;m<populationSize;m++)
    {
        cout<<"\nInput vector "<<m+1<<" :";

        for(int i=0;i<wire;i++)
        {
            circuit[i][0]=population[m][i];
        }

        cout << "\n";

        for(int i=0; i<wire; i++)
        {
            for(int j=0; j<col; j++)
            {
                cout << circuit[i][j]<<" ";
            }
            printf("\n");
        }

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
/*
                cout << "after temp initialization\n";
                for(int i=0; i<wire; i++)           //result
                {
                    for(int j=0; j<col; j++)
                    {
                        cout << circuit[i][j]<<" ";
                    }
                    printf("\n");
                }*/


                //simulation part

                int c=0;

                for(int j=0;j<wire;j++)
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


        cout << "\nafter simulation\n";
        for(int i=0; i<wire; i++)           //result after simulation
        {
            for(int j=0; j<col; j++)
            {
                cout << circuit[i][j]<<" ";
            }
            printf("\n");
        }

        bool change;                        //control change flag.
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


    //parent Selection Part using binary tournament selection

    int parentOneIndex,parentTwoIndex;

    parentOneIndex = binaryTournamentSelection(fitness, populationSize);

    for(int i=0; i>=0 ; i++ )
    {
        parentTwoIndex = binaryTournamentSelection(fitness, populationSize);
        if(parentOneIndex != parentTwoIndex)
        {
            break;
        }
    }

   //cout << "\n" <<parentOneIndex<<" "<< fitness[parentOneIndex]<<"\n";
   //cout <<parentTwoIndex<<" "<< fitness[parentTwoIndex]<<"\n";

    int parentCromosome[2][cromosomeLength];

    for(i=0;i<2;i++)
    {
        if(i==0)
        {
            for(j=0;j<cromosomeLength;j++)
            {
                parentCromosome[i][j]=population[parentOneIndex][j];
            }
        }
        else{
            for(j=0;j<cromosomeLength;j++)
            {
                parentCromosome[i][j]=population[parentTwoIndex][j];
            }
        }
    }

    cout <<"\n";
    cout << "Parent Selection"<<"\n";

    for(i=0;i<2;i++)
    {
        for(j=0;j<cromosomeLength;j++)
        {
            cout << parentCromosome[i][j] <<" ";
        }
        cout << "\n";
    }

    //Crossover

    int offSpin[2][cromosomeLength];
    int crossOverProbability = rand() % 100;
    int randomCrossOverPosition;

    if(crossOverProbability <= 90)          //Assuming that crossover probability high 0.9
    {
        randomCrossOverPosition = rand()% cromosomeLength;
        for(int i=0; i<cromosomeLength; i++)
        {
            if(i <= randomCrossOverPosition)
            {
                offSpin[0][i] = parentCromosome[0][i];
                offSpin[1][i] = parentCromosome[1][i];
            }
            else{
                offSpin[0][i] = parentCromosome[1][i];
                offSpin[1][i] = parentCromosome[0][i];
            }
        }
        cout << "Crossover Prob"<<crossOverProbability<<"\n";
        cout << "Crossover Position"<<randomCrossOverPosition<<"\n";
        cout << "After Crossover"<<"\n";
        for(int i=0;i<2;i++)
        {
            for(int j=0;j<cromosomeLength;j++)
            {
                cout << offSpin[i][j] <<" ";
            }
            cout << "\n";
        }
    }else{
        cout<<"\nCrossover is not Occurred";
    }

    //Mutation

    int mutationProbability = rand() % 100;
    int randomMutationPosition;

    if(mutationProbability < 2)                 //Assuming that Low Mutation Probability which is 0.02
    {
        randomMutationPosition = rand()% cromosomeLength;
        for(int i=0; i<2; i++)
        {
            for(int j=0; j<cromosomeLength; j++)
            {
                if(j==randomMutationPosition)
                {
                    if(offSpin[i][j]==0)
                    {
                        offSpin[i][j]= 1;
                    }
                    else{
                        offSpin[i][j]=0;
                    }
                }
            }
        }
        cout << "Mutation Prob"<<mutationProbability<<"\n";
        cout << "Mutation Position"<<randomMutationPosition<<"\n";
        cout << "After Mutation"<<"\n";
        for(int i=0;i<2;i++)
        {
            for(j=0;j<cromosomeLength;j++)
            {
                cout << offSpin[i][j] <<" ";
            }
            cout << "\n";
        }
    }
    else{
        cout<<"\nMutation is not Occurred";
    }


    //replaced offspring with lower fittest chromosome of population







    main();

    return 0;

}


int binaryTournamentSelection(int arrayName[], int len)
{
    int check = arrayName[0];
    int fitOne, fitTwo;

    fitOne = rand() % len;

    for(int i=0; i>=0 ; i++ )
    {
        fitTwo = rand()%len;
        if(fitOne!=fitTwo)
        {
            break;
        }
    }

    if(arrayName[fitOne] > arrayName[fitTwo])
    {
        return fitOne;
    }
    else{
        return fitTwo;
    }

}






