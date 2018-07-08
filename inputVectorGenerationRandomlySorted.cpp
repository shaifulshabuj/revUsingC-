#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
using namespace std;

int binaryTournamentSelection(int arrayName[], int len);
int vectorSeq = 0 ;

main()
{
    int i,j,k,d=0,p,m,n;
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


//  int cromosome[cromosomeLength];

    int population[populationSize][cromosomeLength];    //initialization of population randomly.
    int testCand[populationSize][gate];
    int fitness[populationSize];


    int checkGate[gate];

    int vectorAnalysis[10000][cromosomeLength+gate];
    for(int i=0;i<cromosomeLength+gate+1;i++)
    {
        if(i<cromosomeLength)
        {
            vectorAnalysis[vectorSeq][i] = 5;
        }
        else{
            vectorAnalysis[vectorSeq][i] = 0;
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

    cout <<"\n";
    cout <<"\n";




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
    cout << "\nAfter sorting:\n";

    for(int k=0;k<populationSize;k++)
    {
        for(j=0;j<cromosomeLength;j++)
        {
            cout << population[k][j]<<" ";
        }
        cout << "\n";
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

    cout << "\nAfter removing duplicate\n";

    for(int i=0;i<populationSize;i++)
    {
        for(int j=0;j<cromosomeLength;j++)
        {
            cout << population[i][j]<<" ";
        }
        cout << "\n";
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
    int arrayReplace[cromosomeLength]={4},replaceCount=0;
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

    cout << "\nAfter replacing duplicates with unique randoms\n";
    for(int i=0;i<populationSize;i++)
    {
        for(int j=0;j<cromosomeLength;j++)
        {
            cout << population[i][j]<<" ";
        }
        cout << "\n";
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

z:
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
                        testCand[m][d++]=i;
                    }
                }

            }

            fitness[m]=d;

            cout << "Fitness is "<<fitness[m]<<"\n";


            d=0;

        }

        cout << "\nTest Candidates\n";

        for(int j=0;j<populationSize;j++)
        {
            for(int i=0;i<gate;i++)
            {
                cout << ((testCand[j][i])+1)/2 <<" ";
            }
            cout << "\n";
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

        cout <<"\nMax Fit Cromosome "<< maxFitAddress+1<<" : ";
        cout <<"Max Fitness"<< maxFit<<"\n";
        cout <<"\nMin Fit Cromosome "<< minFitAddress+1<<" : ";
        cout <<"Min Fitness"<< minFit<<"\n";

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
            cout<<"\nMutation is not Occurred\n";
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
                cout<<"\nOffSpring "<<m+1<<" :";

                for(int i=0;i<wire;i++)
                {
                    circuit[i][0]=offSpin[m][i];
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
                            offSprinCand[m][d++]=i;
                        }
                    }

                }

                offSprinFitness[m]=d;

                cout << "Fitness is "<<offSprinFitness[m]<<"\n";


                d=0;

            }

            //replacing max offSpring with lowest fit population
            for(int i=0;i<2;i++)
            {
                if(offSprinFitness[i] > minFit)
                {
                    for(int j=0;j<cromosomeLength;j++)      //replacing max offspring vector with min population vector
                    {
                        cout <<".";
                        population[minFitAddress][j]=offSpin[i][j];
                    }
                    cout <<".";
                    fitness[minFitAddress]=offSprinFitness[i];  //replacing fitness
                    for(int p=0;p<gate;p++)                     //replacing test Candidates
                    {
                        cout <<".";
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

        cout <<"\nOff Spring Candidates\n";

        for(int i=0;i<2;i++)
        {
            for(int j=0;j<gate;j++)
            cout << ((offSprinCand[i][j])+1)/2 <<" ";
            cout <<"\n";
        }

        */

        for(int i=0;i<cromosomeLength+gate;i++)
        {
            if(i<cromosomeLength)
            {
                cout <<".";
                vectorAnalysis[vectorSeq][i]=population[maxFitAddress][i];
            }
            else if(i>=cromosomeLength)
            {
                for(int g=0;g<gate;g++)
                {
                    if(((((testCand[maxFitAddress][g])+1)/2)-1)==g)
                    {
                        cout <<"@";
                        vectorAnalysis[vectorSeq][i]=1;
                    }
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

        //sumCheckGate=0;
        for(int i=0;i<gate;i++)
        {
            if(checkGate[i]==0)
            {
                //sumCheckGate=sumCheckGate+1;
                goto z;
            }
        }

        cout << "\n";
        for(int j=0;j<100;j++)
        for(int i=0;i<cromosomeLength+gate;i++)
        {
            if(vectorAnalysis[j][i]!=5)
            {
                cout << vectorAnalysis[j][i]<<" ";
            }
            else{
                break;
            }
        }

        vectorSeq++;



    cout <<"\n";




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






