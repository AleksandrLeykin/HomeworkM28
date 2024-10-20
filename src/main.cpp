#include <iostream>
#include <future>


//Давайте теперь рассмотрим функцию merge. Она принимает массив arr, в котором записаны 
//все части, l — начало части, m — середина части и r — конец части.
void merge(int* arr, int l, int m, int r)
{
   int nl = m - l + 1;
   int nr = r - m;

   // создаем временные массивы
   int left[nl], right[nr];

   // копируем данные во временные массивы
   for (int i = 0; i < nl; i++)
       left[i] = arr[l + i];
   for (int j = 0; j < nr; j++)
       right[j] = arr[m + 1 + j];

   int i = 0, j = 0;
   int k = l;  // начало левой части

   while (i < nl && j < nr) {
       // записываем минимальные элементы обратно во входной массив
       if (left[i] <= right[j]) {
           arr[k] = left[i];
           i++;
       }
       else {
           arr[k] = right[j];
           j++;
       }
       k++;
   }
   // записываем оставшиеся элементы левой части
   while (i < nl) {
       arr[k] = left[i];
       i++;
       k++;
   }
   // записываем оставшиеся элементы правой части
   while (j < nr) {
       arr[k] = right[j];
       j++;
       k++;
   }
}

void mergeSort(int *arr, int l, int r) {
    if (l >= r)
        return;    
    int m = (l + r - 1) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

int main(int argc, char** argv) {
int arr[] = {5, 2, 7, 3, 22, 13, 6, 87, 15};
int size = sizeof(arr) / sizeof(arr[0]);
mergeSort(arr, 0, size -1);

for (int i = 0; i < size; ++i)
{
    std::cout << arr[i] << " ";
}

    return 0;
}