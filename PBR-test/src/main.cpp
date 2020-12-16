#include "pbr.h"
#include <time.h>

int		main(void)
{
	Engine	engine;
	Sandbox	sandbox;
	
	srand(time(NULL));
	engine.init_engine(640, 480);
	sandbox.place_ent(&engine);
	engine.run_engine();
	return 0;
}
