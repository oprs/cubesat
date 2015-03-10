#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED






enum MsgTyp {
   T_QUAT   = 0,
   T_ROT    = 1,
   T_GPS=2,
   T_POS=3,
   T_DETUMB = 4,
   T_PING   = 5,
   T_TEMPS=6,
   T_MESURE=7,
   T_STOP=8,
} ;

struct ping{
    MsgTyp typ=T_PING;
    int p;
};

struct temps
{MsgTyp typ=T_TEMPS;
int t;
};


struct quaternion {
MsgTyp typ=T_QUAT;
int Q[4];
};

struct rotation {
MsgTyp typ=T_ROT;
   int R[3];
};

struct gps{
  MsgTyp typ=T_GPS;
int GPST [3];
};

struct position{
MsgTyp typ=T_POS;
int P[3];

};

struct message {
   MsgTyp typ;
      signed int M[4];

struct quaternion quat;
struct rotation rot;
struct position pos;
struct ping pin;
struct temps tem;
struct gps gpss;
};

#endif // STRUCTURE_H_INCLUDED
