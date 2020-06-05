#include "../include/status.h"

int finalizar = 0;

/**
 * Funcion main
 */
int
main(void)
  {
    struct _u_instance instance;

    if( inicializar_server(&instance) == SERVER_ER )
      {
        print_log(LOG_STATUS, "ERROR: iniciando instancia ulfius\n");
        exit(EXIT_FAILURE);
      }

    while( finalizar == 0 )
      dormir();

    finalizar_server(&instance);

    return SERVER_OK;
  }

int
inicializar_server(struct _u_instance * instance)
  {
    // Initialize instance with the port number
    if (ulfius_init_instance(instance, PUERTO, NULL, NULL) != U_OK)
      {
        return(SERVER_ER);
      }

    ulfius_add_endpoint_by_val( instance, "GET", "/hardwareinfo",
                                NULL, 0, &callback_status, NULL);

    // Start the framework
    if (ulfius_start_framework(instance) == U_OK)
      {
        char mensaje[BUFFER_SIZE];
        sprintf(mensaje, "Servidor escuchando en puerto %d\n", instance->port);
        print_log(LOG_STATUS, mensaje);
        return SERVER_OK;
      }
    else
      {
        char mensaje[BUFFER_SIZE];
        sprintf(mensaje, "ERROR: iniciando framework uflius\n");
        print_log(LOG_USERS, mensaje);
        return SERVER_ER;
      }
  }

#pragma GCC diagnostic ignored "-Wunused-parameter"
int
callback_status ( const struct _u_request * request,
                struct _u_response * response, void * user_data)
  {
    #pragma GCC diagnostic pop

    char kernel_version[BUFFER_SIZE];
    FILE * file = popen("uname -r", "r");
    fgets(kernel_version, BUFFER_SIZE, file);
    pclose(file);
    kernel_version[strlen(kernel_version) - 1] = '\0';

    char processor_name[BUFFER_SIZE];
    get_cpuinfo(processor_name, CPUINFO_CPU_LINE);

    char cpu_cores[BUFFER_SIZE];
    get_cpuinfo(cpu_cores, CPUINFO_CORES_LINE);

    char total_memory[BUFFER_SIZE];
    get_meminfo(total_memory, MEMINFO_TOTALMEMORY_LINE);

    char free_memory[BUFFER_SIZE];
    get_meminfo(free_memory, MEMINFO_FREEMEMORY_LINE);

    char disk_total[BUFFER_SIZE];
    get_disk_total(disk_total);

    char disk_free[BUFFER_SIZE];
    get_disk_free(disk_free);

    char load_avg[BUFFER_SIZE];
    get_load_avg(load_avg);

    char uptime[BUFFER_SIZE];
    get_uptime(uptime);

    json_t *body = json_pack("{s:s, s:s, s:s, s:s, s:s, s:s, s:s, s:s, s:s}",
                         "kernelVersion", kernel_version,
                         "processorName", processor_name,
                         "totalCPUCore", cpu_cores,
                         "totalMemory", total_memory,
                         "freeMemory", free_memory,
                         "diskTotal", disk_total,
                         "diskFree", disk_free,
                         "loadAvg", load_avg,
                         "uptime", uptime
                         );
    ulfius_set_json_body_response(response, 200, body);

    char mensaje[BUFFER_SIZE];
    sprintf(  mensaje, "Estadísticas requeridas desde el host %s\n",
              u_map_get(request->map_header, "X-Forwarded-For") );
    print_log(LOG_STATUS, mensaje);

    return U_CALLBACK_CONTINUE;
  }
