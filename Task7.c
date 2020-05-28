#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef
struct Student_{
    char name[256];
    int group;
    float rating;
    int IsElder;
}Student;
int Input(Student* Stud_array, FILE* file, int number_of_students);
int Output(Student* Stud_array, int number_of_students);
void alter(Student* Stud_array, int* number_of_students, int *mediana);

int Input(Student* Stud_array, FILE* file, int number_of_students){
    Student Tmp_student;
    int temp_group = 0;
    float temp_rating = 0;
    char temp_name[256];
    int temp_IsElder = 0;

    for (int i = 0; i  < number_of_students; i++){

        fscanf(file, "%s", &temp_name);
        fscanf(file, "%d", &temp_group);
        fscanf(file, "%g", &temp_rating);
        fscanf(file, "%d", &temp_IsElder);

        Stud_array[i].group = temp_group;
        Stud_array[i].rating = temp_rating;
        Stud_array[i].IsElder = temp_IsElder;
        strcpy(Stud_array[i].name, temp_name);

    }
    return 0;
}

int Output(Student* Stud_array, int number_of_students){
    for (int i = 0; i < number_of_students; i++){
        printf("%s  %d  %g %d\n", Stud_array[i].name, Stud_array[i].group, Stud_array[i].rating, Stud_array[i].IsElder);
    }
    return 0;
}

void alter(Student* Stud_array, int* number_of_students, int *mediana){
    Student Temp_student;
    printf("%d\n", *mediana);
    for (int j = 0; j < *number_of_students; j++){
           Stud_array[j].IsElder = 0;
           if (Stud_array[j].rating == *mediana){
           Stud_array[j].IsElder = 1;
            }
    }
}


int main(void){
    FILE* input_file;
    Student* Stud_array;
    int number_of_students = 0;
    char count_temp[512];
    int  mediana;
    int* tmp_array;

    input_file = fopen("data.txt", "r");
    if (!input_file){
        printf("Невозможно открыть файл\n");
        exit(-1);
    }

    while (fgets(count_temp, sizeof(count_temp), input_file) != NULL){
        number_of_students++;
    }
    fseek(input_file, 0, 0);
    Stud_array = (Student*)malloc(number_of_students*sizeof(Student));
    if (Stud_array==NULL)
    {
        printf("Невозможно выделить память\n");
        return 1;
    }

    Input(Stud_array, input_file, number_of_students);
    Output(Stud_array, number_of_students);
    printf("\n");

    tmp_array = (int*)malloc(number_of_students * sizeof(int));
    for(int i = 0; i < number_of_students; i++){
      tmp_array[i] = Stud_array[i].rating;
    }

    for (int j = 0; j < number_of_students-1; j++)
   {
         for(int i = 0; i < number_of_students-j-1; i++)
         {
             if (tmp_array[i] > tmp_array[i+1])
             {
                 int b = tmp_array[i];
                 tmp_array[i] = tmp_array[i+1];
                 tmp_array[i+1] = b;
             }
         }
     }
        if (number_of_students % 2){
            mediana = tmp_array[number_of_students/2];
          }
        else{
            mediana = tmp_array[number_of_students/2-1];
          }
          printf("%d\n", mediana);

    alter(Stud_array, &number_of_students, &mediana);

    Output(Stud_array, number_of_students);
    free(Stud_array);
    return 0;

}
