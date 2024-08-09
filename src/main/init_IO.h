#ifndef IOFILE
#define IOFILE

#define SwitchJoint1UP A2
#define SwitchJoint1DOWN A1

#define SwitchJoint2UP A6
#define SwitchJoint2DOWN A3

#define SwitchJoint3UP A4
#define SwitchJoint3DOWN A5

#define SwitchJoint4UP A0
#define SwitchJoint4DOWN A7

// #define DIR_Joint1 51
// #define PUL_Joint1 53

// #define DIR_Joint2 46
// #define PUL_Joint2 52

// #define DIR_Joint3 50
// #define PUL_Joint3 44

// #define DIR_Joint4 48
// #define PUL_Joint4 45

#define DIR_Joint1 44
#define PUL_Joint1 45

#define DIR_Joint2 46
#define PUL_Joint2 47

#define DIR_Joint3 48
#define PUL_Joint3 49

#define DIR_Joint4 50
#define PUL_Joint4 51

#define DIR_Joint5 52
#define PUL_Joint5 53


int pinIN[8] = {
                SwitchJoint1UP,SwitchJoint1DOWN,
                SwitchJoint2UP,SwitchJoint2DOWN,
                SwitchJoint3UP,SwitchJoint3DOWN,
                SwitchJoint4UP,SwitchJoint4DOWN,
};

#endif