//  Author: Tuan Trung
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
   struct Address **rows;
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
  //  int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
  //  if (rc != 1)
  //   die("Failed to load database.");
  size_t i=0;
    
  // Each database will have two `int` values. read
  // those first. 
  assert(conn->db && conn->file);
  if (!(conn->db && conn->file))
     die("Database load : Invalid Connection info");
  if (fread(&conn->db->max_data, sizeof(conn->db->max_data), 1, conn->file) != 1)
     die("Database load : Couldn't read MAX_DATA");
  if (fread(&conn->db->max_rows, sizeof(conn->db->max_rows), 1, conn->file) != 1)
     die("Database load : Couldn't read MAX_ROWS");

  conn->db->rows = (struct Address**)malloc(sizeof(struct Address *) * conn->db->max_rows);
  //  printf("Sizeof *conn->db->rows is %lu\n", sizeof(*conn->db->rows));
  assert(conn->db->rows);
  if (!(conn->db->rows))
     die("Database_load : Could not MAX_ROWS Address  structures");
    // Now load each address structure
  for (i=0; i<conn->db->max_rows; i++) {
    // read two int values first.
 
    conn->db->rows[i] = (struct Address*)malloc(sizeof(struct Address));
    struct Address *row = conn->db->rows[i];
    if (fread(&row->id, sizeof(row->id), 1, conn->file) !=1)
         die("Database load : Could not read Address::id");
    if (fread(&row->set, sizeof(row->set), 1, conn->file) != 1)
         die("Database load : Couldn't read  Address::set");

    // allocate two buffers large enough for our data
    row->name = malloc(conn->db->max_data * sizeof(*row->name));
    row->email = malloc(conn->db->max_data * sizeof(*row->email));
    assert(row->email && row->name);
    if (!(row->name && row->email))
       die("Database load : Failed to Allocate Address strings");
    // now just read both strings
    if (fread(row->name, conn->db->max_data * sizeof(*row->name), 1, conn->file) != 1)
       die("Database load : Failed to read Address::name");
    if (fread(row->email, conn->db->max_data * sizeof(*row->email), 1, conn->file) != 1)
       die("Database load : Failed to read Address::email");
  }
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
      if (conn->db->rows) {
        for (unsigned long i = 0; i < conn->db->max_rows; i++) {
             struct Address *cur = conn->db->rows[i];
             free(cur);
        }
      }
      free(conn->db);
     }
     free(conn);
   }
 }

 void Database_write(struct Connection *conn)
 {
   unsigned long i;
   rewind(conn->file);

  //  int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
  //  if (rc != 1)
  //   die("Failed to write database.");
   // Writing MAX_DATA and MAX_ROWS to the file first
   if(fwrite(&conn->db->max_data, sizeof(conn->db->max_data), 1, conn->file) != 1)
    die("Database write : Failed to write max_data");
   if(fwrite(&conn->db->max_rows, sizeof(conn->db->max_rows), 1, conn->file) != 1)
    die("Database write : Failed to write max_rows");
    
   for (i = 0; i < conn->db->max_rows; i++) {
     struct Address *row = conn->db->rows[i];     
     if(fwrite(&row->id, sizeof(row->id), 1, conn->file) != 1)
       die("Failed to write id.");
     if(fwrite(&row->set, sizeof(row->set), 1, conn->file) != 1)
       die("Failed to write set.");
     if(fwrite(row->name, sizeof(char)*conn->db->max_data, 1, conn->file) != 1)
       die("Failed to write name.");
     if(fwrite(row->email, sizeof(char)*conn->db->max_data, 1, conn->file) != 1)
       die("Failed to write email.");
   }

   int rc = fflush(conn->file);
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

   
   conn->db->rows = (struct Address**)malloc(sizeof(struct Address*)*conn->db->max_rows); 

   unsigned long i = 0;
   for (i = 0; i < conn->db->max_rows; i++) {
     conn->db->rows[i] = (struct Address*)malloc(sizeof(struct Address));
     conn->db->rows[i]->id = i;
     conn->db->rows[i]->set = 0;
     conn->db->rows[i]->name = (char *)malloc(conn->db->max_data);
     conn->db->rows[i]->name = (char *)memset(conn->db->rows[i]->name, ' ', conn->db->max_data);
     conn->db->rows[i]->email= (char *)malloc(conn->db->max_data);
     conn->db->rows[i]->email= (char *)memset(conn->db->rows[i]->email, ' ', conn->db->max_data);
   }
 }

 void Database_set(struct Connection *conn, int id, const char *name, const char *email)
 {
   if (!(conn && conn->db && conn->db->rows && conn->db->rows[id])) return;
   struct Address *addr = conn->db->rows[id];
   unsigned long MAX_DATA = conn->db->max_data;
   if (addr->set)
    die("Already set, delete it first");

   addr->set = 1;
   addr->name = malloc(sizeof(char) * MAX_DATA);
   addr->email = malloc(sizeof(char) * MAX_DATA);
  
   // WARNING: bug, read the "How To Break It and fix"

   char *res = strncpy(addr->name, name, MAX_DATA);
   addr->name[conn->db->max_data - 1] = '\0';
   // demonstrate the strncpy bug
   if (!res)
    die("Name copy failed");

   res = strncpy(addr->email, email, MAX_DATA);
   addr->name[conn->db->max_data - 1] = '\0';
   if (!res)
    die("Email copy failed");
 }

 void Database_get(struct Connection *conn, int id)
 {
   struct Address *addr = conn->db->rows[id];

   if (addr->set) {
     Address_print(addr);
   } else {
      die("ID is not set");
   }
 }

 void Database_find_by_name(struct Connection *conn, char *name)
 {
    int i = 0;
    struct Database *db = conn->db;
    
    for (i = 0; i < db->max_rows; i++) {
        struct Address *cur = db->rows[i];

        if (strcmp(cur->name, name) == 0 && cur->set) {
            Address_print(cur);
        }
    }
 }

 void Database_find_by_email(struct Connection *conn, char *email)
 {
    int i = 0;
    struct Database *db = conn->db;
    
    for (i = 0; i < db->max_rows; i++) {
        struct Address *cur = db->rows[i];

        if (strcmp(cur->email, email) == 0 && cur->set) {
            Address_print(cur);
        }
    }
 }
   
 void Database_delete(struct Connection *conn, int id)
 {
   struct Address addr = {.id = id, .set = 0};
   conn->db->rows[id] = &addr;
 }

 void Database_list(struct Connection *conn)
 {
   int i = 0;
   struct Database *db = conn->db;

   for (i = 0; i < conn->db->max_rows; i++) {
     struct Address *cur = db->rows[i];

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
   char *attribute;
   char *value;

   if (argc > 3 && argc != 5) {
        id = atoi(argv[3]);
   }

   if (argc == 5) {
        attribute = argv[3];
        value = argv[4];
   }

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

     case 'f':
      if (argc != 5) {
        die("Need attribute and value to find");
      }

      if (strcmp(attribute, "name") == 0) {
          Database_find_by_name(conn, value);
      } else if (strcmp(attribute, "email") == 0) {
          Database_find_by_email(conn, value);
      }

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
