/*
/* pure - means that the function has no side effects and the value returned depends on the arguments and the state of global variables. Therefore it is safe for the optimizer to elide some calls to it, if the arguments are the same, and the state of the globals didn't change in between calls.
*/
/*
[[gnu::const]]int square (int val) {
	return val * val;
}
*/


/* const means that the return value is solely a function of the arguments, and if any of the arguments are pointers, then the pointers must not be dereferenced
*/
[[gnu::pure]]int square (int val) {
	return val * val;
}

int main (const int argc, const char*[]) {
	return square(argc) + square(argc);
}
