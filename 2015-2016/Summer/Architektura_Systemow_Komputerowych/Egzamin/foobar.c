long int foobar(int* x, int* y, int* z)
{
	int result = 0;
	int r8 = *y;
	int r9 = *x;
	if( r8 <= 0 ) return result;
	long int temp;
	while(r9 > 0)
	{
		if( r9 >= r8)
		{
			x++;
			temp = r9;
		}
		else
		{
			y++;
			temp = r8;
		}
		*z = temp;
		z++;
		result += temp;
		r8 = *y;
		r9 = *x;
		if(r8 <= 0) return result; 
	}

}
