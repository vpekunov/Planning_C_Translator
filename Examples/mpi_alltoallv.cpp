#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

/*
! This program shows how to use MPI_Alltoallv.  Each processor
! send/rec a different and random amount of data to/from other
! processors.  
! We use MPI_Alltoall to tell how much data is going to be sent.
*/
/* globals */
int numnodes,myid,mpi_err;
#define mpi_root 0
/* end module  */

void init_it(int  *argc, char ***argv);

void init_it(int  *argc, char ***argv) {
	mpi_err = MPI_Init(argc,argv);
    mpi_err = MPI_Comm_size( MPI_COMM_WORLD, &numnodes );
    mpi_err = MPI_Comm_rank(MPI_COMM_WORLD, &myid);
}

int main(int argc,char *argv[]){
	int *sray,*rray;
	int *sdisp,*scounts,*rdisp,*rcounts;
	int ssize,rsize,i,k,j;
	float z;

	init_it(&argc,&argv);
	scounts=(int*)malloc(sizeof(int)*numnodes);
	rcounts=(int*)malloc(sizeof(int)*numnodes);
	sdisp=(int*)malloc(sizeof(int)*numnodes);
	rdisp=(int*)malloc(sizeof(int)*numnodes);
/* find out how much data to send */
	for(i=0;i<numnodes;i++){
		scounts[i]=i+1;
	}
	printf("myid= %d scounts=",myid);
        for(i=0;i<numnodes;i++)
		printf("%d ",scounts[i]);
	printf("\n");
/* tell the other processors how much data is coming */
	mpi_err = MPI_Alltoall(	scounts,1,MPI_INT,
						    rcounts,1,MPI_INT,
	                 	    MPI_COMM_WORLD);
/*	write(*,*)"myid= ",myid," rcounts= ",rcounts */
/* calculate displacements and the size of the arrays */
	sdisp[0]=0;
	for(i=1;i<numnodes;i++){
		sdisp[i]=scounts[i-1]+sdisp[i-1];
	}
	rdisp[0]=0;
	for(i=1;i<numnodes;i++){
		rdisp[i]=rcounts[i-1]+rdisp[i-1];
	}
	ssize=0;
	rsize=0;
	for(i=0;i<numnodes;i++){
		ssize=ssize+scounts[i];
		rsize=rsize+rcounts[i];
	}
	
/* allocate send and rec arrays */
	sray=(int*)malloc(sizeof(int)*ssize);
	rray=(int*)malloc(sizeof(int)*rsize);
	for(i=0;i<ssize;i++)
		sray[i]=myid;
/* send/rec different amounts of data to/from each processor */
	mpi_err = MPI_Alltoallv(	sray,scounts,sdisp,MPI_INT,
						        rray,rcounts,rdisp,MPI_INT,
	                 	        MPI_COMM_WORLD);
	                
	printf("myid= %d array=",myid);
	for(i=0;i<rsize;i++)
		printf("%d ",rray[i]);
	printf("\n");
    mpi_err = MPI_Finalize();
}

