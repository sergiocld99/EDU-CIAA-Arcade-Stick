#include "MEF.h"

typedef enum {
    INIT, CONNECTING, ERROR, SUCCESS
} MEF_Status;

MEF_Status status;

void MEF_Init(){
    status = INIT;
}

void MEF_Connecting(){
    status = CONNECTING;

    
}