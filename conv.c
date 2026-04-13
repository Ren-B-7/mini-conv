#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define C_TO_F_MULT 1.8
#define C_TO_F_OFF 32.0
#define KG_TO_LB 2.20462262185
#define CM_TO_IN 0.393700787402
#define M_TO_FT 3.28083989501
#define KM_TO_MI 0.621371
#define M_TO_YD 1.09361

/* Function declarations */
int usage_conv(void);
int usage_c2f(void);
int usage_f2c(void);
int usage_k2l(void);
int usage_l2k(void);
int usage_m2i(void);
int usage_i2m(void);
int usage_m2f(void);
int usage_f2m(void);
int usage_k2m(void);
int usage_m2k(void);
int usage_c2i(void);
int usage_i2c(void);
int usage_m2y(void);
int usage_y2m(void);

int c2f(char* input_c);
int f2c(char* input_f);
int k2l(char* input_kg);
int l2k(char* input_lb);
int m2i(char* input_m);
int i2m(char* input_in);
int m2f(char* input_m);
int f2m(char* input_f);
int k2m(char* input_km);
int m2k(char* input_mi);
int c2i(char* input_cm);
int i2c(char* input_in);
int m2y(char* input_m);
int y2m(char* input_y);

/* Static helper declarations */
static int handle_temperature(int argc, char** argv);
static int handle_weight(int argc, char** argv);
static int handle_distance(int argc, char** argv);
static int run_temp_weight_symlinks(char* progname, int argc, char** argv);
static int check_and_run(char* progname, int argc, char** argv,
 const char* name, int (*func)(char*), int (*usage)(void));
static int run_distance_symlinks(char* progname, int argc, char** argv);
static int run_conversion(char* progname, int argc, char** argv);
static int handle_symlink(char* progname, int argc, char** argv);

/* Usage functions */
int usage_conv(void)
{
	fprintf(stderr,
	 "Usage: conv -t -c  <value>   (Temperature: Celsius to Fahrenheit)\n"
	 "       conv -t -f  <value>   (Temperature: Fahrenheit to Celsius)\n"
	 "       conv -w -k  <value>   (Weight: Kilograms to Pounds)\n"
	 "       conv -w -l  <value>   (Weight: Pounds to Kilograms)\n"
	 "       conv -d -y  <value>   (Distance: Yards to Metres)\n"
	 "       conv -d -me <value>   (Distance: Metres to Yards)\n"
	 "       conv -d -i  <value>   (Distance: Inches to Centimetres)\n");
	fprintf(stderr,
	 "       conv -d -I  <value>   (Distance: Inches to Metres)\n"
	 "       conv -d -mi <value>   (Distance: Miles to Kilometres)\n"
	 "       conv -d -k  <value>   (Distance: Kilometres to Miles)\n"
	 "       conv -d -m  <value>   (Distance: Metres to Inches)\n"
	 "       conv -d -M  <value>   (Distance: Metres to Feet)\n"
	 "       conv -d -F  <value>   (Distance: Feet to Metres)\n"
	 "       conv -d -K  <value>   (Distance: Kilometres to Miles)\n");
	fprintf(stderr,
	 "       conv -d -mi <value>   (Distance: Miles to Kilometres)\n"
	 "       conv -d -c  <value>   (Distance: Centimetres to Inches)\n"
	 "       conv -d -i  <value>   (Distance: Inches to Centimetres)\n");
	return 1;
}

int usage_c2f(void)
{
	fprintf(stderr,
	 "Usage: c2f <celsius_value>\nConvert Celsius to Fahrenheit\n");
	return 1;
}

int usage_f2c(void)
{
	fprintf(stderr,
	 "Usage: f2c <fahrenheit_value>\nConvert Fahrenheit to Celsius\n");
	return 1;
}

int usage_k2l(void)
{
	fprintf(stderr,
	 "Usage: k2l <kilogram_value>\nConvert Kilograms to Pounds\n");
	return 1;
}

int usage_l2k(void)
{
	fprintf(stderr, "Usage: l2k <pound_value>\nConvert Pounds to Kilograms\n");
	return 1;
}

int usage_m2i(void)
{
	fprintf(stderr, "Usage: m2i <metre_value>\nConvert Metres to Inches\n");
	return 1;
}

int usage_i2m(void)
{
	fprintf(stderr, "Usage: i2m <inch_value>\nConvert Inches to Metres\n");
	return 1;
}

int usage_m2f(void)
{
	fprintf(stderr, "Usage: m2f <metre_value>\nConvert Metres to Feet\n");
	return 1;
}

int usage_f2m(void)
{
	fprintf(stderr, "Usage: f2m <foot_value>\nConvert Feet to Metres\n");
	return 1;
}

int usage_k2m(void)
{
	fprintf(stderr,
	 "Usage: k2m <kilometre_value>\nConvert Kilometres to Miles\n");
	return 1;
}

int usage_m2k(void)
{
	fprintf(stderr, "Usage: m2k <mile_value>\nConvert Miles to Kilometres\n");
	return 1;
}

int usage_c2i(void)
{
	fprintf(stderr,
	 "Usage: c2i <centimetre_value>\nConvert Centimetres to Inches\n");
	return 1;
}

int usage_i2c(void)
{
	fprintf(stderr, "Usage: i2c <inch_value>\nConvert Inches to Centimetres\n");
	return 1;
}

int usage_m2y(void)
{
	fprintf(stderr, "Usage: m2y <metre_value>\nConvert Metres to Yards\n");
	return 1;
}

int usage_y2m(void)
{
	fprintf(stderr, "Usage: y2m <yard_value>\nConvert Yards to Metres\n");
	return 1;
}

/* Conversion functions */
int c2f(char* input_c)
{
	char* endptr;
	double input;
	double output;
	errno = 0;

	input = strtod(input_c, &endptr);

	if (input_c == endptr || *endptr != '\0') {
		fprintf(stderr, "Error: '%s' is not a valid number.\n", input_c);
		return 1;
	}

	output = (input * C_TO_F_MULT) + C_TO_F_OFF;
	printf("%.3f°C = %.3f°F\n", input, output);
	return 0;
}

int f2c(char* input_f)
{
	char* endptr;
	double input;
	double output;
	errno = 0;

	input = strtod(input_f, &endptr);

	if (input_f == endptr || *endptr != '\0') {
		fprintf(stderr, "Error: '%s' is not a valid number.\n", input_f);
		return 1;
	}

	output = (input - C_TO_F_OFF) / C_TO_F_MULT;
	printf("%.3f°F = %.3f°C\n", input, output);
	return 0;
}

int k2l(char* input_kg)
{
	char* endptr;
	double input;
	double output;
	errno = 0;

	input = strtod(input_kg, &endptr);

	if (input_kg == endptr || *endptr != '\0') {
		fprintf(stderr, "Error: '%s' is not a valid number.\n", input_kg);
		return 1;
	}

	output = input * KG_TO_LB;
	printf("%.3f kg = %.3f lbs\n", input, output);
	return 0;
}

int l2k(char* input_lb)
{
	char* endptr;
	double input;
	double output;
	errno = 0;

	input = strtod(input_lb, &endptr);

	if (input_lb == endptr || *endptr != '\0') {
		fprintf(stderr, "Error: '%s' is not a valid number.\n", input_lb);
		return 1;
	}

	output = input / KG_TO_LB;
	printf("%.3f lbs = %.3f kg\n", input, output);
	return 0;
}

int m2i(char* input_m)
{
	char* endptr;
	double input;
	double output;
	errno = 0;

	input = strtod(input_m, &endptr);

	if (input_m == endptr || *endptr != '\0') {
		fprintf(stderr, "Error: '%s' is not a valid number.\n", input_m);
		return 1;
	}

	output = input * CM_TO_IN * 100.0;
	printf("%.3f m = %.3f in\n", input, output);
	return 0;
}

int i2m(char* input_in)
{
	char* endptr;
	double input;
	double output;
	errno = 0;

	input = strtod(input_in, &endptr);

	if (input_in == endptr || *endptr != '\0') {
		fprintf(stderr, "Error: '%s' is not a valid number.\n", input_in);
		return 1;
	}

	output = input / CM_TO_IN / 100.0;
	printf("%.3f in = %.3f m\n", input, output);
	return 0;
}

int m2f(char* input_m)
{
	char* endptr;
	double input;
	double output;
	errno = 0;

	input = strtod(input_m, &endptr);

	if (input_m == endptr || *endptr != '\0') {
		fprintf(stderr, "Error: '%s' is not a valid number.\n", input_m);
		return 1;
	}

	output = input * M_TO_FT;
	printf("%.3f m = %.3f ft\n", input, output);
	return 0;
}

int f2m(char* input_f)
{
	char* endptr;
	double input;
	double output;
	errno = 0;

	input = strtod(input_f, &endptr);

	if (input_f == endptr || *endptr != '\0') {
		fprintf(stderr, "Error: '%s' is not a valid number.\n", input_f);
		return 1;
	}

	output = input / M_TO_FT;
	printf("%.3f ft = %.3f m\n", input, output);
	return 0;
}

int k2m(char* input_km)
{
	char* endptr;
	double input;
	double output;
	errno = 0;

	input = strtod(input_km, &endptr);

	if (input_km == endptr || *endptr != '\0') {
		fprintf(stderr, "Error: '%s' is not a valid number.\n", input_km);
		return 1;
	}

	output = input * KM_TO_MI;
	printf("%.3f km = %.3f mi\n", input, output);
	return 0;
}

int m2k(char* input_mi)
{
	char* endptr;
	double input;
	double output;
	errno = 0;

	input = strtod(input_mi, &endptr);

	if (input_mi == endptr || *endptr != '\0') {
		fprintf(stderr, "Error: '%s' is not a valid number.\n", input_mi);
		return 1;
	}

	output = input / KM_TO_MI;
	printf("%.3f mi = %.3f km\n", input, output);
	return 0;
}

int c2i(char* input_cm)
{
	char* endptr;
	double input;
	double output;
	errno = 0;

	input = strtod(input_cm, &endptr);

	if (input_cm == endptr || *endptr != '\0') {
		fprintf(stderr, "Error: '%s' is not a valid number.\n", input_cm);
		return 1;
	}

	output = input * CM_TO_IN;
	printf("%.3f cm = %.3f in\n", input, output);
	return 0;
}

int i2c(char* input_in)
{
	char* endptr;
	double input;
	double output;
	errno = 0;

	input = strtod(input_in, &endptr);

	if (input_in == endptr || *endptr != '\0') {
		fprintf(stderr, "Error: '%s' is not a valid number.\n", input_in);
		return 1;
	}

	output = input / CM_TO_IN;
	printf("%.3f in = %.3f cm\n", input, output);
	return 0;
}

int m2y(char* input_m)
{
	char* endptr;
	double input;
	double output;
	errno = 0;

	input = strtod(input_m, &endptr);

	if (input_m == endptr || *endptr != '\0') {
		fprintf(stderr, "Error: '%s' is not a valid number.\n", input_m);
		return 1;
	}

	output = input * M_TO_YD;
	printf("%.3f m = %.3f yd\n", input, output);
	return 0;
}

int y2m(char* input_y)
{
	char* endptr;
	double input;
	double output;
	errno = 0;

	input = strtod(input_y, &endptr);

	if (input_y == endptr || *endptr != '\0') {
		fprintf(stderr, "Error: '%s' is not a valid number.\n", input_y);
		return 1;
	}

	output = input / M_TO_YD;
	printf("%.3f yd = %.3f m\n", input, output);
	return 0;
}

/* Flag checking */
static int handle_temperature(int argc, char** argv)
{
	if (argc != 4) {
		return usage_conv();
	}
	if (argv[1][0] == '-' && argv[1][1] == 't') {
		if (argv[2][0] == '-' && argv[2][1] == 'c') {
			return c2f(argv[3]);
		}
		if (argv[2][0] == '-' && argv[2][1] == 'f') {
			return f2c(argv[3]);
		}
	}
	usage_conv();
	return 1;
}

static int handle_weight(int argc, char** argv)
{
	if (argc != 4) {
		return usage_conv();
	}
	if (argv[1][0] == '-' && argv[1][1] == 'w') {
		if (argv[2][0] == '-' && argv[2][1] == 'k') {
			return k2l(argv[3]);
		}
		if (argv[2][0] == '-' && argv[2][1] == 'l') {
			return l2k(argv[3]);
		}
	}
	usage_conv();
	return 1;
}

static int handle_distance(int argc, char** argv)
{
	if (argc != 4) {
		return usage_conv();
	}
	if (argv[1][0] == '-' && argv[1][1] == 'd') {
		if (argv[2][0] == '-' && argv[2][1] == 'y' && argv[2][2] == '\0') {
			return y2m(argv[3]);
		}
		if (argv[2][0] == '-' && argv[2][1] == 'm' && argv[2][2] == 'e') {
			return m2y(argv[3]);
		}
		if (argv[2][0] == '-' && argv[2][1] == 'c' && argv[2][2] == '\0') {
			return c2i(argv[3]);
		}
		if (argv[2][0] == '-' && argv[2][1] == 'i' && argv[2][2] == '\0') {
			return i2c(argv[3]);
		}
		if (argv[2][0] == '-' && argv[2][1] == 'I' && argv[2][2] == '\0') {
			return i2m(argv[3]);
		}
		if (argv[2][0] == '-' && argv[2][1] == 'm' && argv[2][2] == 'i') {
			return m2k(argv[3]);
		}
		if (argv[2][0] == '-' && argv[2][1] == 'k' && argv[2][2] == '\0') {
			return k2m(argv[3]);
		}
		if (argv[2][0] == '-' && argv[2][1] == 'm' && argv[2][2] == '\0') {
			return m2i(argv[3]);
		}
		if (argv[2][0] == '-' && argv[2][1] == 'M' && argv[2][2] == '\0') {
			return m2f(argv[3]);
		}
		if (argv[2][0] == '-' && argv[2][1] == 'F' && argv[2][2] == '\0') {
			return f2m(argv[3]);
		}
	}
	usage_conv();
	return 1;
}

/* Symlink checking */
static int run_temp_weight_symlinks(char* progname, int argc, char** argv)
{
	int result;
	result = check_and_run(progname, argc, argv, "c2f", c2f, usage_c2f);
	if (result != -1) {
		return result;
	}
	result = check_and_run(progname, argc, argv, "f2c", f2c, usage_f2c);
	if (result != -1) {
		return result;
	}
	result = check_and_run(progname, argc, argv, "k2l", k2l, usage_k2l);
	if (result != -1) {
		return result;
	}
	result = check_and_run(progname, argc, argv, "l2k", l2k, usage_l2k);
	if (result != -1) {
		return result;
	}
	return -1;
}

static int run_distance_symlinks(char* progname, int argc, char** argv)
{
	int result;
	result = check_and_run(progname, argc, argv, "m2i", m2i, usage_m2i);
	if (result != -1) {
		return result;
	}
	result = check_and_run(progname, argc, argv, "i2m", i2m, usage_i2m);
	if (result != -1) {
		return result;
	}
	result = check_and_run(progname, argc, argv, "m2f", m2f, usage_m2f);
	if (result != -1) {
		return result;
	}
	result = check_and_run(progname, argc, argv, "f2m", f2m, usage_f2m);
	if (result != -1) {
		return result;
	}
	result = check_and_run(progname, argc, argv, "k2m", k2m, usage_k2m);
	if (result != -1) {
		return result;
	}
	result = check_and_run(progname, argc, argv, "m2k", m2k, usage_m2k);
	if (result != -1) {
		return result;
	}
	result = check_and_run(progname, argc, argv, "c2i", c2i, usage_c2i);
	if (result != -1) {
		return result;
	}
	result = check_and_run(progname, argc, argv, "i2c", i2c, usage_i2c);
	if (result != -1) {
		return result;
	}
	result = check_and_run(progname, argc, argv, "m2y", m2y, usage_m2y);
	if (result != -1) {
		return result;
	}
	result = check_and_run(progname, argc, argv, "y2m", y2m, usage_y2m);
	if (result != -1) {
		return result;
	}
	return -1;
}

static int run_conversion(char* progname, int argc, char** argv)
{
	int result;

	result = run_temp_weight_symlinks(progname, argc, argv);
	if (result != -1) {
		return result;
	}
	return run_distance_symlinks(progname, argc, argv);
}

static int handle_symlink(char* progname, int argc, char** argv)
{
	return run_conversion(progname, argc, argv);
}

/* Utils */
static int check_and_run(char* progname, int argc, char** argv,
 const char* name, int (*func)(char*), int (*usage)(void))
{
	if (strcmp(progname, name) == 0) {
		if (argc != 2) {
			return usage();
		}
		return func(argv[1]);
	}
	return -1;
}

/* Main */
int main(int argc, char** argv)
{
	char* progname;
	int result;

	progname = strrchr(argv[0], '/');
	if (progname) {
		progname++;
	} else {
		progname = argv[0];
	}

	result = handle_symlink(progname, argc, argv);
	if (result != -1) {
		return result;
	}

	if (argc >= 2 && argv[1][0] == '-') {
		if (argv[1][1] == 't') {
			return handle_temperature(argc, argv);
		}
		if (argv[1][1] == 'w') {
			return handle_weight(argc, argv);
		}
		if (argv[1][1] == 'd') {
			return handle_distance(argc, argv);
		}
	}
	return usage_conv();
}
