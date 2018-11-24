/*Sắp xếp danh sách cạnh theo trọng số*****************************************/
void FRAME :: Sort()	{
	for (int i=0; i<vertices-1; ++i)
		for (int j=i+1; j<vertices; ++j)
			if (list[i].length > list[j].length)	{
				EDGE temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
}/*Kết thúc hàm Sort***********************************************************/

/*Giải thuật Kruskal tìm cây khung nhỏ nhất************************************/
void FRAME :: Kruskal()	{
	Sort();

	int label[MAX], last_i, last_j, p;

	for (int i=0; i<vertices; ++i)
		label[i] = i;

	for (int i=0; i<edges; ++i)	{
		last_i = list[i].begin;
		last_j = list[i].end;

		if (label[last_i] != label[last_j])	{
			p = label[last_j];

			for (int j=0; j<vertices; ++j)
				if (label[j] == p)
					label[j] = label[last_i];

			result[ count++ ] = list[i];
			sum_length += list[i].length;
		}
	}
}/*Kết thúc hàm Kruskal********************************************************/