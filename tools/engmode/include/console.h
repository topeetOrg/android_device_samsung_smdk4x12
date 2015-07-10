
extern FILE* input;
extern FILE* output;

#define print(arg...) \
	fprintf(output,##arg); \
	fflush(output);
