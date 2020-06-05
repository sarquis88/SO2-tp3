#include "server_utils.h"

#define CPUINFO_CPU_LINE 4
#define CPUINFO_CORES_LINE 12

#define MEMINFO_TOTALMEMORY_LINE 0
#define MEMINFO_FREEMEMORY_LINE 1

/**
 * Retorna informacion de /proc/cpuinfo
 * @param buffer a guardar la informacion
 * @param linea del dato solicitado
 * @return HARD_OK en caso exitoso, de lo contrario, HARD_ERR
 */
int get_cpuinfo(char*, int);

/**
 * Retorna informacion de /proc/meminfo
 * @param buffer a guardar la informacion
 * @param linea del dato solicitado
 * @return HARD_OK en caso exitoso, de lo contrario, HARD_ERR
 */
int get_meminfo(char*, int);

/**
 * Retorna tamaño total del disco
 * @param buffer a guardar la version
 * @return HARD_OK en caso exitoso, de lo contrario, HARD_ERR
 */
int get_disk_total(char*);

/**
 * Retorna espacio libre del disco
 * @param buffer a guardar la version
 * @return HARD_OK en caso exitoso, de lo contrario, HARD_ERR
 */
int get_disk_free(char*);

/**
 * Retorna carga promedio del cpu
 * @param buffer a guardar la version
 * @return HARD_OK en caso exitoso, de lo contrario, HARD_ERR
 */
int get_load_avg(char*);

/**
 * Retorna tiempo desde el ultimo booteo
 * @param buffer a guardar la version
 * @return HARD_OK en caso exitoso, de lo contrario, HARD_ERR
 */
int get_uptime(char*);
