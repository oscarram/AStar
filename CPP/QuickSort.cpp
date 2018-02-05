void swap(node *a, node *b)
{
    unsigned long id = a->id;
	double lon=a->lon;
	double lat=a->lat;

    a->id = b->id;
    a->lon = b->lon;
    a->lat = b->lat;
	b->id = id;
	b->lon = lon;
	b->lat = lat;
}

unsigned long partition (node* arr, int low, int high, int pivotN)
{
    unsigned long pivot = (arr+pivotN)->id;    // pivot
	/*printf("%lu\n", pivot); */
    unsigned long i = (low - 1);  // Index of smaller element
 
    for (int j = low; j <= pivotN- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if ((arr+j)->id <= pivot)
        {
            i++;    // increment index of smaller element
            swap((arr+i), (arr+j));
        }
    }

    swap(arr+i + 1, arr+high);

    return (i + 1);
}
 
/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(node *arr, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        unsigned long pi = partition(arr, low, high, 6);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
