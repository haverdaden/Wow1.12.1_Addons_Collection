//GBMuploader v3.1 part of
//GuildToolS package v3.1
//Uploader for Marshall "Silverwings" Radziwilko's Guild Bank Manager.
//GBM is a php applet with MySQL DB that displayes all the data in 
//orgonized and well planned maner.
//
//Author: Roman Tarakanov (RTE/Arthas)
//Date: Sep 1 '06

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mysql.h"

//banker structure
struct banker {
  char name[20];
  int cash;
  char date[20];
};

//guild structure
struct guild {
  char name[20];
  char date[20];
};

int GBMupload(int argc, char **argv){
  //temp variables
  int i, desc_len=0;
  char buf[10000], tmp[50];
  char link[50000];
  //pipes
  FILE *in;
  //server config vars
  char HOST[101],USER[101],PASS[101],DB[101];
  int PORT=0;
  //sql variables
  MYSQL *sock;
  MYSQL_RES *res;
  MYSQL_ROW row;
  int totalq = 0, sucq = 0;
  //global variables
  int newowner=0;
  //bank
  char num[100], name[100], desc[10000], pic[100], type[100], id[10], subtype[100], owner[20];
  int quality, cost, numbankers = 0;
  struct banker bankers[100];
  //mail
  char sender[20], date[20];
  int minmailid, mailid;
  //roster
  int level, rankNum, prof1lvl, prof2lvl, numranks = -1;
  char clas[20], rank[20], prof1[50], prof2[50], main[30], ranks[30][30];
  struct guild guilds[10];
  int numguilds = 0;
  //config variables
  char LUAFILE[101]="../SV/GTS_Core.lua";
  char prefix[101] ="";
  prefix[0]='\0';
  char VER[7]="3.1";
  
  //reset vars to default
  HOST[0] = '\0';
  USER[0] = '\0';
  PASS[0] = '\0';
  DB[0] = '\0';
  buf[0]= '\0';
  
  //slash handler
  for (i=1; i<argc; i++)
  {
    if (strcmp(argv[i],"-host")==0 && i<argc-1)
    {
      if (strlen(argv[i+1])>100) argv[i+1][100]=0;
      strncpy(HOST, argv[i+1], strlen(argv[i+1]));
      HOST[strlen(argv[i+1])]=0;
      i++;
      continue;
    }
    if (strcmp(argv[i],"-port")==0 && i<argc-1)
    {
      PORT=strtol(argv[i+1], NULL, 10);
      i++;
      continue;
    }
    if (strcmp(argv[i],"-user")==0 && i<argc-1)
    {
      if (strlen(argv[i+1])>100) argv[i+1][100]=0;
      strncpy(USER, argv[i+1], strlen(argv[i+1]));
      USER[strlen(argv[i+1])]=0;
      i++;
      continue;
    }
    if (strcmp(argv[i],"-pass")==0 && i<argc-1)
    {
      if (strlen(argv[i+1])>100) argv[i+1][100]=0;
      strncpy(PASS, argv[i+1], strlen(argv[i+1]));
      PASS[strlen(argv[i+1])]=0;
      i++;
      continue;
    }
    if (strcmp(argv[i],"-db")==0 && i<argc-1)
    {
      if (strlen(argv[i+1])>100) argv[i+1][100]=0;
      strncpy(DB, argv[i+1], strlen(argv[i+1]));
      DB[strlen(argv[i+1])]=0;
      i++;
      continue;
    }
    if (strcmp(argv[i],"-file")==0 && i<argc-1)
    {
      if (strlen(argv[i+1])>100) argv[i+1][100]=0;
      strncpy(LUAFILE, argv[i+1], strlen(argv[i+1]));
      LUAFILE[strlen(argv[i+1])]=0;
      i++;
      continue;
    }
    if (strcmp(argv[i],"-prefix")==0 && i<argc-1)
    {
      if (strlen(argv[i+1])>100) argv[i+1][100]=0;
      strncpy(prefix, argv[i+1], strlen(argv[i+1]));
      prefix[strlen(argv[i+1])]=0;
      i++;
      continue;
    }
    if (strcmp(argv[i],"-?")==0 || strcmp(argv[i],"-help")==0)
    {
      printf("\nBankUploader v%s \nParses the data saved in ", VER); 
      printf("SavedVariables.lua by GTS_BankScan and uploads to GBM database.");
      printf("\n\nList of available flags:\n");
      printf("-file <string>   - sets the location of SV.lua file.\n");
      printf("                   Default: '../SV/GTS_Core.lua'\n");
      printf("-host <string>   - sets the host name to be used for upload.\n");
      printf("                   Default: 'localhost'\n");
      printf("-port <number>   - sets the port number to be used for upload.\n");
      printf("                   Default: default mysql port.\n");
      printf("-user <string>   - sets username to be used for upload.\n");
      printf("                   Default: current windows user name.\n");
      printf("-pass <string>   - sets password to be used for upload.\n");
      printf("                   Default: no password.\n");
      printf("-db <string>     - sets data base to be used for upload.\n");
      printf("                   Default: 'default'.\n");
      printf("-prefix <string> - sets the prefix to all table names in DB for GBM.\n");
      printf("                   Default: ''\n");
      printf("-?               - Prints this help message.\n");
      return 0;
    }
    printf("Improper use of arguments: check help (-?) for proper arguments list.\n");
    return 1;
  }
  
  //Open SavedVariables.lua file for reading
  printf("Opening file %s to read data ... ", LUAFILE);
  if ((in=fopen(LUAFILE,"rt")) == NULL)
  {
    printf("Failed.\n   Reson: Could not find input file.\n");
    printf("          Make sure that you specified proper file.\n");
    return 1;
  }else printf("Ok.\n");
  
  //Make sure there is data in file
  printf("Checking for data availability ... ");
  while ((fscanf(in, "%s", buf)!=EOF) && (strncmp(buf,"GTS_Data",9)!=0)) ;
  //If variables are not found - halt
  if (strncmp(buf,"GTS_Data",9) != 0)
  {
    printf("Failed.\n   Reson: Necessaryata was not found in SavedVariables.lua.\n");
    printf("          Make sure you run GTS_BankScan script first.\n");
    fclose(in);
    return 1;
  }else printf("Ok.\n");
  
  printf("Checking for data entry... ");
  fscanf(in, " = { ");
  fscanf(in, "%s",buf);
  //If variables are not found - halt
  if (strncmp(buf,"[\"OM\"]",4) != 0 && strncmp(buf,"[\"IM\"]",4) != 0 && 
      strncmp(buf,"[\"BS\"]",4) != 0 && strncmp(buf,"[\"GRS\"]",5) != 0)
  {
    printf("Failed.\n   Reson: Necessary data was not found in SavedVariables.lua.\n");
    printf("          Make sure you run GTS_BankScan script first.\n");
    fclose(in);
    return 1;
  }else printf("Ok.\n");
  
  //Initialize mysql protocol
  printf("Initializing mysql protocol ... ");
  if (!(sock=mysql_init(0)))
  {
    printf("Failed.\n    Reson: Couldn't initialize mysql protocol.\n");
    exit(1);
  }else printf("Ok.\n");
  
  //Connect to mysql server
  if (HOST[0] == '\0') strcpy(HOST, "localhost");
  printf("Connecting to '%s' as ", HOST);
  if (USER[0]=='\0') printf("'default' user on "); 
  else printf("'%s' on ",USER);
  if (PORT == 0) printf("'default' port ... ");
  else printf("port '%d' ... ",PORT);
  mysql_options(sock,MYSQL_READ_DEFAULT_GROUP,"connect");
  if (!mysql_real_connect(sock,HOST,USER,PASS,NULL,0,NULL,0))
  {
    printf("Failed.\n   Reson: %s\n",mysql_error(sock));
    perror("");
    exit(1);
  }else printf("Ok.\n");
  sock->reconnect= 1;
  
  //Connect to DB
  if (DB[0]=='\0') strcpy(DB,"default"); 
  printf("Connecting to Data Base '%s' ... ", DB);
  if (mysql_select_db(sock,DB)!=0)
  {
    printf("Failed.\n   Reson: %s\n", mysql_error(sock));
    exit(1);
  }else printf("Ok.\n");
  
  //Start scanning for data in SV.lua
  //untill the end of variables reached do:
  while (strncmp(buf, "}", 1)!=0)
  {
    //Find BankScan data
    //fprintf(stderr, "%s\n", buf);
    if (strncmp(buf,"[\"BS\"]",7) == 0) 
    {  
       fscanf(in, "%s", buf);
       while (strncmp(buf, "},", 2)!=0)
       { 
         //Reads the date scanned for all bank characters
         if (strncmp(buf,"[\"Date\"]",13)==0) 
         {
           while (strncmp(buf,"{",1)!=0) fscanf(in,"%s",buf);
           fscanf(in,"%s",buf);
           while (strncmp(buf, "},", 2)!=0)
           {
             char name[20],date[20];
             //Read the date of last parse
             fscanf(in, " = \" %s \",", date);
             //Read the name of bank char
             if (strstr(buf,"[\"")!=NULL && strstr(buf,"\"]")!=NULL)
             {
               strncpy(name, buf+2, strlen(buf)-4);
               name[strlen(buf)-4] = '\0';
             }
             for (i=0; i<numbankers; i++)
             {
               if (strcmp(name, bankers[i].name) == 0)
               {
                 strcpy(bankers[i].date, date);
                 break;
               }
             }
             if (strcmp(name, bankers[i].name) != 0)
             {
               strcpy(bankers[numbankers].date, date);
               strcpy(bankers[numbankers].name, name);   
               numbankers++;            
             }
             fscanf(in, "%s", buf);
           }  
         }
         
         //Reads the money in posession of bank characters
         if (strncmp(buf,"[\"Money\"]",10)==0) 
         {
           while (strncmp(buf,"{",1)!=0) fscanf(in,"%s",buf);
           fscanf(in,"%s",buf);
           while (strncmp(buf, "},", 2)!=0)
           {
             char name[20];
             int cash;
             //Read the cash of the char
             fscanf(in, " = \" %d \",", &cash);
             //Read the name of bank char
             if (strstr(buf,"[\"")!=NULL && strstr(buf,"\"]")!=NULL)
             {
               strncpy(name, buf+2, strlen(buf)-4);
               name[strlen(buf)-4] = '\0';
             }
             for (i=0; i<numbankers; i++)
             {
               if (strcmp(name, bankers[i].name) == 0)
               {
                 bankers[i].cash = cash;
                 break;
               }
             }
             if (strcmp(name, bankers[i].name) != 0)
             {
               bankers[numbankers].cash = cash; 
               strcpy(bankers[numbankers].name, name);  
               numbankers++;            
             }
             fscanf(in, "%s", buf);
           }
         }
         
         //Reads the items in posession of bank characters
         if (strncmp(buf,"[\"ScannedItems\"]",17)==0) 
         {
           fscanf(in, "%s", buf);
           while (strncmp(buf, "}", 1)!=0)
           {
             if (strstr(buf,"[\"")==NULL || strstr(buf,"\"]")==NULL) 
               fscanf(in, "%s", buf);
             if (strstr(buf,"[\"")!=NULL && strstr(buf,"\"]")!=NULL)
             {
               //Read the name of bank char
               strncpy(owner, buf+2, strlen(buf)-4);
               owner[strlen(buf)-4] = '\0';
               newowner=1;
               fscanf(in, " = { %s", buf);
               
               //Reset all the starage vars for item info before scanning
               quality=0;
               cost = 0;
               name[0]='\0';
               num[0]='\0';
               pic[0]='\0';
               desc[0]='\0';
               link[0]='\0';
               id[0] = '\0';
               type[0]='\0';
               subtype[0]='\0';
               
               //Scan item's info
               while (strncmp(buf, "},", 2)!=0)
               {
                 //Clear old data for this bunk char in DB
                 if (newowner==1)
                 {
                   newowner=0;
                   link[0]='\0';
                   printf("Updating bank content for %s ...\n", owner);
                   sprintf(link, "DELETE FROM `%sitems` WHERE owner='%s';", prefix, owner);
                   printf("Executing: %s ... ",link);
                   totalq++;
                   sucq++;
                   if(mysql_query(sock,link))
                   {
                     sucq--;
                     printf("Failed.\n   Reson: (%s)\n",mysql_error(sock));
                   } else printf("Ok.\n");
                   link[0]='\0';         
                 }
                 
                 //Actual item's scan
                 //Quantity
                 if (strncmp(buf, "[\"number\"]", 10)==0)
	             {
	               fscanf(in, " = \" %s \",", buf);
	               strncpy(num, buf, strlen(buf)+1);
                 }
                 //Price
                 if (strncmp(buf, "[\"price\"]", 9)==0)
	             {
	               fscanf(in, " = \" %d \",", &cost);
                 }
                 //Item ID
	             if (strncmp(buf, "[\"id\"]", 10)==0)
	             {
	               fscanf(in, " = \" %s \",", buf);
	               strncpy(id, buf, strlen(buf)+1);
	             }
	             //Quality
	             if (strncmp(buf, "[\"quality\"]", 11)==0)
	             {
	               fscanf(in, " = \" %d \",", &quality);
	             }
	             //Icon
	             if (strncmp(buf, "[\"pic\"]", 7)==0)
	             {
	               fscanf(in, " = \" %s \",", buf);
	               strncpy(pic, buf, strlen(buf)+1);
	             }
	             //Type
	             if (strncmp(buf, "[\"type\"]", 10)==0)
	             {
                    fscanf(in, " = \" %s", buf);
	               while (strncmp(buf, "\",", 2)!=0)
	               {
	                 if (type[0]!='\0')
	                 {
	                   strncat(type, " ", 1);
                     }
                     strncat(type, buf, strlen(buf)+1);
	                 fscanf(in, "%s", buf);
                   }
	             }
	             //Subtype
	             if (strncmp(buf, "[\"subtype\"]", 10)==0)
	             {
	               fscanf(in, " = \" %s", buf);
	               while (strncmp(buf, "\",", 2)!=0)
	               {
	                 if (subtype[0]!='\0')
	                 {
	                   strncat(subtype, " ", 1);
                     }
                     strncat(subtype, buf, strlen(buf)+1);
	                 fscanf(in, "%s", buf);
                   }
	             }
	             //Name
	             if (strncmp(buf, "[\"name\"]", 8)==0)
	             {
                   fscanf(in, " = \" %s", buf);
	               while (strncmp(buf, "\",", 2)!=0)
	               {
	                 if (name[0]!='\0')
	                 {
	                   strncat(name, " ", 1);
                     }
                     strncat(name, buf, strlen(buf)+1);
	                 fscanf(in, "%s", buf);
                   }
                 }
                 //Description
	             if (strncmp(buf, "[\"description\"]", 15)==0)
            	 {
            	   fscanf(in, " = \" %s", buf);
            	   while (strncmp(buf, "<n>", 3)!=0 && strncmp(buf, "\",", 2)!=0)
            	   {
            	     fscanf(in, "%s", buf);
            	   }
            	   while (strncmp(buf, "\",", 2)!=0)
            	   {
            	     if (strncmp(buf, "<n>", 3)==0)
            	     {
            	       strncat(desc, "<br>", 5);
            	       desc_len=0;
            	     }
            	     else
            	     if (strncmp(buf, "<t>", 3)==0)
            	     {
            	       for (i = desc_len; i<40; i++)
            		     strncat(desc, "&nbsp;", 7);
            	         strncat(desc, "\0", 1);
            	     }
            	     else if (strncmp(buf, "<c>", 3)==0)
           	         {
              	        strcat(desc, "</span><span style=\"font-size: 12px;color:#");
                        fscanf(in, "%s", buf);
                        strcat(desc, buf);
                        strcat(desc, ";\">");
              	        strncat(desc, "\0", 1);
     	             }
            	     else
            	     {
            	       strncat(desc, " ", 1);
            	       strncat(desc, buf, strlen(buf)+1);
            	       desc_len+=strlen(buf)+1;
            	     }
            	     fscanf(in, "%s", buf);
            	   }
            	 }
                 //End of variables list
                 
                 fscanf(in, "%s", buf);
                 //If all the variables have been scanned for this item - 
                 //send them to the DB
                 if (strncmp(buf, "},", 2)==0 && name[0]!='\0')
                 {                 
                   //Puts esc chars infront of every ' char in name
                   buf[0]='\0';
                   strcpy(buf, name);
                   name[0]='\0';
                   while(strchr(buf,'\'')!=NULL)
                   {
                     int pos,len;
                     pos = strlen(buf)-strlen(strchr(buf,'\''));
                     len = strlen(buf);
                     char a[100];
                     a[0]='\0';
                     strncpy(a,buf,pos);
                     a[pos]='\0';
                     strcat(name, a);
                     strcat(name, "\\'");
                     strncpy(buf, buf+pos+1, len-pos);                   
                   }
                   strcat(name, buf);
                   //Puts esc chars infront of every ' char in description
                   strcpy(buf, desc);
                   desc[0]='\0';
                 
                   while(strchr(buf,'\'')!=NULL)
                   {
                     int pos,len;
                     pos = strlen(buf)-strlen(strchr(buf,'\''));
                     len = strlen(buf);
                     char a[1000];
                     a[0]='\0';
                     strncpy(a,buf,pos);
                     a[pos]='\0';
                     strcat(desc, a);
                     strcat(desc, "\\'");
                     strncpy(buf, buf+pos+1, len-pos);                    
                   }
                   strcat(desc, buf);
                 
                   //Creates an sql statement to add the item into DB
                   link[0]='\0';
                   strcat(link, "INSERT INTO `");
                   strcat(link, prefix);
                   strcat(link, "items` ( `id` , `name` , `itemid`");
                   strcat(link, " , `quality` , `icon` , `tooltip` , `stock` ,");
                   strcat(link, " `type` , `subType` , `g` , `s`, `c` , `owner`");
                   strcat(link, " ) VALUES ( '', '");
                   strcat(link, name);
                   strcat(link, "', '");
                   strcat(link, id);
                   strcat(link, "', '");
                   sprintf(tmp, "%d", quality); strcat(link, tmp);
                   strcat(link, "', '");
                   strcat(link, pic);
                   strcat(link, "', '");
                   //description is actually html code of the tooltip
                   /* For posible future use
                   strcat(link,"<table width=200 border=0 cellpadding=0 cellspacing=0>");
                   strcat(link,"<tr><td><img src=images/items/top.gif></td></tr><tr>");
                   strcat(link,"<td><table width=200 border=0 cellspacing=0 ");
                   strcat(link,"cellpadding=0><tr><td width=19 background=");
                   strcat(link,"images/items/left.jpg>&nbsp;</td><td  bgcolor=#303030  valign=top>");
                   */
                   strcat(link,"<table bgcolor=\"#303030\" width=162 cellpadding=3 ");
                   strcat(link,"cellspacing=0 border=0 valign=top align=left><tr><td>");
                   strcat(link,"<span style=\"font-size: 12px;");
                   if (quality==0) strcat(link,"color:#9D9D9D;\"><b>");
                   if (quality==1) strcat(link,"color:#FFFFFF;\"><b>");
                   if (quality==2) strcat(link,"color:#1EFF00;\"><b>");
                   if (quality==3) strcat(link,"color:#0070DD;\"><b>");
                   if (quality==4) strcat(link,"color:#A335EE;\"><b>");
                   if (quality==5) strcat(link,"color:#EE9900;\"><b>");
                   strcat(link, name);
                   strcat(link,"</b></span><span style=\"font-size: 12px; color:white\">");
                   strcat(link, desc);
                   strcat(link,"</span></td></tr></table>");
                   /* For posible future use
                   strcat(link, "</td><td width=19 background=");
                   strcat(link, "images/items/right.jpg>&nbsp;</td></tr></table></td></tr><tr><td>");
                   strcat(link,"<img src=images/items/");
                   strcat(link,"bot.jpg width=200 height=19></td></tr></table>");
                   */
                   strcat(link, "', '");
                   strcat(link, num);
                   strcat(link, "', '");
                   strcat(link, type);
                   strcat(link, "', '");
                   strcat(link, subtype);
                   strcat(link, "', '");
                   sprintf(buf, "%d', '%d', '%d', '",cost/10000, (cost/100)%100, cost%100);
                   strcat(link, buf);
                   strcat(link, owner);
	               strcat(link, "');");
	               
	               //If sql statement was generated - send it to server
                   if (id[0]!='\0') 
                   {
                     printf("Executing: %s ... ", link);
                     totalq++;
                     sucq++;
                     if(mysql_query(sock,link))
                     {
                       sucq--;
                       printf("Failed.\n   Reson: (%s)\n",mysql_error(sock));
                     } else printf("Ok.\n");
                   }
                   
                   //reset store variables for the next scan
                   quality=0;
                   cost = 0;
                   name[0]='\0';
                   num[0]='\0';
                   pic[0]='\0';
                   desc[0]='\0';
                   id[0] = '\0';
                   type[0]='\0';
                   subtype[0]='\0';
                   link[0]='\0';
                   
                   fscanf(in, "%s", buf);
                 }
               }               
             }
             fscanf(in, "%s", buf);
		   }  
         }
         fscanf(in, "%s", buf);
       }                        
    }
    
    // ---------------- IM data ------------------
    if (strncmp(buf,"[\"IM\"]",7) == 0) 
    {  
       fscanf(in, "%s", buf);
       while (strncmp(buf, "},", 2)!=0)
       { 
         if (strncmp(buf,"[\"GlobalID\"]",13)==0) 
         {
           while (strncmp(buf, "},",2)!=0) 
             fscanf(in, "%s", buf);                                                  
         }
         //Reads the items in the log of current character
         if (strncmp(buf,"[\"ReceivedItems\"]",18)==0) 
         {
           fscanf(in, "%s", buf);
           while (strncmp(buf, "}", 1)!=0)
           {
             if (strstr(buf,"[\"")==NULL || strstr(buf,"\"]")==NULL) 
               fscanf(in, "%s", buf);
             if (strstr(buf,"[\"")!=NULL && strstr(buf,"\"]")!=NULL)
             {
               //Read the name of char
               strncpy(owner, buf+2, strlen(buf)-4);
               owner[strlen(buf)-4] = '\0';
               newowner=1;
               fscanf(in, " = { %s", buf);
               
               //Reset all the starage vars for item info before scanning
               quality=0;
               cost = 0;
               mailid = 0;
               sender[0] = '\0';
               date[0] = '\0';
               name[0]='\0';
               num[0]='\0';
               pic[0]='\0';
               desc[0]='\0';
               link[0]='\0';
               id[0] = '\0';
               type[0]='\0';
               subtype[0]='\0';
               minmailid = -1;
               
               //Scan item's info
               while (strncmp(buf, "},", 2)!=0)
               {
                 //Find the latest entry in DB for this char
                 if (newowner==1)
                 {
                   newowner=0;
                   link[0]='\0';
                   printf("Checking lates IM entry for %s ...\n", owner);
                   sprintf(link, "SELECT max(mailid) FROM `imail` WHERE owner='%s';",owner);
                   printf("Executing: %s ... ",link);
                   totalq++;
                   sucq++;
                   
                   if(mysql_query(sock,link))
                   {
                     sucq--;
                     printf("Failed.\n   Reson: (%s)\n",mysql_error(sock));
                   } else printf("Ok.\n"); 
                   res=mysql_use_result(sock);
                   int r,t;
                   for(r=0;r<mysql_field_count(sock);r++){
                     row=mysql_fetch_row(res);
                     if(row<0) break;
                     for(t=0;t<mysql_num_fields(res);t++){
                       sprintf(tmp,"%s",row[t]);
                       if (strncmp(tmp,"(null)",6)==0) 
                         minmailid = -1;
                       else
                         sscanf(tmp,"%d",&minmailid);
                     }
                   }
                   mysql_free_result(res);
                   link[0]='\0';         
                 }
                 
                 //Actual item's scan
                 //Quantity
                 if (strncmp(buf, "[\"number\"]", 10)==0)
	             {
	               fscanf(in, " = \" %s \",", buf);
	               strncpy(num, buf, strlen(buf)+1);
                 }
                 //Price
                 if (strncmp(buf, "[\"price\"]", 9)==0)
	             {
	               fscanf(in, " = \" %d \",", &cost);
                 }
                 //Mail id
                 if (strncmp(buf, "[\"globalid\"]", 12)==0)
	             {
	               fscanf(in, " = \" %d \",", &mailid);
                 }
	             //Item ID
	             if (strncmp(buf, "[\"id\"]", 10)==0)
	             {
	               fscanf(in, " = \" %s \",", buf);
	               strncpy(id, buf, strlen(buf)+1);
	             }
	             //Quality
	             if (strncmp(buf, "[\"quality\"]", 11)==0)
	             {
	               fscanf(in, " = \" %d \",", &quality);
	             }
	             //Icon
	             if (strncmp(buf, "[\"pic\"]", 7)==0)
	             {
	               fscanf(in, " = \" %s \",", buf);
	               strncpy(pic, buf, strlen(buf)+1);
	             }
	             //Date
	             if (strncmp(buf, "[\"date\"]", 8)==0)
	             {
	               fscanf(in, " = \" %s \",", buf);
	               strncpy(date, buf, strlen(buf)+1);
	             }
	             //Sender
	             if (strncmp(buf, "[\"from\"]", 8)==0)
	             {
	               fscanf(in, " = \" %s \",", buf);
	               strncpy(sender, buf, strlen(buf)+1);
	             }
	             //Type
	             if (strncmp(buf, "[\"type\"]", 10)==0)
	             {
                    fscanf(in, " = \" %s", buf);
	               while (strncmp(buf, "\",", 2)!=0)
	               {
	                 if (type[0]!='\0')
	                 {
	                   strncat(type, " ", 1);
                     }
                     strncat(type, buf, strlen(buf)+1);
	                 fscanf(in, "%s", buf);
                   }
	             }
	             //Subtype
	             if (strncmp(buf, "[\"subtype\"]", 10)==0)
	             {
	               fscanf(in, " = \" %s", buf);
	               while (strncmp(buf, "\",", 2)!=0)
	               {
	                 if (subtype[0]!='\0')
	                 {
	                   strncat(subtype, " ", 1);
                     }
                     strncat(subtype, buf, strlen(buf)+1);
	                 fscanf(in, "%s", buf);
                   }
	             }
	             //Name
	             if (strncmp(buf, "[\"name\"]", 8)==0)
	             {
                   fscanf(in, " = \" %s", buf);
	               while (strncmp(buf, "\",", 2)!=0)
	               {
	                 if (name[0]!='\0')
	                 {
	                   strncat(name, " ", 1);
                     }
                     strncat(name, buf, strlen(buf)+1);
	                 fscanf(in, "%s", buf);
                   }
                 }
	             //Description
	             if (strncmp(buf, "[\"description\"]", 15)==0)
            	 {
            	   fscanf(in, " = \" %s", buf);
            	   while (strncmp(buf, "<n>", 3)!=0 && strncmp(buf, "\",", 2)!=0)
            	   {
            	     fscanf(in, "%s", buf);
            	   }
            	   while (strncmp(buf, "\",", 2)!=0)
            	   {
            	     if (strncmp(buf, "<n>", 3)==0)
            	     {
            	       strncat(desc, "<br>", 5);
            	       desc_len=0;
            	     }
                     else if (strncmp(buf, "<c>", 3)==0)
           	         {
              	        strcat(desc, "</span><span style=\"font-size: 12px;color:#");
                        fscanf(in, "%s", buf);
                        strcat(desc, buf);
                        strcat(desc, ";\">");
              	        strncat(desc, "\0", 1);
     	             }
            	     else
            	     if (strncmp(buf, "<t>", 3)==0)
            	     {
            	       for (i = desc_len; i<40; i++)
            		     strncat(desc, "&nbsp;", 7);
            	       strncat(desc, "\0", 1);
            	     }
            	     else
            	     {
            	       strncat(desc, " ", 1);
            	       strncat(desc, buf, strlen(buf)+1);
            	       desc_len+=strlen(buf)+1;
            	     }
            	     fscanf(in, "%s", buf);
            	   }
            	 }
                 //End of variables list
                 
                 fscanf(in, "%s", buf);
                 //If all the variables have been scanned for this item - 
                 //send them to the DB
                 if (strncmp(buf, "},", 2)==0 && name[0]!='\0')
                 {
                   //Puts esc chars infront of every ' char in name
                   buf[0]='\0';
                   strcpy(buf, name);
                   name[0]='\0';
                   while(strchr(buf,'\'')!=NULL)
                   {
                     int pos,len;
                     pos = strlen(buf)-strlen(strchr(buf,'\''));
                     len = strlen(buf);
                     char a[100];
                     a[0]='\0';
                     strncpy(a,buf,pos);
                     a[pos]='\0';
                     strcat(name, a);
                     strcat(name, "\\'");
                     strncpy(buf, buf+pos+1, len-pos);                   
                   }
                   strcat(name, buf);
                   //Puts esc chars infront of every ' char in description
                   strcpy(buf, desc);
                   desc[0]='\0';
                   while(strchr(buf,'\'')!=NULL)
                   {
                     int pos,len;
                     pos = strlen(buf)-strlen(strchr(buf,'\''));
                     len = strlen(buf);
                     char a[100];
                     a[0]='\0';
                     strncpy(a,buf,pos);
                     a[pos]='\0';
                     strcat(desc, a);
                     strcat(desc, "\\'");
                     strncpy(buf, buf+pos+1, len-pos);                    
                   }
                   strcat(desc, buf);
                   
                   //Creates an sql statement to add the item into DB
                   link[0]='\0';
                   strcat(link, "INSERT INTO `");
                   strcat(link, prefix);
                   strcat(link, "imail` ( `id` , `name` , `itemid`");
                   strcat(link, " , `quality` , `icon` , `tooltip` , `stock` ,");
                   strcat(link, " `type` , `subType` , `g` , `s`, `c` , `owner`,");
                   strcat(link, " `sender`, `date`, `mailid`");
                   strcat(link, " ) VALUES ( '', '");
                   strcat(link, name);
                   strcat(link, "', '");
                   strcat(link, id);
                   strcat(link, "', '");
                   sprintf(tmp, "%d", quality); strcat(link, tmp);
                   strcat(link, "', '");
                   strcat(link, pic);
                   strcat(link, "', '");
                   //description is actually html code of the tooltip
                   strcat(link,"<table bgcolor=\"#303030\" width=162 cellpadding=3 ");
                   strcat(link,"cellspacing=0 border=0 valign=top align=left>");
                   strcat(link, "<tr><td><span style=\"font-size: 12px;");
                   if (quality==0) strcat(link,"color:#9D9D9D;\"><b>");
                   if (quality==1) strcat(link,"color:#FFFFFF;\"><b>");
                   if (quality==2) strcat(link,"color:#1EFF00;\"><b>");
                   if (quality==3) strcat(link,"color:#0070DD;\"><b>");
                   if (quality==4) strcat(link,"color:#A335EE;\"><b>");
                   if (quality==5) strcat(link,"color:#EE9900;\"><b>");
                   strcat(link, name);
                   strcat(link,"</b></span><span style=\"font-size: 12px; color:white\">");
                   strcat(link, desc);
                   strcat(link,"</td></tr></table>");
                   strcat(link, "', '");
                   strcat(link, num);
                   strcat(link, "', '");
                   strcat(link, type);
                   strcat(link, "', '");
                   strcat(link, subtype);
                   strcat(link, "', '");
                   sprintf(buf, "%d', '%d', '%d', '",cost/10000, (cost/100)%100, cost%100);
                   strcat(link, buf);
                   strcat(link, owner);
	               strcat(link, "', '");
                   strcat(link, sender);
                   strcat(link, "', '20");
                   strcat(link, date);
                   sprintf(buf, "', '%d');", mailid);
                   strcat(link, buf);
	               
	               //If sql statement was generated - send it to server
                   if (id[0]!='\0' && mailid>minmailid) 
                   {
                     printf("Executing: %s ... ", link);
                     totalq++;
                     sucq++;
                     
                     if(mysql_query(sock,link))
                     {
                       sucq--;
                       printf("Failed.\n   Reson: (%s)\n",mysql_error(sock));
                     } else printf("Ok.\n");
                   }
                   
                   //reset store variables for the next scan
                   quality=0;
                   cost = 0;
                   name[0]='\0';
                   num[0]='\0';
                   pic[0]='\0';
                   desc[0]='\0';
                   id[0] = '\0';
                   type[0]='\0';
                   subtype[0]='\0';
                   link[0]='\0';
                   
                   fscanf(in, "%s", buf);
                 }
               }               
             }
             fscanf(in, "%s", buf);
		   }  
         }
         fscanf(in, "%s", buf);
       }                        
    }
    //------------GRS----------------
    if (strncmp(buf,"[\"GRS\"]",8) == 0) 
    {  
       fscanf(in, "%s", buf);
       while (strncmp(buf, "},", 2)!=0)
       { 
         //Reads the date scanned for all guilds
         if (strncmp(buf,"[\"Date\"]",8)==0) 
         {
           while (strncmp(buf,"{",1)!=0) fscanf(in,"%s",buf);
           fscanf(in,"%s",buf);
           
           while (strncmp(buf, "},", 2)!=0)
           {
             char name[20],date[20];
             tmp[0] = '\0';
             strcpy(tmp, buf);
             while (strstr(tmp,"[\"")==NULL || strstr(tmp,"\"]")==NULL) 
             {
                     
               fscanf(in, "%s", buf);
               strcat(tmp, " ");
               strcat(tmp, buf);     
             }
             strcpy(buf, tmp);
             //Read the date of last parse
             fscanf(in, " = \" %s \",", date);
             //Read the name of bank char
             if (strstr(buf,"[\"")!=NULL && strstr(buf,"\"]")!=NULL)
             {
               strncpy(name, buf+2, strlen(buf)-4);
               name[strlen(buf)-4] = '\0';
             }
             for (i=0; i<numguilds; i++)
             {
               if (strcmp(name, guilds[i].name) == 0)
               {
                 strcpy(guilds[i].date, date);
                 break;
               }
             }
             if (strcmp(name, guilds[i].name) != 0)
             {
               strcpy(guilds[numguilds].date, date);
               strcpy(guilds[numguilds].name, name);   
               numguilds++;            
             }
             fscanf(in, "%s", buf);
           }  
         }
         
         //Reads the guild roster
         if (strncmp(buf,"[\"GuildRoster\"]",17)==0) 
         {
           fscanf(in, "%s", buf);
           while (strncmp(buf, "}", 1)!=0)
           {
             if (strstr(buf,"[\"")==NULL) 
               fscanf(in, "%s", buf);
             if (strstr(buf,"[\"")!=NULL)
             {
               tmp[0] = '\0';
               strcpy(tmp, buf);
               while (strstr(tmp,"[\"")==NULL || strstr(tmp,"\"]")==NULL) 
               {
                 
                 fscanf(in, "%s", buf);
                 strcat(tmp, " ");
                 strcat(tmp, buf);     
               }
               tmp[0]='\0';
               newowner=1;
               fscanf(in, " = { %s", buf);
               
               //Reset all the starage vars for item info before scanning
               level = 0;
               rankNum = 0;
               main[0] = '\0';
               prof1lvl = 0;
               prof2lvl = 0;
               clas[0] = '\0';
               rank[0] = '\0';
               name[0]='\0';
               prof1[0]='\0';
               prof2[0]='\0';
               
               //Scan item's info
               while (strncmp(buf, "},", 2)!=0)
               {
                 //Clear old data for characters in DB
                 if (newowner==1)
                 {
                   newowner=0;
                   link[0]='\0';
                   printf("Clearing existing DB table ...\n", owner);
                   sprintf(link, "UPDATE `%smembers` SET flag=1;", prefix);
                   printf("Executing: %s ... ",link);
                   totalq++;
                   sucq++;
                   
                   if(mysql_query(sock,link))
                   {
                     sucq--;
                     printf("Failed.\n   Reson: (%s)\n",mysql_error(sock));
                   } else printf("Ok.\n"); 
                   
                   link[0]='\0';     
                 }
                 
                 //Actual roster scan
                 //Class
                 if (strncmp(buf, "[\"class\"]", 10)==0)
	             {
	               fscanf(in, " = \" %s \",", buf);
	               strncpy(clas, buf, strlen(buf)+1);
                 }
                 //Level
                 if (strncmp(buf, "[\"level\"]", 9)==0)
	             {
	               fscanf(in, " = \" %d \",", &level);
                 }
                 //Rank number
                 if (strncmp(buf, "[\"rankNum\"]", 12)==0)
	             {
	               fscanf(in, " = \" %d \",", &rankNum);
                 }
	             //Rank
	             if (strncmp(buf, "[\"rank\"]", 8)==0)
	             {
                   fscanf(in, " = \" %s", buf);
                   while (strncmp(buf, "\",", 2)!=0)
                   {
                     if (rank[0]!='\0')
                     {
                       strncat(rank, " ", 1);
                     }
                     strncat(rank, buf, strlen(buf)+1);
                     fscanf(in, "%s", buf);
                   }
	             }
	             //Main-alt relation
	             if (strncmp(buf, "[\"main\"]", 8)==0)
	             {
	               fscanf(in, " = \" %s \",", buf);
	               strncpy(main, buf, strlen(buf)+1);
	             }
	             //Name
	             if (strncmp(buf, "[\"name\"]", 8)==0)
	             {
	               fscanf(in, " = \" %s \",", buf);
	               strncpy(name, buf, strlen(buf)+1);
	             }
	             //Profession 1
	             if (strncmp(buf, "[\"prof1\"]", 9)==0)
	             {
	               fscanf(in, " = \" %s", buf);
	               while (strncmp(buf, "\",", 2)!=0)
	               {
	                 strncat(prof1, buf, strlen(buf)+1);
	                 strcat(prof1," ");
	                 fscanf(in, "%s", buf);
                   }
                 }
	             //Profession 2
	             if (strncmp(buf, "[\"prof2\"]", 9)==0)
	             {
	               fscanf(in, " = \" %s", buf);
	               while (strncmp(buf, "\",", 2)!=0)
	               {
	                 strncat(prof2, buf, strlen(buf)+1);
	                 strcat(prof2," ");
	                 fscanf(in, "%s", buf);
                   }
                 }
                 //Profession 1 level
                 if (strncmp(buf, "[\"prof1lvl\"]", 12)==0)
	             {
	               fscanf(in, " = \" %d \",", &prof1lvl);
                 }
                 //Profession 2 level
                 if (strncmp(buf, "[\"prof2lvl\"]", 12)==0)
	             {
	               fscanf(in, " = \" %d \",", &prof2lvl);
                 }
                 //End of variables list
                 
                 fscanf(in, "%s", buf);
                 //If all the variables have been scanned for this character - 
                 //send them to the DB
                 if (strncmp(buf, "},", 2)==0 && name[0]!='\0')
                 {
                   //Creates an sql statement to add the character into DB
                   link[0]='\0';
                   int asd = 0;
                   
                   //Check if character is already in DB
                   printf("Checking lates GRS entry for %s ...\n", owner);
                   sprintf(link, "SELECT count(flag) FROM `members` WHERE name='%s';",name);
                   printf("Executing: %s ... ",link);
                   totalq++;
                   sucq++;
                   
                   if(mysql_query(sock,link))
                   {
                     sucq--;
                     printf("Failed.\n   Reson: (%s)\n",mysql_error(sock));
                   } else printf("Ok.\n"); 
                   res=mysql_use_result(sock);
                   
                   int r,t;
                   for(r=0;r<mysql_field_count(sock);r++){
                     row=mysql_fetch_row(res);
                     if(row<0) break;
                     for(t=0;t<mysql_num_fields(res);t++){
                       sprintf(tmp,"%s",row[t]);
                       if (strncmp(tmp,"(null)",6)==0) 
                         asd = -1;
                       else
                         sscanf(tmp,"%d",&asd);
                     }
                   }
                   
                   mysql_free_result(res);
                   link[0]='\0'; 
                   
                   //If cahracter with this name exist in DB - update entry,
                   //otherwise - add new entry
                   if (asd<=0) 
                   {
                     strcat(link, "INSERT INTO `");
                     strcat(link, prefix);
                     strcat(link, "members` ( `id` , `name` , `class`");
                     strcat(link, " , `lvl` , `ismain` , `main` , `prof1` ,");
                     strcat(link, " `prof2` , `prof1lvl` , `prof2lvl` , `rank`, `flag`");
                     strcat(link, " ) VALUES ( '', '");
                     strcat(link, name);
                     strcat(link, "', '");
                     strcat(link, clas);
                     strcat(link, "', '");
                     sprintf(buf, "%d", level);
                     strcat(link, buf);
                     strcat(link, "', '");
                     if (strcmp(main,"1") == 0) strcat(link, "1");
                     else strcat(link, "0");
                     strcat(link, "', '");
                     if (strcmp(main,"1") == 0) strcat(link, name);
                     else strcat(link, main);
                     strcat(link, "', '");
                     strcat(link, prof1);
                     strcat(link, "', '");
                     strcat(link, prof2);
                     strcat(link, "', '");
                     sprintf(buf, "%d", prof1lvl);
                     strcat(link, buf);
                     strcat(link, "', '");
                     sprintf(buf, "%d", prof2lvl);
                     strcat(link, buf);
                     strcat(link, "', '");
                     strcat(link, rank);
                     strcat(link, "', '0');");
                   }
                   else
                   {
                     strcat(link, "UPDATE `");
                     strcat(link, prefix);
                     strcat(link, "members` SET `name`='");
                     strcat(link, name);
                     strcat(link, "', `class`='");
                     strcat(link, clas);
                     strcat(link, "', `lvl`='");
                     sprintf(buf, "%d", level);
                     strcat(link, buf);
                     strcat(link, "', `ismain`='");
                     if (strcmp(main,"1") == 0) strcat(link, "1");
                     else strcat(link, "0");
                     strcat(link, "', `main`='");
                     if (strcmp(main,"1") == 0) strcat(link, name);
                     else strcat(link, main);
                     strcat(link, "', `prof1`='");
                     strcat(link, prof1);
                     strcat(link, "', `prof2`='");
                     strcat(link, prof2);
                     strcat(link, "', `prof1lvl`='");
                     sprintf(buf, "%d", prof1lvl);
                     strcat(link, buf);
                     strcat(link, "', `prof2lvl`='");
                     sprintf(buf, "%d", prof2lvl);
                     strcat(link, buf);
                     strcat(link, "', `rank`='");
                     strcat(link, rank);
                     strcat(link, "', `flag`='0' WHERE name='");   
                     strcat(link, name);
                     strcat(link, "';");
                   }
                   printf("Executing: %s ... ",link);
                   totalq++;
                   sucq++;
                   //Save rank-rank number relation in memory for further upload
                   strcpy(ranks[rankNum], rank);
                   if (numranks<=rankNum) numranks=rankNum;
                   
                   if(mysql_query(sock,link))
                   {
                     sucq--;
                     printf("Failed.\n   Reson: (%s)\n",mysql_error(sock));
                   } else printf("Ok.\n"); 
                   
                   
                   //reset store variables for the next scan
                   link[0]='\0';
                   level = 0;
                   rankNum = 0;
                   main[0] = '\0';
                   prof1lvl = 0;
                   prof2lvl = 0;
                   clas[0] = '\0';
                   rank[0] = '\0';
                   name[0]='\0';
                   prof1[0]='\0';
                   prof2[0]='\0';
                   
                   fscanf(in, "%s", buf);
                 }
               }               
             }
             fscanf(in, "%s", buf);
		   }  
         }
         fscanf(in, "%s", buf);
       }  
       //Post upload clean-up
       link[0]='\0';
       printf("Cleaning up DB ...\n", owner);
       sprintf(link, "UPDATE `%smembers` SET flag=2 WHERE flag=1;", prefix);
       printf("Executing: %s ... ",link);
       totalq++;
       sucq++;
       
       if(mysql_query(sock,link))
       {
         sucq--;
         printf("Failed.\n   Reson: (%s)\n",mysql_error(sock));
       } else printf("Ok.\n"); 
       
       link[0]='\0';                        
    }
    
    //--------------OM-----------------------------
    if (strncmp(buf,"[\"OM\"]",7) == 0) 
    {  
       fscanf(in, "%s", buf);
       while (strncmp(buf, "},", 2)!=0)
       { 
         
         if (strncmp(buf,"[\"GlobalID\"]",13)==0) 
         {
           while (strncmp(buf, "},",2)!=0) 
             fscanf(in, "%s", buf);                                                  
         }
         //Reads the items sent by current characters
         if (strncmp(buf,"[\"SentItems\"]",13)==0) 
         {
           fscanf(in, "%s", buf);
           while (strncmp(buf, "}", 1)!=0)
           {
             if (strstr(buf,"[\"")==NULL || strstr(buf,"\"]")==NULL) 
               fscanf(in, "%s", buf);
             if (strstr(buf,"[\"")!=NULL && strstr(buf,"\"]")!=NULL)
             {
               //Read the name of char
               strncpy(owner, buf+2, strlen(buf)-4);
               owner[strlen(buf)-4] = '\0';
               newowner=1;
               fscanf(in, " = { %s", buf);
               
               //Reset all the starage vars for item info before scanning
               quality=0;
               cost = 0;
               mailid = 0;
               sender[0] = '\0';
               date[0] = '\0';
               name[0]='\0';
               num[0]='\0';
               pic[0]='\0';
               desc[0]='\0';
               link[0]='\0';
               id[0] = '\0';
               type[0]='\0';
               subtype[0]='\0';
               minmailid = -1;
               
               //Scan item's info
               while (strncmp(buf, "},", 2)!=0)
               {
                 //Find the latest entry in the DB for current char
                 if (newowner==1)
                 {
                   newowner=0;
                   link[0]='\0';
                   printf("Checking lates OM entry for %s ...\n", owner);
                   sprintf(link, "SELECT max(mailid) FROM `omail` WHERE owner='%s';",owner);
                   printf("Executing: %s ... ",link);
                   totalq++;
                   sucq++;
                   
                   if(mysql_query(sock,link))
                   {
                     sucq--;
                     printf("Failed.\n   Reson: (%s)\n",mysql_error(sock));
                   } else printf("Ok.\n"); 
                   res=mysql_use_result(sock);
                   int r,t;
                   for(r=0;r<mysql_field_count(sock);r++){
                     row=mysql_fetch_row(res);
                     if(row<0) break;
                     for(t=0;t<mysql_num_fields(res);t++){
                       sprintf(tmp,"%s",row[t]);
                       if (strncmp(tmp,"(null)",6)==0) 
                         minmailid = -1;
                       else
                         sscanf(tmp,"%d",&minmailid);
                     }
                   }
                   mysql_free_result(res);
                   link[0]='\0';         
                 }
                 
                 //Actual item's scan
                 //Quantity
                 if (strncmp(buf, "[\"number\"]", 10)==0)
	             {
	               fscanf(in, " = \" %s \",", buf);
	               strncpy(num, buf, strlen(buf)+1);
                 }
                 //Price
                 if (strncmp(buf, "[\"price\"]", 9)==0)
	             {
	               fscanf(in, " = \" %d \",", &cost);
                 }
                 //Mail id
                 if (strncmp(buf, "[\"globalid\"]", 12)==0)
	             {
	               fscanf(in, " = \" %d \",", &mailid);
                 }
	             //Item ID
	             if (strncmp(buf, "[\"id\"]", 10)==0)
	             {
	               fscanf(in, " = \" %s \",", buf);
	               strncpy(id, buf, strlen(buf)+1);
	             }
	             //Quality
	             if (strncmp(buf, "[\"quality\"]", 11)==0)
	             {
	               fscanf(in, " = \" %d \",", &quality);
	             }
	             //Icon
	             if (strncmp(buf, "[\"pic\"]", 7)==0)
	             {
	               fscanf(in, " = \" %s \",", buf);
	               strncpy(pic, buf, strlen(buf)+1);
	             }
	             //Date
	             if (strncmp(buf, "[\"date\"]", 8)==0)
	             {
	               fscanf(in, " = \" %s \",", buf);
	               strncpy(date, buf, strlen(buf)+1);
	             }
	             //Recepient
	             if (strncmp(buf, "[\"to\"]", 6)==0)
	             {
	               fscanf(in, " = \" %s \",", buf);
	               strncpy(sender, buf, strlen(buf)+1);
	             }
	             //Type
	             if (strncmp(buf, "[\"type\"]", 10)==0)
	             {
                    fscanf(in, " = \" %s", buf);
	               while (strncmp(buf, "\",", 2)!=0)
	               {
	                 if (type[0]!='\0')
	                 {
	                   strncat(type, " ", 1);
                     }
                     strncat(type, buf, strlen(buf)+1);
	                 fscanf(in, "%s", buf);
                   }
	             }
	             //Subtype
	             if (strncmp(buf, "[\"subtype\"]", 10)==0)
	             {
	               fscanf(in, " = \" %s", buf);
	               while (strncmp(buf, "\",", 2)!=0)
	               {
	                 if (subtype[0]!='\0')
	                 {
	                   strncat(subtype, " ", 1);
                     }
                     strncat(subtype, buf, strlen(buf)+1);
	                 fscanf(in, "%s", buf);
                   }
	             }
	             //Name
	             if (strncmp(buf, "[\"name\"]", 8)==0)
	             {
                   fscanf(in, " = \" %s", buf);
	               while (strncmp(buf, "\",", 2)!=0)
	               {
	                 if (name[0]!='\0')
	                 {
	                   strncat(name, " ", 1);
                     }
                     strncat(name, buf, strlen(buf)+1);
	                 fscanf(in, "%s", buf);
                   }
                 }
	             //Description
	             if (strncmp(buf, "[\"description\"]", 15)==0)
            	 {
            	   fscanf(in, " = \" %s", buf);
            	   while (strncmp(buf, "<n>", 3)!=0 && strncmp(buf, "\",", 2)!=0)
            	   {
            	     fscanf(in, "%s", buf);
            	   }
            	   while (strncmp(buf, "\",", 2)!=0)
            	   {
            	     if (strncmp(buf, "<n>", 3)==0)
            	     {
            	       strncat(desc, "<br>", 5);
            	       desc_len=0;
            	     }
            	     else
            	     if (strncmp(buf, "<t>", 3)==0)
            	     {
            	       for (i = desc_len; i<40; i++)
            		     strncat(desc, "&nbsp;", 7);
            	       strncat(desc, "\0", 1);
            	     }
            	     else if (strncmp(buf, "<c>", 3)==0)
           	         {
              	        strcat(desc, "</span><span style=\"font-size: 12px;color:#");
                        fscanf(in, "%s", buf);
                        strcat(desc, buf);
                        strcat(desc, ";\">");
              	        strncat(desc, "\0", 1);
     	             }
            	     else
            	     {
            	       strncat(desc, " ", 1);
            	       strncat(desc, buf, strlen(buf)+1);
            	       desc_len+=strlen(buf)+1;
            	     }
            	     fscanf(in, "%s", buf);
            	   }
            	 }
                 //End of variables list
                 
                 fscanf(in, "%s", buf);
                 //If all the variables have been scanned for this item - 
                 //send them to the DB
                 if (strncmp(buf, "},", 2)==0 && name[0]!='\0')
                 {
                   //Puts esc chars infront of every ' char in name
                   buf[0]='\0';
                   strcpy(buf, name);
                   name[0]='\0';
                   while(strchr(buf,'\'')!=NULL)
                   {
                     int pos,len;
                     pos = strlen(buf)-strlen(strchr(buf,'\''));
                     len = strlen(buf);
                     char a[100];
                     a[0]='\0';
                     strncpy(a,buf,pos);
                     a[pos]='\0';
                     strcat(name, a);
                     strcat(name, "\\'");
                     strncpy(buf, buf+pos+1, len-pos);                   
                   }
                   strcat(name, buf);
                   //Puts esc chars infront of every ' char in description
                   strcpy(buf, desc);
                   desc[0]='\0';
                   while(strchr(buf,'\'')!=NULL)
                   {
                     int pos,len;
                     pos = strlen(buf)-strlen(strchr(buf,'\''));
                     len = strlen(buf);
                     char a[100];
                     a[0]='\0';
                     strncpy(a,buf,pos);
                     a[pos]='\0';
                     strcat(desc, a);
                     strcat(desc, "\\'");
                     strncpy(buf, buf+pos+1, len-pos);                    
                   }
                   strcat(desc, buf);
                   
                   //Creates an sql statement to add the item into DB
                   link[0]='\0';
                   strcat(link, "INSERT INTO `");
                   strcat(link, prefix);
                   strcat(link, "omail` ( `id` , `name` , `itemid`");
                   strcat(link, " , `quality` , `icon` , `tooltip` , `stock` ,");
                   strcat(link, " `type` , `subType` , `g` , `s`, `c` , `owner`,");
                   strcat(link, " `recepient`, `date`, `mailid`");
                   strcat(link, " ) VALUES ( '', '");
                   strcat(link, name);
                   strcat(link, "', '");
                   strcat(link, id);
                   strcat(link, "', '");
                   sprintf(tmp, "%d", quality); strcat(link, tmp);
                   strcat(link, "', '");
                   strcat(link, pic);
                   strcat(link, "', '");
                   //description is actually html code of the tooltip
                   strcat(link,"<table bgcolor=\"#303030\" width=162 cellpadding=3 ");
                   strcat(link,"cellspacing=0 border=0 valign=top align=left>");
                   strcat(link, "<tr><td><span style=\"font-size: 12px;");
                   if (quality==0) strcat(link,"color:#9D9D9D;\"><b>");
                   if (quality==1) strcat(link,"color:#FFFFFF;\"><b>");
                   if (quality==2) strcat(link,"color:#1EFF00;\"><b>");
                   if (quality==3) strcat(link,"color:#0070DD;\"><b>");
                   if (quality==4) strcat(link,"color:#A335EE;\"><b>");
                   if (quality==5) strcat(link,"color:#EE9900;\"><b>");
                   strcat(link, name);
                   strcat(link,"</b></span><span style=\"font-size: 12px; color:white\">");
                   strcat(link, desc);
                   strcat(link,"</td></tr></table>");
                   strcat(link, "', '");
                   strcat(link, num);
                   strcat(link, "', '");
                   strcat(link, type);
                   strcat(link, "', '");
                   strcat(link, subtype);
                   strcat(link, "', '");
                   sprintf(buf, "%d', '%d', '%d', '",cost/10000, (cost/100)%100, cost%100);
                   strcat(link, buf);
                   strcat(link, owner);
	               strcat(link, "', '");
                   strcat(link, sender);
                   strcat(link, "', '20");
                   strcat(link, date);
                   sprintf(buf, "', '%d');", mailid);
                   strcat(link, buf);
	               
	               //If sql statement was generated - send it to server
                   if (id[0]!='\0' && mailid>minmailid) 
                   {
                     printf("Executing: %s ... ", link);
                     totalq++;
                     sucq++;
                     
                     if(mysql_query(sock,link))
                     {
                       sucq--;
                       printf("Failed.\n   Reson: (%s)\n",mysql_error(sock));
                     } else printf("Ok.\n");
                   }
                   
                   //reset store variables for the next scan
                   quality=0;
                   cost = 0;
                   name[0]='\0';
                   num[0]='\0';
                   pic[0]='\0';
                   desc[0]='\0';
                   id[0] = '\0';
                   type[0]='\0';
                   subtype[0]='\0';
                   link[0]='\0';
                   
                   fscanf(in, "%s", buf);
                 }
               }               
             }
             fscanf(in, "%s", buf);
		   }  
         }
         fscanf(in, "%s", buf);
       }                        
    }

    fscanf(in, "%s", buf);
  }

  //Updates the banker's info: name, money, last scan date
  printf("Updating bankers information ... \n");
  for (i=0; i<numbankers; i++)
  {
    char query[200];
    
    sprintf(query,"SELECT name FROM bmembers WHERE name='%s'",bankers[i].name);
    if(mysql_query(sock,query))
    {
      printf("Failed.\n   Reson: Query failed (%s)\n",mysql_error(sock));
      continue;
    }
    if (!(res=mysql_store_result(sock)))
    {
      printf("Failed.\n   Reson: Couldn't get result from %s\n",
	      mysql_error(sock));
      continue;
    } else printf("Ok.\n"); 

    if (mysql_num_rows(res) == 0)
    {
      sprintf(query,
      "INSERT INTO `%sbmembers` (`id`, `name`, `g`, `s`, `c`, `ldate`) VALUES ('', '%s', '%d', '%d', '%d', '20%s');",
      prefix, bankers[i].name, bankers[i].cash/10000, bankers[i].cash/100%100, 
      bankers[i].cash%100, bankers[i].date);  
      printf("Executing: %s ...", query);
      totalq++;
      sucq++;
      if(mysql_query(sock,query))
      {
        sucq--;
        printf("Failed.\n   Reson: (%s)\n",mysql_error(sock));
      } else printf("Ok.\n");                    
    }
    else if (mysql_num_rows(res) == 1)
    {
      sprintf(query,"UPDATE `%sbmembers` SET g=%d, s=%d, c=%d, ldate='20%s' WHERE name='%s';",
      prefix, bankers[i].cash/10000, (bankers[i].cash/100)%100, bankers[i].cash%100, 
      bankers[i].date, bankers[i].name);
      printf("Executing: %s ...", query);
      totalq++;
      sucq++;
      if(mysql_query(sock,query))
      {
        sucq--;
        printf("Failed.\n   Reson: (%s)\n",mysql_error(sock));
      } else printf("Ok.\n"); 
    }
    else
    {
      printf("Error in the database: there are 2 or more entries for banker %s.\n", bankers[i].name);
    }
    mysql_free_result(res);
  }
  
  //Update the rank-rank number relation
  printf("Updating rank-rank number relation ...\n");
  for (i=0; i<=numranks; i++)
  {
    link[0]='\0';
    int asd = 0;
    
    sprintf(link, "SELECT count(name) FROM `usercat` WHERE `order`='%d';",i);
    printf("Executing: %s ... ",link);
    totalq++;
    sucq++;
    
    if(mysql_query(sock,link))
    {
      sucq--;
      printf("Failed.\n   Reson: (%s)\n",mysql_error(sock));
    } else printf("Ok.\n"); 
    res=mysql_use_result(sock);
    int r,t;
    
    for(r=0;r<mysql_field_count(sock);r++)
    {
      row=mysql_fetch_row(res);
      if(row<0) break;
      for(t=0;t<mysql_num_fields(res);t++){
        sprintf(tmp,"%s",row[t]);
        if (strncmp(tmp,"(null)",6)==0) 
          asd = -1;
        else
          sscanf(tmp,"%d",&asd);
      }
    }
    
    mysql_free_result(res);
    link[0]='\0'; 
    
    //If an old entry - update, new - insert
    if (asd<=0) 
    {
      strcat(link, "INSERT INTO `");
      strcat(link, prefix);
      strcat(link, "usercat` ( `id` , `name` , `rnkimg`");
      strcat(link, " , `order`) VALUES ( '', '");
      strcat(link, ranks[i]);
      strcat(link, "', '', '");
      sprintf(buf, "%d", i);
      strcat(link, buf);
      strcat(link, "');");
    }
    else
    {
      strcat(link, "UPDATE `");
      strcat(link, prefix);
      strcat(link, "usercat` SET `name`='");
      strcat(link, ranks[i]);
      strcat(link, "' WHERE `order`='");
      sprintf(buf, "%d", i);
      strcat(link, buf);
      strcat(link, "';");
    }
    printf("Executing: %s ... ",link);
    totalq++;
    sucq++;
    
    if(mysql_query(sock,link))
    {
      sucq--;
      printf("Failed.\n   Reson: (%s)\n",mysql_error(sock));
    } else printf("Ok.\n"); 
  }

  printf("Data Base upload complete.\nTotal queries executed:%d, successfull:%d.\n", totalq, sucq);
  fclose(in);
  mysql_close(sock);
  return 0;
}
