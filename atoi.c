
/**
 * atoi - converts the initial portion of the string pointed to a integer
 * @str: the string to be converted
 * Return: returns (0) if numbers in string or a set of
 * converted number
 */

int atoi(char *str)
{
	int a, prod;
	int sign = 1, flagg = 0;
	unsigned int res = 0;

	for (a = 0; str[a] != '\0' && flagg != 2; a++)
	{
		if (str[a] == '-')
			sign *= -1;

		if (str[a] >= '0' && str[a] <= '9')
		{
			flagg = 1;
			res *= 10;
			res += (str[a] - '0');
		}
		else if (flagg == 1)
			flagg = 2;
	}

	if (sign == -1)
		prod = -res;
	else
		prod = res;

	return (prod);
}


/**
 * alpha - checks for alphabet
 * @cc: the input character
 * Return: returns (1) if true and (0) if not
 */

int alpha(int cc)
{
	if ((cc >= 'a' && cc <= 'z') || (cc >= 'A' && cc <= 'Z'))
		return (1);
	else
		return (0);
}


/**
 * delim - this checks if character is a delimeter
 * @cc: the character to check
 * @dd: the delimeter
 * Return: returns (1) there is a delimeter, (0) if false
 */
int delim(char cc, char *dd)
{
	while (*dd)
		if (*dd++ == cc)
			return (1);
	return (0);
}
