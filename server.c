#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "admin.c"
#include "student.c"
#include "faculty.c"

void handle_client(int client_socket) {

    char string[20];
    char buff[] = "----------Welcome to Academia Portal----------\nChoose login type \n1. Admin\t 2. Faculty\t 3. Student\n";

    //sending menu to client
    int bytesSend = send(client_socket,&buff,sizeof(buff),0);

    //recieving choice from client
    int recvBytes = recv(client_socket,&string,sizeof(string),0);
    string[recvBytes] = '\0';
    int choice = atoi(string);

    switch(choice) {
    case 1:
        char menu_student[] = "\nWelcome to Admin Menu\nChoose from the following options\n 1) Add Student \n 2) View Student Details \n 3) Add Faculty\n 4) View Faculty Details\n 5) Activate Student\n 6) Block Student\n 7) Modify Student Details\n 8) Modify Faculty Details\n 9) Logout and Exit\n ";
        send(client_socket,menu_student,strlen(menu_student), 0);
        while(1)
        {
            //if choice is 1 send admin menu
            char student_choice;
            recv(client_socket, &student_choice,sizeof(student_choice), 0);
            //call to respective c functions
            if(student_choice=='1')
            {
                add_student(client_socket);
            }
            if(student_choice=='2')
            {
                viewStudentDetails(client_socket);
            }
            if(student_choice=='3')
            {
                add_faculty(client_socket);
            }
            if(student_choice=='4')
            {
                viewFacultyDetails(client_socket);
            }
            if(student_choice=='5')
            {
                activate_student(client_socket);
            }
            if(student_choice=='6')
            {
                block_student(client_socket);
            }
            if(student_choice=='7')
            {
                modify_student_details(client_socket);
            }
            if(student_choice=='8')
            {
                modify_faculty_details(client_socket);
            }
            if(student_choice=='9') break;
        }
        break;
    case 2:
        char login_prompt[]="Enter login id: ";
        char password_prompt[]="Enter password: ";
        char recv_login_id[30];
        char recv_password[30];
        //sending login prompt
        send(client_socket,login_prompt,strlen(login_prompt),0);

        //recieving login id
        recv(client_socket,&recv_login_id,sizeof(recv_login_id),0);
        int id=atoi(recv_login_id);
        printf("%d\n",id);

        //sending password prompt
        send(client_socket,password_prompt,strlen(password_prompt),0);

        //recieving password
        recv(client_socket,&recv_password,sizeof(recv_password),0);
        printf("%s\n",recv_password);
        
        //sending valid value to check if user is found or not
        int valid = login_faculty(client_socket,id,recv_password);
        send(client_socket,&valid,sizeof(valid),0);

        if(valid==1)
        {
            char result[]="Login done successfully....Welcome faculty....\n";
            send(client_socket,result,strlen(result),0);

            //if login is successfull send faculty menu
            char menu_faculty[] = "\nChoose from the following options\n 1) View Offering Courses\n 2) Add New Course\n 3) Remove Course From Catalog\n 4) Update Course Details\n 5) Change Password\n 6) Logout And Exit\n ";
            send(client_socket,menu_faculty,strlen(menu_faculty),0);
            
            while(1)
            {
                
                char faculty_choice;
                recv(client_socket, &faculty_choice,sizeof(faculty_choice), 0);
                
                if(faculty_choice=='1')
                {
                    view_course(client_socket,id);
                }
                if(faculty_choice=='2')
                {
                    add_course(client_socket,id);
                }
                if(faculty_choice=='3')
                {
                    //sending delete prompt 
                    char delete_prompt[]="Select course id you want to delete: ";
                    send(client_socket,delete_prompt,strlen(delete_prompt),0);

                    //recieving course id to delete
                    int c_id;
                    recv(client_socket,&c_id,sizeof(c_id),0);

                    delete_course_from_catalog(client_socket,c_id);
                }   
                if(faculty_choice=='4')
                {
                    modify_course_details(client_socket);
                }
                if(faculty_choice=='5')
                {
                    //asking password of user
                    char old_password[]="Enter password: ";
                    send(client_socket,old_password,strlen(old_password),0);
                    
                    //recieving password of user
                    char password[20];
                    recv(client_socket,&password,sizeof(password),0);
                    
                    change_password(client_socket,id,password);
                    
                }
                if(faculty_choice=='6') break;
            
            }
        }
        else
        {
            char result[]="Invalid Credentials..Try again.\n";
            send(client_socket,result,strlen(result),0);
        }

        break;
    
    case 3:
        char login_prompt1[]="Enter login id: ";
        char password_prompt1[]="Enter password: ";
        char recv_login_id1[30];
        char recv_password1[30];

        //sending login prompt
        send(client_socket,login_prompt1,strlen(login_prompt1),0);

        //recieving login id
        recv(client_socket,&recv_login_id1,sizeof(recv_login_id1),0);
        int id1=atoi(recv_login_id1);
        printf("%d\n",id1);

        //sending password prompt
        send(client_socket,password_prompt1,strlen(password_prompt1),0);

        //recieving password
        recv(client_socket,&recv_password1,sizeof(recv_password1),0);
        printf("%s\n",recv_password1);
        
        //sending valid value to check if user is found or not
        int valid1 = login_student(client_socket,id1,recv_password1);
        send(client_socket,&valid1,sizeof(valid1),0);

        if(valid1==1)
        {
            char result1[]="Login done successfully....Welcome Student...\n";
            send(client_socket,result1,strlen(result1),0);

            //if login is successfull send faculty menu
            char menu_student1[] = "\nChoose from the following options\n 1) View Courses\n 2) Enroll New Course\n 3) Drop Course\n 4) View Enrolled Course Details\n 5) Change Password\n 6) Logout And Exit\n";
            send(client_socket,menu_student1,strlen(menu_student1),0);
            
            while(1)
            {
            //recieve choice of student
            int student_choice1;
            recv(client_socket,&student_choice1,sizeof(student_choice1),0);
            if(student_choice1==1)
            {
                view_offered_courses_to_student(client_socket,id1);
            }
            if(student_choice1==2)
            {
                //courseid prompt
                send(client_socket,"Which course id you want to register? ",sizeof("Which course id you want to register? "),0);

                //recieve courseid
                int course_id1;
                recv(client_socket,&course_id1,sizeof(course_id1),0);

                enroll_course(client_socket,id1,course_id1);
            }
            if(student_choice1==3)
            {
                //asking the user which course they want to denroll
                send(client_socket,"Enter the course id you want to de-enroll for: ",sizeof("Enter the course id you want to denroll for: "),0);

                //recieving course id
                int course_id1;
                recv(client_socket,&course_id1,sizeof(course_id1),0);

                //calling de-enroll function
                denroll_student(client_socket,id1,course_id1);
            }
            if(student_choice1==4)
            {
                view_enrolled_course_details(client_socket,id1);
            }
            if(student_choice1==5)
            {
                //asking password of user
                char old_password1[]="Enter password: ";
                send(client_socket,old_password1,strlen(old_password1),0);
                
                //recieving password of user
                char password1[20];
                recv(client_socket,&password1,sizeof(password1),0);
                
                change_password_s(client_socket,id1,password1);
            }
            }
        }
        else
        {
            char result[]="Invalid Credentials...Try again.\n";
            send(client_socket,result,strlen(result),0);
        } 
        break;
    default:
        close(client_socket);
    }
        printf("\n");
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error creating socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding");
        exit(1);
    }

    if (listen(server_socket, 10) == 0) {
        printf("Server listening on port %d...\n", ntohs(server_addr.sin_port));
    } else {
        perror("Error listening");
        exit(1);
    }

    while (1) {
        addr_size = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);

        if (client_socket < 0) {
            perror("Error accepting client");
            exit(1);
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("Error forking");
            exit(1);
        } else if (pid == 0) {
            // Child process
            close(server_socket);
            handle_client(client_socket);
            exit(0);
        } else {
            // Parent process
            close(client_socket);
        }
    }
    return 0;
}