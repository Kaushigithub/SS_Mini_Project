#include <stdio.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "structures.c"
bool login_faculty(int client_socket,int id,char* password)
{
    printf("%d",id);
    printf("%s",password);
    int file=open("faculty.txt",O_RDONLY);
    struct FacultyDetail faculty;
    ssize_t read_result;
    int found=0;

    //reading file and checking if id and passwords match
    while(read(file,&faculty,sizeof(struct FacultyDetail)))
    {
        if(faculty.id==id)
        {
           if(strcmp(faculty.password,password)==0)
           {
            found=1;
            break;
           }
        }
    }
    close(file);
    return found;    
}

void add_course(int client_socket, int id) {

    int fd=open("course.txt",O_RDWR);
    struct CourseDetail course;
    memset(&course,0,sizeof(course));
    char buff[30];

    struct stat info;
    fstat(fd, &info);
    if(info.st_size != 0)
    {
        lseek(fd,-(sizeof(struct CourseDetail)),SEEK_END);
        struct CourseDetail c;
        read(fd,&c,sizeof(struct CourseDetail));
        course.id = c.id + 1;
        
    }
    else{
        course.id=1;
    }
    course.fac_id = id;
    
    // course.active=true;
    char msg1[]="Enter course name:";
    send(client_socket,&msg1,strlen(msg1),0);
    recv(client_socket,&buff,sizeof(buff),0);
    strcpy(course.course_name,buff);
    memset(&buff,0,sizeof(buff));

    char msg2[]="Enter course department:";
    send(client_socket,&msg2,strlen(msg2),0);
    recv(client_socket,&buff,sizeof(buff),0);
    strcpy(course.dept,buff);
    memset(&buff,0,sizeof(buff));

    char msg3[]="Enter number of seats:";
    send(client_socket,&msg3,strlen(msg3),0);
    recv(client_socket,&buff,sizeof(buff),0);
    course.no_seats=atoi(buff);
    memset(&buff,0,sizeof(buff));

    char msg4[]="Enter course credits:";
    send(client_socket,&msg4,strlen(msg4),0);
    recv(client_socket,&buff,sizeof(buff),0);
    course.course_credits=atoi(buff);
    memset(&buff,0,sizeof(buff));
    
    lseek(fd,0,SEEK_END);
    write(fd,&course,sizeof(struct CourseDetail));

    printf("Course Id=%d\n",course.id);
    printf("Course name=%s\n",course.course_name);
    printf("Department=%s\n",course.dept);
    printf("No. of seats=%d\n",course.no_seats);
    printf("Course credits=%d\n",course.course_credits);

    close(fd);

    // Send success message back to the client
    char successMsg[] = "Course added successfully.\n";
    send(client_socket, successMsg, sizeof(successMsg), 0);
}


void view_course(int client_socket,int id)
{
    //printf("hi\n");
    int fd=open("course.txt",O_RDWR);
    if(fd==-1)
    {
        perror("ERROR:");
    }
    struct CourseDetail course;
    int ack=1;
    printf("after 1\n");
    while(read(fd,&course,sizeof(course)))
    {
        if(course.fac_id==id)
        {
            printf("inside loop\n");
            ack=1;
            send(client_socket,&ack,sizeof(ack),0);
            send(client_socket,&course,sizeof(course),0);
            // send(client_socket,course.name,sizeof(course.name),0);
            // send(client_socket,&course.department,sizeof(course.department),0);
            // send(client_socket,&course.seat,sizeof(course.seat),0);
            // send(client_socket,&course.credit,sizeof(course.credit),0);
        }
    }
    ack=0;
    send(client_socket,&ack,sizeof(ack),0);
}

void delete_course_from_catalog(int client_socket,int id)
{
    int fd=open("course.txt",O_RDWR);
    struct CourseDetail course;
   
    int temp_fd = open("temp.txt", O_CREAT|O_RDWR|S_IRUSR|S_IWUSR,0777);
    
    //reading file and finding id to delete
    while(read(fd,&course,sizeof(course)))
    {
        if(course.id!=id)
        {
            write(temp_fd, &course,sizeof(struct CourseDetail));
        }
    }

    close(fd);
    close(temp_fd);

    remove("course.txt");
    rename("temp.txt", "course.txt");
}

void modify_course_details(int client_socket)
{
    int file = open("course.txt", O_RDWR);
    if (file == -1) {
        perror("Error in opening the file.");
    }
    struct CourseDetail detail;
    char course_buff[30];
    memset(&course_buff,0,sizeof(course_buff));
    char txt1[]="Enter course id:";
    send(client_socket,txt1,strlen(txt1),0);
    recv(client_socket,&course_buff,sizeof(course_buff),0);
    int course_id=atoi(course_buff);
    printf("Received id:%d\n",course_id);
    
    //set the cursor to the end of the previous record
    int offset=(course_id-1)*sizeof(struct CourseDetail);
    lseek(file,offset,SEEK_SET);
    //read the structure
    read(file,&detail,sizeof(struct CourseDetail));
    printf("id=%d\n",detail.id);
    printf("name=%s\n",detail.course_name);
    printf("department=%s\n",detail.dept);
    printf("seats=%d\n",detail.no_seats);
    printf("credit=%d\n",detail.course_credits);
    printf("faculty id=%d\n",detail.fac_id);

    char course_field[30];
    memset(&course_field,0,sizeof(course_field));
    char txt2[]="Enter field:";
    send(client_socket,txt2,strlen(txt2),0);
    recv(client_socket,&course_field,sizeof(course_field),0);
    printf("Received field:%s\n",course_field);
    
    char course_value[30];
    memset(&course_value,0,sizeof(course_value));
    char txt3[]="Enter value:";
    send(client_socket,txt3,strlen(txt3),0);
    recv(client_socket,&course_value,sizeof(course_value),0);
    printf("Received value:%s\n",course_value);
    
    //compare each value with field
    if(strcmp(course_field,"name")==0)
    {
        memset(&detail.course_name,0,sizeof(detail.course_name));
        memcpy(&detail.course_name,&course_value,strlen(course_value));
    }
    else if(strcmp(course_field,"seat")==0)
    {
        detail.no_seats=atoi(course_value);
    }
    else if(strcmp(course_field,"credit")==0)
    {
        detail.course_credits=atoi(course_value);
    }
    else if(strcmp(course_field,"department")==0)
    {
        memset(&detail.dept,0,sizeof(detail.dept));
        memcpy(&detail.dept,&course_value,strlen(course_value));
    }
    printf("id=%d\n",detail.id);
    printf("name=%s\n",detail.course_name);
    printf("department=%s\n",detail.dept);
    printf("seats=%d\n",detail.no_seats);
    printf("credit=%d\n",detail.course_credits);
    printf("faculty id=%d\n",detail.fac_id);
    
    //write the data to the file
    lseek(file,offset,SEEK_SET);
    write(file,&detail,sizeof(struct CourseDetail));
    
    char course_send[]="Course Details modified successfully.\n";
    send(client_socket,course_send,sizeof(course_send),0);
    close(file);
    
}

void change_password(int client_socket,int id,char* password)
{
    int fd=open("faculty.txt",O_RDWR);
    if(fd==-1)
    {
        perror("ERROR:");
    }
    struct FacultyDetail faculty;
    while(read(fd,&faculty,sizeof(faculty)))
    {
        if(faculty.id==id)
        {
            strcpy(faculty.password,password);
            printf("%s",faculty.password);
            lseek(fd, -sizeof(faculty), SEEK_CUR); // Move the file pointer back to the beginning of the record
            write(fd, &faculty, sizeof(faculty)); 
            char password[50]="Password changed successfully..";
            send(client_socket,password,sizeof(password),0);
            break; 
        }   
    }
}




