#include "../include/users_info.h"

int
get_users_list(json_t * body)
  {
    char * path = "/etc/passwd";
    FILE * file = fopen(path, "r");
    if( file == NULL)
      {
        char mensaje[BUFFER_SIZE];
        sprintf(mensaje, "ERROR: %s - %s\n", path, strerror(errno));
        print_log(LOG_USERS, mensaje);
        return SERVER_ER;
      }

    char linea[BUFFER_SIZE];
    char usuario_actual[BUFFER_SIZE];
    while( fgets(linea, BUFFER_SIZE, file) != NULL )
      {
        char * uid_c;
        uid_c = strtok(linea, ":");
        sprintf(usuario_actual, "%s", uid_c);
        uid_c = strtok(NULL, ":");
        uid_c = strtok(NULL, ":");

        json_t *user = json_pack("{s:s, s:s},",
                              "user_id", uid_c,
                              "username", usuario_actual
                             );
        json_array_append( body, user );

      }

    fclose(file);

    return SERVER_OK;
  }

int
user_exists(char* nombre)
  {
    char * path = "/etc/passwd";
    FILE * file = fopen(path, "r");
    if( file == NULL)
      {
        char mensaje[BUFFER_SIZE];
        sprintf(mensaje, "ERROR: %s - %s\n", path, strerror(errno));
        print_log(LOG_USERS, mensaje);
        return SERVER_ER;
      }

      char linea[BUFFER_SIZE];
      while( fgets(linea, BUFFER_SIZE, file) != NULL )
        {
          char * usuario = strtok(linea, ":");
          if( strcmp(usuario, nombre) == 0 )
            {
              fclose(file);
              return SERVER_YES;
            }
        }

      fclose(file);

      return SERVER_NO;
  }

int
get_user_id(char* nombre)
  {
    char * path = "/etc/passwd";
    FILE * file = fopen(path, "r");
    if( file == NULL)
      {
        char mensaje[BUFFER_SIZE];
        sprintf(mensaje, "ERROR: %s - %s\n", path, strerror(errno));
        print_log(LOG_USERS, mensaje);
        return SERVER_ER;
      }
      int id = 0;
      char linea[BUFFER_SIZE];
      while( fgets(linea, BUFFER_SIZE, file) != NULL )
        {
          char * uid_c;
          char usuario[BUFFER_SIZE];
          uid_c = strtok(linea, ":");
          sprintf(usuario, "%s", uid_c);
          uid_c = strtok(NULL, ":");
          uid_c = strtok(NULL, ":");

          if( strcmp(usuario, nombre) == 0 )
            {
              id = (int) strtol(uid_c, NULL, 10);
              break;
            }
        }

      fclose(file);

      return id;
  }

int
get_users_count()
  {
    char * path = "/etc/passwd";
    FILE * file = fopen(path, "r");
    if( file == NULL)
      {
        char mensaje[BUFFER_SIZE];
        sprintf(mensaje, "ERROR: %s - %s\n", path, strerror(errno));
        print_log(LOG_USERS, mensaje);
        return SERVER_ER;
      }

    int cantidad = 0;
    char linea[BUFFER_SIZE];
    while( fgets(linea, BUFFER_SIZE, file) != NULL )
      {
        cantidad++;
      }

    fclose(file);

    return cantidad;
  }

int
add_user(char* name, char* passwd)
  {
    char password[PASSWORD_SIZE];
    sprintf(password, "%c%s%c", 34, passwd, 34);
    char cmd[BUFFER_SIZE];
    sprintf(cmd, "sudo useradd -p $(openssl passwd -1 %s) %s", password, name);
    system(cmd);
    return SERVER_OK;
  }
