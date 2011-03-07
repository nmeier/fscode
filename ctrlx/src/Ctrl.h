
// module's state
struct CTRL
{
	int foo;
};

// forwards
void ctrl_init(CTRL* pIvent);
void ctrl_timer(CTRL* pIvent);
void ctrl_set_gear(CTRL* pIvent, int gear);
