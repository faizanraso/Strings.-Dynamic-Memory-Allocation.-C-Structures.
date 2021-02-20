//QUESTION 2

#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int NO;
    int grades1,grades2;
    char firstname[15]; // these are kept to store the names of students
    char lastname[15]; // these are kept to store the names of students
    float finalmarks;
}

student;
student **create_class_list(char *filname, int *sizePtr);
int find(int idNo, student **list, int size);
void input_grades( char *filename, student **list, int size );
void compute_final_course_grades(student **list,int size);
void output_final_course_grades(char* out, student **list, int size);
void print_list(student** list, int size);
void withdraw(int idNo, student** list,int* sizePtr);
void destroy_list(student** list, int *sizePtr);


int main()
{
    student** ptr;
    int size;

    ptr = create_class_list("question2_students.txt",&size); //part 1

    //printf("%d",find(3480, ptr, size)); //part 2

    input_grades("question2_grades.txt", ptr, size);// part 3

    compute_final_course_grades(ptr,size); //part 4

    output_final_course_grades("outputfile.txt", ptr, size); //part 5

    //print_list(ptr, size);//part 6

    //withdraw(2019, ptr, &size); //part7

    //destroy_list(ptr, &size);//part 8
    print_list(ptr, size);


}

// PART 1
student **create_class_list(char *filename, int *sizePtr)
{
    FILE *textfile = fopen(filename, "r"); //initializes the opening of the text file
    fscanf(textfile, "%d", sizePtr); //reads the textfilfe
    if (textfile == NULL) //if the file DNE (NULL) returns following message
    {
        printf("Unable to open %s",filename);
        return 0;
    }
    student** newlist = malloc(*sizePtr*sizeof(student*)); //newlist will hold student id's and names and place to allocated method using malloc function
    int counter = 0;
    while (counter < *sizePtr)
    {
        newlist[counter] = calloc(1,sizeof(student));
        fscanf(textfile, "%d %s %s", &(newlist[counter]->NO), (newlist[counter]->firstname), (newlist[counter]->lastname));
        newlist[counter]->grades1 = 0;
        newlist[counter]->grades2 = 0;
        newlist[counter]->finalmarks = 0;//these lines initialized the starting valuyes of grades1, grades2 and finalmarks as 0 as requested in the lab
        counter ++;
    }
    return newlist;
}

//PART 2
int find(int idNo, student **list, int size)
{

  int counter = 0;
  int integer = -1;
  while (counter <size)
  {
    if (list[counter]->NO == idNo)
    {
        integer = counter;
        return integer; //returns position of the found idNo
    }
    counter++;
  }
  if (integer == -1) //returns -1 if idNo is not found
  {
      return integer;
  }
}

// PART 3
void input_grades( char *filename, student **list, int size )
{
    FILE *studentgrades = fopen(filename, "r");
    int counter, placeholder, idnumber;
    for (counter = 0; counter<size; counter++)
    {
        fscanf(studentgrades, "%d", &idnumber);
        placeholder = find(idnumber, list, size); //find function is to find the correspondin id number with grades to add to list
        fscanf(studentgrades,"%d %d",&(list[placeholder]->grades1),&(list[placeholder]->grades2)); //adds grades to corresponiding student to grades 1 and 2
        if (list[placeholder]->grades1 < 0)
        {
            list[placeholder]->grades1 = 0;
        }
        if (list[placeholder]->grades2 < 0)
        {
            list[placeholder]->grades2 = 0;
        }
    }
}


//PART 4
void compute_final_course_grades(student **list,int size)
{
    int counter = 0;
    while (counter<size)
    {
        list[counter]->finalmarks = (list[counter]->grades1 + list[counter]->grades2)/2.0; // takes grades1 and 2 and obtains their averaged saved to final grade
        counter ++;
    }
}

//PART 5
void output_final_course_grades(char* out, student **list, int size)
{
    FILE *outputfile = fopen(out, "w");
    fprintf(outputfile, "%d\n", size);
    for (int counter = 0; counter<size; counter++)
    {
        fprintf(outputfile, "%d %f\n", list[counter]->NO, list[counter]->finalmarks); //prints studnt id no and their final grades
    }
}

//PART 6
void print_list(student** list, int size)
{
    int counter = 0;
    while (counter<size) // function will print the required elements fot all students
    {
        printf("Student ID: %d, Name: %s %s, Grade 1: %d, Grade 2: %d, Final Mark: %f\n", list[counter]->NO,list[counter]->firstname,list[counter]->lastname,list[counter]->grades1, list[counter]->grades2,list[counter]->finalmarks);
        counter++;
    }
}
//PART 7
void withdraw(int idNo, student** list,int* sizePtr)
{
    int counter, counter2;
    counter = find(idNo, list, sizePtr);
    if (counter != *sizePtr -1)
    {
        counter2 = counter+1;
        while (counter2<*sizePtr)
        {
            list[counter2-1] = list[counter]; //moves all the "good locations"
            counter2++;
        }
    }
    *sizePtr = *sizePtr-1;
    free(&list[*sizePtr]); //frees the last spot in the list from memory
}

//PART 8
void destroy_list(student** list, int *sizePtr)
{
    int counter = 0;
    while (counter< *sizePtr)
    {
        free(&list[counter]); //frees up counter spot of list
        counter++;
    }
    free(&list); //free function clears up list
    *sizePtr = 0;
}


