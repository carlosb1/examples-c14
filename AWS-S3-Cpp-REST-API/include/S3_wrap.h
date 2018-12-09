#ifndef __S3_WRAP__
#define __S3_WRAP__

#ifdef __cplusplus
	extern "C" {
#endif 
	struct PDClient{
		void* s3;
		char* name_bucket;

	};
	
	void init_pd_client(struct PDClient * client, char* name_bucket);

	void get(struct PDClient *client, char *output);
	void put(struct PDClient *client, const char* directory_to_upload_char);
	
	void hello_world();
	void hello(const char *example_text);

#ifdef __cplusplus
	}
#endif


#endif

