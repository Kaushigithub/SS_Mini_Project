//#include<stdio.h>
struct StudentDetail
{
	int id;
	char name[50];
	char password[50];
    int age;
    char email[50];
    char address[50];
    int isactive;
};

struct FacultyDetail
{
	int id;
	char name[50];
	char password[50];
    char department[50];
    char designation[50];
    char email[50];
    char address[50];
};

struct CourseDetail
{
    int id;
    int fac_id;
    char course_name[50];
    char dept[50];
    int no_seats;
    int course_credits;
    int max_seats;
};

struct EnrolledCourse
{
	int student_id;
	int course_id;
	char course_name[50];
	int fac_id;
    int enrolled;
};
