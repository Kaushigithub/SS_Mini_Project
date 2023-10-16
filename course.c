#include <stdio.h>
#include "structures.c"
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>


void add_course(int client_socket) {

    int fd=open("course.txt",O_WRONLY|O_CREAT,0744);
    struct CourseDetail course;
    memset(&course,0,sizeof(course));
    char buff[30];

    course.id=1;
    
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

