#include "S3_wrap.h"
#include "S3.h"

#ifdef __cplusplus
	extern "C" {
#endif 

	void init_pd_client(struct PDClient * client, char* name_bucket) {
		S3 s3;
		client->s3 = (void *)(&s3);
		client->name_bucket = name_bucket;
	}

	void get(struct PDClient *client, char *output) {
		std::string str_output = ((S3*)(client->s3))->getObjects(client->name_bucket);
		output = const_cast<char*>(str_output.c_str());
	
	}
	void put(struct PDClient *client, const char* directory_to_upload_char) {
		std::string directory_to_upload(directory_to_upload_char);
		std::vector<std::string> storage;
       		Helper::getFilesInDirectory(storage, directory_to_upload);
		for (auto string_to_upload: storage) {
			((S3*)(client->s3))->putObject(string_to_upload, (*client).name_bucket);
		}

	}

	void hello_world() {
		std::cout << "hello world\n";
	}

	void hello(const char *example_text) {
		std::string tex(example_text);	
		std::cout << "Hello "<<tex << "\n";
	}


#ifdef __cplusplus
	}
#endif

