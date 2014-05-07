#include <stdio.h>

extern struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent 
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
  };


extern int TRACE;
extern int YES;
extern int NO;
extern float clocktime;

struct distance_table 
{
  int costs[4][4];
} dt3;

      /* printdt3(distance_table); */
      struct rtpkt node3pkt; 


/* students to write the following two routines, and maybe some others */


void rtinit3() 
{

     for (int i=0; i<4; i++){
          for (int j=0; j<4; j++)
               node3->costs[i][j] = 9999;
     }

     node3->costs[0][0] = 7;
     node3->costs[1][1] = 9999;
     node3->costs[2][2] = 2;
     node3->costs[3][3] = 0;
     
     struct rtpkt packet; 
     for (i=0; i<=3; i++){
          pkt2send3.mincost[i] = 999; // default mincost
     }
     for (i=0; i<=3; i++){
          for (j=0; j<=3; j++){
               if (node3->costs[i][j]<pkt2send3.mincost[i]){
                    pkt2send3.mincost[i] = node3->costs[i][j];
               }
          }
     }
     
      packet.sourceid = 3;
      packet.destid = 0;
      tolayer2(packet);
      packet.destid = 1;
      tolayer2(packet);
      packet.destid = 2;
      tolayer2(packet);
      printdt0(dt3);
}


void rtupdate3(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{


     int c[4];
     for (int i=0; i<4; i++){
          c[i] = packet.mincost[i];
    }

/* get the mincost values sent and compare them to values in the distance table */
     int src = rcvdpkt->sourceid;
     for (int i=0; i<4; i++){
          dt3.costs[i][src] = packet.mincost[src] + rcvdpkt->mincost[i];
     }

     struct rtpkt packet3;
     for (int i=0; i<4; i++){
          for (int k=0; k<4; k++){
               packet3.mincost[k] = 9999; // default mincost
          }
          for (int j=0; j<=3; j++){
               if (dt3.costs[i][j]<packet3.mincost[i]){
                    packet3.mincost[i] = dt3.costs[i][j];
               }
          }
     }


     int k = 0; 
     for (int i=0; i<4; i++){
          if (packet3.mincost[i]<packet.mincost[i]){
               packet.mincost[i]=packet3.mincost[i];
               k = 1;
          }
     }


     if (int k == 1) {
          packet.sourceid = 0;
          packet.destid = 1;
          tolayer2(packet);
          packet.destid = 2;
          tolayer2(packet);
          packet.destid = 3;
          tolayer2(packet);
          printdt3(dt3);
     }

}


printdt3(dtptr)
  struct distance_table *dtptr;
  
{
  printf("             via   \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}



linkhandler3(linkid, newcost)   
int linkid, newcost;   
/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}


