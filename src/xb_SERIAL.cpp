#include <xb_SERIAL.h>

bool XB_SERIAL_DoMessage(TMessageBoard *Am);
void XB_SERIAL_Setup();
uint32_t XB_SERIAL_DoLoop();

TTaskDef XB_SERIAL_DefTask = { 1, &XB_SERIAL_Setup, &XB_SERIAL_DoLoop, &XB_SERIAL_DoMessage };


#ifdef Serial0Board_BAUD
uint8_t *XB_SERIAL0_RXBuf;
uint8_t XB_SERIAL0_UseGET;
#endif
#ifdef Serial1Board_BAUD
uint8_t *XB_SERIAL1_RXBuf;
uint8_t XB_SERIAL1_UseGET;
#endif
#ifdef Serial2Board_BAUD
uint8_t *XB_SERIAL2_RXBuf;
uint8_t XB_SERIAL2_UseGET;
#endif


//extern "C" void * _sbrk(int);
//extern uint32_t _estack;

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
	board.Log("Start...");
	board.Log("OK");
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
	return 0;
}

bool XB_SERIAL_DoMessage(TMessageBoard *Am)
{
	bool res = false;
	switch (Am->IDMessage)
	{
	case IM_GET_TASKNAME_STRING:
		{
			*(Am->Data.PointerString) = "SERIAL";
			return true;
		}
	case IM_GET_TASKSTATUS_STRING:
		{
#ifdef Serial0Board_BAUD
			*(Am->Data.PointerString) += "S0(" + String(Serial0Board_BAUD) + ")";
#endif
#ifdef Serial1Board_BAUD
			*(Am->Data.PointerString) += ",S1(" + String(Serial1Board_BAUD) + ")";
#endif
#ifdef Serial2Board_BAUD
			*(Am->Data.PointerString) += ",S2(" + String(Serial2Board_BAUD) + ")";
#endif
			res = true;
			break;
		}
	case IM_STREAM:
		{
			switch (Am->Data.StreamData.StreamAction)
			{
			case saGet:
				{
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
								((uint8_t *)Am->Data.StreamData.Data)[count] = ch;
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
								((uint8_t *)Am->Data.StreamData.Data)[count] = ch;
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
					res = true;
					break;
				}
			case saPut:
				{
#ifdef Serial0Board_BAUD
					if (Am->Data.StreamData.ToAddress == 0)
					{
						Am->Data.StreamData.LengthResult = Serial.write((uint8_t *)Am->Data.StreamData.Data, Am->Data.StreamData.Length);
						res = true;
						break;
					}
#endif
#ifdef Serial1Board_BAUD
					if (Am->Data.StreamData.ToAddress == 1)
					{
						Am->Data.StreamData.LengthResult = Serial1.write((uint8_t *)Am->Data.StreamData.Data, Am->Data.StreamData.Length);
						res = true;
						break;
					}
#endif
#ifdef Serial2Board_BAUD
					if (Am->Data.StreamData.ToAddress == 2)
					{
						Am->Data.StreamData.LengthResult = Serial2.write((uint8_t *)Am->Data.StreamData.Data, Am->Data.StreamData.Length);
						res = true;
						break;
					}
#endif
					res = true;
					break;
				}
			case saBeginUseGet:
				{
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
					res = true;
					break;
				}
			case saEndUseGet:
				{
#ifdef Serial0Board_BAUD
					if (Am->Data.StreamData.ToAddress == 0)
					{
						if (XB_SERIAL0_UseGET>0) XB_SERIAL0_UseGET--;
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
					res = true;
					break;
				}
			}
			break;
		}
	default: break;
	}

	return res;
}