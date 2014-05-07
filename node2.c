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
} dt2;

      /*  printdt2(distance_table); */
      struct rtpkt node2pkt; 


/* students to write the following two routines, and maybe some others */


void rtinit2() 
{

      for (int i=0; i<4; i++){
          for (int j=0; j<4; j++)
               node2->costs[i][j] = 9999;
      }

      node2->costs[0][0] = 3;
      node2->costs[1][1] = 1;
      node2->costs[2][2] = 0;
      node2->costs[3][3] = 2;
     
      struct rtpkt packet; 
      for (i=0; i<=3; i++){
          pkt2send2.mincost[i] = 999; // default mincost
       }
       for (i=0; i<=3; i++){
            for (j=0; j<=3; j++){
                 if (node2->costs[i][j]<pkt2send2.mincost[i]){
                      pkt2send2.mincost[i] = node2->costs[i][j];
                 }
            }
       }
     
      packet.sourceid = 2;
      packet.destid = 0;
      tolayer2(packet);
      packet.destid = 1;
      tolayer2(packet);
      packet.destid = 3;
      tolayer2(packet);
      printdt0(dt2);

}


void rtupdate2(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{

     int c[4];
     for (int i=0; i<4; i++){
          c[i] = packet.mincost[i];
    }

/* get the mincost values sent and compare them to values in the distance table */
     int src = rcvdpkt->sourceid;
     for (int i=0; i<4; i++){
          dt0.costs[i][src] = packet.mincost[src] + rcvdpkt->mincost[i];
     }

     struct rtpkt packet2;
     for (int i=0; i<4; i++){
          for (int k=0; k<4; k++){
               packet2.mincost[k] = 9999; // default mincost
          }
          for (int j=0; j<=3; j++){
               if (dt2.costs[i][j]<packet2.mincost[i]){
                    packet2.mincost[i] = dt2.costs[i][j];
               }
          }
     }


     int k = 0; 
     for (int i=0; i<4; i++){
          if (packet2.mincost[i]<packet.mincost[i]){
               packet.mincost[i]=packet2.mincost[i];
               k = 1;
          }
     }


     if (int k == 1) {
          packet.sourceid = 2;
          packet.destid = 0;
          tolayer2(packet);
          packet.destid = 1;
          tolayer2(packet);
          packet.destid = 3;
          tolayer2(packet);
          printdt2(dt2);
     }

}


printdt2(dtptr)
  struct distance_table *dtptr;
  
{
  printf("             via   \n");
  printf("   D2 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}



linkhandler2(linkid, newcost)   
int linkid, newcost;   
/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}


