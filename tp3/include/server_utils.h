#include <ulfius.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <errno.h>

#define SERVICE_NAME_SIZE 10
#define HORA_SIZE 20
#define LOG_FILE_NAME_SIZE 30
#define BUFFER_SIZE 1023
#define PASSWORD_SIZE 32

#define SERVER_OK 0
#define SERVER_ER 1
#define SERVER_NO 2
#define SERVER_YES 3
#define LOG_USERS 4
#define LOG_STATUS 5

#define SEC_TIME 0
#define NSEC_TIME 200

#define LINE_SIZE 64


/**
 * Duerme el hilo durante SEC_TIME + NSEC_TIME
 */
void dormir();

/**
 * Finaliza el servidor
 * @param instance instancia a cerrar
 */
void finalizar_server(struct _u_instance*);

/**
 * Impresion de log
 * @param servicio int igual a LOG_USERS o LOG_STATUS dependiendo del servicio
 *        que se quiere loguear
 * @param msg mensaje a imprimir
 */
void print_log(int, char*);

/**
 * Setea el tiempo en la variable ingresada
 * @param buffer  variable char a donde se guarda el tiempo
 */
void get_time(char*);
