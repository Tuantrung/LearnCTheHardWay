# Author: Tuan Trung
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// #define MAX_DATA 512
// #define MAX_ROWS 100
static unsigned long rows;
static unsigned long data;
 struct Address {
   int id;
   int set;
   char *name;
   char *email;
 };

 struct Database {
   unsigned long max_rows;
   unsigned long max_data;
   struct Address *rows;
 };

 struct Connection {
  FILE *file;
  struct Database *db;
 };

 void die(const char *message)
 {
  if (errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }

  exit(1);
 }

 void Address_print(struct Address *addr)
 {
   printf("%d %s %s\n", addr->id, addr->name, addr->email);
 }

 void Database_load(struct Connection *conn)
 {
   int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
   if (rc != 1)
    die("Failed to load database.");
 }

 struct Connection *Database_open(const char *filename, char mode)
 {
  struct Connection *conn = malloc(sizeof(struct Connection));
  if (!conn)
    die("Memory error");

  conn->db = malloc(sizeof(struct Database));
  if (!conn->db)
    die("Memory error");
  
  if (mode == 'c') {
    conn->file = fopen(filename, "w");
  } else {
    conn->file = fopen(filename, "r+");
    if (conn->file) {
      Database_load(conn);
    }
  }

  if (!conn->file)
    die("Failed to open the file");

  return conn;
}

 void Database_close(struct Connection *conn)
 {
   if (conn) {
     if (conn->file)
      fclose(conn->file);
     if (conn->db) {
      if (conn->db->rows)
        free(conn->db->rows);
      free(conn->db);
     }
     free(conn);
   }
 }

 void Database_write(struct Connection *conn)
 {
   rewind(conn->file);

   int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
   if (rc != 1)
    die("Failed to write database.");
    
   for (size_t i = 0; i < conn->db->max_rows; i++) {
     if(fwrite(&((conn->db->rows[i]).id), sizeof(int), 1, conn->file) != 1)
       die("Failed to write id.");
     if(fwrite(&((conn->db->rows[i]).set), sizeof(int), 1, conn->file) != 1)
       die("Failed to write set.");
     if(fwrite((conn->db->rows[i]).name, conn->db->max_data, 1, conn->file) != 1)
       die("Failed to write name.");
     if(fwrite((conn->db->rows[i]).email, conn->db->max_data, 1, conn->file) != 1)
       die("Failed to write email.");
   }

   rc = fflush(conn->file);
   if (rc == -1)
    die("Cannot fflush database.");
 }

 void Database_create(struct Connection *conn)
 {
   printf("Enter the max number of rows: ");
   scanf("%ld", &rows);
   conn->db->max_rows = rows;
   int rc = fwrite(&conn->db->max_rows, sizeof(unsigned int), 1, conn->file);
   if (!rc)
     die("Memory error");

   printf("Enter the max number of data: ");
   scanf("%ld", &data);
   conn->db->max_data = data;
   rc = fwrite(&conn->db->max_data, sizeof(unsigned int), 1, conn->file);
   if (!rc)
     die("Memory error");  

   
   conn->db->rows = (struct Address*)malloc(sizeof(struct Address)*conn->db->max_rows); 

   int i = 0;
   for (i = 0; i < conn->db->max_rows; i++) {
     char* a = (char*)malloc(conn->db->max_data);
     memset(a, 0, conn->db->max_data);
     char* b = (char*)malloc(conn->db->max_data);
     memset(b, 0, conn->db->max_data);

     // make a prototype to initialize it
     struct Address addr = {.id = i, .set = 0, .name = a, .email = b};
     // then just assign it
     conn->db->rows[i] = addr;
   }
 }

 void Database_set(struct Connection *conn, int id, const char *name, const char *email)
 {
   struct Address *addr = &conn->db->rows[id];
   printf("%ld", sizeof(addr->set));
  //  if (addr->set)
  //   die("Already set, delete it first");

   addr->set = 1;
  
   // WARNING: bug, read the "How To Break It and fix"

   char *res = strncpy(addr->name, name, conn->db->max_data);
   addr->name[conn->db->max_data - 1] = '\0';
   // demonstrate the strncpy bug
   if (!res)
    die("Name copy failed");

   res = strncpy(addr->email, email, conn->db->max_data);
   addr->name[conn->db->max_data - 1] = '\0';
   if (!res)
    die("Email copy failed");
 }

 void Database_get(struct Connection *conn, int id)
 {
   struct Address *addr = &conn->db->rows[id];

   if (addr->set) {
     Address_print(addr);
   } else {
      die("ID is not set");
   }
 }

 void Database_delete(struct Connection *conn, int id)
 {
   struct Address addr = {.id = id, .set = 0};
   conn->db->rows[id] = addr;
 }

 void Database_list(struct Connection *conn)
 {
   int i = 0;
   struct Database *db = conn->db;

   for (i = 0; i < conn->db->max_rows; i++) {
     struct Address *cur = &db->rows[i];

     if (cur->set) {
       Address_print(cur);
     }
   }
 }

 int main(int argc, char *argv[])
 {
   if (argc < 3)
    die("USAGE: ex17 <dbfile> <action> [action params]");

   char *filename = argv[1];
   char action = argv[2][0];
   struct Connection *conn = Database_open(filename, action);
   int id = 0;

   if (argc > 3) id = atoi(argv[3]);
  //  if (id >= conn->db->max_rows)
  //   die("There's not that many records.");

   switch (action) {
     case 'c':
      Database_create(conn);
      Database_write(conn);
      break;

     case 'g':
      if (argc != 4)
        die("Need an id to get");
      Database_get(conn, id);
      break;

     case 's':
      if (argc != 6)
        die("Need id, name, email to set");

      Database_set(conn, id, argv[4], argv[5]);
      Database_write(conn);
      break;

     case 'd':
      if (argc != 4)
        die("Need id to delete");

      Database_delete(conn, id);
      Database_write(conn);
      break;

     case 'l':
      Database_list(conn);
      break;

     default:
      die("Invalid action: c=create, g=get, s=set, d=del, l=list");
   }

   Database_close(conn);

   return 0;
 }
