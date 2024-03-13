#include <chrono>
#include <string>
#include <fstream>  // ������ � �������
#include <iostream>
#include <cstdlib> // ��� ��������� ��������� �����
#include <ctime>

using namespace std;


void write_arr(const string& filename, const int* arr, const int n)
{
    fstream fs;

    fs.open(filename, fstream::out);
    if (fs.is_open()) // ���������, ��� ���� ������� ������
    {
        fs << n << '\n';  // ���������� ������ �������
        for (int i = 0; i < n; i++)
            fs << arr[i] << ' '; // ���������� �������� ����� ������
        fs << '\n';

        fs.close(); // ��������� ����
    }
}

void read_arr(const string& filename, int*& arr, int& n)
{
    fstream fs;

    fs.open(filename, fstream::in);
    if (fs.is_open()) // ���������, ��� ���� ������� ������
    {
        fs >> n;  // ������ ������ �������
        arr = new int[n];
        for (int i = 0; i < n; i++)
            fs >> arr[i]; // ������ �� ����� �������������� ������� - ������ � ������� ������

        fs.close(); // ��������� ����
    }
}



int compare(const void* x1, const void* x2)   // ������� ��������� ��������� �������
{
    return (*(int*)x1 - *(int*)x2);              // ���� ��������� ��������� ����� 0, �� ����� �����, < 0: x1 < x2; > 0: x1 > x2
}


// ������ 2-� ��������������� �������� �������� � ���� ����
void write_merger_arr(const string& filename, const int* arr1, const int size1, const int* arr2, const int size2)
{
    fstream fs;

    fs.open(filename, fstream::out);
    if (fs.is_open()) // ���������, ��� ���� ������� ������
    {
        fs << size1 + size2 << '\n';  // ���������� ����� ������ ��������

        int i = 0, j = 0; // ���������� �������� ��� ����� (i - ������� �������, j - �������)

        for (; i < size1 && j < size2; )
        {
            if (arr1[i] < arr2[j]) // �������� ����� ������� ������
            {
                fs << arr1[i] << ' '; // ������ ��������� ����� ������
                i++;
            }
            else
            {
                fs << arr2[j] << ' ';
                j++;
            }
        }

        for (i; i < size1; i++) // ������ ���������� ��������� �������� �������
        {
            fs << arr1[i] << ' ';
        }
        for (j; j < size2; j++)
        {
            fs << arr2[j] << ' ';
        }

        fs << '\n';

        fs.close(); // ��������� ����
    }
}

// ������� 2-� ��������������� ��������
void merger(int* arr1, const int size1, int* arr2, const int size2, int*& all_arr)
{
    int i = 0, j = 0, k = 0; // ���������� �������� ��� ����� (i - ������� �������, j - �������, k - ������������)

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

    // ��������� �����
    string filename = "array_data.txt"; // ��� ������� �������
    string filename2 = "array_data2.txt"; // ��� ������� �������
    string filename3 = "array_data3.txt"; // ��� ������� �������
    string filename4 = "array_data4.txt"; // ��� ������� �������
    string filename5 = "all_array.txt"; // ����� ����

    // ��������� 4 �������������� �������
    const int size = 131500000;
    int* rand_arr = new int[size];
    int* rand_arr2 = new int[size];
    int* rand_arr3 = new int[size];
    int* rand_arr4 = new int[size];



    srand(time(nullptr)); // ���������� ������� �����, ����� ������������� ��������� ��������
    int lef_border = 5;
    int range_len = 1000; // ������ ������� = range_len + left_border



    // ���������� ����� � ��������� ��������� � ���������� � �������
    for (int i = 0; i < size; i++)
        rand_arr[i] = lef_border + rand() % range_len; // 1 ������

    for (int i = 0; i < size; i++)
        rand_arr2[i] = lef_border + rand() % range_len; // 2 ������

    for (int i = 0; i < size; i++)
        rand_arr3[i] = lef_border + rand() % range_len; // 3 ������

    for (int i = 0; i < size; i++)
        rand_arr4[i] = lef_border + rand() % range_len; // 4 ������


    // ���������� ������� � �����
    write_arr(filename, rand_arr, size); // 1 ������
    write_arr(filename2, rand_arr2, size); // 2 ������
    write_arr(filename3, rand_arr3, size); // 3 ������
    write_arr(filename4, rand_arr4, size); // 4 ������


    // ������ ������� �� ������
    int* array_from_file = nullptr;
    int m = 0;
    read_arr(filename, array_from_file, m); // �� ����� 1

    int* array_from_file2 = nullptr;
    int m2 = 0;
    read_arr(filename2, array_from_file2, m2); // �� ����� 2

    int* array_from_file3 = nullptr;
    int m3 = 0;
    read_arr(filename3, array_from_file3, m3); // �� ����� 3

    int* array_from_file4 = nullptr;
    int m4 = 0;
    read_arr(filename4, array_from_file4, m4); // �� ����� 4


    // ���������� ��������
    qsort(array_from_file, m, sizeof(int), compare); // 1 ������
    qsort(array_from_file2, m2, sizeof(int), compare); // 2 ������
    qsort(array_from_file3, m3, sizeof(int), compare); // 3 ������
    qsort(array_from_file4, m4, sizeof(int), compare); // 4 ������


    // ����������� 1&2 � 3&4 ��������
    int* rand_all_arr = nullptr;
    int* rand_all_arr2 = nullptr;
    merger(array_from_file, m, array_from_file2, m2, rand_all_arr); // (����������� 1 � 2 �������)
    merger(array_from_file3, m3, array_from_file4, m4, rand_all_arr2); // (����������� 3 � 4 �������)


    // ������ 2-� ��������������� �������� �������� � ���� ����
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