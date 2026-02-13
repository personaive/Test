#include <iostream>
#include <ctime>
using namespace std;

// фаст сорт по убыванию
void sortDown(int arr[], int start, int end) {
    if (start >= end) return;
    // центральный элемент
    int centr = arr[end];
    // указатель для элементов больше центра
    int i = start - 1;

    // идем по массиву
    for (int j = start; j < end; j++) {
        if (arr[j] >= centr) {
            i++; // сдвигаем указатель
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // ставим центральный элемент на правильное место
    i++;
    int temp = arr[i];
    arr[i] = arr[end];
    arr[end] = temp;

    // теперь центральный элемент на позиции i
    int centrIndex = i;

    // реекурсивно сортируем левую и правую части
    sortDown(arr, start, centrIndex - 1);  // Левая часть
    sortDown(arr, centrIndex + 1, end);    // Правая часть
}

// фаст сорт по возрастанию
void sortUp(int arr[], int start, int end) {
    if (start >= end) return;

    int centr = arr[end];
    int i = start - 1;

    for (int j = start; j < end; j++) {
        if (arr[j] <= centr) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    i++;
    int temp = arr[i];
    arr[i] = arr[end];
    arr[end] = temp;

    int centrIndex = i;
    sortUp(arr, start, centrIndex - 1);
    sortUp(arr, centrIndex + 1, end);
}

int main() {
    srand(time(0));

    int n;
    cout << "Введите N: ";
    cin >> n;

    int* mainArr = new int[n];

    cout << "Массив: ";
    for (int i = 0; i < n; i++) {
        mainArr[i] = rand() % 41 - 20; // от -20 до 20
        cout << mainArr[i] << " ";
    }
    cout << endl;

    // + и -
    int PlusCount = 0;
    int OtricCount = 0;

    for (int i = 0; i < n; i++) {
        if (mainArr[i] > 0) PlusCount++;
        else if (mainArr[i] < 0) OtricCount++;
    }

    // создаём отдельные массивы
    int* PlusChisla = new int[PlusCount];
    int* OtricChisla = new int[OtricCount];

    int* IndexOsnovMassivePLUS = new int[PlusCount]; // где стояли положительные
    int* IndexOsnovMassiveOTRIC = new int[OtricCount]; // где стояли отрицательные

    // заполняем массивы
    int p = 0, q = 0; // счётчики

    for (int i = 0; i < n; i++) {
        if (mainArr[i] > 0) {
            PlusChisla[p] = mainArr[i];    // сохраняем значение
            IndexOsnovMassivePLUS[p] = i;  // сохраняем позицию
            p++;
        }
        else if (mainArr[i] < 0) {
            OtricChisla[q] = mainArr[i];    // сохраняем значение
            IndexOsnovMassiveOTRIC[q] = i;  // сохраняем позицию
            q++;
        }
    }

    // сортируем фаст сортом
    if (PlusCount > 0) {
        sortDown(PlusChisla, 0, PlusCount - 1); // положительные по убыванию
    }
    if (OtricCount > 0) {
        sortUp(OtricChisla, 0, OtricCount - 1);   // отрицательные по возрастанию
    }

    // возвращаем в основной массив
    for (int i = 0; i < PlusCount; i++) {
        mainArr[IndexOsnovMassivePLUS[i]] = PlusChisla[i];
    }
    for (int i = 0; i < OtricCount; i++) {
        mainArr[IndexOsnovMassiveOTRIC[i]] = OtricChisla[i];
    }

    cout << "Результат: ";
    for (int i = 0; i < n; i++) {
        cout << mainArr[i] << " ";
    }
    cout << endl;

    delete[] mainArr;
    delete[] PlusChisla;
    delete[] OtricChisla;
    delete[] IndexOsnovMassivePLUS;
    delete[] IndexOsnovMassiveOTRIC;

    return 0;
}