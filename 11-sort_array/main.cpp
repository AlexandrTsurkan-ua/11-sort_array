#include <chrono>
#include <string>
#include <fstream>  // работа с файлами
#include <iostream>
#include <cstdlib> // для получения рандомных чисел
#include <ctime>

using namespace std;


void write_arr(const string& filename, const int* arr, const int n)
{
    fstream fs;

    fs.open(filename, fstream::out);
    if (fs.is_open()) // проверяем, что файл успешно открыт
    {
        fs << n << '\n';  // записываем размер массива
        for (int i = 0; i < n; i++)
            fs << arr[i] << ' '; // записываем значения через пробел
        fs << '\n';

        fs.close(); // закрываем файл
    }
}

void read_arr(const string& filename, int*& arr, int& n)
{
    fstream fs;

    fs.open(filename, fstream::in);
    if (fs.is_open()) // проверяем, что файл успешно открыт
    {
        fs >> n;  // читаем размер массива
        arr = new int[n];
        for (int i = 0; i < n; i++)
            fs >> arr[i]; // читаем из файла разделительные символы - пробел и перенос строки

        fs.close(); // закрываем файл
    }
}



int compare(const void* x1, const void* x2)   // функция сравнения элементов массива
{
    return (*(int*)x1 - *(int*)x2);              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}


// запись 2-х отсортированных массивов слиянием в один файл
void write_merger_arr(const string& filename, const int* arr1, const int size1, const int* arr2, const int size2)
{
    fstream fs;

    fs.open(filename, fstream::out);
    if (fs.is_open()) // проверяем, что файл успешно открыт
    {
        fs << size1 + size2 << '\n';  // записываем общий размер массивов

        int i = 0, j = 0; // переменные счетчики для цикла (i - первого массива, j - второго)

        for (; i < size1 && j < size2; )
        {
            if (arr1[i] < arr2[j]) // проверка какой элемент меньше
            {
                fs << arr1[i] << ' '; // запись элементов через пробел
                i++;
            }
            else
            {
                fs << arr2[j] << ' ';
                j++;
            }
        }

        for (i; i < size1; i++) // запись оставшихся элементов большего массива
        {
            fs << arr1[i] << ' ';
        }
        for (j; j < size2; j++)
        {
            fs << arr2[j] << ' ';
        }

        fs << '\n';

        fs.close(); // закрываем файл
    }
}

// слияние 2-х отсортированных массивов
void merger(int* arr1, const int size1, int* arr2, const int size2, int*& all_arr)
{
    int i = 0, j = 0, k = 0; // переменные счетчики для цикла (i - первого массива, j - второго, k - совмещенного)

    all_arr = new int[size1 + size2];

    for (; i < size1 && j < size2; k++)
    {
        if (arr1[i] < arr2[j])
        {
            all_arr[k] = arr1[i];
            i++;
        }
        else
        {
            all_arr[k] = arr2[j];
            j++;
        }
    }

    for (i; i < size1; i++)
    {
        all_arr[k] = arr1[i];
        k++;
    }
    for (j; j < size2; j++)
    {
        all_arr[k] = arr2[j];
        k++;
    }
}







int main()
{

    // обьявляем файлы
    string filename = "array_data.txt"; // для первого массива
    string filename2 = "array_data2.txt"; // для второго массива
    string filename3 = "array_data3.txt"; // для первого массива
    string filename4 = "array_data4.txt"; // для второго массива
    string filename5 = "all_array.txt"; // общий файл

    // обьявляем 4 первоначальных массива
    const int size = 131500000;
    int* rand_arr = new int[size];
    int* rand_arr2 = new int[size];
    int* rand_arr3 = new int[size];
    int* rand_arr4 = new int[size];



    srand(time(nullptr)); // используем текущее время, чтобы сгенерировать рандомные значения
    int lef_border = 5;
    int range_len = 1000; // правая граница = range_len + left_border



    // генерируем число в указанном диапазоне и записываем в массивы
    for (int i = 0; i < size; i++)
        rand_arr[i] = lef_border + rand() % range_len; // 1 массив

    for (int i = 0; i < size; i++)
        rand_arr2[i] = lef_border + rand() % range_len; // 2 массив

    for (int i = 0; i < size; i++)
        rand_arr3[i] = lef_border + rand() % range_len; // 3 массив

    for (int i = 0; i < size; i++)
        rand_arr4[i] = lef_border + rand() % range_len; // 4 массив


    // записываем массивы в файлы
    write_arr(filename, rand_arr, size); // 1 массив
    write_arr(filename2, rand_arr2, size); // 2 массив
    write_arr(filename3, rand_arr3, size); // 3 массив
    write_arr(filename4, rand_arr4, size); // 4 массив


    // читаем массивы из файлов
    int* array_from_file = nullptr;
    int m = 0;
    read_arr(filename, array_from_file, m); // из файла 1

    int* array_from_file2 = nullptr;
    int m2 = 0;
    read_arr(filename2, array_from_file2, m2); // из файла 2

    int* array_from_file3 = nullptr;
    int m3 = 0;
    read_arr(filename3, array_from_file3, m3); // из файла 3

    int* array_from_file4 = nullptr;
    int m4 = 0;
    read_arr(filename4, array_from_file4, m4); // из файла 4


    // сортировка массивов
    qsort(array_from_file, m, sizeof(int), compare); // 1 массив
    qsort(array_from_file2, m2, sizeof(int), compare); // 2 массив
    qsort(array_from_file3, m3, sizeof(int), compare); // 3 массив
    qsort(array_from_file4, m4, sizeof(int), compare); // 4 массив


    // объединение 1&2 и 3&4 массивов
    int* rand_all_arr = nullptr;
    int* rand_all_arr2 = nullptr;
    merger(array_from_file, m, array_from_file2, m2, rand_all_arr); // (объединение 1 и 2 массива)
    merger(array_from_file3, m3, array_from_file4, m4, rand_all_arr2); // (объединение 3 и 4 массива)


    // запись 2-х отсортированных массивов слиянием в один файл
    write_merger_arr(filename5, rand_all_arr, m + m2, rand_all_arr2, m3 + m4);




    delete[] rand_arr;
    delete[] rand_arr2;
    delete[] rand_arr3;
    delete[] rand_arr4;
    delete[] array_from_file;
    delete[] array_from_file2;
    delete[] array_from_file3;
    delete[] array_from_file4;
    delete[] rand_all_arr;
    delete[] rand_all_arr2;

    return 0;
}