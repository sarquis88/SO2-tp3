#include "../include/server_utils.h"

void
finalizar_server(struct _u_instance * instance)
  {
    printf("Servidor cerrándose\n");

    ulfius_stop_framework(instance);
    ulfius_clean_instance(instance);
  }

void
print_log(int servicio, char* mensaje)
  {
  	char hora[HORA_SIZE];
    get_time(hora);

    char serv[SERVICE_NAME_SIZE];
    if(servicio == LOG_USERS)
      sprintf(serv, "users");
    else if(servicio == LOG_STATUS)
      sprintf(serv, "status");
    else
      sprintf(serv, "err");

    char log[BUFFER_SIZE];
    sprintf(log, "%s | %s | %s", hora, serv, mensaje);
    printf("%s", log);

    char log_file[LOG_FILE_NAME_SIZE];
    sprintf(log_file, "/var/log/%s.log", serv);
    FILE * file = fopen(log_file, "a+");
    if (file == NULL)
      {
        char msg[BUFFER_SIZE];
        sprintf(msg, "ERROR %s", log_file);
        perror(msg);
        return;
      }
    fprintf(file, "%s", log);
    fclose(file);
  }

void
dormir()
  {
    struct timespec time;
    time.tv_sec = SEC_TIME;
    time.tv_nsec = NSEC_TIME;
    if(nanosleep(&time ,NULL) < 0)
      perror("Error durmiendo");
  }

void
get_time(char * tiempo)
  {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(tiempo, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900,
  	 tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  }
