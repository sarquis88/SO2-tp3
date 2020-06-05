#include "../include/users.h"

int finalizar = 0;

// TODO falta contraseña para el user

/**
 * Funcion main
 */
int
main(void)
  {
    struct _u_instance instance;

    if( inicializar_server(&instance) == SERVER_ER )
      {
        print_log(LOG_USERS, "ERROR: iniciando instancia ulfius\n");
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

    ulfius_add_endpoint_by_val( instance, "GET", "/users",
                                NULL, 0, &callback_users, NULL);
    ulfius_add_endpoint_by_val( instance, "POST", "/users",
                                NULL, 0, &callback_users_post, NULL);

    // Start the framework
    if (ulfius_start_framework(instance) == U_OK)
      {
        char mensaje[BUFFER_SIZE];
        sprintf(mensaje, "Servidor escuchando en puerto %d\n", instance->port);
        print_log(LOG_USERS, mensaje);
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
callback_users ( const struct _u_request * request,
                struct _u_response * response, void * user_data)
  {
    #pragma GCC diagnostic pop

    json_t *users = json_array();
    if( get_users_list(users) == SERVER_ER)
      {
        return SERVER_ER;
      }
    json_t *respuesta = json_pack("{s:o}", "data", users);

    ulfius_set_json_body_response( response, 200, respuesta );

    char mensaje[BUFFER_SIZE];
    sprintf(mensaje, "Usuario listados: %d\n", get_users_count());
    print_log(LOG_USERS, mensaje);

    return U_CALLBACK_CONTINUE;
  }

#pragma GCC diagnostic ignored "-Wunused-parameter"
int
callback_users_post ( const struct _u_request * request,
                      struct _u_response * response, void * user_data)
  {
    #pragma GCC diagnostic pop

    json_error_t * json_error = malloc( sizeof (struct json_error_t));
    json_t * json_request = ulfius_get_json_body_request(request, json_error);

    if( request == NULL)
      {
        char mensaje[BUFFER_SIZE];
        sprintf(mensaje, "ERROR: %s\n", json_error->text);
        print_log(LOG_USERS, mensaje);
        free(json_error);
        return SERVER_ER;
      }

    json_t * username = json_object();
    username = json_object_get(json_request, "username");

    json_t * password = json_object();
    password = json_object_get(json_request, "password");

    if( !json_is_string(username) ||
        !json_is_string(password) ||
        username == NULL          ||
        password == NULL            )
      {
        json_t * respuesta = json_pack("{s:s}", "description",
          "La estructura de la request debe ser: "
          "'username'='<my_username>','password=<my_password>'");
        ulfius_set_json_body_response(response, 400, respuesta);
      }
    else
      {
        char user[BUFFER_SIZE];
        sprintf(user, "%s", json_string_value(username) );
        char pass[BUFFER_SIZE];
        sprintf(pass, "%s", json_string_value(password) );

        if( user_exists( user ) == SERVER_YES)
          {
            json_t * respuesta = json_pack("{s:s}", "description",
                      "Usuario duplicado");
            ulfius_set_json_body_response(response, 409, respuesta);
          }
        else
          {
            add_user( user, pass );

            int id = get_user_id( user );
            if(id == 0)
              {
                return SERVER_ER;
              }

            char tiempo[HORA_SIZE];
            get_time(tiempo);
            json_t *user_json = json_pack("{s:i, s:s, s:s},",
            "id", id,
            "username", user,
            "created_at",tiempo
          );

          ulfius_set_json_body_response( response, 200, user_json );

          char mensaje[BUFFER_SIZE];
          sprintf(mensaje, "Usuario %d creado\n", id);
          print_log(LOG_USERS, mensaje);
        }
      }

    return U_CALLBACK_CONTINUE;
  }
