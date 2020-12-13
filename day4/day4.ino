#include "day4_input.h"
/*
 Name:		day4.ino
 Created:	09-Dec-20 10:23:03 PM
 Author:	KyleHofer
*/

const char BIRTH[] = { "byr" };
const char ISSUE[] = { "iyr" };
const char EXPIRATION[] = { "eyr" };
const char HEIGHT[] = { "hgt" };
const char HAIR[] = { "hcl" };
const char EYE[] = { "ecl" };
const char PASSPORT[] = { "pid" };
const char COUNTRY[] = { "cid" };

/**
 * Reads all sequential integers in a string.
 * Will translate their value from string to int.
 * @param passwords A pointeWr to our progressive pointer that is being moved through the list.
 * @return An integer representation of the value read from the string.
 */
uint8_t read_field(const char** position)
{
	char buffer[3];

	memcpy_P(buffer, *position, 3);

	const char* index = *position += 3;
	char value = 0;

	do {
		value = pgm_read_byte_near(index++);
		
	} while (value != 32 && value != 10 && value != 0);

	*position = index;

	uint8_t result = (memcmp(buffer, BIRTH, 3) == 0 || memcmp(buffer, ISSUE, 3) == 0 || memcmp(buffer, EXPIRATION, 3) == 0 ||
		memcmp(buffer, HEIGHT, 3) == 0 || memcmp(buffer, HAIR, 3) == 0 ||
		memcmp(buffer, EYE, 3) == 0 || memcmp(buffer, PASSPORT, 3) == 0);

	delete buffer;
	return result;
}

/**
 * Validates the password by reading two integer values from the string and storing them as a min and max value.
 * Counts the number of occurance of the key letter inside the password, and compares that to the min and max values.
 * A password is valid if the occurance of the key character is between the min and max.
 * A progressive pointer is managed throughout the list.
 * @param passwords A pointer to our progressive pointer that is being moved through the list.
 * @return Whether the password is valid or not
 */
uint8_t validate_password(const char** position, const char* upper)
{
	uint8_t count = 0;

	do
	{
		count += read_field(position);
	} while (*position < upper && pgm_read_byte_near(*position) != 10);


	return count >= 7;
}

/**
 * Validates the password by reading two integer values from the string and storing them as two indexes.
 * Checks whether the key character occurs at one or the other, but not both of the indexes (XOR).
 * A password is valid if the key character occurs atleast 1 index, but not both.
 * A progressive pointer is managed throughout the list.
 * @param passwords A pointer to our progressive pointer that is being moved through the list.
 * @return Whether the password is valid or not
 */
uint8_t validate_input(const char* position, const char* upper)
{
	uint8_t count = 0;
	do
	{
		count += validate_password(&position, upper);
	} while (position++ < upper);
	return count;
}


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	while (!Serial);
	unsigned long startTime;
	unsigned long endTime;
	unsigned long duration;

	Serial.print("");
	Serial.print("");

	const char* upper = (sizeof(PASSPORTS) / sizeof(*PASSPORTS)) + PASSPORTS;

	startTime = micros();
	uint16_t validCount = validate_input(PASSPORTS, upper);
	endTime = micros();
	duration = endTime - startTime;
	Serial.print("validate_input time: ");
	Serial.println(duration);
	Serial.print("validate_input value: ");
	Serial.println(validCount);

}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
