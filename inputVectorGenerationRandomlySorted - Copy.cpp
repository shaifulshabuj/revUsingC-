#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
#include <fstream>
using namespace std;

int binaryTournamentSelection(int arrayName[], int len);
int vectorSeq = 0 ;

main()
{
    ofstream reportFile;
    reportFile.open ("report.txt");
    int i,j,k,d=0,p,m,n;
    int itr=1;          //iteration
    int minFit;
    int maxFit;
    int sumCheckGate=0;

    int wire,gate,col;
    int gNo=0;
    cout<< "enter the num of wire:";
    cin >> wire;
    cout<< "enter the num of gate:";
    cin >> gate;

    col = 2*gate + 1;

    int circuit[wire][col] ;        //circuit
    int temp[wire+1];   //
    int cromosomeLength;            //genetic algorithm
    int populationSize;

    cromosomeLength = wire;
    populationSize = ceil(0.2*(pow(2,wire)));
    int population[populationSize][cromosomeLength];    //initialization of population randomly.
    int testCand[populationSize][gate];
    int fitness[populationSize];
    int checkGate[gate];
    int vectorAnalysis[10000][cromosomeLength+gate];
    int dupVectorAnalysis[10000][cromosomeLength+gate];

    for(int i=0;i<cromosomeLength+gate;i++)
    {
        if(i<cromosomeLength)
        {
            vectorAnalysis[vectorSeq][i] = 5;
            dupVectorAnalysis[vectorSeq][i] = 5;
        }
        else if(i>=cromosomeLength){
            vectorAnalysis[vectorSeq][i] = 0;
            dupVectorAnalysis[vectorSeq][i] = 0;
        }
    }

/*
    for(int i=0;i<=vectorSeq;i++)
    {
        for(int j=0;j<cromosomeLength+gate;j++)
        {
            cout << vectorAnalysis[i][j]<<" ";
        }
        cout <<"\n";
    }
    cout <<"\n";*/

    for(int i=0;i<gate;i++)
    {
        checkGate[i]=0;
    }

/*
    for(int i=0;i<gate;i++)
    {
        cout<<checkGate[i]<<" ";
    }
    */

    //reportFile <<"\n";
    //reportFile <<"\n";




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
            reportFile << population[i][j]<<" ";
        }
        reportFile<<"\n";
    }
    reportFile<<"\n";



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

    for(i=cromosomeLength-1; i>=0 ;i--)
    {
        for(j=0;j<populationSize;j++)
        {
            if(population[j][i]==0)
            {
                for(int k=0; k<cromosomeLength; k++)
                {
                    sortPopulation[countRow][k]=population[j][k];
                }
                countRow++;
            }
        }

        for(j=0;j<populationSize;j++)
        {
            if(population[j][i]==1)
            {
                for(int k=0; k<cromosomeLength; k++)
                {
                    sortPopulation[countRow][k]=population[j][k];
                }
                countRow++;
            }
        }

        for(int k=0;k<populationSize;k++)
        {
            for(j=0;j<cromosomeLength;j++)
            {
                population[k][j]=sortPopulation[k][j];
            }
        }

        countRow=0;

    }
    reportFile << "\nAfter sorting:\n";

    for(int k=0;k<populationSize;k++)
    {
        for(j=0;j<cromosomeLength;j++)
        {
            reportFile << population[k][j]<<" ";
        }
        reportFile << "\n";
    }


    //duplicate removal part
    int dupMov[populationSize][cromosomeLength];

    for(int i=0;i<populationSize;i++)
    {
        for(int j=0;j<cromosomeLength;j++)
        {
            dupMov[i][j]=5;
        }
    }

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

    reportFile << "\nAfter removing duplicate\n";

    for(int i=0;i<populationSize;i++)
    {
        for(int j=0;j<cromosomeLength;j++)
        {
            reportFile << population[i][j]<<" ";
        }
        reportFile << "\n";
    }

    int x=0;                //duplicate counting
    for(i=0; i<populationSize;i++)
    {
        if(population[i][0]==5)
        {
            x++;
        }
    }

    //duplicate replacement
    /*int arrayReplace[cromosomeLength]={4},replaceCount=0;
    for(i=0; i<populationSize;i++)
    {
        if(population[i][0]==5)
        {
            Z:
            for(j=0;j<cromosomeLength;j++)
            {
                arrayReplace[j] = rand() % 2;
            }
            for(m=0;m<populationSize;m++)
            {
                for(n=0;n<cromosomeLength;n++)
                {
                    if(population[m][n]!=arrayReplace[n] && population[m][0]!=5)
                    {
                        replaceCount++;
                        break;
                    }
                }
            }
            if(replaceCount == populationSize-x)
            {
                for(n=0;n<cromosomeLength;n++)
                {
                    population[i][n]=arrayReplace[n];
                }
                replaceCount = 0;
            }
            else{
                replaceCount = 0;
                goto Z;
            }
        }
    }

    reportFile << "\nAfter replacing duplicates with unique randoms\n";
    for(int i=0;i<populationSize;i++)
    {
        for(int j=0;j<cromosomeLength;j++)
        {
            reportFile << population[i][j]<<" ";
        }
        reportFile << "\n";
    }*/

    int replaceCount=0;
    int arrayReplace[x][cromosomeLength];

    int uniqueDup = 0;
    while(uniqueDup == 0)
    {
        for(int i=0; i<x; i++)
        {
            for(int j=0; j<cromosomeLength; j++)
            {
                arrayReplace[i][j] = rand() % 2;
            }
        }

        int dupCount = 0;
        for(int i=0; i<x; i++)
        {
            uniqueDup = 0;
            for(int j=0; j<populationSize; j++)
            {
                for(int k=0; k<cromosomeLength && population[j][0]!=5; k++)
                {
                    if(arrayReplace[i][k] != population[j][k])
                    {
                        uniqueDup = 1;
                        break;
                    }
                    else{
                        dupCount++;
                    }
                    if(dupCount == cromosomeLength)
                    {
                        break;
                    }
                }
                if(dupCount == cromosomeLength)
                {
                    dupCount = 0;
                    break;
                }
            }
        }
    }

    for(int m=0; m<x; m++)
    {
        for(int i=0; i<populationSize; i++)
        {
            if(population[i][0] == 5)
            {
                for(int j=0; j<cromosomeLength; j++)
                {
                    population[i][j] = arrayReplace[m][j];
                }
            }
        }
    }


    //fitness defaulting initialize

    for(i=0;i<populationSize;i++)
    {
        fitness[i]=0;
    }



    for(j=0;j<populationSize;j++)
    {
        for(i=0;i<gate;i++)
        {
            testCand[j][i]=0;
        }
    }




    for(int i=0; i<col; i++)        //gates and input/output initialization.
    {
        if(i%2!=0)
        {
            cout <<"Gate No"<<++gNo<<" : ";
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
    reportFile << "\n";


    z1:{
        reportFile << "Iteration "<<itr<<" :\n";
        for(m=0;m<populationSize;m++)
        {
            reportFile<<"\nInput vector "<<m+1<<" :";

            for(int i=0;i<wire;i++)
            {
                circuit[i][0]=population[m][i];
            }

            reportFile << "\n";

            for(int i=0; i<wire; i++)
            {
                for(int j=0; j<col; j++)
                {
                    reportFile << circuit[i][j]<<" ";
                }
                reportFile << "\n";
            }

            reportFile << "\n";


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


            reportFile << "\nafter simulation\n";
            for(int i=0; i<wire; i++)           //result after simulation
            {
                for(int j=0; j<col; j++)
                {
                    reportFile << circuit[i][j]<<" ";
                }
                reportFile << "\n";
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
                        testCand[m][d++]=i;
                    }
                }

            }

            fitness[m]=d;

            reportFile << "Fitness is "<<fitness[m]<<"\n";


            d=0;

        }

        reportFile << "\nTest Candidates\n";

        for(int j=0;j<populationSize;j++)
        {
            for(int i=0;i<gate;i++)
            {
                reportFile << ((testCand[j][i])+1)/2 <<" ";
            }
            reportFile << "\n";
        }

        maxFit = -1;
        int maxFitAddress = -1;
        minFit = gate;
        int minFitAddress = -1;

        for(int j=0;j<populationSize;j++)
        {
            if(fitness[j] > maxFit)
            {
                maxFit = fitness[j];
                maxFitAddress = j;
            }
            else if(fitness[j] < minFit){
                minFit = fitness[j];
                minFitAddress = j;
            }
        }

        reportFile <<"\nMax Fit Cromosome "<< maxFitAddress+1<<" : ";
        reportFile <<"Max Fitness"<< maxFit<<"\n";
        reportFile <<"\nMin Fit Cromosome "<< minFitAddress+1<<" : ";
        reportFile <<"Min Fitness"<< minFit<<"\n";

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

       //reportFile << "\n" <<parentOneIndex<<" "<< fitness[parentOneIndex]<<"\n";
       //reportFile <<parentTwoIndex<<" "<< fitness[parentTwoIndex]<<"\n";

        int parentCromosome[2][cromosomeLength];

        for(int i=0;i<2;i++)
        {
            if(i==0)
            {
                for(j=0;j<cromosomeLength;j++)
                {
                    parentCromosome[i][j]=population[parentOneIndex][j];
                }
            }
            else{
                for(int j=0;j<cromosomeLength;j++)
                {
                    parentCromosome[i][j]=population[parentTwoIndex][j];
                }
            }
        }

        reportFile <<"\n";
        reportFile << "Parent Selection"<<"\n";

        for(i=0;i<2;i++)
        {
            for(j=0;j<cromosomeLength;j++)
            {
                reportFile << parentCromosome[i][j] <<" ";
            }
            reportFile << "\n";
        }

        //Crossover

        int offSpin[2][cromosomeLength];
        int crossOverNotOccuredFlag = 0;
        int mutationNotOccuredFlag = 0;
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
            reportFile << "Crossover Prob"<<crossOverProbability<<"\n";
            reportFile << "Crossover Position"<<randomCrossOverPosition<<"\n";
            reportFile << "After Crossover"<<"\n";
            for(int i=0;i<2;i++)
            {
                for(int j=0;j<cromosomeLength;j++)
                {
                    reportFile << offSpin[i][j] <<" ";
                }
                reportFile << "\n";
            }
        }else{
            reportFile<<"\nCrossover is not Occurred";
            crossOverNotOccuredFlag = 1;
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
            reportFile << "Mutation Prob"<<mutationProbability<<"\n";
            reportFile << "Mutation Position"<<randomMutationPosition<<"\n";
            reportFile << "After Mutation"<<"\n";
            for(int i=0;i<2;i++)
            {
                for(j=0;j<cromosomeLength;j++)
                {
                    reportFile << offSpin[i][j] <<" ";
                }
                reportFile << "\n";
            }
        }
        else{
            reportFile<<"\nMutation is not Occurred\n";
            mutationNotOccuredFlag =1;
        }

        //chances of having offspring's duplicate in population.(Not Worked on it yet)


        //replaced offspring with lower fittest chromosome of population

        int offSprinCand[2][gate];

        for(int i=0;i<2;i++)
        {
            for(int j=0;j<gate;j++)
            {
                offSprinCand[i][j]=0;
            }

        }

        int offSprinFitness[2]={0,0};
        if(crossOverNotOccuredFlag != 1)
        {
            for(m=0;m<2;m++)
            {
                reportFile<<"\nOffSpring "<<m+1<<" :";

                for(int i=0;i<wire;i++)
                {
                    circuit[i][0]=offSpin[m][i];
                }

                reportFile << "\n";

                for(int i=0; i<wire; i++)
                {
                    for(int j=0; j<col; j++)
                    {
                        reportFile << circuit[i][j]<<" ";
                    }
                    reportFile << "\n";
                }

                reportFile << "\n";


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


                reportFile << "\nafter simulation\n";
                for(int i=0; i<wire; i++)           //result after simulation
                {
                    for(int j=0; j<col; j++)
                    {
                        reportFile << circuit[i][j]<<" ";
                    }
                    reportFile << "\n";
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
                            offSprinCand[m][d++]=i;
                        }
                    }

                }

                offSprinFitness[m]=d;

                reportFile << "Fitness is "<<offSprinFitness[m]<<"\n";


                d=0;

            }

            //replacing max offSpring with lowest fit population
            for(int i=0;i<2;i++)
            {
                if(offSprinFitness[i] > minFit)
                {
                    for(int j=0;j<cromosomeLength;j++)      //replacing max offspring vector with min population vector
                    {
                        reportFile <<".";
                        population[minFitAddress][j]=offSpin[i][j];
                    }
                    reportFile <<".";
                    fitness[minFitAddress]=offSprinFitness[i];  //replacing fitness
                    for(int p=0;p<gate;p++)                     //replacing test Candidates
                    {
                        reportFile <<".";
                        testCand[minFitAddress][p]=offSprinCand[i][p];
                    }

                    for(int k=0;k<populationSize;k++)
                    {
                        if(fitness[k] > maxFit)
                        {
                            maxFit = fitness[k];
                            maxFitAddress = k;
                        }
                        else if(fitness[k] < minFit){
                            minFit = fitness[k];
                            minFitAddress = k;
                        }
                    }
                }
            }
        }

        /*

        reportFile <<"\nOff Spring Candidates\n";

        for(int i=0;i<2;i++)
        {
            for(int j=0;j<gate;j++)
            reportFile << ((offSprinCand[i][j])+1)/2 <<" ";
            reportFile <<"\n";
        }

        */

        int vectorArray[cromosomeLength+gate];
        for(int i=0;i<cromosomeLength+gate;i++)
        {
            if(i<cromosomeLength)
            {
                vectorArray[i]=5;
            }
            else if(i>=cromosomeLength)
            {
                vectorArray[i]=0;
            }

        }

        for(int i=0;i<cromosomeLength+gate;i++)
        {
            if(i<cromosomeLength)
            {
                reportFile <<".";
                vectorArray[i]=population[maxFitAddress][i];
            }
            else if(i>=cromosomeLength)
            {
                for(int g=0;g<gate;g++)
                {
                    if(((((testCand[maxFitAddress][g])+1)/2)-1)==g)
                    {
                        reportFile <<"@";
                        vectorArray[i]=1;
                    }
                }
            }
        }

        int countSameVec=0;

        for(int i=0;i<=10000;i++)
        {
            if(vectorAnalysis[i][0]!=5)
            {
                for(int j=0;j<cromosomeLength+gate;j++)
                {
                    if(vectorAnalysis[i][j]==vectorArray[j])
                    {
                        countSameVec++;
                    }
                }
                if(countSameVec!=(cromosomeLength+gate))
                {
                    for(int j=0;j<cromosomeLength+gate;j++)
                    {
                        vectorAnalysis[vectorSeq][j]=vectorArray[j];
                    }
                }
            }
            else if(vectorAnalysis[i][0]==5 && vectorSeq==0)
            {
                for(int j=0;j<cromosomeLength+gate;j++)
                {
                    vectorAnalysis[i][j]=vectorArray[j];
                }
            }
        }

        for(int i=0;i<gate;i++)
        {
            if(((((testCand[maxFitAddress][i])+1)/2)-1)==i && testCand[maxFitAddress][i]>0)
            {
                checkGate[i]=1;
            }
        }

        reportFile << "\n";

        vectorSeq++;

    }

    for(int i=0;i<gate;i++)
    {
        if(checkGate[i]==0)
        {
            itr++;
            goto z1;
        }
    }

    reportFile <<"\n";



    //duplicate removal part

    int countVecSame=0;
    for(int i=0;i<vectorSeq;i++)
    {
        if(vectorAnalysis[i][0]!=5)
        {
            for(int j=0;j<cromosomeLength+gate;j++)
            {
                dupVectorAnalysis[i][j]=vectorAnalysis[i][j];
                vectorAnalysis[i][j]=5;
            }

            for(int m=0;m<vectorSeq;m++)
            {
                if(vectorAnalysis[m][0]!=5)
                {
                    for(int n=0;n<cromosomeLength+gate;n++)
                    {
                        if(vectorAnalysis[m][n]==dupVectorAnalysis[i][n])
                        {
                            countVecSame++;
                        }
                    }
                    if(countVecSame==cromosomeLength+gate)
                    {
                        vectorAnalysis[m][0]=5;
                    }
                }
                countVecSame =0;
            }
        }
        else{
            break;
        }
    }


    for(int i=0;i<vectorSeq;i++)
    {
        if(dupVectorAnalysis[i][0]!=5)
        {
            for(int j=0;j<cromosomeLength+gate;j++)
            {
                vectorAnalysis[i][j]=dupVectorAnalysis[i][j];
            }
        }
        else{
                break;
        }
    }

    reportFile << "\n....................\n";
    reportFile << "\n  Vector Analysis \n";
    reportFile << "\n....................\n";

    for(int j=0;j<10000;j++)
    {
        for(int i=0;i<cromosomeLength+gate;i++)
        {
            if(vectorAnalysis[j][0]!=5)
            {
                reportFile << vectorAnalysis[j][i]<<" ";
            }
            else{
                break;
            }
        }
        reportFile << "\n";
    }



    reportFile << "\n";
    reportFile << "\n";

    reportFile.close();
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






