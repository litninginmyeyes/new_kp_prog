#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_LENGTH 100

struct SoftwareForDoc {
    char name[MAX_LENGTH];
    char developer[MAX_LENGTH];
    int yearReleased;
    char exeption[MAX_LENGTH];
    char dateofRecord[MAX_LENGTH];
};

void writeDataToFile(struct SoftwareForDoc* data, int numRecords, char* filename);//Запись в файл
struct SoftwareForDoc* readDataFromFile(int* numRecords, char* filename);//Чтение из файла
void displayData(struct SoftwareForDoc* data, int numRecords);//Вывод данных
struct SoftwareForDoc* searchData(struct SoftwareForDoc* data, int numRecords, struct SoftwareForDoc key);//Поиск 
void addRecord(struct SoftwareForDoc** data, int* numRecords, struct SoftwareForDoc newRecord);//Добавление записи
void digitalSort(struct SoftwareForDoc* array, int size);//Поразрядная сортировка 1
char findMaxChar(struct SoftwareForDoc* array, int size);//Поиск наибольшего элемента 1

int main() {
    setlocale(LC_ALL, "Russian");
    struct SoftwareForDoc* data = NULL;
    int numRecords = 0;
    int choice;
    char filename[MAX_LENGTH];
    int n = 0;

    printf("Введите имя файла: ");
    scanf("%s", filename);

    while (1) {
        printf("\n---------- Меню ----------\n");
        printf("1. Загрузка данных из файла\n");
        printf("2. Вывести данные\n");
        printf("3. Поиск записи\n");
        printf("4. Сортировка записей\n");
        printf("5. Сохранить данные в файл\n");
        printf("6. Добавить новую запись\n");
        printf("0. Выход\n");
        printf("Введите свой выбор: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            break;
        case 1:
        {
            data = readDataFromFile(&numRecords, filename);
            if (data != NULL) printf("Данные успешно загружены из файла.\n");

            break;
        }
        case 2:
        {
            if (data == NULL || numRecords == 0) printf("Нет данных для печати.\n");
            else displayData(data, numRecords);

            break;
        }
        case 3:
        {
            int searchChoice;
            struct SoftwareForDoc key = { "", 0, " ", " ", " " };

            printf("Выберите критерий поиска:\n");
            printf("1. Разработчик\n");
            printf("2. Год выпуска\n");
            printf("3. Расширение\n");
            printf("Введите свой выбор: ");
            scanf("%d", &searchChoice);

            switch (searchChoice)
            {
            case 1:
            {
                printf("Введите разработчика: ");
                scanf("%s", key.developer);
                break;
            }
            case 2:
            {
                printf("Введите год выпуска: ");
                scanf("%d", &key.yearReleased);
                break;
            }
            case 3:
            {
                printf("Введите расширение: ");
                scanf("%s", key.exeption);
                break;
            }
            }

            struct SoftwareForDoc* foundRecords = searchData(data, numRecords, key);
            int numFoundRecords = 0;
            for (int i = 0; i < numRecords; i++)
            {
                if (foundRecords[i].yearReleased == 0) break;
                numFoundRecords++;
            }

            printf("Найдено записей: %d\n", numFoundRecords);
            displayData(foundRecords, numFoundRecords);
            break;
        }
        case 4:
        {
            digitalSort(data, numRecords);
            displayData(data, numRecords);
            break;
        }
        case 5:
        {
            if (data == NULL || numRecords == 0) printf("Нет данных для сохранения.\n");
            else
            {
                writeDataToFile(data, numRecords, filename);
                printf("Данные успешно сохранены в файл.\n");
            }
            break;
        }
        case 6:
        {
            struct SoftwareForDoc newRecord;
            printf("Введите данные для новой записи:\n");
            printf("Разработчик: ");
            scanf("%s", newRecord.developer);
            printf("Год выпуска: ");
            scanf("%d", &newRecord.yearReleased);
            printf("Расширение: ");
            scanf("%s", newRecord.exeption);
            printf("Название: ");
            scanf("%s", newRecord.name);
            printf("Дата создания записи: ");
            scanf("%s", &newRecord.dateofRecord);
            addRecord(&data, &numRecords, newRecord);
            printf("Новая запись добавлена.\n");
            break;
        }
        default:
        {
            printf("Неправильный выбор. Пожалуйста, повторите попытку.\n");
            break;
        }
        }
        if (choice == 0) break;
    }
    free(data);
    return 0;
}


void writeDataToFile(struct SoftwareForDoc* data, int numRecords, char* filename) {
    FILE* file = fopen(filename, "a");

    if (data != NULL) {
        printf("Данные успешно загружены из файла.\n");
    }
    else if (file == NULL) {
        printf("Ошибка: Не удается открыть файл для записи.\n");
        return 0;
    }
    for (int i = 0; i < numRecords; i++) {
        fprintf(file, "%s %d %s %s %s\n", data[i].developer, data[i].yearReleased, data[i].exeption, data[i].name, data[i].dateofRecord);
    }
    fclose(file);
}

struct SoftwareForDoc* readDataFromFile(int* numRecords, char* filename) {
    FILE* file = fopen(filename, "r");
    char symbol;
    *numRecords = 0;
    if (file == NULL) {
        printf("Ошибка: Не удается открыть файл для чтения.\n");
        return NULL;
    }

    while (!feof(file))
    {
        fscanf(file, "%c", &symbol);
        if (symbol == '\n') *numRecords += 1;
    }
    *numRecords -= 1;
    struct SoftwareForDoc* data = (struct SoftwareForDoc*)malloc(*numRecords * sizeof(struct SoftwareForDoc));

    file = fopen(filename, "r");
    for (int i = 0; i < *numRecords; i++) {
        fscanf(file, "%s %d %s %s %s", data[i].developer, &data[i].yearReleased, data[i].exeption, data[i].name, &data[i].dateofRecord);
    }

    fclose(file);
    return data;
}

void displayData(struct SoftwareForDoc* data, int numRecords) {
    if (data == NULL) {
        printf("Нет данных для печати.\n");
    }
    else {
        printf("%-15s %-15s %-10s %-15s %-10s\n", "Разработчик", "Год выпуска", "Расширение", "Название", "Дата создания записи");
        for (int i = 0; i < numRecords; i++) {
            printf("%-15s %-15d %-10s %-15s %-10s\n", data[i].developer, data[i].yearReleased, data[i].exeption, data[i].name, data[i].dateofRecord);
        }
    }
}

struct SoftwareForDoc* searchData(struct SoftwareForDoc* data, int numRecords, struct SoftwareForDoc key) {
    struct SoftwareForDoc* foundRecords = (struct SoftwareForDoc*)calloc(numRecords, sizeof(struct SoftwareForDoc));
    int count = 0;

    for (int i = 0; i < numRecords; i++) {
        if (strcmp(data[i].developer, key.developer) == 0) {
            foundRecords[count++] = data[i];
        }
        if (strcmp(data[i].exeption, key.exeption) == 0) {
            foundRecords[count++] = data[i];
        }
        if (data[i].yearReleased == key.yearReleased) {
            foundRecords[count++] = data[i];
        }
    }
    /*foundRecords[count].yearReleased = 0;*/
    return foundRecords;
}

void addRecord(struct SoftwareForDoc** data, int* numRecords, struct SoftwareForDoc newRecord) {
    (*numRecords)++;
    *data = (struct SoftwareForDoc*)realloc(*data, *numRecords * sizeof(struct SoftwareForDoc));
    (*data)[*numRecords - 1] = newRecord;
}

char findMaxChar(struct SoftwareForDoc* array, int size)
{
    char maxElement = 0;

    for (int i = 0; i < size; i++)
        if (array[i].name[0] > maxElement)
            maxElement = array[i].name[0];

    return maxElement;
}

void digitalSort(struct SoftwareForDoc* data, int numRecords)
{
    struct SoftwareForDoc* sortArray = malloc(sizeof(struct SoftwareForDoc) * numRecords);
    int digitNumber = 1;//Разряд кода символа
    char maxElement = findMaxChar(data, numRecords);//Максимальный(по коду) символ

    while ((int)maxElement / digitNumber > 0)
    {
        int arrayForSort[10] = { 0 };

        for (int i = 0; i < numRecords; i++)
            arrayForSort[(data[i].name[0] / digitNumber) % 10]++;

        for (int i = 1; i < 10; i++)
            arrayForSort[i] += arrayForSort[i - 1];

        for (int i = numRecords - 1; i >= 0; i--)
            sortArray[--arrayForSort[(data[i].name[0] / digitNumber) % 10]] = data[i];

        for (int i = 0; i < numRecords; i++)
            data[i] = sortArray[i];

        digitNumber *= 10;//Переход к следующему разряду
    }
    free(sortArray);
}
