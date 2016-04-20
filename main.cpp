#include "mpi.h"
#include <stdlib.h> 
#include <ctime>
#include <iostream>
#include <locale.h> 
#include <conio.h> 
using namespace std;

int main(int argc, char *argv[])
{
   int size, rank;
   clock_t begin,end; 
   
   MPI_Status status;
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   //srand(time(NULL) + rank); 
     
   int ptr[3][100];
   int count[3][100];
   int first = 5040, second = 945, third = 30240;
   int f = 567, s = 854, th = 876;
   int seq1[100], seq2[100], seq3[100];
   int res[100];
   int st[100];
   int prevNok[200];
   int endNok[200];
   int resultSeq = 0;
   begin = clock();
   for(int i = 0; i < 100; i++){
         seq1[i] = 0;
         seq2[i] = 0;
         seq3[i] = 0;
         res[i] = 0;
         st[i] = 0;
   }
   for(int i = 0; i < 200; i++){
         prevNok[i] = 0;
         endNok[i] = 0;
   }

   for(int i = 0; i < 3; i++){
         for(int j = 0; j < 100; j++){
			ptr[i][j] = 0;
			count[i][j] = 0;
	    }
   }
 
   if ( rank == 0 ){
      
      int j = 0, i = 2;
      cout<<endl<<"Разложение числа "<<first<<": ";
	  while(i<=first)
	  {
		if(first%i==0)
		{
			first = first/i;
			cout<<i; 
			ptr[0][j] = i;
            j++;
			if(first>1)
                 cout<<"*";
		}
		else{
			i++;	
        }
      } 
   }
   
   if ( rank == 1 ){
      int j = 0, i = 2;
      cout<<endl<<"Разложение числа "<<third<<": ";
	  while(i<=third)
	  {
		if(third%i==0)
		{			
			third = third/i;
			cout<<i; 
			ptr[1][j] = i;
            j++;
			if(third>1)
                 cout<<"*";
		}
		else{
			i++;	
        }
       }   
   }
   
   if ( rank == 2 ){
      int j = 0, i = 2;
      cout<<endl<<"Разложение числа "<<second<<": ";
	  while(i<=second)
	  {
		if(second%i==0)
		{	
			second = second/i;
			cout<<i; 
			ptr[2][j] = i;
            j++;
			if(second>1)
                 cout<<"*";
		}
		else{
			i++;	
        }
       }
   }
   
   for(int j = 0; j < 100; j++){
		count[0][j] = ptr[rank][j];
   }
   
   MPI_Gather(count, 100, MPI_INT, ptr, 100, MPI_INT, 0, MPI_COMM_WORLD);
   MPI_Gather(count, 100, MPI_INT, ptr, 100, MPI_INT, 1, MPI_COMM_WORLD);
    
    if (rank == 0){
             cout<<endl;
        for(int i = 0; i < 100; i++){
              seq1[i] = ptr[0][i]; 
        } 
        
        for(int i = 0; i < 100; i++){
              seq2[i] = ptr[1][i];     
        }
         
        for(int i = 0; i < 100; i++){
              seq3[i] = ptr[2][i]; 
        }     
        
        
        
        bool check = false;
	    for(int i = 0; i < 100; i++){
         for(int j = 0; j < 100; j++){
		   if((seq1[i] == seq2[j])&&((seq1[i] != 0)&&(seq2[j] != 0))){
			   if(!check){
					res[resultSeq] = seq1[i];
				    resultSeq++;
					seq2[j] = 0;
					check = true;
			   }
		   }
   
           }
	       check = false;
        } 
        
         check = false;
         resultSeq = 0;
         for(int i = 0; i < 100; i++){
           for(int j = 0; j < 100; j++){
		   if((res[i] == seq3[j])&&((res[i] != 0)&&(seq3[j] != 0))){
			   if(!check){
					st[resultSeq] = res[i];
				    resultSeq++;
					seq3[j] = 0;
					check = true;
			   }
		   }
   
           }
	       check = false;
           }
           
           
           int nod = 1;
        for(int i=0; i<100; i++){
                if(st[i] != 0){
                         nod *= st[i];         
                }
	    }
        
       /* 
	cout<<endl<<" prevNOD: ";
	for(int i=0; i < 10; i++){
               cout<<st[i];
       } 
       cout<<endl;*/
       
        if (nod == 0){
           nod = 1;
        }
	    
	    cout<<"NOD: "<<nod<<endl;
    }
    
    if (rank == 1){
             cout<<endl;
          for(int i = 0; i < 100; i++){
              seq1[i] = ptr[0][i]; 
        } 
        
        for(int i = 0; i < 100; i++){
              seq2[i] = ptr[1][i];     
        }
         
        for(int i = 0; i < 100; i++){
              seq3[i] = ptr[2][i]; 
        }
        
        bool check = false;
	for(int i = 0; i < 100; i++){
       for(int j = 0; j < 100; j++){
		   if((seq1[i] == seq2[j])&&((seq1[i] != 0)&&(seq2[j] != 0))){
			   if(!check){
					seq2[j] = 0;
					check = true;
			   }
		   }
       }
	   check = false;
    }
	
	resultSeq = 0;
	for(int i=0; i<100; i++){
		if (seq1[i] != 0){
			prevNok[resultSeq] = seq1[i];
			resultSeq++;
		}
	}
	
	for(int i=0; i<100; i++){
		if (seq2[i] != 0){
			prevNok[resultSeq] = seq2[i];
			resultSeq++;
		}
	}
	/*
	cout<<endl<<" prevNOK: ";
	for(int i=0; i < 20; i++){
               cout<<prevNok[i];
       } 
       cout<<endl;*/


	check = false;
	for(int i = 0; i < 200; i++){
       for(int j = 0; j < 100; j++){
		   if((prevNok[i] == seq3[j])&&((prevNok[i] != 0)&&(seq3[j] != 0))){
			   if(!check){
					seq3[j] = 0;
					check = true;
			   }
		   }
       }
	   check = false;
    }

	resultSeq = 0;
	for(int i=0; i<200; i++){
		if (prevNok[i] != 0){
			endNok[resultSeq] = prevNok[i];
			resultSeq++;
		}
	}
	
	for(int i=0; i<100; i++){
		if (seq3[i] != 0){
			endNok[resultSeq] = seq3[i];
			resultSeq++;
		}
	   }
	  /*
	cout<<endl<<" endNOK: ";
	for(int i=0; i < 200; i++){
               cout<<endNok[i];
       } 
       cout<<endl;*/
	   
	   int nok = 1;
       for(int i=0; i < 200; i++){
               if(endNok[i] != 0) {
                   nok = nok * endNok[i];            
               }       
       }  
       
       cout<<"NOK: "<<nok<<endl;
    }
    


        end = clock();
        cout<<endl<<"Время выполнения алгоритма: "<<(double)(end-begin)/CLOCKS_PER_SEC<<" секунд."<<endl;
		
     MPI_Finalize();
}
