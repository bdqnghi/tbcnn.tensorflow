

int comparison(int** matrix, int i, int j)
{
	int left = matrix[i][j - 1] + 1;
	int up = matrix[i - 1][j] + 1;
	int diag = matrix[i - 1][j - 1] + ();

}
int countLevensteinDistance(int** matrix, int length_s1, int length_s2, char* s1, char* s2)
{
	for (int i = 0; i < length_s1 + 1; i++){
		matrix[0][i] = i;
	}
	for (int i = 0; i < length_s2 + 1; i++){
		matrix[i][0] = i;
	}
	for (int i = 1; i < length_s1 + 1; i++){
		for (int j = 1; j < length_s2 + 1; j++)
		{
			matrix[i][j] = comparison()
		}
	}
}


int main()
{
	int length_s1;
	int length_s2;
	char* s1 = new char[length_s1];
	char* s2 = new char[length_s2];
	input();

	int** matrix = new int[length_s1 + 1]; //�������� ������� ������� (����� ������� ����� +1  �  ����� ������� ����� +2)
	for (int i = 0; i < length_s1 + 1; i++) //s1 - �����, ������� ���� �������������� ����� � ����� �������
	{
		matrix[i] = new int[length_s2 + 1];
	}
	
}