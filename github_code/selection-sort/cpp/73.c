/**************************************************
 * Function selectionSort                         *
 * This function performs the selection sort      *
 * algorithm on array, sorting it into ascending  *
 * order. The parameter size holds the number of  *
 * elements in the array.                         *
 **************************************************/

void selectionSort(int *array, int size)
{
   int startScan, minIndex, minValue;

   for (startScan = 0; startScan < (size - 1); startScan++)
   {
      minIndex = startScan;
      minValue = *(array+startScan);
      for(int index = startScan + 1; index < size; index++)
      {
         if (*(array+index) < minValue)
         {
            minValue = *(array+index);
            minIndex = index;
         }
      }
      *(array+minIndex) = *(array+startScan);
      *(array+startScan) = minValue;
	}
}