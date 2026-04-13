#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/* Usage functions */
int usage_conv(void)
{
	fprintf(stderr,
	 "Usage: conv -t -c <value>   (Temperature: Celsius to Fahrenheit)\n");
	fprintf(stderr,
	 "       conv -t -f <value>   (Temperature: Fahrenheit to Celsius)\n");
	fprintf(stderr,
	 "       conv -w -k <value>   (Weight: Kilograms to Pounds)\n");
	fprintf(stderr,
	 "       conv -w -l <value>   (Weight: Pounds to Kilograms)\n");
	fprintf(stderr, "       conv -d -c <value>   (Distance: Centimetres to Inches)\n");
	fprintf(stderr, "       conv -d -i <value>   (Distance: Inches to Centimetres)\n");
	fprintf(stderr, "       conv -d -I <value>   (Distance: Inches to Metres)\n");
	fprintf(stderr, "       conv -d -mi <value>  (Distance: Miles to Kilometres)\n");
	fprintf(stderr, "       conv -d -k <value>   (Distance: Kilometres to Miles)\n");
	fprintf(stderr, "       conv -d -m <value>   (Distance: Metres to Inches)\n");
	fprintf(stderr, "       conv -d -M <value>   (Distance: Metres to Feet)\n");
	fprintf(stderr, "       conv -d -F <value>   (Distance: Feet to Metres)\n");
	fprintf(stderr,
	 "       conv -d -K <value>   (Distance: Kilometres to Miles)\n");
	fprintf(stderr,
	 "       conv -d -mi <value>  (Distance: Miles to Kilometres)\n");
	fprintf(stderr,
	 "       conv -d -c <value>   (Distance: Centimetres to Inches)\n");
	fprintf(stderr,
	 "       conv -d -i <value>  (Distance: Inches to Centimetres)\n");
	return 1;
}

int usage_c2f(void)
{
	fprintf(stderr, "Usage: c2f <celsius_value>\n");
	fprintf(stderr, "Convert Celsius to Fahrenheit\n");
	return 1;
}

int usage_f2c(void)
{
	fprintf(stderr, "Usage: f2c <fahrenheit_value>\n");
	fprintf(stderr, "Convert Fahrenheit to Celsius\n");
	return 1;
}

int usage_k2l(void)
{
	fprintf(stderr, "Usage: k2l <kilogram_value>\n");
	fprintf(stderr, "Convert Kilograms to Pounds\n");
	return 1;
}

int usage_l2k(void)
{
	fprintf(stderr, "Usage: l2k <pound_value>\n");
	fprintf(stderr, "Convert Pounds to Kilograms\n");
	return 1;
}

int usage_m2i(void)
{
	fprintf(stderr, "Usage: m2i <metre_value>\n");
	fprintf(stderr, "Convert Metres to Inches\n");
	return 1;
}

int usage_i2m(void)
{
	fprintf(stderr, "Usage: i2m <inch_value>\n");
	fprintf(stderr, "Convert Inches to Metres\n");
	return 1;
}

int usage_m2f(void)
{
	fprintf(stderr, "Usage: m2f <metre_value>\n");
	fprintf(stderr, "Convert Metres to Feet\n");
	return 1;
}

int usage_f2m(void)
{
	fprintf(stderr, "Usage: f2m <foot_value>\n");
	fprintf(stderr, "Convert Feet to Metres\n");
	return 1;
}

int usage_k2m(void)
{
	fprintf(stderr, "Usage: k2m <kilometre_value>\n");
	fprintf(stderr, "Convert Kilometres to Miles\n");
	return 1;
}

int usage_m2k(void)
{
	fprintf(stderr, "Usage: m2k <mile_value>\n");
	fprintf(stderr, "Convert Miles to Kilometres\n");
	return 1;
}

int usage_c2i(void)
{
	fprintf(stderr, "Usage: c2i <centimetre_value>\n");
	fprintf(stderr, "Convert Centimetres to Inches\n");
	return 1;
}

int usage_i2c(void)
{
	fprintf(stderr, "Usage: i2c <inch_value>\n");
	fprintf(stderr, "Convert Inches to Centimetres\n");
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

	output = (input * 9.0 / 5.0) + 32.0;
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

	output = (input - 32.0) * 5.0 / 9.0;
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

	output = input * 2.20462262185;
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

	output = input / 2.20462262185;
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

	output = input * 39.3700787402;
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

	output = input / 39.3700787402;
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

	output = input * 3.28083989501;
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

	output = input / 3.28083989501;
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

	output = input * 0.621371;
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

	output = input / 0.621371;
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

	output = input * 0.393701;
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

	output = input / 0.393701;
	printf("%.3f in = %.3f cm\n", input, output);
	return 0;
}

/* Main function */
int main(int argc, char** argv)
{
	char* progname;

	/* Get the program name (basename) */
	progname = strrchr(argv[0], '/');
	if (progname) {
		progname++;
	} else {
		progname = argv[0];
	}

	/* Check if invoked as c2f */
	if (strcmp(progname, "c2f") == 0) {
		if (argc != 2) {
			return usage_c2f();
		}
		return c2f(argv[1]);
	}

	/* Check if invoked as f2c */
	if (strcmp(progname, "f2c") == 0) {
		if (argc != 2) {
			return usage_f2c();
		}
		return f2c(argv[1]);
	}

	/* Check if invoked as k2l */
	if (strcmp(progname, "k2l") == 0) {
		if (argc != 2) {
			return usage_k2l();
		}
		return k2l(argv[1]);
	}

	/* Check if invoked as l2k */
	if (strcmp(progname, "l2k") == 0) {
		if (argc != 2) {
			return usage_l2k();
		}
		return l2k(argv[1]);
	}

	/* Check if invoked as m2i */
	if (strcmp(progname, "m2i") == 0) {
		if (argc != 2) {
			return usage_m2i();
		}
		return m2i(argv[1]);
	}

	/* Check if invoked as i2m */
	if (strcmp(progname, "i2m") == 0) {
		if (argc != 2) {
			return usage_i2m();
		}
		return i2m(argv[1]);
	}

	/* Check if invoked as m2f */
	if (strcmp(progname, "m2f") == 0) {
		if (argc != 2) {
			return usage_m2f();
		}
		return m2f(argv[1]);
	}

	/* Check if invoked as f2m */
	if (strcmp(progname, "f2m") == 0) {
		if (argc != 2) {
			return usage_f2m();
		}
		return f2m(argv[1]);
	}

	/* Check if invoked as k2m */
	if (strcmp(progname, "k2m") == 0) {
		if (argc != 2) {
			return usage_k2m();
		}
		return k2m(argv[1]);
	}

	/* Check if invoked as m2k */
	if (strcmp(progname, "m2k") == 0) {
		if (argc != 2) {
			return usage_m2k();
		}
		return m2k(argv[1]);
	}

	/* Check if invoked as c2i */
	if (strcmp(progname, "c2i") == 0) {
		if (argc != 2) {
			return usage_c2i();
		}
		return c2i(argv[1]);
	}

	/* Check if invoked as i2c */
	if (strcmp(progname, "i2c") == 0) {
		if (argc != 2) {
			return usage_i2c();
		}
		return i2c(argv[1]);
	}

	/* Otherwise use conv behavior with flags */
	if (argc != 4) {
		return usage_conv();
	}

	/* Temperature conversions */
	if (argv[1][0] == '-' && argv[1][1] == 't') {
		if (argv[2][0] == '-' && argv[2][1] == 'c') {
			return c2f(argv[3]);
		} else if (argv[2][0] == '-' && argv[2][1] == 'f') {
			return f2c(argv[3]);
		} else {
			usage_conv();
			return 1;
		}
	}

	/* Weight conversions */
	if (argv[1][0] == '-' && argv[1][1] == 'w') {
		if (argv[2][0] == '-' && argv[2][1] == 'k') {
			return k2l(argv[3]);
		} else if (argv[2][0] == '-' && argv[2][1] == 'l') {
			return l2k(argv[3]);
		} else {
			usage_conv();
			return 1;
		}
	}

	/* Distance conversions */
	if (argv[1][0] == '-' && argv[1][1] == 'd') {
		if (argv[2][0] == '-' && argv[2][1] == 'c' && argv[2][2] == '\0') {
			return c2i(argv[3]);
		} else if (argv[2][0] == '-' && argv[2][1] == 'i' && argv[2][2] == '\0') {
			return i2c(argv[3]);
		} else if (argv[2][0] == '-' && argv[2][1] == 'I' && argv[2][2] == '\0') {
			return i2m(argv[3]);
		} else if (argv[2][0] == '-' && argv[2][1] == 'm' && argv[2][2] == 'i') {
			return m2k(argv[3]);
		} else if (argv[2][0] == '-' && argv[2][1] == 'k' && argv[2][2] == '\0') {
			return k2m(argv[3]);
		} else if (argv[2][0] == '-' && argv[2][1] == 'm' && argv[2][2] == '\0') {
			return m2i(argv[3]);
		} else if (argv[2][0] == '-' && argv[2][1] == 'M' && argv[2][2] == '\0') {
			return m2f(argv[3]);
		} else if (argv[2][0] == '-' && argv[2][1] == 'F' && argv[2][2] == '\0') {
			return f2m(argv[3]);
		} else {
			usage_conv();
			return 1;
		}
	}

	usage_conv();
	return 1;
}
