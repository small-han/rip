#include <stdio.h>

extern struct rtpkt
{
  int sourceid;   /* id of sending router sending this pkt */
  int destid;     /* id of router to which pkt being sent 
                         (must be an immediate neighbor) */
  int mincost[4]; /* min cost to node 0 ... 3 */
};

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table
{
  int costs[4][4];
} dt0;

/* students to write the following two routines, and maybe some others */

void rtinit0()
{
  int i = 0, j = 0;
  for (i = 0; i <= 3; i++)
    for (j = 0; j <= 3; j++)
      dt0.costs[i][j] = 999;
  dt0.costs[0][0] = 0;
  dt0.costs[0][1] = 1;
  dt0.costs[0][2] = 3;
  dt0.costs[0][3] = 7;
  printdt0(&dt0);
}

void rtupdate0(rcvdpkt) struct rtpkt *rcvdpkt;
{
}

printdt0(dtptr) struct distance_table *dtptr;

{
  printf("   D0 |    0     1    2    3\n");
  printf("  ----|--------------------\n");
  printf("     0|  %3d   %3d   %3d   %3d\n", dtptr->costs[0][0],
         dtptr->costs[0][1], dtptr->costs[0][2], dtptr->costs[0][3]);
  printf("     1|  %3d   %3d   %3d   %3d\n", dtptr->costs[1][0], dtptr->costs[1][1],
         dtptr->costs[1][2], dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d   %3d\n", dtptr->costs[2][3], dtptr->costs[2][1],
         dtptr->costs[2][2], dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d   %3d\n", dtptr->costs[3][3], dtptr->costs[3][1],
         dtptr->costs[3][2], dtptr->costs[3][3]);
  printf("\n");
}

linkhandler0(linkid, newcost) int linkid, newcost;

/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */

{
}
