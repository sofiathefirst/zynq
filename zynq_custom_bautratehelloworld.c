

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xuartps.h"

XUartPs Uart_0_ps,pcuart; //uart 0 指针


int main()
{
    init_platform();

	XUartPs_Config *Uart_0_ps_config,*pcconfig;
	XUartPsFormat Uart_0_format = {
			.BaudRate = 256000,
			.DataBits = XUARTPS_FORMAT_8_BITS,
			.Parity = XUARTPS_FORMAT_NO_PARITY,
			.StopBits = XUARTPS_FORMAT_1_STOP_BIT,
	};

	XUartPsFormat Uart_1_format = {
			.BaudRate = 460800,
			.DataBits = XUARTPS_FORMAT_8_BITS,
			.Parity = XUARTPS_FORMAT_NO_PARITY,
			.StopBits = XUARTPS_FORMAT_1_STOP_BIT,
	};

    Uart_0_ps_config = XUartPs_LookupConfig(XPAR_PS7_UART_0_DEVICE_ID);
    XUartPs_CfgInitialize(&Uart_0_ps,Uart_0_ps_config,XPAR_PS7_UART_0_BASEADDR);
    XUartPs_SetDataFormat(&Uart_0_ps,&Uart_0_format);

    pcconfig = XUartPs_LookupConfig(XPAR_PS7_UART_1_DEVICE_ID);
    XUartPs_CfgInitialize(&pcuart,pcconfig,XPAR_PS7_UART_1_BASEADDR);
    XUartPs_SetDataFormat(&pcuart,&Uart_1_format);

    u8 recvbuf[30],num,RecvByte;
    /*
    while(1)
    {
    	num = XUartPs_Recv(&Uart_0_ps,recvbuf,30);

    	//num = 1;
    	//recvbuf[0]=0x45;
    	//XUartPs_SendByte(XPAR_PS7_UART_0_BASEADDR,0x45);
    	//UartPs_SendByte(XPAR_PS7_UART_0_BASEADDR, 0x25);
    	//for(u8 i=0;i<num;i++)
    	// XUartPs_SendByte(XPAR_PS7_UART_0_BASEADDR, recvbuf[i]);
    	XUartPs_Send (&pcuart,recvbuf, num);//XPAR_PS7_UART_0_BASEADDR, 0x34);
    	//print("i23wef\r\n");
    }
*/

    while(1)
    {

    	while (XUartPs_IsReceiveData(XPAR_PS7_UART_0_BASEADDR))//不能用if
    		{
    	//		led_Control(LED_PL17,0);
    		    RecvByte = XUartPs_RecvByte(XPAR_PS7_UART_0_BASEADDR);
    		    XUartPs_SendByte(XPAR_PS7_UART_1_BASEADDR, RecvByte);
    	//	    print_uart_ps0(&RecvByte,1);
    		   // sbus_common_decode_event(RecvByte);
    	//	    led_Control(LED_PL17,1);
    		}
    }
    cleanup_platform();
    return 0;
}
