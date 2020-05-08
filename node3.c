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

struct distance_table 
{
  int costs[4][4];
} dt3;

/* students to write the following two routines, and maybe some others */

static int me=3;

void rtinit3() 
{
  int i = 0, j = 0;
  for (i = 0; i <= 3; i++)
    for (j = 0; j <= 3; j++)
      dt3.costs[i][j] = 999;
  dt3.costs[3][0] = 7;
  dt3.costs[3][1] = 999;
  dt3.costs[3][2] = 2;
  dt3.costs[3][3] = 0;
  printdt3(&dt3);
  send_packet3();
}

void send_packet3()
{
  struct rtpkt mypkt;
  mypkt.sourceid=3;
  int i=0;
  for (i=0;i<=3;i++)
  {
    mypkt.mincost[i]=dt3.costs[3][i];
  }
  mypkt.destid=0;
  tolayer2(mypkt);
  mypkt.destid=2;
  tolayer2(mypkt);
}

void rtupdate3(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{

  int i = 0;
  int flag=0;
  // printf("src=%d,dst=%d\ndata=%3d  %3d  %3d  %3d  \n", rcvdpkt->sourceid, rcvdpkt->destid, rcvdpkt->mincost[0], rcvdpkt->mincost[1], rcvdpkt->mincost[2], rcvdpkt->mincost[3]);
  for (i = 0; i <= 3; i++)
    dt3.costs[rcvdpkt->sourceid][i] = rcvdpkt->mincost[i];
  for (i = 0; i <= 3; i++)
  {
    if (dt3.costs[3][i] > (dt3.costs[3][rcvdpkt->sourceid] + dt3.costs[rcvdpkt->sourceid][i]))
    {
      dt3.costs[3][i] = dt3.costs[3][rcvdpkt->sourceid] + dt3.costs[rcvdpkt->sourceid][i];
      flag=1;
    }
  }
  printdt3(&dt3);
  if(flag)
    send_packet3();
}


printdt3(dtptr)
  struct distance_table *dtptr;
  
{
  printf("   D3 |    0     1    2    3\n");
  printf("  ----|--------------------\n");
  printf("     0|  %3d   %3d   %3d   %3d\n", dtptr->costs[0][0],
         dtptr->costs[0][1], dtptr->costs[0][2], dtptr->costs[0][3]);
  printf("     1|  %3d   %3d   %3d   %3d\n", dtptr->costs[1][0], dtptr->costs[1][1],
         dtptr->costs[1][2], dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d   %3d\n", dtptr->costs[2][0], dtptr->costs[2][1],
         dtptr->costs[2][2], dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d   %3d\n", dtptr->costs[3][0], dtptr->costs[3][1],
         dtptr->costs[3][2], dtptr->costs[3][3]);
  printf("\n");

}







