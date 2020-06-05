#include "../include/hard_info.h"

int
get_cpuinfo(char* buffer, int line)
  {
    char * path = "/proc/cpuinfo";
    FILE* file = fopen(path, "r");
    if( file == NULL)
      {
        char mensaje[BUFFER_SIZE];
        sprintf(mensaje, "ERROR: %s - %s\n", path, strerror(errno));
        print_log(LOG_STATUS, mensaje);
        return SERVER_ER;
      }

    char linea[BUFFER_SIZE];
    for( int i = 0; i <= line; i++)
      fgets(linea, BUFFER_SIZE, file);

    char * aux = strtok(linea, ":");
    aux = strtok(NULL, ":");
    for( size_t i = 1; i < strlen(aux); i++ )
      {
        if( aux[i] == '\n' )
          {
            buffer[i - 1] = '\0';
            break;
          }
        else
          buffer[i - 1] = aux[i];
      }
    fclose(file);
    return SERVER_OK;
  }

int
get_meminfo(char* buffer, int line)
  {
    char * path = "/proc/meminfo";
    FILE* file = fopen(path, "r");
    if( file == NULL)
      {
        char mensaje[BUFFER_SIZE];
        sprintf(mensaje, "ERROR: %s - %s\n", path, strerror(errno));
        print_log(LOG_STATUS, mensaje);
        return SERVER_ER;
      }

    char linea[BUFFER_SIZE];
    for( int i = 0; i <= line; i++)
      fgets(linea, BUFFER_SIZE, file);

    char * aux = strtok(linea, ":");
    aux = strtok(NULL, ":");
    int buffer_index = 0;
    for( size_t i = 0; i < strlen(aux); i++ )
      {
        if( aux[i] == 'k' )
          {
            buffer[buffer_index] = '\0';
            break;
          }
        else if( aux[i] != ' ')
          {
            buffer[buffer_index] = aux[i];
            buffer_index++;
          }
      }
    fclose(file);

    long meminfo = strtol(buffer, NULL, 10);
    meminfo = meminfo / 1024;
    sprintf(buffer, "%ld MB", meminfo);
    return SERVER_OK;
  }

int
get_disk_total(char* buffer)
  {
    char * path = "/sys/block/sda/size";
    FILE* file = fopen(path, "r");
    if( file == NULL)
      {
        char mensaje[BUFFER_SIZE];
        sprintf(mensaje, "ERROR: %s - %s\n", path, strerror(errno));
        print_log(LOG_STATUS, mensaje);
        return SERVER_ER;
      }

    char size_c[BUFFER_SIZE];
    fgets(size_c, BUFFER_SIZE, file);

    long size = strtol(size_c, NULL, 10);
    size = size * 512;
    size = size / 1014;

    sprintf(buffer, "%ld MB", size);
    fclose(file);
    return SERVER_OK;
  }

int
get_disk_free(char* buffer)
  {
    struct statvfs * stat = malloc( sizeof (struct statvfs) );

    char * path = "/dev/sda";
    if( statvfs(path, stat) == -1  )
      {
        char mensaje[BUFFER_SIZE];
        sprintf(mensaje, "ERROR: %s - %s\n", path, strerror(errno));
        print_log(LOG_STATUS, mensaje);
        return SERVER_ER;
      }

    long unsigned int size = stat->f_bfree * (long unsigned int) stat->f_bsize / 1024;
    sprintf(buffer, "%lu MB", size);
    free(stat);
    return SERVER_OK;
  }

int
get_load_avg(char * buffer)
  {
    double load_avg[1];
    getloadavg(load_avg, 1);
    sprintf(buffer, "%f", load_avg[0]);
    return SERVER_OK;
  }

int
get_uptime(char* buffer)
  {
    struct sysinfo * info = malloc( sizeof (struct sysinfo) );

    if( sysinfo(info) == -1)
      {
        char mensaje[BUFFER_SIZE];
        sprintf(mensaje, "ERROR: %s\n", strerror(errno));
        print_log(LOG_STATUS, mensaje);
        return SERVER_ER;
      }

    long uptime_h = info->uptime / 3600;
    long uptime_m = (info->uptime - uptime_h * 3600) / 60;
    long uptime_s = info->uptime - uptime_h * 3600 - uptime_m * 60;
    sprintf(buffer, "%ldh %ldm %lds", uptime_h, uptime_m, uptime_s);
    return SERVER_OK;
  }
