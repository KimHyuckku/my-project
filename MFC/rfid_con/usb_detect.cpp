//#define _NO_CRT_SECURE_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "is_d2xx.h"


int main(void)
{
	IS_HANDLE ftHandle=0;
	char readSerialNumber[100]="COM07";
	char changeSerialNumber[100]="RFID01";
	short usbnumber;
	unsigned char wirteData[1024];
	unsigned short writeLength = 0;
	unsigned char readData[1024];
	unsigned short readLength = 0;

	//���� ��Ʈ��ȣ ã��
	if (is_GetDeviceNumber(&usbnumber) == IS_OK)
	{
		printf("FTDI USB To Serial ����� ���� : %d\n", usbnumber);
		if (is_GetSerialNumber(0, readSerialNumber) == IS_OK)
		{
			if (memcmp(changeSerialNumber, readSerialNumber, sizeof(changeSerialNumber) != 0))
			{
				if (is_SetSerialNumber(0, changeSerialNumber) == IS_OK)
				{
					printf(" USB To Serial Number �� ���� �Ͽ����ϴ�.\n");
					printf(" FTDI SerialNumber :  %s \n", changeSerialNumber);
				}
			}
			else
				printf(" FTDI SerialNumber :  %s \n", changeSerialNumber);
		}
	}

	//���� ��Ʈ��ȣ�� ����
	unsigned long portNumber;
	if (is_GetCOMPort_NoConnect(0, &portNumber) == IS_OK)
	{
		printf("COM Port : %d\n", portNumber);
	}
	if (is_OpenSerialNumber(&ftHandle, readSerialNumber, 115200) != IS_OK)
	{
		printf("USB To Serial�� ��� ���� ����\n");
		return -1;
	}
	else {
		printf("Serial��Ʈ %d�� ��� ���Ἲ��!! \n", portNumber);
	}
	Sleep(100);

	
	//ISO15693���� �б�( �̱۸�� �б� )
	if (is_WriteReadCommand(ftHandle, CM1_ISO15693, CM2_ISO15693_ACTIVE + BUZZER_ON,
		            writeLength, wirteData, &readLength, readData) == IS_OK)
	{
		int i;
		printf("ISO 15693 UID : ");
		for (i = 0; i < readLength; i++)
		{
			printf("%02x ", readData[i]);
		}
		printf("\n");
	}
	
	//ISO14443A���� �б�
	if (is_WriteReadCommand(ftHandle, CM1_ISO14443AB, CM2_ISO14443A_ACTIVE + BUZZER_ON,
			writeLength, wirteData, &readLength, readData) == IS_OK)
		{
			int i;
			printf("ISO 14443AB UID : "); 
			for (i = 0; i < readLength; i++)
			{
				printf("%02x ", readData[i]);
			}
			printf("\n");
		}

	printf("\n������������߾��!!\n");
	// �����Ŀ��� �����.
	is_RfOff(ftHandle);
	//USB ��Ʈ�� Close
	if (is_Close(ftHandle) == IS_OK)
	{
		printf("������ �ݽ��ϴ�. ");
	}

	return 0;
}
