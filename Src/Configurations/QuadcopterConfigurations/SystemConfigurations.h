/* 
 _____ _______     __   ____  _    _         _____   _____ ____  _____ _______ ______ _____  
 |  __ \_   _\ \   / /  / __ \| |  | |  /\   |  __ \ / ____/ __ \|  __ \__   __|  ____|  __ \ 
 | |  | || |  \ \_/ /  | |  | | |  | | /  \  | |  | | |   | |  | | |__) | | |  | |__  | |__) |
 | |  | || |   \   /   | |  | | |  | |/ /\ \ | |  | | |   | |  | |  ___/  | |  |  __| |  _  / 
 | |__| || |_   | |    | |__| | |__| / ____ \| |__| | |___| |__| | |      | |  | |____| | \ \ 
 |_____/_____|  |_|     \___\_\\____/_/    \_\_____/ \_____\____/|_|      |_|  |______|_|  \_
 */
#ifndef SYSTEMCONFIGURATIONS_H_
#define SYSTEMCONFIGURATIONS_H_

/******************************************************************************/
/*                               Includes                                     */
/******************************************************************************/

/******************************************************************************/
/*                           Public Constants                                 */
/******************************************************************************/
#define ENABLED		1
#define	DISABLED	0

#define TRUE		1
#define FALSE		0


/******************************************************************************/
/*                           	 TRANSMITER                                   */
/******************************************************************************/
#define APC220						ENABLED
#define RFD900						DISABLED


/******************************************************************************/
/*                           DEVICES TASKS TO START                           */
/******************************************************************************/
//THIS FLAG OVERRIDES INDIVIDUAL TASK FLAG BELOW, IF SET TO TRUE EVERY TASKS ARE
//STARTED DESPITE THEIR FLAG STATE
#define START_ALL_TASKS				TRUE

/******************************************************************************/
/*                           DEVICES TASKS TO START                           */
/******************************************************************************/
#define START_TELEMETRY				TRUE
#define	START_ACCELEROMETER			TRUE
#define	START_GYROSCOPE				TRUE
#define START_COMPASS				TRUE
#define	START_GPS					TRUE
#define START_MOTOR					TRUE

/******************************************************************************/
/*                         CONTROLLERS TASKS TO START                         */
/******************************************************************************/
#define START_TELEMETRY_CONTROLLER			TRUE
#define START_INERTIALSTATION_CONTROLLER	TRUE

#endif /* SYSTEMCONFIGURATIONS_H_ */
