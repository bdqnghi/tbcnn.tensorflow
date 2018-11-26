const int maxN = 31;
output ("Enter the number of disks (make sure it's less than 32): ");
int N;
input (N);

if ((N < 0) || (N > 31))
{
	output ("I don't want to play with you!..");
}
else
{

	int k = 1;
	int n = N;
	while (n > 0)
	{
		k = k * 2;
		n--;
	}
	k--;



	int start_tower[maxN];
	int second_tower[maxN];
	int third_tower[maxN];
	int start_tower_count = N;
	int second_tower_count = 0;
	int third_tower_count = 0;

	n = N;
	while (n > 0)
	{
		start_tower[n - 1] = N - n + 1;
		second_tower[n - 1] = 0;
		third_tower[n - 1] = 0;
		n--;
	}

	int t = 1;

	second_tower[second_tower_count] = start_tower[start_tower_count - 1];
	start_tower[start_tower_count - 1] = 0;
	start_tower_count--;
	second_tower_count++;
	t++;
	k--;
	output("1->2; ");

	while (k > 0)
	{
		if (t % 3 == 1)
		{
			if ((second_tower_count == 0) || ((second_tower[second_tower_count - 1] > third_tower[third_tower_count - 1]) && (third_tower_count != 0)))
			{
				second_tower[second_tower_count] = third_tower[third_tower_count - 1];
				third_tower[third_tower_count - 1] = 0;
				third_tower_count--;
				second_tower_count++;
				k--;
				output("3->2; ");
			}
			else
			{
				if (third_tower_count == 0 || ((second_tower[second_tower_count - 1] < third_tower[third_tower_count - 1]) && (second_tower_count != 0)))
				{
					third_tower[third_tower_count] = second_tower[second_tower_count - 1];
					second_tower[second_tower_count - 1] = 0;
					second_tower_count--;
					third_tower_count++;
					k--;
					output("2->3; ");
				}
			}

			second_tower[second_tower_count] = start_tower[start_tower_count - 1];
			start_tower[start_tower_count - 1] = 0;
			start_tower_count--;
			second_tower_count++;
			t++;
			k--;
			output("1->2; ");
		}
		else
		{
			if (t % 3 == 2)
			{
				if ((start_tower_count == 0) || ((start_tower[start_tower_count - 1] > third_tower[third_tower_count - 1]) && third_tower_count != 0))
				{
					start_tower[start_tower_count] = third_tower[third_tower_count - 1];
					third_tower[third_tower_count - 1] = 0;
					third_tower_count--;
					start_tower_count++;
					k--;
					output("3->1; ");
				}
				else
				{
					if ((third_tower_count == 0) || ((start_tower[start_tower_count - 1] < third_tower[third_tower_count - 1]) && start_tower_count != 0))
					{
						third_tower[third_tower_count] = start_tower[start_tower_count - 1];
						start_tower[start_tower_count - 1] = 0;
						start_tower_count--;
						third_tower_count++;
						k--;
						output("1->3; ");
					}
				}

				third_tower[third_tower_count] = second_tower[second_tower_count - 1];
				second_tower[second_tower_count - 1] = 0;
				second_tower_count--;
				third_tower_count++;
				t++;
				k--;
				output("2->3; ");
			}
			else
			{
				if (t % 3 == 0)
				{
					if (start_tower_count == 0 || ((start_tower[start_tower_count - 1] > second_tower[second_tower_count - 1]) && (second_tower_count != 0)))
					{
						start_tower[start_tower_count] = second_tower[second_tower_count - 1];
						second_tower[second_tower_count - 1] = 0;
						second_tower_count--;
						start_tower_count++;
						k--;
						output("2->1; ");
					}
					else
					{
						if ((second_tower_count == 0) || ((start_tower[start_tower_count - 1] < second_tower[second_tower_count - 1]) && (start_tower_count != 0)))
						{
							second_tower[second_tower_count] = start_tower[start_tower_count - 1];
							start_tower[start_tower_count - 1] = 0;
							start_tower_count--;
							second_tower_count++;
							k--;
							output("1->2; ");
						}
					}

					start_tower[start_tower_count] = third_tower[third_tower_count - 1];
					third_tower[third_tower_count - 1] = 0;
					third_tower_count--;
					start_tower_count++;
					t++;
					k--;
					output("3->1; ");
				}
				else
				{
					output("error");
				}
			}
		}
	}
}