#pragma once
class portlight
{
public:
	portlight();
	void getPort(CComboBox& comboBox);
	CString SerialPortHandle(CString portName, unsigned char AllSend[], int len, BOOL CHECK);
	unsigned char* LightTotalSetting(int command, int intChannel1, int intChannel2, int intChannel3, int intChannel4, int intChannel5, int intChannel6, int intChannel7, int intChannel8);
	unsigned char* LightSetting(int channel, int value100, int value10, int value1);
	BOOL CNT;
};

