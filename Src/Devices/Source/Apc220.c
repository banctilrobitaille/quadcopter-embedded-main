/* 
 _____ _______     __   ____  _    _         _____   _____ ____  _____ _______ ______ _____  
 |  __ \_   _\ \   / /  / __ \| |  | |  /\   |  __ \ / ____/ __ \|  __ \__   __|  ____|  __ \ 
 | |  | || |  \ \_/ /  | |  | | |  | | /  \  | |  | | |   | |  | | |__) | | |  | |__  | |__) |
 | |  | || |   \   /   | |  | | |  | |/ /\ \ | |  | | |   | |  | |  ___/  | |  |  __| |  _  / 
 | |__| || |_   | |    | |__| | |__| / ____ \| |__| | |___| |__| | |      | |  | |____| | \ \ 
 |_____/_____|  |_|     \___\_\\____/_/    \_\_____/ \_____\____/|_|      |_|  |______|_|  \_
 */

/******************************************************************************/
/*                               Includes                                     */
/******************************************************************************/
#include "Apc220.h"

/******************************************************************************/
/*                            Local Constants                                 */
/******************************************************************************/

/******************************************************************************/
/*                           Private Variables                                */
/******************************************************************************/
static DeviceState state 	= UNINITIALIZED;
static UART_HandleTypeDef	UART_handle;
static uint8_t				rxBuffer[RECEIVE_FRAME_LENGTH];
/******************************************************************************/
/*                      Private Function Prototypes                           */
/******************************************************************************/
static void Initialize();
static void Initialize_Pins();
static void Initialize_UART(UART_HandleTypeDef uartHandle);
/******************************************************************************/

static void Initialize_Pins(){

}

static void Initialize_UART(UART_HandleTypeDef uartHandle){

}

static void Initialize() {
	Initialize_Pins();
	Initialize_UART(UART_handle);
}

#if APC220 == ENABLED
void Start_Telemetry_Task(void) {
	if(state != INITIALIZED){
		Initialize();
	}

	while(TRUE){
		if(HAL_OK == HAL_UART_Receive_IT(&UART_handle, rxBuffer, RECEIVE_FRAME_LENGTH)){

		}
	}
}

void Send_Frame(SendFrame frame) {

}
#endif
