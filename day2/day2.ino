#include "day2_input.h"

/**
 * Reads all sequential integers in a string.
 * Will translate their value from string to int.
 * @param passwords A pointeWr to our progressive pointer that is being moved through the list.
 * @return An integer representation of the value read from the string.
 */
uint8_t read_integer(const char **passwords)
{
	const char *index = *passwords;
	char read = pgm_read_byte_near(index++);
	uint8_t value = 0;
	while (read > 47U && read < 58U)
	{
		if (value != 0)
			value *= 10U;
		value += (read - 48U);
		read = pgm_read_byte_near(index++);
	} 
	*passwords = index;
	return value;
}

/**
 * Validates the password by reading two integer values from the string and storing them as a min and max value.
 * Counts the number of occurance of the key letter inside the password, and compares that to the min and max values.
 * A password is valid if the occurance of the key character is between the min and max.
 * A progressive pointer is managed throughout the list.
 * @param passwords A pointer to our progressive pointer that is being moved through the list.
 * @return Whether the password is valid or not
 */
bool validate_password_old(const char **passwords)
{
	uint8_t min, max, count = 0;
	char compareValue = 0;

	min = read_integer(passwords);
	max = read_integer(passwords);

	const char * index = *passwords;

	// Read our key character
	compareValue = pgm_read_byte_near(index);    

	index += 3;
	char testValue = pgm_read_byte_near(index);
	while (testValue > 96U && testValue < 123U)
	{
		index++;
		if (testValue == compareValue)
			count++;

		testValue = pgm_read_byte_near(index);
	} 
	*passwords = index;

	return (count >= min && count <= max);
}

/**
 * Validates the password by reading two integer values from the string and storing them as two indexes.
 * Checks whether the key character occurs at one or the other, but not both of the indexes (XOR).
 * A password is valid if the key character occurs atleast 1 index, but not both.
 * A progressive pointer is managed throughout the list.
 * @param passwords A pointer to our progressive pointer that is being moved through the list.
 * @return Whether the password is valid or not
 */
bool validate_password_new(const char **passwords)
{
	uint8_t first, second, count = 0;
	char compareValue = 0;

	first = read_integer(passwords);
	second = read_integer(passwords);

	const char * index = *passwords;

	compareValue = pgm_read_byte_near(index);    

	index += 2;
	char firstValue = pgm_read_byte_near(index + first);
	char secondValue = pgm_read_byte_near(index + second);

	index++;

	char testValue = pgm_read_byte_near(index);

	while (testValue > 96U && testValue < 123U)
	{
		index++;
		testValue = pgm_read_byte_near(index);
	}

	*passwords = index;

	return ((firstValue == compareValue) ^ (secondValue == compareValue));
}

/**
 * Validates a large string of continous passwords using a password validator function.
 * Each valid password will increase the counter.
 * @param data A pointer to the start of the string.
 * @param func A pointer to the validation function to run on the passwords.
 * @return The number of valid passwords in the string.
 */
uint32_t passwords_validator(const char *data, bool(*func) (const char **))
{
	uint16_t count = 0;

	do
	{
		if (func(&data))
			count++;
	} while (pgm_read_byte_near(data) != 0);
	return count;
}

void setup()
{
	Serial.begin(9600);
	while (!Serial);
	unsigned long startTime;
	unsigned long endTime;
	unsigned long duration;

	startTime = micros();
	uint16_t validCount = passwords_validator(PASSWORDS, &validate_password_old);
	endTime = micros();
	duration = endTime - startTime;
	Serial.print("validate_passwords_old time: ");
	Serial.println(duration);
	Serial.print("validate_passwords_old value: ");
	Serial.println(validCount);

	startTime = micros();
	validCount = passwords_validator(PASSWORDS, &validate_password_new);
	endTime = micros();
	duration = endTime - startTime;

	Serial.print("validate_passwords_new time: ");
	Serial.println(duration);
	Serial.print("validate_passwords_new value: ");
	Serial.println(validCount);
}

void loop() {

}