#include <stdio.h>
#include "mpi.h"

int main(int argc,char *argv[]){
        int size, rank, dest, source, count, tag=1, i;
        int inmsg;
        int  outmsg;
        int nInicio, nParada;
	int sumas=0;

	MPI_Status Stat;
	
        MPI_Init(&argc,&argv);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        if (rank == 0) {
          dest = 1;
          source = size-1;
	for(i=1; i<=20000; i++){sumas++;}
	outmsg = sumas;
          MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
          MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
         printf("nodo maestro %d numero que envia %d\n",rank,outmsg);
                return 0;
        }else{

        for(i=0; i <= size-1; i++)
                {
                if(rank == i && i != size-1){
                        dest = i+1;
                        source = i-1;
                          MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
			nInicio = inmsg + 1;
			nParada = inmsg + 20000;
                          printf("nodo %d recibido de %d numero recibido %d\n",rank,source,nInicio);
			  for(i=nInicio; i<=nParada; i++){sumas=i;}
			  outmsg = sumas;
			  MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
			 printf("nodo %d recibido de %d numero enviado %d\n",rank,source,outmsg);

                          break;
                        }else if(rank==i){
                         dest = 0;
                         source = i-1;
                          MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
			 nInicio = inmsg+1;
                         nParada = inmsg * 2;

			 for(i=nInicio; i<=nParada; i++){sumas=i;}
                          outmsg = sumas;
                          printf("nodo final %d recibido de %d numero recibido %d\n",rank,source,outmsg);
                          MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
                        break;
                        }
                }

        }

        MPI_Get_count(&Stat, MPI_INT, &count);
        printf("Task %d: Received %d  procesos %d char(s) from task %d with tag %d \n",
                   rank, count,size, Stat.MPI_SOURCE, Stat.MPI_TAG);

        MPI_Finalize();
}    
