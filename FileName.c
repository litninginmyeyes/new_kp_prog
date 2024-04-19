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

void writeDataToFile(struct SoftwareForDoc* data, int numRecords, char* filename);//������ � ����
struct SoftwareForDoc* readDataFromFile(int* numRecords, char* filename);//������ �� �����
void displayData(struct SoftwareForDoc* data, int numRecords);//����� ������
struct SoftwareForDoc* searchData(struct SoftwareForDoc* data, int numRecords, struct SoftwareForDoc key);//����� 
void addRecord(struct SoftwareForDoc** data, int* numRecords, struct SoftwareForDoc newRecord);//���������� ������
void digitalSort(struct SoftwareForDoc* array, int size);//����������� ���������� 1
char findMaxChar(struct SoftwareForDoc* array, int size);//����� ����������� �������� 1

int main() {
    setlocale(LC_ALL, "Russian");
    struct SoftwareForDoc* data = NULL;
    int numRecords = 0;
    int choice;
    char filename[MAX_LENGTH];
    int n = 0;

    printf("������� ��� �����: ");
    scanf("%s", filename);

    while (1) {
        printf("\n---------- ���� ----------\n");
        printf("1. �������� ������ �� �����\n");
        printf("2. ������� ������\n");
        printf("3. ����� ������\n");
        printf("4. ���������� �������\n");
        printf("5. ��������� ������ � ����\n");
        printf("6. �������� ����� ������\n");
        printf("0. �����\n");
        printf("������� ���� �����: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            break;
        case 1:
        {
            data = readDataFromFile(&numRecords, filename);
            if (data != NULL) printf("������ ������� ��������� �� �����.\n");

            break;
        }
        case 2:
        {
            if (data == NULL || numRecords == 0) printf("��� ������ ��� ������.\n");
            else displayData(data, numRecords);

            break;
        }
        case 3:
        {
            int searchChoice;
            struct SoftwareForDoc key = { "", 0, " ", " ", " " };

            printf("�������� �������� ������:\n");
            printf("1. �����������\n");
            printf("2. ��� �������\n");
            printf("3. ����������\n");
            printf("������� ���� �����: ");
            scanf("%d", &searchChoice);

            switch (searchChoice)
            {
            case 1:
            {
                printf("������� ������������: ");
                scanf("%s", key.developer);
                break;
            }
            case 2:
            {
                printf("������� ��� �������: ");
                scanf("%d", &key.yearReleased);
                break;
            }
            case 3:
            {
                printf("������� ����������: ");
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

            printf("������� �������: %d\n", numFoundRecords);
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
            if (data == NULL || numRecords == 0) printf("��� ������ ��� ����������.\n");
            else
            {
                writeDataToFile(data, numRecords, filename);
                printf("������ ������� ��������� � ����.\n");
            }
            break;
        }
        case 6:
        {
            struct SoftwareForDoc newRecord;
            printf("������� ������ ��� ����� ������:\n");
            printf("�����������: ");
            scanf("%s", newRecord.developer);
            printf("��� �������: ");
            scanf("%d", &newRecord.yearReleased);
            printf("����������: ");
            scanf("%s", newRecord.exeption);
            printf("��������: ");
            scanf("%s", newRecord.name);
            printf("���� �������� ������: ");
            scanf("%s", &newRecord.dateofRecord);
            addRecord(&data, &numRecords, newRecord);
            printf("����� ������ ���������.\n");
            break;
        }
        default:
        {
            printf("������������ �����. ����������, ��������� �������.\n");
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
        printf("������ ������� ��������� �� �����.\n");
    }
    else if (file == NULL) {
        printf("������: �� ������� ������� ���� ��� ������.\n");
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
        printf("������: �� ������� ������� ���� ��� ������.\n");
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
        printf("��� ������ ��� ������.\n");
    }
    else {
        printf("%-15s %-15s %-10s %-15s %-10s\n", "�����������", "��� �������", "����������", "��������", "���� �������� ������");
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
    int digitNumber = 1;//������ ���� �������
    char maxElement = findMaxChar(data, numRecords);//������������(�� ����) ������

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

        digitNumber *= 10;//������� � ���������� �������
    }
    free(sortArray);
}
