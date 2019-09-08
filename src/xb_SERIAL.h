#ifndef _XB_SERIAL_h
#define _XB_SERIAL_h

#include <xb_board.h>
#include <xb_board_def.h>

#ifndef SERIAL0_SizeRXBuffer
#define SERIAL0_SizeRXBuffer 128
#endif
#ifndef SERIAL1_SizeRXBuffer
#define SERIAL1_SizeRXBuffer 128
#endif
#ifndef SERIAL2_SizeRXBuffer
#define SERIAL2_SizeRXBuffer 128
#endif
#ifndef SERIALBT_SizeRXBuffer
#define SERIALBT_SizeRXBuffer 128
#endif


extern TTaskDef XB_SERIAL_DefTask;

#endif