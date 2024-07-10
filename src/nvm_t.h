#ifndef D693DD34_021C_482B_A532_AB5B31D18C64
#define D693DD34_021C_482B_A532_AB5B31D18C64

typedef enum nvm_state_result_t {
	NVM_UNINITIALIZED,
	NVM_OK,
	NVM_NO_SPACE_LEFT,
	NVM_INIT_ERROR,
	NVM_PGM_ERROR
}nvm_state_result_t;

typedef enum nvm_event_result_t {
	NVM_EVENT_OK,
	NVM_EVENT_OVERRUN_NO_TS,
	NVM_EVENT_OVERRUN,
	NVM_EVENT_SINGLE_TS,
	NVM_EVENT_EMPTY,
	NVM_EVENT_AREA_ERROR
}nvm_event_result_t;

#endif /* D693DD34_021C_482B_A532_AB5B31D18C64 */
