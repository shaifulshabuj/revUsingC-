//negative control  :   0
//positive control  :   1
//target node       :   2
//no control        :   3
//input-output      :   4



#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

main()
{
    int i,j,m,n,d=0,q;
    int wire,gate,col,sameControl=0;
    int gNo=0;
    cout<< "enter the num of wire:";
    cin >> wire;
    cout<< "enter the num of gate:";
    cin >> gate;

    col = 2*gate + 1;

    int circuit[wire][col] ;
    int copyCircuit[wire][col];
    int tempCircuit[wire][col-2];
    int temp[wire+1];
    int testCand[gate];


    for(i=0;i<gate;i++)
    {
        testCand[i]=0;
    }

    for(i=0;i<wire;i++)
    {
        for(j=0;j<col-2;j++)
        {
            tempCircuit[i][j]=5;
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
                copyCircuit[j][i]=circuit[j][i];
            }
        }
        else
        {
            for(int j=0; j<wire; j++)       //for input-output
            {
                circuit[j][i]=4;
                copyCircuit[j][i]=circuit[j][i];
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


    cout<<"enter your circuit input vector:";

    for(int i=0;i<wire;i++)
    {
        cin >> circuit[i][0];
        copyCircuit[i][0]=circuit[i][0];
    }



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

            int c=0;

            for(int j=0;j<wire;j++)         //simulation part
            {
                if(circuit[j][i]==2)
                {
                    for(int k=0;k<wire;k++)
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

                                for(int p=0;p<wire;p++)
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


    if(d>0)
    {
        cout << "\nTest candidate gate : \n";

        for(i=0;i<gate;i++)
        {
            if(testCand[i]!=0)
            {
                cout << " Gate "<<(testCand[i]+1)/2 << "\n";
                sameControl+=1;
            }


        }

        cout << "\n";
        cout << "\n";


        for(m=0;m<sameControl;m++)
        {
            cout << "For test Gate"<<(testCand[m]+1)/2<<": \n";
            for(n=0;n<col;n++)
            {
                if(n!=testCand[m])
                {
                    for(int q=0;q<wire;q++)
                    {
                        tempCircuit[q][n]=copyCircuit[q][n];
                    }
                }
                else
                {
                    if(n!=(col-2))
                    {
                        for(i=n;i<col-2;i++)
                        {
                            for(int q=0;q<wire;q++)
                            {
                                tempCircuit[q][i]=copyCircuit[q][i+2];
                            }
                        }
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            for(int i=0;i<col-2;i++)
            {
                if(i%2!=0)
                {
                    for(int j=0;j<wire;j++)
                    {
                        if(tempCircuit[j][i]==0)            //temp initialization for negative control
                        {
                            if(tempCircuit[j][i-1]==0)
                            {
                                temp[j]=1;
                            }
                            else if(tempCircuit[j][i-1]==1)
                            {
                                temp[j]=0;
                            }
                        }
                        else if(tempCircuit[j][i]==1)       //temp initialization for positive control
                        {
                            if(tempCircuit[j][i-1]==0)
                            {
                                temp[j]=0;
                            }
                            else if(tempCircuit[j][i-1]==1)
                            {
                                temp[j]=1;
                            }
                        }
                        else if(tempCircuit[j][i]==2)
                        {
                            temp[j]=tempCircuit[j][i-1];
                        }

                    }

                    for(int j=0;j<wire;j++)         //simulation part
                    {
                        if(tempCircuit[j][i]==2)
                        {
                            for(int k=0;k<wire;k++)
                            {
                                if(k!=j && tempCircuit[k][i]!=3)
                                {
                                    temp[wire]=temp[k];

                                    for(int p=0;p<wire;p++)
                                    {
                                        if(p!=j && p!=k && tempCircuit[p][i]!=3)
                                        {
                                            temp[wire]=temp[wire]&temp[p];
                                        }
                                    }
                                    break;
                                }
                            }
                            temp[j]=temp[j]^temp[wire];
                            tempCircuit[j][i+1]=temp[j];
                        }
                    }

                    for(int j=0;j<wire;j++)
                    {
                        if(tempCircuit[j][i]==0)            //check negative control
                        {
                            if(tempCircuit[j][i-1]==0)
                            {
                                tempCircuit[j][i+1]=0;
                            }
                            else if(tempCircuit[j][i-1]==1)
                            {
                                tempCircuit[j][i+1]=1;
                            }
                        }
                        else if(tempCircuit[j][i]==1)       //check positive control
                        {
                            if(tempCircuit[j][i-1]==1)
                            {
                                tempCircuit[j][i+1]=1;
                            }
                            else if(tempCircuit[j][i-1]==0)
                            {
                                tempCircuit[j][i+1]=0;
                            }

                        }
                        else if(tempCircuit[j][i]==3)       //check no control and no target
                        {
                            tempCircuit[j][i+1]=tempCircuit[j][i-1];
                        }
                    }
                }
            }



            for(int i=0; i<wire; i++)           //result after simulation
            {
                for(int j=0; j<col-2; j++)
                {
                    cout << tempCircuit[i][j]<<" ";
                }
                printf("\n");
            }

            cout <<"\n";


            for(i=0;i<wire;i++)
            {
                if(tempCircuit[i][col-2]!=circuit[i][col])
                {
                    cout << "Test Gate "<<(testCand[m]+1)/2<<" is testable by input Vector : ";
                    for(i=0;i<wire;i++)
                    {
                        cout << tempCircuit[i][0] <<" ";
                    }
                }
            }

            cout <<"\n";
            cout <<"\n";
        }

    }
    else{
        cout << "\nTest candidate gates are not available. \n";
    }


    main();

}





