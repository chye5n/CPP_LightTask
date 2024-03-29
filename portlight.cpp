#include "stdafx.h"
#include "portlight.h"
#include "VSLightTaskDlg.h"

portlight::portlight()
{
	
}

void portlight::getPort(CComboBox& comboBox)	//Port 받아오기
{
	HKEY hKey;
	RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"), &hKey);

	TCHAR szData[20];
	TCHAR szName[100];
	DWORD index = 0;
	DWORD dwSize = 100;
	DWORD dwSize2 = 20;
	DWORD dwType = REG_SZ;
	comboBox.ResetContent();
	memset(szData, 0x00, sizeof(szData));
	memset(szName, 0x00, sizeof(szName));

	while (ERROR_SUCCESS == RegEnumValue(hKey, index, szName, &dwSize, NULL, NULL, NULL, NULL)) {
		index++;
		RegQueryValueEx(hKey, szName, NULL, &dwType, (LPBYTE)szData, &dwSize2);
		comboBox.AddString(szData);

		memset(szData, 0x00, sizeof(szData));
		memset(szName, 0x00, sizeof(szName));
		dwSize = 100;
		dwSize2 = 20;
	}
	RegCloseKey(hKey);
}

CString portlight::SerialPortHandle(CString portName, unsigned char AllSend[], int len, BOOL CHECK)
{
	// 시리얼 포트 핸들
	unsigned char Send[14];
	CString str;
	for (int i = 0; i < len; i++)
	{
		Send[i] = AllSend[i];
	}
	
	HANDLE hSerialPort = CreateFile(portName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if ((hSerialPort != INVALID_HANDLE_VALUE) && CHECK)
	{
		DWORD bytesWritten;	// 데이터 전송
		if (WriteFile(hSerialPort, Send, len, &bytesWritten, NULL)) { str = "데이터 전송 완료"; }
		else { str = "데이터 전송 실패"; }
	}
	else { str = "시리얼 포트 열기 실패"; }
	CloseHandle(hSerialPort);
	return str;
}

unsigned char* portlight::LightTotalSetting(int command, int intChannel1, int intChannel2, int intChannel3, int intChannel4, int intChannel5, int intChannel6, int intChannel7, int intChannel8)
{
	unsigned char AllSend[14];

	AllSend[0] = 0xEF;										//Header1
	AllSend[1] = 0xEF;										//Header2
	AllSend[2] = static_cast<unsigned char>(command);		//Command

	AllSend[3] = static_cast<unsigned char>(intChannel1);	//ch1
	AllSend[4] = static_cast<unsigned char>(intChannel2);	//ch2
	AllSend[5] = static_cast<unsigned char>(intChannel3);	//ch3
	AllSend[6] = static_cast<unsigned char>(intChannel4);	//ch4
	AllSend[7] = static_cast<unsigned char>(intChannel5);	//ch5
	AllSend[8] = static_cast<unsigned char>(intChannel6);	//ch6
	AllSend[9] = static_cast<unsigned char>(intChannel7);	//ch7
	AllSend[10] = static_cast<unsigned char>(intChannel8);	//ch8

	int CheckSum = AllSend[2] ^ AllSend[3] ^ AllSend[4] ^ AllSend[5] ^ AllSend[6] ^ AllSend[7] ^ AllSend[8] ^ AllSend[9] ^ (AllSend[10] + 0x01);

	AllSend[11] = static_cast<unsigned char>(CheckSum);		//Check sum
	AllSend[12] = 0xEE;										//tail1
	AllSend[13] = 0xEE;										//tail2

	return AllSend;
}

unsigned char* portlight::LightSetting(int channel, int value100, int value10, int value1)
{
	unsigned char AllSend[7];

	AllSend[0] = 0x4C;									//command
	AllSend[1] = static_cast<unsigned char>(channel);	//channel
	AllSend[2] = static_cast<unsigned char>(value100);	//value 100
	AllSend[3] = static_cast<unsigned char>(value10);	//value 10
	AllSend[4] = static_cast<unsigned char>(value1);	//value 1
	AllSend[5] = 0x0D;									//tail1
	AllSend[6] = 0x0A;									//tail2

	return AllSend;
}