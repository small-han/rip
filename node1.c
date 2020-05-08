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

int connectcosts1[4] = { 1,  0,  1, 999 };

struct distance_table 
{
  int costs[4][4];
} dt1;


/* students to write the following two routines, and maybe some others */

static int me=1;

rtinit1() 
{
  int i = 0, j = 0;
  for (i = 0; i <= 3; i++)
    for (j = 0; j <= 3; j++)
      dt1.costs[i][j] = 999;
  dt1.costs[1][0] = 1;
  dt1.costs[1][1] = 0;
  dt1.costs[1][2] = 1;
  dt1.costs[1][3] = 999;
  printdt1(&dt1);
  send_packet1();

}


void send_packet1()
{
  struct rtpkt mypkt;
  mypkt.sourceid=1;
  int i=0;
  for (i=0;i<=3;i++)
  {
    mypkt.mincost[i]=dt1.costs[1][i];
  }
  mypkt.destid=0;
  tolayer2(mypkt);
  mypkt.destid=2;
  tolayer2(mypkt);
}

rtupdate1(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{
  int i = 0;
  int flag=0;
  // printf("src=%d,dst=%d\ndata=%3d  %3d  %3d  %3d  \n", rcvdpkt->sourceid, rcvdpkt->destid, rcvdpkt->mincost[0], rcvdpkt->mincost[1], rcvdpkt->mincost[2], rcvdpkt->mincost[3]);
  for (i = 0; i <= 3; i++)
    dt1.costs[rcvdpkt->sourceid][i] = rcvdpkt->mincost[i];
  for (i = 0; i <= 3; i++)
  {
    if (dt1.costs[1][i] > (dt1.costs[1][rcvdpkt->sourceid] + dt1.costs[rcvdpkt->sourceid][i]))
    {
      dt1.costs[1][i] = dt1.costs[1][rcvdpkt->sourceid] + dt1.costs[rcvdpkt->sourceid][i];
      flag=1;
    }
  }
  printdt1(&dt1);
  if(flag)
    send_packet1();

}


printdt1(dtptr)
  struct distance_table *dtptr;
  
{
  printf("   D1 |    0     1    2    3\n");
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



linkhandler1(linkid, newcost)   
int linkid, newcost;   
/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}


