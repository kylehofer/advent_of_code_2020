#include "day3_input.h"


/**
 * Runs a toboggan down a 'slope' and counts the trees encountered along the journey.
 * The course has a total width of 31, and 
 * @param data A pointer to the start of the string.
 * @param func A pointer to the validation function to run on the passwords.
 * @return The number of valid passwords in the string.
 */
uint16_t traverse_course(const char *start, const char* upper, const uint16_t right, const uint16_t down)
{
	unsigned long startTime, endTime, duration;
	startTime = micros();	

	const uint16_t stage_size = 31;
	uint16_t count = 0, offset = 0;
	
	const uint16_t increment = stage_size * down;

	const char* pivot = start + increment;

	do
	{
		offset += right;
		if (offset >= stage_size) {
			offset -= stage_size;
		}

		if (pgm_read_byte_near(pivot + offset) == 35) {
			count++;
		}

		pivot += increment;
	} while (pivot < upper);

	endTime = micros();
	duration = endTime - startTime;

	Serial.print(SETUP_MESSAGE_1);
	Serial.print(right);
	Serial.print(SETUP_MESSAGE_2);
	Serial.println(down);
	Serial.print(TIME_MESSAGE);
	Serial.println(duration);
	Serial.print(VALUE_MESSAGE);
	Serial.println(count);
	return count;
}


void setup()
{
	Serial.begin(9600);
	while (!Serial);

	Serial.println("");

	const char* upper = (sizeof(COURSE) / sizeof(*COURSE)) + COURSE;

	uint32_t count = traverse_course(COURSE, upper, 1, 1);
	count *= traverse_course(COURSE, upper, 3, 1);
	count *= traverse_course(COURSE, upper, 5, 1);
	count *= traverse_course(COURSE, upper, 7, 1);
	count *= traverse_course(COURSE, upper, 1, 2);

	Serial.print(F("Total trees encountered: "));
	Serial.println(count);
}

void loop() {

}