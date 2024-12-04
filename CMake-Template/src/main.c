#include "platform/platform.h"

void init(void)
{
	hal_init();
}

void loop(void)
{
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	init();
	for (;;) {
		loop();
	}

	return 0;
}
