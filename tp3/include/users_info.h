#include "server_utils.h"

/**
 * Setea los usuarios en formato json en el cuerpo pasado como parametro
 * @param json_list cuerpo en el cual se setean los usuarios
 * @return SERVER_ER en caso de error, de lo contrario SERVER_OK
 */
int get_users_list(json_t*);

/**
 * Chequea si el nombre ingresado ya existe dentro de los usuarios
 * @param name nombre a chequear
 * @return  SERVER_ER en caso de error, SERVER_YES en caso de existir y
 *          SERVER_NO en caso de no existir
 */
int user_exists(char*);

/**
 * Retorna el id del usuario indicado
 * @param name nombre del usuario
 * @return id del usuario
 */
int get_user_id(char*);

/**
 * Retorna la cantidad de usuarios en el sistema
 * @return cantidad de usuario
 */
int get_users_count();

/**
 * Creacion de un nuevo usuario UNIX
 * @param name nombre del usuario
 * @param passwd contraseña del usuario
 * @return SERVER_ER en caso de error, de lo contrario SERVER_OK
 */
int add_user(char*, char*);
