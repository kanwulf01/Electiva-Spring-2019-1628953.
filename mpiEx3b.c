
#include <stdio.h>
#include "mpi.h"

int main(int argc,char *argv[]){
        int size, rank, dest, source, count, tag=1, i;
        char inmsg;
        int  outmsg=100;
        MPI_Status Stat;

        MPI_Init(&argc,&argv);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        if (rank == 0) {
          dest = 1;
          source = size-1;
          MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
          MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
         printf("nodo maestro %d mensaje recibido de %d mensaje de llegada %d\n",rank,source,inmsg);
		return 0;
        }else{
	
	for(i=0; i <= size-1; i++)
		{
		if(rank == i && i != size-1){
			dest = i+1;
			source = i-1;
			  MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
			  printf("nodo %d mensaje recibido de %d mensaje de llegada %d\n",rank,source,inmsg);
			  MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
			  break;
			}else if(rank==i){
			 dest = 0;
			 source = i-1;
			  MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
                          printf("nodo final %d mensaje recibido de %d mensaje de llegada %d\n",rank,source,inmsg);
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

