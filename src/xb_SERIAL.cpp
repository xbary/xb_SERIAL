#include <xb_board.h>
#include <xb_board_def.h>
#include <xb_SERIAL.h>
#ifdef XB_GUI
#include <xb_GUI.h>
#endif

#ifdef SerialBluetooth
#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
#endif


bool XB_SERIAL_DoMessage(TMessageBoard *Am);
void XB_SERIAL_Setup();
uint32_t XB_SERIAL_DoLoop();

TTaskDef XB_SERIAL_DefTask = {0, &XB_SERIAL_Setup, &XB_SERIAL_DoLoop, &XB_SERIAL_DoMessage };


#ifdef Serial0Board_BAUD
uint8_t *XB_SERIAL0_RXBuf;
uint8_t XB_SERIAL0_UseGET;
#endif
#ifdef Serial0BoardBuf_BAUD
TBuf XB_SERIAL0_RXBuf;
TBuf XB_SERIAL0_TXBuf;
uint8_t XB_SERIAL0_UseGET;
bool XB_SERIAL0_DisableTX;
#endif

#ifdef Serial1Board_BAUD
uint8_t *XB_SERIAL1_RXBuf;
uint8_t XB_SERIAL1_UseGET;
#endif
#ifdef Serial2Board_BAUD
uint8_t *XB_SERIAL2_RXBuf;
uint8_t XB_SERIAL2_UseGET;
#endif
#ifdef SerialBluetooth
uint8_t* XB_SERIALBT_RXBuf;
uint8_t XB_SERIALBT_UseGET;
#endif

void XB_SERIAL_Setup()
{

#ifdef Serial0Board_BAUD

#ifndef __riscv64
#if defined(Serial0Board_RX_PIN) && defined(Serial0Board_TX_PIN)
	Serial.begin(Serial0Board_BAUD, SERIAL_8N1, Serial0Board_RX_PIN, Serial0Board_TX_PIN);
#else
	Serial.begin(Serial0Board_BAUD, SERIAL_8N1);
#endif
#else
	Serial.begin(Serial0Board_BAUD);
#endif
	XB_SERIAL0_UseGET = 0;
	XB_SERIAL0_RXBuf = (uint8_t *)board._malloc(SERIAL0_SizeRXBuffer);

#if defined(ESP32) || defined(ESP8266)
#ifdef Serial0Board_UseDebugOutPut
	Serial.setDebugOutput(true);
#else
	Serial.setDebugOutput(false);
#endif
#endif

#ifdef Serial0Board_UseKeyboard 
	board.BeginUseGetStream(&XB_SERIAL_DefTask, 0);
	board.AddStreamAddressAsKeyboard(&XB_SERIAL_DefTask, 0);
#endif
#ifdef Serial0Board_UseLog
	board.AddStreamAddressAsLog(&XB_SERIAL_DefTask, 0);
#endif	
#ifdef Serial0Board_UseGui
	board.AddStreamAddressAsGui(&XB_SERIAL_DefTask, 0);
#endif	

#endif

#ifdef Serial0BoardBuf_BAUD

#ifndef __riscv64
#if defined(Serial0Board_RX_PIN) && defined(Serial0Board_TX_PIN)
	Serial.begin(Serial0BoardBuf_BAUD, SERIAL_8N1, Serial0Board_RX_PIN, Serial0Board_TX_PIN);
#else
	Serial.begin(Serial0BoardBuf_BAUD, SERIAL_8N1);
#endif
#else
	Serial.begin(Serial0BoardBuf_BAUD);
#endif
	XB_SERIAL0_UseGET = 0;
	XB_SERIAL0_RXBuf.SectorSize = 32;
	XB_SERIAL0_TXBuf.SectorSize = 512;
	XB_SERIAL0_TXBuf.AlarmMaxLength = 4096;
	XB_SERIAL0_DisableTX = false;

#if defined(ESP32) || defined(ESP8266)
#ifdef Serial0BoardBuf_UseDebugOutPut
	Serial.setDebugOutput(true);
#else
	Serial.setDebugOutput(false);
#endif
#endif

#ifdef Serial0BoardBuf_UseKeyboard 
	board.BeginUseGetStream(&XB_SERIAL_DefTask, 0);
	board.AddStreamAddressAsKeyboard(&XB_SERIAL_DefTask, 0);
#endif
#ifdef Serial0BoardBuf_UseLog
	board.AddStreamAddressAsLog(&XB_SERIAL_DefTask, 0);
#endif	
#ifdef Serial0BoardBuf_UseGui
	board.AddStreamAddressAsGui(&XB_SERIAL_DefTask, 0);
#endif	

#endif


#ifdef Serial1Board_BAUD

#ifndef __riscv64
#if defined(Serial1Board_RX_PIN) && defined(Serial1Board_TX_PIN)
	Serial1.begin(Serial1Board_BAUD, SERIAL_8N1, Serial1Board_RX_PIN, Serial1Board_TX_PIN);
#else
	Serial1.begin(Serial1Board_BAUD, SERIAL_8N1);
#endif
#else
	Serial.begin(Serial0Board_BAUD);
#endif
#if defined(ESP32) || defined(ESP8266)
#ifdef Serial1Board_UseDebugOutPut
	Serial1.setDebugOutput(true);
#else
	Serial1.setDebugOutput(false);
#endif
#endif

	XB_SERIAL1_UseGET = 0;
	XB_SERIAL1_RXBuf = (uint8_t *)board._malloc(SERIAL1_SizeRXBuffer);

	
	
#ifdef Serial1Board_UseKeyboard 
	board.BeginUseGetStream(&XB_SERIAL_DefTask, 1);
	board.AddStreamAddressAsKeyboard(&XB_SERIAL_DefTask, 1);
#endif
#ifdef Serial1Board_UseLog
	board.AddStreamAddressAsLog(&XB_SERIAL_DefTask, 1);
#endif	
#ifdef Serial1Board_UseGui
	board.AddStreamAddressAsGui(&XB_SERIAL_DefTask, 1);
#endif	
	
#endif

#ifdef Serial2Board_BAUD
#ifndef __riscv64
#if defined(Serial2Board_RX_PIN) && defined(Serial2Board_TX_PIN)
	Serial2.begin(Serial2Board_BAUD, SERIAL_8N1, Serial2Board_RX_PIN, Serial2Board_TX_PIN);
#else
	Serial2.begin(Serial2Board_BAUD, SERIAL_8N1);
#endif
#else
	Serial.begin(Serial0Board_BAUD);
#endif

#if defined(ESP32) || defined(ESP8266)
#ifdef Serial2Board_UseDebugOutPut
	Serial2.setDebugOutput(true);
#else
	Serial2.setDebugOutput(false);
#endif
#endif
	XB_SERIAL2_UseGET = 0;
	XB_SERIAL2_RXBuf = (uint8_t *)board._malloc(SERIAL2_SizeRXBuffer);
	
#ifdef Serial2Board_UseKeyboard 
	board.BeginUseGetStream(&XB_SERIAL_DefTask, 2);
	board.AddStreamAddressAsKeyboard(&XB_SERIAL_DefTask, 2);
#endif
#ifdef Serial2Board_UseLog
	board.AddStreamAddressAsLog(&XB_SERIAL_DefTask, 2);
#endif	
#ifdef Serial2Board_UseGui
	board.AddStreamAddressAsGui(&XB_SERIAL_DefTask, 2);
#endif	

#endif

#ifdef SerialBluetooth
	SerialBT.begin(board.DeviceName);
	XB_SERIALBT_UseGET = 0;
	XB_SERIALBT_RXBuf = (uint8_t*)board._malloc(SERIALBT_SizeRXBuffer);

#ifdef SerialBTBoard_UseKeyboard 
	board.BeginUseGetStream(&XB_SERIAL_DefTask, 10);
	board.AddStreamAddressAsKeyboard(&XB_SERIAL_DefTask, 10);
#endif
#ifdef SerialBTBoard_UseLog
	board.AddStreamAddressAsLog(&XB_SERIAL_DefTask, 10);
#endif	
#ifdef SerialBTBoard_UseGui
	board.AddStreamAddressAsGui(&XB_SERIAL_DefTask, 10);
#endif	

#endif
	
}

bool XB_Serial0_DoRX()
{
	int r = -1;
	int sa = Serial.available();
	if (sa > 0)
	{
		while (Serial.available() > 0)
		{
			r = Serial.read();
			if (r < 0) break;
			BUFFER_Write_UINT8(&XB_SERIAL0_RXBuf, (uint8_t)r);
		}
		return true;
	}
	return false;
}

#define FRAMETX_MAXSIZE 4096
void XB_Serial0_DoTX()
{
	
	int32_t sdtx = BUFFER_GetSizeData(&XB_SERIAL0_TXBuf);
	while (sdtx > 0)
	{
		if (sdtx < FRAMETX_MAXSIZE)
		{
			uint8_t* PTR = BUFFER_GetReadPtr(&XB_SERIAL0_TXBuf);
			size_t wr = Serial.write((const char*)PTR, sdtx);
			BUFFER_Readed(&XB_SERIAL0_TXBuf, wr);
			sdtx -= wr;
			Serial.flush();
		}
		else
		{
			uint8_t* PTR = BUFFER_GetReadPtr(&XB_SERIAL0_TXBuf);
			size_t wr = Serial.write((const char*)PTR, FRAMETX_MAXSIZE);
			BUFFER_Readed(&XB_SERIAL0_TXBuf, FRAMETX_MAXSIZE);
			sdtx -= FRAMETX_MAXSIZE;
		}
	}

}


uint32_t XB_SERIAL_DoLoop()
{


#ifdef Serial0Board_BAUD
	if (XB_SERIAL0_UseGET == 0)
	{
		if (XB_SERIAL0_RXBuf == NULL) XB_SERIAL0_RXBuf = (uint8_t *)board._malloc(SERIAL0_SizeRXBuffer);
		int32_t s = board.GetStream(XB_SERIAL0_RXBuf, SERIAL0_SizeRXBuffer, &XB_SERIAL_DefTask,0);
		(void)s;
	}
	else
	{
		if (XB_SERIAL0_RXBuf != NULL) board.freeandnull((void **)&XB_SERIAL0_RXBuf);
	}	
#endif
#ifdef Serial0BoardBuf_BAUD
	BUFFER_Handle(&XB_SERIAL0_RXBuf, 1000);
	BUFFER_Handle(&XB_SERIAL0_TXBuf, 1000);

	int sa = Serial.available();
	int r=-1;
	if (!XB_Serial0_DoRX())
	{
		if (XB_SERIAL0_UseGET == 0)
		{
			uint32_t sd = BUFFER_GetSizeData(&XB_SERIAL0_RXBuf);
			if (sd > 0)
			{
				void* tmpbuf = board._malloc_psram(sd);
				if (tmpbuf != NULL)
				{
					int32_t s = board.GetStream(tmpbuf, sd, &XB_SERIAL_DefTask, 0);
					(void)s;
				}
				board.free(tmpbuf);
			}
		}

		XB_Serial0_DoTX();
	}
#endif

#ifdef Serial1Board_BAUD
	if (XB_SERIAL1_UseGET == 0)
	{
		if (XB_SERIAL1_RXBuf == NULL) XB_SERIAL1_RXBuf = (uint8_t *)board._malloc(SERIAL1_SizeRXBuffer);
		int32_t s = board.GetStream(XB_SERIAL1_RXBuf, SERIAL1_SizeRXBuffer, &XB_SERIAL_DefTask,1);
		(void)s;
	}
	else
	{
		if (XB_SERIAL1_RXBuf != NULL) board.freeandnull((void **)&XB_SERIAL1_RXBuf);
	}
#endif
#ifdef Serial2Board_BAUD
	if (XB_SERIAL2_UseGET == 0)
	{
		if (XB_SERIAL2_RXBuf == NULL) XB_SERIAL2_RXBuf = (uint8_t *)board._malloc(SERIAL2_SizeRXBuffer);
		int32_t s = board.GetStream(XB_SERIAL2_RXBuf, SERIAL2_SizeRXBuffer, &XB_SERIAL_DefTask,2);
		(void)s;
	}
	else
	{
		if (XB_SERIAL2_RXBuf != NULL) board.freeandnull((void **)&XB_SERIAL2_RXBuf);
	}
#endif
#ifdef SerialBluetooth
	if (XB_SERIALBT_UseGET == 0)
	{
		if (XB_SERIALBT_RXBuf == NULL) XB_SERIALBT_RXBuf = (uint8_t*)board._malloc(SERIALBT_SizeRXBuffer);
		int32_t s = board.GetStream(XB_SERIALBT_RXBuf, SERIALBT_SizeRXBuffer, &XB_SERIAL_DefTask, 10);
		(void)s;
	}
	else
	{
		if (XB_SERIALBT_RXBuf != NULL) board.freeandnull((void**)& XB_SERIALBT_RXBuf);
	}
#endif
	return 0;
}

bool XB_SERIAL_DoMessage(TMessageBoard *Am)
{
	bool res = false;
	switch (Am->IDMessage)
	{
	case IM_GET_TASKNAME_STRING:
	{
		GET_TASKNAME("SERIAL");
		return true;
	}
	case IM_GET_TASKSTATUS_STRING:
	{
#ifdef Serial0BoardBuf_BAUD
		GET_TASKSTATUS_ADDSTR("S0(" + String(Serial0BoardBuf_BAUD) + ") ");
		GET_TASKSTATUS_ADDSTR("MLTX(" + String(XB_SERIAL0_TXBuf.MaxLength) + ") ");
#endif
#ifdef Serial0Board_BAUD
		* (Am->Data.PointerString) += "S0(" + String(Serial0Board_BAUD) + ")";
#endif
#ifdef Serial1Board_BAUD
		* (Am->Data.PointerString) += ",S1(" + String(Serial1Board_BAUD) + ")";
#endif
#ifdef Serial2Board_BAUD
		* (Am->Data.PointerString) += ",S2(" + String(Serial2Board_BAUD) + ")";
#endif
#ifdef SerialBluetooth
		* (Am->Data.PointerString) += ",SBT10(" + String(board.DeviceName) + ")";
#endif
		res = true;
		break;
	}
	case IM_STREAM:
	{
		switch (Am->Data.StreamData.StreamAction)
		{
		case saTaskStream:
		{
			res = true;
			break;
		}
		case saDisableTX:
		{
#ifdef XB_GUI
			GUI_ClearScreen();
#endif
			XB_SERIAL0_DisableTX = true;
			res = true;
			break;
		}
		case saEnableTX:
		{
			XB_SERIAL0_DisableTX = false;
			res = true;
			break;
		}
		case saStatusDisableTX:
		{
			res = XB_SERIAL0_DisableTX;
			break;
		}
		case saGet:
		{
#ifdef Serial0BoardBuf_BAUD
			if (Am->Data.StreamData.FromAddress == 0)
			{
				uint32_t sd = BUFFER_GetSizeData(&XB_SERIAL0_RXBuf);
				uint32_t count = 0;
				if (sd > 0)
				{
					uint8_t* PTR = BUFFER_GetReadPtr(&XB_SERIAL0_RXBuf);
					for (uint32_t i = 0; i < sd; i++)
					{
						((uint8_t*)Am->Data.StreamData.Data)[i] = PTR[i];
						count++;
						if (count >= Am->Data.StreamData.Length) break;
					}
					Am->Data.StreamData.LengthResult = count;
					BUFFER_Readed(&XB_SERIAL0_RXBuf, count);
				}
				else
				{
					Am->Data.StreamData.LengthResult = 0;
				}
				res = true;
				break;
			}
#endif
#ifdef Serial0Board_BAUD
			if (Am->Data.StreamData.FromAddress == 0)
			{
				int av = Serial.available();
				if (av > 0)
				{
					int ch = 0;
					uint32_t count = 0;
					while (av > 0)
					{
						ch = Serial.read();
						if (ch >= 0)
						{
							((uint8_t*)Am->Data.StreamData.Data)[count] = ch;
							count++;
						}
						else break;
						if (count >= Am->Data.StreamData.Length) break;
						av = Serial.available();
					}
					Am->Data.StreamData.LengthResult = count;
				}
				else
				{
					Am->Data.StreamData.LengthResult = 0;
				}
				res = true;
				break;
			}
#endif
#ifdef Serial1Board_BAUD
			if (Am->Data.StreamData.FromAddress == 1)
			{
				int av = Serial1.available();
				if (av > 0)
				{
					uint8_t ch = 0;
					uint8_t count = 0;
					while (av > 0)
					{
						ch = (uint8_t)Serial1.read();
						((uint8_t*)Am->Data.StreamData.Data)[count] = ch;
						count++;
						if (count >= Am->Data.StreamData.Length) break;
						av = Serial1.available();
					}
					Am->Data.StreamData.LengthResult = count;
				}
				else
				{
					Am->Data.StreamData.LengthResult = 0;
				}
				res = true;
				break;
			}
#endif
#ifdef Serial2Board_BAUD
			if (Am->Data.StreamData.FromAddress == 2)
			{
				int av = Serial2.available();
				if (av > 0)
				{
					uint8_t ch = 0;
					uint8_t count = 0;
					while (av > 0)
					{
						ch = (uint8_t)Serial2.read();
						((uint8_t*)Am->Data.StreamData.Data)[count] = ch;
						count++;
						if (count >= Am->Data.StreamData.Length) break;
						av = Serial2.available();
					}
					Am->Data.StreamData.LengthResult = count;
				}
				else
				{
					Am->Data.StreamData.LengthResult = 0;
				}
				res = true;
				break;
			}
#endif
#ifdef SerialBluetooth
			if (Am->Data.StreamData.FromAddress == 10)
			{
				int av = SerialBT.available();
				if (av > 0)
				{
					int ch = 0;
					uint32_t count = 0;
					while (av > 0)
					{
						ch = SerialBT.read();
						if (ch >= 0)
						{
							((uint8_t*)Am->Data.StreamData.Data)[count] = ch;
							count++;
						}
						else break;
						if (count >= Am->Data.StreamData.Length) break;
						av = SerialBT.available();
					}
					Am->Data.StreamData.LengthResult = count;
				}
				else
				{
					Am->Data.StreamData.LengthResult = 0;
				}
				res = true;
				break;
			}
#endif

			res = true;
			break;
		}
		case saPut:
		{
#ifdef Serial0BoardBuf_BAUD
			if (Am->Data.StreamData.ToAddress == 0)
			{
				if (!XB_SERIAL0_DisableTX)
				{
					Am->Data.StreamData.LengthResult = 0;
					for (uint32_t i = 0; i < Am->Data.StreamData.Length; i++)
					{
						if (!BUFFER_Write_UINT8(&XB_SERIAL0_TXBuf, ((uint8_t*)Am->Data.StreamData.Data)[i]))
						{
							XB_Serial0_DoTX();
						}
						Am->Data.StreamData.LengthResult++;
					}
				}
				else
				{
					Am->Data.StreamData.LengthResult = Am->Data.StreamData.LengthResult;
				}
				res = true;
				break;
			}
#endif

#ifdef Serial0Board_BAUD
			if (Am->Data.StreamData.ToAddress == 0)
			{
				uint32_t last_Length = Am->Data.StreamData.Length;
				uint8_t* last_Data = (uint8_t*)Am->Data.StreamData.Data;
				uint32_t tick = SysTickCount;
				Am->Data.StreamData.LengthResult = Serial.write((uint8_t*)Am->Data.StreamData.Data, Am->Data.StreamData.Length);

				while (Am->Data.StreamData.LengthResult != Am->Data.StreamData.Length)
				{
					if (SysTickCount - tick > 1000)
					{
						break;
					}
					Serial.flush(true);
					uint32_t P = (uint32_t)Am->Data.StreamData.Data;
					P += Am->Data.StreamData.LengthResult;
					Am->Data.StreamData.Data = (void*)P;
					Am->Data.StreamData.Length -= Am->Data.StreamData.LengthResult;

					Am->Data.StreamData.LengthResult = Serial.write((uint8_t*)Am->Data.StreamData.Data, Am->Data.StreamData.Length);
				}
				Am->Data.StreamData.Length = last_Length;
				Am->Data.StreamData.LengthResult = last_Length;
				Am->Data.StreamData.Data = (void*)last_Data;
				Serial.flush(true);
				res = true;
				break;
			}
#endif
#ifdef Serial1Board_BAUD
			if (Am->Data.StreamData.ToAddress == 1)
			{
				Am->Data.StreamData.LengthResult = Serial1.write((uint8_t*)Am->Data.StreamData.Data, Am->Data.StreamData.Length);
				res = true;
				break;
			}
#endif
#ifdef Serial2Board_BAUD
			if (Am->Data.StreamData.ToAddress == 2)
			{
				Am->Data.StreamData.LengthResult = Serial2.write((uint8_t*)Am->Data.StreamData.Data, Am->Data.StreamData.Length);
				res = true;
				break;
			}
#endif
#ifdef SerialBluetooth
			if (Am->Data.StreamData.ToAddress == 10)
			{
				Am->Data.StreamData.LengthResult = SerialBT.write((uint8_t*)Am->Data.StreamData.Data, Am->Data.StreamData.Length);
				res = true;
				break;
			}
#endif
			res = true;
			break;
		}
		case saBeginUseGet:
		{
#ifdef Serial0BoardBuf_BAUD
			if (Am->Data.StreamData.ToAddress == 0)
			{
				XB_SERIAL0_UseGET++;
			}
#endif
#ifdef Serial0Board_BAUD
			if (Am->Data.StreamData.ToAddress == 0)
			{
				XB_SERIAL0_UseGET++;
			}
#endif
#ifdef Serial1Board_BAUD
			if (Am->Data.StreamData.ToAddress == 1)
			{
				XB_SERIAL1_UseGET++;
			}
#endif
#ifdef Serial2Board_BAUD
			if (Am->Data.StreamData.ToAddress == 2)
			{
				XB_SERIAL2_UseGET++;
			}
#endif
#ifdef SerialBluetooth
			if (Am->Data.StreamData.ToAddress == 10)
			{
				XB_SERIALBT_UseGET++;
			}
#endif
			res = true;
			break;
		}
		case saEndUseGet:
		{
#ifdef Serial0BoardBuf_BAUD
			if (Am->Data.StreamData.ToAddress == 0)
			{
				if (XB_SERIAL0_UseGET > 0) XB_SERIAL0_UseGET--;
			}
#endif
#ifdef Serial0Board_BAUD
			if (Am->Data.StreamData.ToAddress == 0)
			{
				if (XB_SERIAL0_UseGET > 0) XB_SERIAL0_UseGET--;
			}
#endif
#ifdef Serial1Board_BAUD
			if (Am->Data.StreamData.ToAddress == 1)
			{
				if (XB_SERIAL1_UseGET > 0) XB_SERIAL1_UseGET--;
			}
#endif
#ifdef Serial2Board_BAUD
			if (Am->Data.StreamData.ToAddress == 2)
			{
				if (XB_SERIAL2_UseGET > 0) XB_SERIAL2_UseGET--;
			}
#endif
#ifdef SerialBluetooth
			if (Am->Data.StreamData.ToAddress == 10)
			{
				if (XB_SERIALBT_UseGET > 0) XB_SERIALBT_UseGET--;
			}
#endif
			res = true;
			break;
		}
		case saGetLocalAddress:
		{
			res = true;
			break;
		}
		break;
		}
	default: break;
	}
	}
	return res;

}