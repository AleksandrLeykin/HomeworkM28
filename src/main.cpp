#include <iostream>
#include <future>
#include <random>
#include <chrono>

//flag to tell the function to run calculations in the thread.
//флаг для указания функции запускать вычисления в потоке.
bool make_thread = true;

//принимает массив arr, в котором записаны все части, 
//l — начало части, m — середина части и r — конец части.
void merge(int* arr, long l, long m, long r)
{
   long nl = m - l + 1;
   long nr = r - m;

   // create temporary arrays создаем временные массивы
   int left[nl], right[nr];

   // copy data into temporary arrays копируем данные во временные массивы
   for (int i = 0; i < nl; i++)
       left[i] = arr[l + i];
   for (int j = 0; j < nr; j++)
       right[j] = arr[m + 1 + j];

   int i = 0, j = 0;
   int k = l;  // beginning of the left part начало левой части

   while (i < nl && j < nr) {
        // write the minimum elements back to the input array
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
   //we write down the remaining elements of the left side
   // записываем оставшиеся элементы левой части
   while (i < nl) {
       arr[k] = left[i];
       i++;
       k++;
   }
   //we write down the remaining elements of the right side
   // записываем оставшиеся элементы правой части
   while (j < nr) {
       arr[k] = right[j];
       j++;
       k++;
   }
}

void mergeSort(int *arr, long l, long r) {
    if (l >= r)
        return;    
    long m = (l + r - 1) / 2;

    if (make_thread && ((m - l) > 10000)) {
        auto f = std::async(std::launch::async, [&] () {
            mergeSort(arr, l, m);
        });
        mergeSort(arr, m + 1, r);
        //merge(arr, l, m, r);
    }
    else {
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        //merge(arr, l, m, r);
    }   
    merge(arr, l, m, r);     
}

int main(int argc, char** argv) {
// int arr[] = {5, 2, 7, 3, 22, 13, 6, 87, 15};
// int size = sizeof(arr) / sizeof(arr[0]);
// mergeSort(arr, 0, size -1);

// for (int i = 0; i < size; ++i)
// {
//     std::cout << arr[i] << " ";
// }

    srand(0);

    long arr_size = 1000000;
    int *array = new int[arr_size];

    for (long i = 0; i < arr_size; ++i) {
        array[i] = rand() % 500000;
    }

    // multithreaded launch многопоточный запуск
    auto begin = std::chrono::steady_clock::now();
    mergeSort(array, 0, arr_size);
    auto end = std::chrono::steady_clock::now();

    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "the time: " << elapsed_ms.count() << " ms\n";

    //sort check проверка сортировки
    for (long i = 0; i < arr_size - 1; ++i) {
        if(array[i] > array[i + 1]) {
             std::cout << "Unsorted" << std::endl;
             break;
        }
    }

    for(long i = 0; i < arr_size; i++) {
       array[i] = rand() % 500000;
    }

    // single threaded launch однопоточный запуск
    make_thread = false;

    begin = std::chrono::steady_clock::now();
    mergeSort(array, 0, arr_size);
    end = std::chrono::steady_clock::now();

    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "the time: " << elapsed_ms.count() << " ms\n";

    delete [] array;
    return 0;
}