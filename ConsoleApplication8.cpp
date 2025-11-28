#include <iostream>
#include <string>
using namespace std;

int** create_arr(int rows, int cols)
{
    int** x = new int* [rows];
    for (int i = 0; i < rows; i++)
        x[i] = new int[cols];
    return x;
}

void add_column(int** a, int rows, int& cols)
{
    for (int i = 0; i < rows; i++)
    {
        int* newrow = new int[cols + 1];

        for (int j = 0; j < cols; j++)
            newrow[j] = a[i][j];

        newrow[cols] = 0;
        delete[] a[i];
        a[i] = newrow;
    }
    cols++;
}

void delete_column(int** a, int rows, int& cols, int index)
{
    if (index < 0 || index >= cols) return;

    for (int i = 0; i < rows; i++)
    {
        int* newrow = new int[cols - 1];
        int k = 0;

        for (int j = 0; j < cols; j++)
        {
            if (j != index)
                newrow[k++] = a[i][j];
        }

        delete[] a[i];
        a[i] = newrow;
    }

    cols--;
}

void shift_rows(int** a, int rows, int cols, int times, bool right)
{
    times %= cols;

    while (times--)
    {
        for (int i = 0; i < rows; i++)
        {
            if (right)
            {
                int temp = a[i][cols - 1];
                for (int j = cols - 1; j > 0; j--)
                    a[i][j] = a[i][j - 1];
                a[i][0] = temp;
            }
            else
            {
                int temp = a[i][0];
                for (int j = 0; j < cols - 1; j++)
                    a[i][j] = a[i][j + 1];
                a[i][cols - 1] = temp;
            }
        }
    }
}

void shift_cols(int** a, int rows, int cols, int times, bool down)
{
    times %= rows;

    while (times--)
    {
        for (int j = 0; j < cols; j++)
        {
            if (down)
            {
                int temp = a[rows - 1][j];
                for (int i = rows - 1; i > 0; i--)
                    a[i][j] = a[i - 1][j];
                a[0][j] = temp;
            }
            else
            {
                int temp = a[0][j];
                for (int i = 0; i < rows - 1; i++)
                    a[i][j] = a[i + 1][j];
                a[rows - 1][j] = temp;
            }
        }
    }
}

int** transpose(int** a, int& rows, int& cols)
{
    int** t = create_arr(cols, rows);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            t[j][i] = a[i][j];

    return t;
}

string* create_names(int size)
{
    return new string[size];
}

string* create_phones(int size)
{
    return new string[size];
}

int find_by_name(string* names, int size, string name)
{
    for (int i = 0; i < size; i++)
        if (names[i] == name) return i;
    return -1;
}

int find_by_phone(string* phones, int size, string phone)
{
    for (int i = 0; i < size; i++)
        if (phones[i] == phone) return i;
    return -1;
}

void print(int** a, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            cout << a[i][j] << "\t";
        cout << endl;
    }
}

int main()
{
    int rows = 3, cols = 3;
    int** arr = create_arr(rows, cols);

    int c = 1;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            arr[i][j] = c++;

    cout << "Початкова матриця:\n";
    print(arr, rows, cols);

    add_column(arr, rows, cols);
    cout << "\nПісля додавання стовпця:\n";
    print(arr, rows, cols);

    delete_column(arr, rows, cols, 1);
    cout << "\nПісля видалення стовпця №1:\n";
    print(arr, rows, cols);

    shift_rows(arr, rows, cols, 1, true);
    cout << "\nПісля циклічного зсуву вправо:\n";
    print(arr, rows, cols);

    int** tr = transpose(arr, rows, cols);
    cout << "\nТранспонована матриця:\n";
    print(tr, cols, rows);

    int size = 3;
    string* names = create_names(size);
    string* phones = create_phones(size);

    names[0] = "Ivan";
    phones[0] = "123";

    names[1] = "Petro";
    phones[1] = "456";

    names[2] = "Oleh";
    phones[2] = "789";

    cout << "\nПошук 'Petro': індекс = " << find_by_name(names, size, "Petro") << endl;
    cout << "Пошук телефону '789': індекс = " << find_by_phone(phones, size, "789") << endl;

    return 0;
}
