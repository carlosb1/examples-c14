#include "S3_wrap.h"
int main () {
	struct PDClient client;
	char * name_bucket = "prodcast-stress";
	init_pd_client(&client, name_bucket);
	
	hello_world();
}
