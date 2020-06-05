#include "hard_info.h"
#include "server_utils.h"

#define PUERTO 5000

/**
 * Inicializacion del servidor
 * @param instance instancia a cerrar
 * @return SERVER_OK en exito, de lo contrario, SERVER_ER
 */
int inicializar_server(struct _u_instance*);

/**
 * Funcion callback para la aplicacion web en la llamada a GET /status
 * @param request estructura de peticion
 * @param response estructura de respuesta
 * @param user_data puntero a datos de usuario
 * @return U_CALLBACK_CONTINUE
 */
int callback_status(const struct _u_request*, struct _u_response*, void*);
