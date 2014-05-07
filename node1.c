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
} dt1;

      /* printdt1(distance_table); */
      struct rtpkt node1pkt; 


/* students to write the following two routines, and maybe some others */


void rtinit1() 
{
      for (int i=0; i<4; i++){
          for (int j=0; j<4; j++)
               node1->costs[i][j] = 9999;
      }

      node1->costs[0][0] = 1;
      node1->costs[1][1] = 0;
      node1->costs[2][2] = 1;
      node1->costs[3][3] = 9999;
     
      struct rtpkt packet; 
      for (i=0; i<=3; i++){
          pkt2send1.mincost[i] = 999; // default mincost
       }
       for (i=0; i<=3; i++){
            for (j=0; j<=3; j++){
                 if (node1->costs[i][j]<pkt2send1.mincost[i]){
                      pkt2send1.mincost[i] = node1->costs[i][j];
                 }
            }
       }

      packet.sourceid = 1;
      packet.destid = 0;
      tolayer2(packet);
      packet.destid = 2;
      tolayer2(packet);
      packet.destid = 3;
      tolayer2(packet);
      printdt0(dt1);
}


void rtupdate1(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{

     int c[4];
     for (int i=0; i<4; i++){
          c[i] = packet.mincost[i];
    }

/* get the mincost values sent and compare them to values in the distance table */
     int src = rcvdpkt->sourceid;
     for (int i=0; i<4; i++){
          dt1.costs[i][src] = packet.mincost[src] + rcvdpkt->mincost[i];
     }

     struct rtpkt packet1;
     for (int i=0; i<4; i++){
          for (int k=0; k<4; k++){
               packet1.mincost[k] = 9999; // default mincost
          }
          for (int j=0; j<=3; j++){
               if (dt1.costs[i][j]<packet1.mincost[i]){
                    packet1.mincost[i] = dt1.costs[i][j];
               }
          }
     }


     int k = 0; 
     for (int i=0; i<4; i++){
          if (packet1.mincost[i]<packet.mincost[i]){
               packet.mincost[i]=packet1.mincost[i];
               k = 1;
          }
     }


     if (int k == 1) {
          packet.sourceid = 1;
          packet.destid = 0;
          tolayer2(packet);
          packet.destid = 2;
          tolayer2(packet);
          packet.destid = 3;
          tolayer2(packet);
          printdt1(dt1);
     }

}


printdt1(dtptr)
  struct distance_table *dtptr;
  
{
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}



linkhandler1(linkid, newcost)   
int linkid, newcost;   
/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}


