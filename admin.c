#include <stdio.h>
#include "structures.c"
#include <sys/socket.h>
#include <fcntl.h>
#include<string.h>
#include <sys/stat.h>
void add_student(int client_socket) {

    int fd=open("Student.txt",O_RDWR);
    struct StudentDetail student;
    memset(&student,0,sizeof(student));
    char buff[30];

    struct stat info;
    fstat(fd, &info);

    if(info.st_size != 0)
    {
        lseek(fd,-(sizeof(struct StudentDetail)),SEEK_END);
        struct StudentDetail s;
        read(fd,&s,sizeof(struct StudentDetail));
        student.id = s.id + 1;
    }
    else
    {
        student.id= 1;
    }

    strcpy(student.password,"initial");
    // student.active=true;
    char msg1[]="Enter student name:";
    send(client_socket,&msg1,strlen(msg1),0);
    recv(client_socket,&buff,sizeof(buff),0);
    strcpy(student.name,buff);
    memset(&buff,0,sizeof(buff));

    char msg2[]="Enter student age:";
    send(client_socket,&msg2,strlen(msg2),0);
    recv(client_socket,&buff,sizeof(buff),0);
    student.age=atoi(buff);
    memset(&buff,0,sizeof(buff));

    char msg3[]="Enter student email:";
    send(client_socket,&msg3,strlen(msg3),0);
    recv(client_socket,&buff,sizeof(buff),0);
    strcpy(student.email,buff);
    memset(&buff,0,sizeof(buff));

    char msg4[]="Enter student address:";
    send(client_socket,&msg4,strlen(msg4),0);
    recv(client_socket,&buff,sizeof(buff),0);
    strcpy(student.address,buff);
    memset(&buff,0,sizeof(buff));
    
    lseek(fd,0,SEEK_END);
    write(fd,&student,sizeof(struct StudentDetail));

    printf("Id=%d\n",student.id);
    printf("name=%s\n",student.name);
    printf("password=%s\n",student.password);
    printf("age=%s\n",student.email);
    printf("address=%s\n",student.address);

    close(fd);

    // Send success message back to the client
    char successMsg[] = "Student added successfully.\n";
    send(client_socket, successMsg, sizeof(successMsg), 0);
}

void viewStudentDetails(int client_socket)
{
    int file = open("Student.txt", O_RDONLY | O_CREAT,0744);

    char idp[] = "Enter student id:\n";
    send(client_socket,&idp,strlen(idp),0);
    
    char st[10];
    int id;
    recv(client_socket,&st,sizeof(st),0);
    id=atoi(st);

    int offset = (id-1)*(sizeof(struct StudentDetail));
    struct StudentDetail sd;
    int seekdata = lseek(file,offset,SEEK_SET);
    int dread = read(file,&sd,sizeof(struct StudentDetail));
    char temp[10*sizeof(struct StudentDetail)];
    sprintf(temp,"\nStudent id: %d \nName: %s\nAge: %d\nEmail: %s\nAddress: %s\nStudent Activity Status: %d\n",sd.id,sd.name,sd.age,sd.email,sd.address,sd.isactive);

    send(client_socket,&temp,strlen(temp),0);
    close(file);
}

void add_faculty(int client_socket) {
    
    int fd=open("faculty.txt",O_RDWR);
    struct FacultyDetail faculty;
    memset(&faculty,0,sizeof(faculty));
    char buff1[30];

    struct stat file_info_faculty;
    fstat(fd, &file_info_faculty);

    if(file_info_faculty.st_size!=0)
    {
        lseek(fd,-(sizeof(struct FacultyDetail)),SEEK_END);
        struct FacultyDetail faculty_cpy;
        read(fd,&faculty_cpy,sizeof(struct FacultyDetail));
        faculty.id = faculty_cpy.id+1;
    }
    else
    {
        faculty.id= 1;
    }
    strcpy(faculty.password,"initial");
    // student.active=true;
    char msg1[]="Enter faculty name:";
    send(client_socket,&msg1,strlen(msg1),0);
    recv(client_socket,&buff1,sizeof(buff1),0);
    strcpy(faculty.name,buff1);
    memset(&buff1,0,sizeof(buff1));

    char msg2[]="Enter faculty department:";
    send(client_socket,&msg2,strlen(msg2),0);
    recv(client_socket,&buff1,sizeof(buff1),0);
    strcpy(faculty.department,buff1);
    memset(&buff1,0,sizeof(buff1));

    char msg3[]="Enter faculty email:";
    send(client_socket,&msg3,strlen(msg3),0);
    recv(client_socket,&buff1,sizeof(buff1),0);
    strcpy(faculty.email,buff1);
    memset(&buff1,0,sizeof(buff1));

    char msg4[]="Enter faculty address:";
    send(client_socket,&msg4,strlen(msg4),0);
    recv(client_socket,&buff1,sizeof(buff1),0);
    strcpy(faculty.address,buff1);
    memset(&buff1,0,sizeof(buff1));
    
    lseek(fd,0,SEEK_END);
    write(fd,&faculty,sizeof(struct FacultyDetail));

    printf("Id=%d\n",faculty.id);
    printf("Name=%s\n",faculty.name);
    printf("Password=%s\n",faculty.password);
    printf("Department=%s\n",faculty.department);
    printf("Email=%s\n",faculty.email);
    printf("Address=%s\n",faculty.address);

    close(fd);

    // Send success message back to the client
    char successMsg[] = "Faculty added successfully.\n";
    send(client_socket, successMsg, sizeof(successMsg), 0);
}

void viewFacultyDetails(int client_socket)
{
    int file = open("faculty.txt", O_RDONLY | O_CREAT,0744);

    char idp[] = "Enter faculty id:\n";
    send(client_socket,&idp,strlen(idp),0);
    
    char ft[10];
    int id;
    recv(client_socket,&ft,sizeof(ft),0);
    id=atoi(ft);

    int offset = (id-1)*(sizeof(struct FacultyDetail));
    struct FacultyDetail fd;
    int seekdata = lseek(file,offset,SEEK_SET);
    int dread = read(file,&fd,sizeof(struct FacultyDetail));
    char temp[10*sizeof(struct FacultyDetail)];
    sprintf(temp,"\nFaculty id: %d \nName: %s\nDepartment: %s\nEmail: %s\nAddress: %s\n",fd.id,fd.name,fd.department,fd.email,fd.address);

    send(client_socket,&temp,strlen(temp),0);
    close(file);   
}

void modify_student_details(int client_socket)
{
    int file = open("Student.txt", O_RDWR);
    if (file == -1) 
    {
        perror("Error in opening the file");
    }
    struct StudentDetail s;
    char buff2[30];
    char msg1[]="Enter student id:";
    send(client_socket,msg1,strlen(msg1),0);
    recv(client_socket,&buff2,sizeof(buff2),0);
    int sid=atoi(buff2);
    printf("Received id:%d\n",sid);
    
    //set the cursor to the end of the previous record
    int offset=(sid-1)*sizeof(struct StudentDetail);
    lseek(file,offset,SEEK_SET);
    //read the structure
    read(file,&s,sizeof(struct StudentDetail));
    printf("Id=%d\n",s.id);
    printf("name=%s\n",s.name);
    printf("password=%s\n",s.password);
    printf("age=%d\n",s.age);
    printf("email=%s\n",s.email);
    printf("address=%s\n",s.address);

    char field[30];
    memset(&field,0,sizeof(field));
    char msg2[]="Enter field:";
    send(client_socket,msg2,strlen(msg2),0);
    recv(client_socket,&field,sizeof(field),0);
    printf("Received field:%s\n",field);
    
    char value[30];
    memset(&value,0,sizeof(value));
    char msg3[]="Enter value:";
    send(client_socket,msg3,strlen(msg3),0);
    recv(client_socket,&value,sizeof(value),0);
    printf("Received value:%s\n",value);
    
    //compare each value with field
    if(strcmp(field,"name")==0)
    {
        memset(&s.name,0,sizeof(s.name));
        memcpy(&s.name,&value,strlen(value));
    }
    else if(strcmp(field,"age")==0)
    {
        s.age=atoi(value);
    }
    else if(strcmp(field,"email")==0)
    {
        memset(&s.email,0,sizeof(s.email));
        memcpy(&s.email,&value,strlen(value));
    }
    else if(strcmp(field,"address")==0)
    {
        memset(&s.address,0,sizeof(s.address));
        memcpy(&s.address,&value,strlen(value));
    }
    printf("Id=%d\n",s.id);
    printf("name=%s\n",s.name);
    printf("password=%s\n",s.password);
    printf("age=%d\n",s.age);
    printf("email=%s\n",s.email);
    printf("address=%s\n",s.address);
    
    //write the data to the file
    lseek(file,offset,SEEK_SET);
    write(file,&s,sizeof(struct StudentDetail));
    
    char succ_send[]="Updation done successfully.\n";
    send(client_socket,succ_send,sizeof(succ_send),0);
    close(file);
    
}

void modify_faculty_details(int client_socket)
{
    int file = open("faculty.txt", O_RDWR);
    if (file == -1) {
        perror("Error opening file");
    }
    struct FacultyDetail fac1;
    char buff2[30];
    char msg4[]="Enter faculty id:";
    send(client_socket,msg4,strlen(msg4),0);
    recv(client_socket,&buff2,sizeof(buff2),0);
    int fid=atoi(buff2);
    printf("Received id:%d\n",fid);
    
    //set the cursor to the end of the previous record
    int offset=(fid-1)*sizeof(struct FacultyDetail);
    lseek(file,offset,SEEK_SET);
    //read the structure
    read(file,&fac1,sizeof(struct FacultyDetail));
    printf("Id=%d\n",fac1.id);
    printf("Name=%s\n",fac1.name);
    printf("Password=%s\n",fac1.password);
    printf("Department=%s\n",fac1.department);
    printf("Email=%s\n",fac1.email);
    printf("Address=%s\n",fac1.address);
    

    char fac_field[30];
    memset(&fac_field,0,sizeof(fac_field));
    char msg6[]="Enter field:";
    send(client_socket,msg6,strlen(msg6),0);
    recv(client_socket,&fac_field,sizeof(fac_field),0);
    printf("Received field:%s\n",fac_field);
    
    char fac_value[30];
    memset(&fac_value,0,sizeof(fac_value));
    char msg5[]="Enter value:";
    send(client_socket,msg5,strlen(msg5),0);
    recv(client_socket,&fac_value,sizeof(fac_value),0);
    printf("Received value:%s\n",fac_value);
    
    //compare each value with field
    if(strcmp(fac_field,"name")==0)
    {
        memset(&fac1.name,0,sizeof(fac1.name));
        memcpy(&fac1.name,&fac_value,strlen(fac_value));
    }
    else if(strcmp(fac_field,"department")==0)
    {
        memset(&fac1.department,0,sizeof(fac1.department));
        memcpy(&fac1.department,&fac_value,strlen(fac_value));
    }
    else if(strcmp(fac_field,"email")==0)
    {
        memset(&fac1.email,0,sizeof(fac1.email));
        memcpy(&fac1.email,&fac_value,strlen(fac_value));
    }
    else if(strcmp(fac_field,"address")==0)
    {
        memset(&fac1.address,0,sizeof(fac1.address));
        memcpy(&fac1.address,&fac_value,strlen(fac_value));
    }
    
    printf("Id=%d\n",fac1.id);
    printf("Name=%s\n",fac1.name);
    printf("Password=%s\n",fac1.password);
    printf("Department=%s\n",fac1.department);
    printf("Email=%s\n",fac1.email);
    printf("Address=%s\n",fac1.address);

    
    //write the data to the file
    lseek(file,offset,SEEK_SET);
    write(file,&fac1,sizeof(struct FacultyDetail));
    
    char fac_send[]="Updation done successfully.\n";
    send(client_socket,fac_send,sizeof(fac_send),0);
    close(file);
    
}

void activate_student(int client_socket)
{
    char student_id_str[10];
    int student_id;

    // Prompt the admin to enter the student's ID
    char prompt[] = "Enter the ID of the student to activate: ";
    send(client_socket, prompt, strlen(prompt), 0);
    recv(client_socket, student_id_str, sizeof(student_id_str), 0);
    student_id = atoi(student_id_str);

    // Open the student data file (Student.txt) for reading and writing
    int student_file = open("Student.txt", O_RDWR);
    // if (student_file == -1)
    // {
    //     char error_msg[] = "Error opening the student data file.";
    //     send(client_socket, error_msg, sizeof(error_msg), 0);
    //     close(student_file);
    //     return;
    // }

    // Calculate the offset to the student's data
    int offset = (student_id - 1) * sizeof(struct StudentDetail);

    // Seek to the student's data in the file
    int seek_result = lseek(student_file, offset, SEEK_SET);

    // if (seek_result == -1)
    // {
    //     char error_msg[] = "Error seeking to student data.";
    //     send(client_socket, error_msg, sizeof(error_msg), 0);
    //     close(student_file);
    //     return;
    // }

    // Read the student's data
    struct StudentDetail student;
    int read_result = read(student_file, &student, sizeof(struct StudentDetail));

    // if (read_result == -1)
    // {
    //     char error_msg[] = "Error reading student data.";
    //     send(client_socket, error_msg, sizeof(error_msg), 0);
    //     close(student_file);
    //     return;
    // }

    // Activate the student
    student.isactive = 1;

    // Seek back to the student's data and write the updated information
    int write_result = lseek(student_file, offset, SEEK_SET);
    // if (write_result == -1)
    // {
    //     char error_msg[] = "Error seeking to student data for writing.";
    //     send(client_socket, error_msg, sizeof(error_msg), 0);
    //     close(student_file);
    //     return;
    // }

    int write_result2 = write(student_file, &student, sizeof(struct StudentDetail));
    // if (write_result2 == -1)
    // {
    //     char error_msg[] = "Error writing student data.";
    //     send(client_socket, error_msg, sizeof(error_msg), 0);
    //     close(student_file);
    //     return;
    // }

    // Close the student data file
    close(student_file);

    // Send a success message to the admin
    char success_msg[] = "Student activated successfully.";
    send(client_socket, success_msg, sizeof(success_msg), 0);
}