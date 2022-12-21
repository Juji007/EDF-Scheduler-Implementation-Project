/*
 * FreeRTOS Kernel V10.2.0
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/* 
	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used.
*/


/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the demo application tasks.
 * 
 * Main.c also creates a task called "Check".  This only executes every three 
 * seconds but has the highest priority so is guaranteed to get processor time.  
 * Its main function is to check that all the other tasks are still operational.
 * Each task (other than the "flash" tasks) maintains a unique count that is 
 * incremented each time the task successfully completes its function.  Should 
 * any error occur within such a task the count is permanently halted.  The 
 * check task inspects the count of each task to ensure it has changed since
 * the last time the check task executed.  If all the count variables have 
 * changed all the tasks are still executing error free, and the check task
 * toggles the onboard LED.  Should any task contain an error at any time 
 * the LED toggle rate will change from 3 seconds to 500ms.
 *
 */

/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "lpc21xx.h"
#include "semphr.h"



/* Peripheral includes. */
#include "serial.h"
#include "GPIO.h"


void wastTime(TickType_t time);
BaseType_t xTaskPeriodicCreate( TaskFunction_t pxTaskCode,
                            const char * const pcName, /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
                            const configSTACK_DEPTH_TYPE usStackDepth,
                            void * const pvParameters,
                            UBaseType_t uxPriority,
                            TaskHandle_t * const pxCreatedTask,
														TickType_t period);

/*-----------------------------------------------------------*/

/* Constants to setup I/O and processor. */
#define mainBUS_CLK_FULL	( ( unsigned char ) 0x01 )

/* Constants for the ComTest demo application tasks. */
#define mainCOM_TEST_BAUD_RATE	( ( unsigned long ) 115200 )
	
 
//Tasks Handles
TaskHandle_t Task_1_Handle = NULL;
TaskHandle_t Task_2_Handle = NULL;
TaskHandle_t Task_3_Handle = NULL;
TaskHandle_t Task_4_Handle = NULL;
TaskHandle_t Task_5_Handle = NULL;
TaskHandle_t Task_6_Handle = NULL;

//Queues Handles
QueueHandle_t Queue1 = NULL;
QueueHandle_t Queue2 = NULL;
QueueHandle_t Queue3 = NULL;
/*
 * Configure the processor for use with the Keil demo board.  This is very
 * minimal as most of the setup is managed by the settings in the project
 * file.
 */
static void prvSetupHardware( void );
/*-----------------------------------------------------------*/
//-------------------------------------------------
// Tasks Protopies
//-------------------------------------------------

void Task1 (void *pvParameters); 
void Task2 (void *pvParameters);
void Task3 (void *pvParameters);
void Task4 (void *pvParameters);
void Task5 (void *pvParameters);
void Task6 (void *pvParameters);
//-------------------------------------------------
// Global Variables
//-------------------------------------------------

#define Task1_PERIOD 		50
#define Task2_PERIOD 		50
#define Task3_PERIOD		100
#define Task4_PERIOD		20
#define Task5_PERIOD		10
#define Task6_PERIOD		100

 int Task1_StartTime=0 ,Task1_FinishTime =0 ,Task1_TotalTime = 0 ,Task1_ExcutionTime ;
 int Task2_StartTime=0 ,Task2_FinishTime =0 ,Task2_TotalTime = 0 ,Task2_ExcutionTime ;
 int Task3_StartTime=0 ,Task3_FinishTime =0 ,Task3_TotalTime = 0 ,Task3_ExcutionTime ;
 int Task4_StartTime=0 ,Task4_FinishTime =0 ,Task4_TotalTime = 0 ,Task4_ExcutionTime ;
 int Task5_StartTime=0 ,Task5_FinishTime =0 ,Task5_TotalTime = 0 ,Task5_ExcutionTime ;
 int Task6_StartTime=0 ,Task6_FinishTime =0 ,Task6_TotalTime = 0 ,Task6_ExcutionTime;

int SystemTime = 0;
float CPU_Load = 0 ;

void Task1 (void *pvParameters)
	{
	TickType_t xLastWakeTime;
	pinState_t prvBtnState = GPIO_read(PORT_1,PIN1);
	pinState_t curBtnState ;
	char edgeFlage ;
		// Set Task Tag for monitoring
  vTaskSetApplicationTaskTag( NULL, ( void * ) 1 );
	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = 0;

	
	for( ; ; )
{
	curBtnState = GPIO_read(PORT_1 , PIN1);
	
 if ((curBtnState != prvBtnState )&& (prvBtnState == PIN_IS_LOW)){
 
 edgeFlage = 'P';
 }else if ((curBtnState != prvBtnState )&& (prvBtnState == PIN_IS_HIGH)){
 
  edgeFlage = 'N';
 }else
 {
 edgeFlage = 'X';
 }
 prvBtnState = curBtnState;
 
 xQueueOverwrite(Queue1,&edgeFlage);
 
  vTaskDelayUntil(&xLastWakeTime,Task1_PERIOD);

}

 }

 void Task2 (void *pvParameters)
	{
	TickType_t xLastWakeTime;
	pinState_t prvBtnState = GPIO_read(PORT_1,PIN2);
	pinState_t curBtnState ;
	char edgeFlage ;	
		// Set Task Tag for monitoring
  vTaskSetApplicationTaskTag( NULL, ( void * ) 2 );
	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = 0;

	
	for( ; ; )
{
	
	curBtnState = GPIO_read(PORT_1 , PIN2);
 if ((curBtnState != prvBtnState )&& (prvBtnState == PIN_IS_LOW)){
 
 edgeFlage = 'P';
 }else if ((curBtnState != prvBtnState )&& (prvBtnState == PIN_IS_HIGH)){
 
  edgeFlage = 'N';
 }else
 {
 edgeFlage = 'X';
 }
 prvBtnState = curBtnState;
 
 xQueueOverwrite(Queue2,&edgeFlage);
 
 vTaskDelayUntil(&xLastWakeTime,Task2_PERIOD);

}

}
	
 void Task3 (void *pvParameters)
	{
	TickType_t xLastWakeTime;
	char Message[10] = "listening";
	
		// Set Task Tag for monitoring
  vTaskSetApplicationTaskTag( NULL, ( void * ) 3 );
	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = 0;

	for( ; ; )
{
 
	xQueueOverwrite(Queue3 , Message );
	
 vTaskDelayUntil(&xLastWakeTime,Task3_PERIOD);

}

}
	
void Task4 (void *pvParameters)
	{
	TickType_t xLastWakeTime;
	 char Btn1Data , Btn2Data; 
	 char ReceivedString[7];
	 char Btn1Message[11] ="BUTTON_1 : ";
	// Set Task Tag for monitoring
  vTaskSetApplicationTaskTag( NULL, ( void * ) 4 );
	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = 0;

 
	for( ; ; )
{
	xQueueReceive(Queue1,&Btn1Data,0);
  xQueueReceive(Queue2,&Btn2Data,0);
	
	if(Btn1Data != 'X'&& ((Btn1Data == 'P')||(Btn1Data == 'N'))){
	xSerialPutChar('\n');
	xSerialPutChar('B');
	xSerialPutChar('T');
	xSerialPutChar('N');
	xSerialPutChar('1');
	xSerialPutChar(' ');
	xSerialPutChar(':');
	xSerialPutChar(' ');
	xSerialPutChar(Btn1Data);
	Btn1Data = 'X';
	}
	if(Btn2Data != 'X'&& ((Btn2Data == 'P')||(Btn2Data == 'N'))){
	xSerialPutChar('\n');
	xSerialPutChar('B');
	xSerialPutChar('T');
	xSerialPutChar('N');
	xSerialPutChar('2');
	xSerialPutChar(' ');
	xSerialPutChar(':');
	xSerialPutChar(' ');
	xSerialPutChar(Btn2Data);
	Btn2Data = 'X';
	}
	if(xQueueReceive(Queue3,ReceivedString,5) == pdPASS){
	xSerialPutChar('\n');
	vSerialPutString(ReceivedString,10);
	}
	
	
  vTaskDelayUntil(&xLastWakeTime,Task4_PERIOD);

}

}
	
void Task5 (void *pvParameters)
	{
	TickType_t xLastWakeTime;
		// Set Task Tag for monitoring
  vTaskSetApplicationTaskTag( NULL, ( void * ) 5 );
	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = 0;

	for( ; ; )
{
	
	wastTime(5);
	
 vTaskDelayUntil(&xLastWakeTime,Task5_PERIOD);

}

}
void Task6 (void *pvParameters)
	{
	TickType_t xLastWakeTime;
		// Set Task Tag for monitoring
  vTaskSetApplicationTaskTag( NULL, ( void * ) 6 );
	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = 0;

	for( ; ; )
{
 
	wastTime(12);
	
 vTaskDelayUntil(&xLastWakeTime,Task6_PERIOD);

}

}

/*
 * Application entry point:
 * Starts all the other tasks, then starts the scheduler. 
 */
int main( void )
 {
	/* Setup the hardware for use with the Keil demo board. */
	prvSetupHardware();
//Queue Creation
	 Queue1 = xQueueCreate( 1,sizeof(char));
	 Queue2 = xQueueCreate( 1,sizeof(char));
	 Queue3 = xQueueCreate( 1,sizeof(char[10]));
		
	 
    /* Create Tasks here */
 xTaskPeriodicCreate(Task1,
	"Button1",
	100,
	( void * ) 1,
	1,
	&Task_1_Handle,
	Task1_PERIOD );	
	
	xTaskPeriodicCreate(Task2,
	"Button2",
	100,
	( void * ) 1,
	1,
	&Task_2_Handle,
	Task2_PERIOD );

	xTaskPeriodicCreate(Task3,
	"Sender",
	100,
	( void * ) 1,
	1,
	&Task_3_Handle,
	Task3_PERIOD );
	
	xTaskPeriodicCreate(Task4,
	"Receiver",
	100,
	( void * ) 1,
	1,
	&Task_4_Handle,
	Task4_PERIOD );
	
	xTaskPeriodicCreate(Task5,
	"Load1",
	100,
	( void * ) 1,
	1,
	&Task_5_Handle,
	Task5_PERIOD );
	
	xTaskPeriodicCreate(Task6,
	"Load2",
	100,
	( void * ) 1,
	1,
	&Task_6_Handle,
	Task6_PERIOD );
	/* Now all the tasks have been started - start the scheduler.

	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used here. */
	vTaskStartScheduler();
  
	/* Should never reach here!  If you do then there was not enough heap
	available for the idle task to be created. */
	for( ;; );
			
}
/*-----------------------------------------------------------*/


// Tick Hook Function
void vApplicationTickHook( void )
{
GPIO_write(PORT_0,PIN0,PIN_IS_HIGH);
GPIO_write(PORT_0,PIN0,PIN_IS_LOW);

}



/* Function to reset timer 1 */
void timer1Reset(void)
{
	T1TCR |= 0x2;
	T1TCR &= ~0x2;
}

/* Function to initialize and start timer 1 */
static void configTimer1(void)
{
	T1PR = 1000;
	T1TCR |= 0x1;
}

static void prvSetupHardware( void )
{
	/* Perform the hardware setup required.  This is minimal as most of the
	setup is managed by the settings in the project file. */

	/* Configure UART */
	xSerialPortInitMinimal(mainCOM_TEST_BAUD_RATE);

	/* Configure GPIO */
	GPIO_init();
	
	/* Config trace timer 1 and read T1TC to get current tick */
	configTimer1();

	/* Setup the peripheral bus to be the same as the PLL output. */
	VPBDIV = mainBUS_CLK_FULL;
}

void wastTime(TickType_t time){
	
	TickType_t wastCounter = 0;
	TickType_t WastedTicks = 12000* time;
	while(wastCounter < WastedTicks){
	
		wastCounter++;
	}
}
/*-----------------------------------------------------------*/


