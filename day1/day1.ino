

typedef struct
{
	int16_t *lower;
	int16_t *upper;
} DoublePtr_t;

/**
 * Sorts a region of a list of 16-bit integers by using Hoare partition scheme.
 * Read more here: https://en.wikipedia.org/wiki/Quicksort#Hoare_partition_scheme
 * @param low pointer to the lower boundary of the sort.
 * @param high pointer to the upper boundary of the sort.
 * @return A pointer of the mid point of the upper and lower boundaries.
 */
int16_t *partition(int16_t *low, int16_t *high)
{
	int16_t pivot = *((((high - low) >> 1)) + low);
	int16_t temp;

	low--;
	high++;

	for (;;)
	{
		do
		{
			low++;
		} while (*low < pivot);
		do
		{
			high--;
		} while (*high > pivot);

		if (low >= high)
			return high;

		temp = *high;
		*high = *low;
		*low = temp;
	}
}

/**
 * C++ implementation of a quicksort algorithm
 * Read more here: https://en.wikipedia.org/wiki/Quicksort#Hoare_partition_scheme
 * @param low pointer to the lower boundary of the sort.
 * @param high pointer to the upper boundary of the sort.
 */
void quick_sort(int16_t *low, int16_t *high)
{
	if (low >= high)
	{
		return;
	}
	int16_t *pivot = partition(low, high);

	quick_sort(low, pivot);
	quick_sort(pivot + 1, high);
}

/**
 * Traverses a sorted list of integers to find two values that add up to 2020.
 * Will move the upper/lower pointers based of whether the sum is above or below 2020.
 * Once the sum is found, the values will be multiplied together and returned.
 * @param low pointer to the lower boundary of the list.
 * @param high pointer to the upper boundary of the list.
 * @return The multiplication of two values who's sum add up to 2020.
 */
uint32_t find_2020(int16_t *low, int16_t *high)
{
	for (;;)
	{
		int16_t sum = *low + *high;
		if (sum < 2020)
		{
			low++;
		}
		else if (sum > 2020)
		{
			high--;
		}
		else
		{
			return uint32_t(*low) * uint32_t(*high);
		}
	}
}

/**
 * Traverses a sorted list of integers to find three values that add up to 2020.
 * Will move a pivot pointer up from the lower to high boundary.
 * If the pivot hits the upper boundary, a pointer that is one position lower than the high is returned.
 * If the sum exceeds 2020, then this function will be recursively called with an incremented lower boundary.
 * Once the sum is found, the pointers of the lower boundary and pivot will be returned.
 * @param low pointer to the lower boundary of the list.
 * @param high pointer to the upper boundary of the list.
 * @param pivot A starting point for the pivot.
 * @return The multiplication of two values who's sum add up to 2020.
 */
DoublePtr_t pivot_track_low(int16_t *low, int16_t *high, int16_t *pivot)
{
	int16_t remainder = (2020 - (*low + *high));

	do
	{
		pivot++;
	} while (pivot < high && remainder > *pivot);
	if (pivot >= high)
	{
		DoublePtr_t value;
		value.lower = (high - 1);
		return value;
	}
	else if (remainder < *pivot)
	{
		return pivot_track_low(low + 1, high, low + 2);
	}
	DoublePtr_t value;
	value.upper = low;
	value.lower = pivot;
	return value;
}

/**
 * Traverses a sorted list of integers to find three values that add up to 2020.
 * Will move a pivot pointer down from the upper to lower boundary.
 * If the pivot hits the lower boundary, a pointer that is one position above than the lower boundary is returned.
 * If the sum exceeds 2020, then this function will be recursively called with an incremented upper boundary.
 * Once the sum is found, the pointers of the upper boundary and pivot will be returned.
 * @param low pointer to the lower boundary of the list.
 * @param high pointer to the upper boundary of the list.
 * @param pivot A starting point for the pivot.
 * @return The multiplication of two values who's sum add up to 2020.
 */
DoublePtr_t pivot_track_high(int16_t *low, int16_t *high, int16_t *pivot)
{
	int16_t remainder = (2020 - (*low + *high));

	do
	{
		pivot--;
	} while (pivot > low && remainder < *pivot);
	if (pivot <= low)
	{
		DoublePtr_t value;
		value.lower = (low + 1);

		return value;
	}
	else if (remainder > *pivot)
	{
		return pivot_track_high(low, high - 1, high - 2);
	}

	DoublePtr_t value;
	value.upper = high;
	value.lower = pivot;
	return value;
}

/**
 * Applies the same behaviour of finding 2020 with two values, with the addition of a floating pivot.
 * The floating pivot will read the values between the boundaries.
 * @param low The lower boundary of the list.
 * @param high The upper boundary of the list.
 * @return The multiplication of the 3 values that sum to 2020.
 */
uint32_t find_2020_triple(int16_t *low, int16_t *high)
{
	int16_t *pivot = low + 1;
	for (;;)
	{
		int16_t remainder = (2020 - (*low + *high));
		if (remainder > *pivot)
		{
			DoublePtr_t result = pivot_track_low(low, high, pivot);

			if (result.upper)
			{
				return uint32_t(*high) * *result.upper * *result.lower;
			}
			pivot = result.lower;
			low++;
		}
		else if (remainder < *pivot)
		{
			DoublePtr_t result = pivot_track_high(low, high, pivot);

			if (result.upper)
			{
				return uint32_t(*low) * *result.upper * *result.lower;
			}
			pivot = result.lower;
			high--;
		}
		else
		{
			return uint32_t(*low) * (*high) * (*pivot);
		}
	}
}


int16_t day1_list[] = {1765, 1742, 1756, 1688, 1973, 1684, 1711, 1728, 1603, 1674, 1850, 1836, 1719, 1937, 1970, 1770, 1954, 1848, 1885, 1851, 1474, 1801, 1769, 1904, 1906, 1739, 1717, 1830, 1985, 1930, 1791, 1977, 1713, 1787, 1773, 1672, 1750, 1931, 1807, 1762, 1835, 1736, 1979, 1923, 1782, 1797, 1822, 1903, 1729, 343, 1678, 1753, 1873, 1358, 1987, 1821, 1761, 1988, 1886, 1669, 857, 1894, 1404, 1909, 1789, 1752, 1882, 1969, 1892, 1701, 1956, 1839, 483, 1897, 1730, 1829, 1879, 1810, 1755, 1799, 1932, 1715, 1809, 418, 1896, 1691, 1749, 1922, 1631, 1780, 1734, 1859, 1695, 1548, 1948, 1997, 1921, 1994, 1369, 1364, 1764, 1697, 1833, 1239, 616, 1786, 1890, 677, 1867, 1705, 1993, 1925, 1774, 1732, 1686, 1847, 1911, 1841, 1962, 1907, 1919, 1725, 1687, 1236, 1864, 1855, 1928, 1941, 1709, 1683, 1676, 1889, 1982, 1595, 1735, 1857, 1731, 1816, 2003, 1724, 741, 1655, 1308, 1959, 1955, 1768, 1795, 1804, 1961, 1693, 1884, 1813, 1927, 1845, 1689, 1646, 1803, 2008, 1599, 1984, 1871, 1814, 1918, 1990, 1858, 1908, 1949, 1980, 1618, 1718, 1712, 1989, 1876, 1947, 1974, 1838, 1865, 1842, 1817, 680, 1986, 1812, 1895, 1991, 1644, 1877, 1880, 1792, 1800, 1899, 1806, 1699, 1685, 1793, 1647, 1429, 1751, 1722, 1887, 1968};

void setup()
{
	Serial.begin(9600);
	while (!Serial); // wait for serial port to connect. Needed for native USB

	unsigned long startTime;
	unsigned long endTime;
	unsigned long duration;

	uint8_t listSize = (sizeof(day1_list) / sizeof(*day1_list));

	int16_t *lower = day1_list;
	int16_t *upper = day1_list + (listSize - 1);

	uint32_t result;

	startTime = micros();
	quick_sort(lower, upper);
	endTime = micros();
	duration = endTime - startTime;
	Serial.print("Quicksort time: ");
	Serial.println(duration);

	startTime = micros();
	result = find_2020(lower, upper);
	endTime = micros();
	duration = endTime - startTime;
	Serial.print("find_2020 time: ");
	Serial.println(duration);
	Serial.print("find_2020 result: ");
	Serial.println(result);

	startTime = micros();
	result = find_2020_triple(lower, upper);
	endTime = micros();
	duration = endTime - startTime;
	Serial.print("find_2020_triple time: ");
	Serial.println(duration);
	Serial.print("find_2020_triple result: ");
	Serial.println(result);
}

void loop()
{

}