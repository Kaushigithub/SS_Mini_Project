#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "structures.c"

int main() 
{
    int client_socket;
    struct sockaddr_in server_addr;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    // (error checking code...)

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // (error checking code...)

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error connecting to server");
        exit(1);
    }

    printf("Successfully created connection with server.\n");

    //recieving main menu prompt and writing to standard output
    char buf[200];
    int recvdata = recv(client_socket,&buf,sizeof(buf),0);
    int writedata = write(1,buf,recvdata);
    
    //taking user choice to login as
    char choiceprompt[] ="\nEnter your choice : ";
    writedata = write(1,choiceprompt,sizeof(choiceprompt));

    char readchoice;
    int choice = read(0,&readchoice,sizeof(readchoice));

    //sending choice to server
    int senddata = send(client_socket,&readchoice,sizeof(readchoice),0);

    if(readchoice=='1')
    {
     char server_response_admin[512];
     memset(server_response_admin,'\0',512*sizeof(char));
     recv(client_socket, &server_response_admin, sizeof(server_response_admin), 0);
     while(1)
     {
        printf("%s",server_response_admin);
    
        char choice_admin;
        printf("\nEnter your choice admin: ");
        scanf(" %c", &choice_admin);
        send(client_socket, &choice_admin, sizeof(choice_admin), 0);
        if(choice_admin=='9') break;
        //add student
        if(choice_admin=='1')
        {
        // struct StudentDetail newStudent;
            char buffer[512],ques[30];
            memset(ques,0,sizeof(ques));
            recv(client_socket,ques,sizeof(ques),0);
            printf("%s",ques);
            memset(ques,0,sizeof(ques));
            scanf("%s",ques);
            scanf("%[^/\n]", ques);
            send(client_socket,ques,sizeof(ques),0);
            memset(ques,0,sizeof(ques));

            recv(client_socket,ques,sizeof(ques),0);
            printf("%s",ques);
            memset(ques,0,sizeof(ques));
            scanf("%s",ques);
            scanf("%[^/\n]", ques);
            send(client_socket,ques,sizeof(ques),0);
            memset(ques,0,sizeof(ques));

            recv(client_socket,ques,sizeof(ques),0);
            printf("%s",ques);
            memset(ques,0,sizeof(ques));
            scanf("%s",ques);
            scanf("%[^/\n]", ques);
            send(client_socket,ques,sizeof(ques),0);
            memset(ques,0,sizeof(ques));

            recv(client_socket,ques,sizeof(ques),0);
            printf("%s",ques);
            memset(ques,0,sizeof(ques));
            scanf("%s",ques);
            scanf("%[^/\n]", ques);
            send(client_socket,ques,sizeof(ques),0);
            memset(&ques,0,sizeof(ques));

            char server_response[512];
            recv(client_socket, server_response, sizeof(server_response), 0);
            printf("%s\n", server_response);
        }
        if(choice_admin=='2')
        {

            char idp[50];
            memset(idp,0,sizeof(idp));
            recv(client_socket,idp,sizeof(idp),0);
            printf("%s",idp);

            char sid[10];
            scanf("%s",sid);
            scanf("%[^/\n]", sid);
            send(client_socket,sid,sizeof(sid),0);

            char sdata[300];
            memset(sdata,0,sizeof(sdata));
            recv(client_socket,&sdata,sizeof(sdata),0);
            printf("%s",sdata);
        }
        if(choice_admin=='3')
        {
            // struct StudentDetail newStudent;
            char buffer1[800],ques1[30];
            memset(ques1,0,sizeof(ques1));

            recv(client_socket,ques1,sizeof(ques1),0);
            printf("%s",ques1);
            memset(ques1,0,sizeof(ques1));
            scanf("%s",ques1);
            scanf("%[^/\n]", ques1);
            send(client_socket,ques1,sizeof(ques1),0);
            memset(ques1,0,sizeof(ques1));

            recv(client_socket,ques1,sizeof(ques1),0);
            printf("%s",ques1);
            memset(ques1,0,sizeof(ques1));
            scanf("%s",ques1);
            scanf("%[^/\n]", ques1);
            send(client_socket,ques1,sizeof(ques1),0);
            memset(ques1,0,sizeof(ques1));

            recv(client_socket,ques1,sizeof(ques1),0);
            printf("%s",ques1);
            memset(ques1,0,sizeof(ques1));
            scanf("%s",ques1);
            scanf("%[^/\n]", ques1);
            send(client_socket,ques1,sizeof(ques1),0);
            memset(ques1,0,sizeof(ques1));

            recv(client_socket,ques1,sizeof(ques1),0);
            printf("%s",ques1);
            memset(ques1,0,sizeof(ques1));
            scanf("%s",ques1);
            scanf("%[^/\n]", ques1);
            send(client_socket,ques1,sizeof(ques1),0);
            memset(ques1,0,sizeof(ques1));

            recv(client_socket,ques1,sizeof(ques1),0);
            printf("%s",ques1);
            memset(ques1,0,sizeof(ques1));
            scanf("%s",ques1);
            scanf("%[^/\n]", ques1);
            send(client_socket,ques1,sizeof(ques1),0);
            memset(ques1,0,sizeof(ques1));

            char server_response1[512];
            recv(client_socket, server_response1, sizeof(server_response1), 0);
            printf("%s", server_response1);
        }
        if(choice_admin=='4')
        {

            char idp1[50];
            memset(idp1,0,sizeof(idp1));
            recv(client_socket,idp1,sizeof(idp1),0);
            printf("%s",idp1);

            char fid[10];
            scanf("%s",fid);
            send(client_socket,fid,sizeof(fid),0);

            char fdata[300];
            memset(fdata,0,sizeof(fdata));
            recv(client_socket,&fdata,sizeof(fdata),0);
            printf("%s",fdata);
        }
        if(choice_admin=='5')
        {
            char get_sid[50];
            memset(get_sid,0,sizeof(get_sid));
            recv(client_socket,get_sid,sizeof(get_sid),0);
            printf("%s",get_sid);
            memset(get_sid,0,sizeof(get_sid));
            scanf("%s",get_sid);
            send(client_socket,get_sid,sizeof(get_sid),0);
            memset(get_sid,0,sizeof(get_sid));
            char s_response[400];
            memset(s_response,0,sizeof(s_response));
            recv(client_socket,s_response,sizeof(s_response),0);
            printf("%s",s_response);
        }
        if(choice_admin=='6')
        {
            char get_sid1[50];
            memset(get_sid1,0,sizeof(get_sid1));
            recv(client_socket,get_sid1,sizeof(get_sid1),0);
            printf("%s",get_sid1);
            memset(get_sid1,0,sizeof(get_sid1));
            scanf("%s",get_sid1);
            send(client_socket,get_sid1,sizeof(get_sid1),0);
            memset(get_sid1,0,sizeof(get_sid1));
            char s_response1[400];
            memset(s_response1,0,sizeof(s_response1));
            recv(client_socket,s_response1,sizeof(s_response1),0);
            printf("%s",s_response1);
        }
        if(choice_admin=='7')
        {

            char get_id[30],set_id[30];
            // int set_id;
            memset(get_id,0,sizeof(get_id));
            recv(client_socket,get_id,sizeof(get_id),0);
            printf("%s",get_id);
            scanf("%s",set_id);
            scanf("%[^/\n]", set_id);
            send(client_socket,set_id,sizeof(int),0);

            char get_field[30],set_field[30];
            memset(get_field,0,sizeof(get_field));
            recv(client_socket,get_field,sizeof(get_field),0);
            printf("%s",get_field);
            scanf("%s",set_field);
            scanf("%[^/\n]", set_field);
            send(client_socket,set_field,sizeof(set_field),0);

            char get_value[30],set_value[30];
            memset(get_value,0,sizeof(get_value));
            recv(client_socket,get_value,sizeof(get_value),0);
            printf("%s",get_value);
            scanf("%s",set_value);
            scanf("%[^/\n]", set_value);
            send(client_socket,set_value,sizeof(set_value),0);

            char gotit[40];
            memset(gotit,0,sizeof(gotit));
            recv(client_socket,&gotit,sizeof(gotit),0);
            printf("%s",gotit);
        }
        if(choice_admin=='8')
        {

            char get_id[30],set_id[30];
            // int set_id;
            memset(get_id,0,sizeof(get_id));
            recv(client_socket,get_id,sizeof(get_id),0);
            printf("%s",get_id);
            scanf("%s",set_id);
            scanf("%[^/\n]", set_id);
            send(client_socket,set_id,sizeof(int),0);

            char get_field[30],set_field[30];
            memset(get_field,0,sizeof(get_field));
            recv(client_socket,get_field,sizeof(get_field),0);
            printf("%s",get_field);
            scanf("%s",set_field);
            scanf("%[^/\n]", set_field);
            send(client_socket,set_field,sizeof(set_field),0);

            char get_value[30],set_value[30];
            memset(get_value,0,sizeof(get_value));
            recv(client_socket,get_value,sizeof(get_value),0);
            printf("%s",get_value);
            scanf("%s",set_value);
            scanf("%[^/\n]", set_value);
            send(client_socket,set_value,sizeof(set_value),0);

            char gotit[40];
            memset(gotit,0,sizeof(gotit));
            recv(client_socket,&gotit,sizeof(gotit),0);
            printf("%s",gotit);
        }

    }
    } 
    if(readchoice=='2')
    {
        //faculty module
        char login_prompt[30];
        memset(&login_prompt,0,sizeof(login_prompt));
        char send_login_id[30];
        char password_prompt1[30];
        memset(&password_prompt1,0,sizeof(password_prompt1));
        char send_password[30];

        //recieving login prompt
        recv(client_socket,&login_prompt,sizeof(login_prompt),0);
        printf("%s",login_prompt);
  
        //sending login id
        scanf("%s",send_login_id);
        scanf("%[^/\n]", send_login_id);
        send(client_socket,send_login_id,sizeof(send_login_id),0);

        //recieving password prompt
        recv(client_socket,&password_prompt1,sizeof(password_prompt1),0);
        printf("%s",password_prompt1);
        
        //sending password
        scanf("%s",send_password);
        scanf("%[^/\n]", password_prompt1);
        send(client_socket,send_password,sizeof(send_password),0);

       //recieving valid value
       int valid;
       recv(client_socket,&valid,sizeof(valid),0);
       if(valid==1)
       {
        char result[37];
        memset(result,0,sizeof(result));
        recv(client_socket,&result,sizeof(result),0);
        printf("%s",result);
        //memset(&result,0,sizeof(result));
        
        //if login is successfull recieve faculty menu
        char server_response_faculty[512];
        memset(server_response_faculty,0,sizeof(server_response_faculty));
        recv(client_socket, &server_response_faculty, sizeof(server_response_faculty),0);
        while(1)
        {
            printf("%s",server_response_faculty);

            //taking choice from that admin menu
            char choice_faculty;
            printf("Enter your choice faculty: ");
            scanf(" %c", &choice_faculty);
            send(client_socket, &choice_faculty, sizeof(choice_faculty), 0);
            if(choice_faculty=='6') break;

            if(choice_faculty=='1')
            {
                int ack;
                while(1)
                {
                recv(client_socket,&ack,sizeof(ack),0);
                if(ack==0)break;
                struct CourseDetail course;
                recv(client_socket,&course,sizeof(course),0);
                printf("Course Id: %d\n",course.id);
                printf("Course Name: %s\n",course.course_name);
                printf("Department offering course: %s\n",course.dept);
                printf("Number of Seats: %d\n",course.no_seats);
                printf("Course credit: %d\n",course.course_credits);
                memset(&course,0,sizeof(course));
                }    
            }
            //add course
            if(choice_faculty=='2')
            {
            
                char buffer[512],fac_ques[30];
                memset(&fac_ques,0,sizeof(fac_ques));
                recv(client_socket,&fac_ques,sizeof(fac_ques),0);
                printf("%s",fac_ques);
                memset(fac_ques,0,sizeof(fac_ques));
                scanf("%s",fac_ques);
                scanf("%[^/\n]", fac_ques);
                send(client_socket,fac_ques,sizeof(fac_ques),0);
                memset(&fac_ques,0,sizeof(fac_ques));

                recv(client_socket,&fac_ques,sizeof(fac_ques),0);
                printf("%s",fac_ques);
                memset(fac_ques,0,sizeof(fac_ques));
                scanf("%s",fac_ques);
                scanf("%[^/\n]", fac_ques);
                send(client_socket,fac_ques,sizeof(fac_ques),0);
                memset(&fac_ques,0,sizeof(fac_ques));

                recv(client_socket,&fac_ques,sizeof(fac_ques),0);
                printf("%s",fac_ques);
                memset(fac_ques,0,sizeof(fac_ques));
                scanf("%s",fac_ques);
                scanf("%[^/\n]", fac_ques);
                send(client_socket,fac_ques,sizeof(fac_ques),0);
                memset(&fac_ques,0,sizeof(fac_ques));

                recv(client_socket,&fac_ques,sizeof(fac_ques),0);
                printf("%s",fac_ques);
                memset(fac_ques,0,sizeof(fac_ques));
                scanf("%s",fac_ques);
                scanf("%[^/\n]", fac_ques);
                send(client_socket,fac_ques,sizeof(fac_ques),0);
                memset(&fac_ques,0,sizeof(fac_ques));

                char fac_rec_msg[512];
                memset(fac_ques,0,sizeof(fac_ques));
                recv(client_socket, &fac_rec_msg, sizeof(fac_rec_msg), 0);
                printf("%s\n", fac_rec_msg);
            }
            
            if(choice_faculty=='3')
            {
                char delete_propmt[40];
                memset(delete_propmt,0,sizeof(delete_propmt));
                recv(client_socket,&delete_propmt,sizeof(delete_propmt),0);
                printf("%s",delete_propmt);

                //sending id to delete
                int sendId;
                scanf("%d",&sendId);
                
                send(client_socket,&sendId,sizeof(sendId),0);
            }
            if(choice_faculty=='4')
            {

                char get_id[30],set_id[30];
                memset(get_id,0,sizeof(get_id));
                recv(client_socket,get_id,sizeof(get_id),0);
                printf("%s",get_id);
                scanf("%s",set_id);
                scanf("%[^/\n]", set_id);
                send(client_socket,set_id,sizeof(sizeof(set_id)),0);

                char get_field[30],set_field[30];
                memset(get_field,0,sizeof(get_field));
                recv(client_socket,get_field,sizeof(get_field),0);
                printf("%s",get_field);
                scanf("%s",set_field);
                scanf("%[^/\n]", set_field);
                send(client_socket,set_field,sizeof(set_field),0);

                char get_value[30],set_value[30];
                memset(get_value,0,sizeof(get_value));
                recv(client_socket,get_value,sizeof(get_value),0);
                printf("%s",get_value);
                scanf("%s",set_value);
                scanf("%[^/\n]", set_value);
                send(client_socket,set_value,sizeof(set_value),0);

                char gotit[40];
                memset(gotit,0,sizeof(gotit));
                recv(client_socket,&gotit,sizeof(gotit),0);
                printf("%s",gotit);
            }
            if(choice_faculty=='5')
            {
                //recieving password prompt
                char recv_pasword[30];
                memset(recv_pasword,0,sizeof(recv_pasword));
                recv(client_socket,&recv_pasword,sizeof(recv_pasword),0);
                printf("%s",recv_pasword);

                //sending password of user
                char password[20];
                scanf("%s",password);
                send(client_socket,password,sizeof(password),0);

                char rec_result[30];
                memset(&rec_result,0,sizeof(rec_result));
                recv(client_socket,&rec_result,sizeof(rec_result),0);
                printf("%s",result);
            }
        }
    }

       else
       {
        char result[32];
        memset(result,0,sizeof(result));
        recv(client_socket,&result,sizeof(result),0);
        printf("%s",result);
       }
   }

   if(readchoice=='3')
    {
        //student module
        char login_prompt[30];
        memset(&login_prompt,0,sizeof(login_prompt));
        char send_login_id[30];
        char password_prompt[30];
        memset(&password_prompt,0,sizeof(password_prompt));
        char send_password[30];

        //recieving login prompt
        recv(client_socket,&login_prompt,sizeof(login_prompt),0);
        printf("%s",login_prompt);
  
        //sending login id
        scanf("%s",send_login_id);
        scanf("%[^/\n]", send_login_id);
        send(client_socket,send_login_id,sizeof(send_login_id),0);

        //recieving password prompt
        recv(client_socket,&password_prompt,sizeof(password_prompt),0);
        printf("%s",password_prompt);

        //sending password
        scanf("%s",send_password);
        scanf("%[^/\n]", send_password);
        send(client_socket,send_password,sizeof(send_password),0);

       //recieving valid value
       int valid;
       recv(client_socket,&valid,sizeof(valid),0);
       if(valid==1)
       {
        char result[35];
        recv(client_socket,&result,sizeof(result),0);
        printf("%s",result);
        
        //if login is successfull recieve student menu
        char server_response_student[512];
        memset(server_response_student,0,sizeof(server_response_student));
        recv(client_socket, &server_response_student, sizeof(server_response_student),0);

        while(1)
        {
        printf("%s",server_response_student);

        //take choice of function to execute
        int choice;
        printf("Enter your choice: ");
        scanf("%d",&choice);
        send(client_socket,&choice,sizeof(choice),0);
        if(choice==1)
        {
            int ack;
            while(1)
            {
              recv(client_socket,&ack,sizeof(ack),0);
              if(ack==0)break;
              struct CourseDetail course;
              recv(client_socket,&course,sizeof(course),0);
              printf("Course id: %d\n",course.id);
              printf("Course Name: %s\n",course.course_name);
              printf("Department offering course: %s\n",course.dept);
              printf("Number of Seats: %d\n",course.no_seats);
              printf("Course credit: %d\n",course.course_credits);
            }    
        }
        if(choice==2)
        {
            //recieve choice of course
            char course_id_prompt[40];
            recv(client_socket,&course_id_prompt,sizeof(course_id_prompt),0);
            printf("%s",course_id_prompt);

            //send courseid
            int course_id;
            scanf("%d",&course_id);
            send(client_socket,&course_id,sizeof(course_id),0); 

            char buff[30];
            recv(client_socket,&buff,sizeof(buff),0);
            printf("%s",buff);
        }
        if(choice==3)
        {
            //recieving course id prompt
            char denroll[45];
            recv(client_socket,&denroll,sizeof(denroll),0);
            printf("%s",denroll);

            //taking user choice for course id
            int course_id;
            scanf("%d",&course_id);
            send(client_socket,&course_id,sizeof(course_id),0);
        }
        if(choice==4)
        {
            int stu_ack;
            while(1)
            {
              recv(client_socket,&stu_ack,sizeof(stu_ack),0);
              if(stu_ack==0)break;
              struct EnrolledCourse stu_course;
              recv(client_socket,&stu_course,sizeof(stu_course),0);
              printf("Course id: %d\n",stu_course.course_id);
              printf("Course Name: %s\n",stu_course.course_name);
              printf("Student id: %d\n",stu_course.student_id);
              printf("Faculty id: %d\n",stu_course.fac_id);        
            }    
        }
        if(choice==5)
        {
            //recieving password prompt
            char recv_pasword_s[30];
            recv(client_socket,&recv_pasword_s,sizeof(recv_pasword_s),0);
            printf("%s",recv_pasword_s);

            //sending password of user
            char password_s[20];
            scanf("%s",password_s);
            send(client_socket,password_s,sizeof(password_s),0);

            char result_s[30];
            recv(client_socket,&result_s,sizeof(result_s),0);
            printf("%s",result_s);
        }
        if(choice==6) break;
        }
     }
       else
       {
        char result[32];
        recv(client_socket,&result,sizeof(result),0);
        printf("%s",result);
       }
    }  
    close(client_socket);
    return 0;
}
