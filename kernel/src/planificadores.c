#include <sys/time.h>
#include "../headers/planificadores.h"

void iniciar_planificadores()
{
    pthread_t hilo_planificador;
    if (pthread_create(&hilo_planificador, NULL, planificador_largo_plazo, NULL) != 0)
    {
        LOG_ERROR(kernel_log, "Error al crear hilo para planificador de largo plazo");
        terminar_kernel(EXIT_FAILURE);
    }
    pthread_detach(hilo_planificador);

    pthread_t hilo_exit;
    if (pthread_create(&hilo_exit, NULL, gestionar_exit, NULL) != 0)
    {
        LOG_ERROR(kernel_log, "Error al crear hilo para gestionar procesos en EXIT");
        terminar_kernel(EXIT_FAILURE);
    }
    pthread_detach(hilo_exit);

    pthread_t hilo_planificador_cp;
    if (pthread_create(&hilo_planificador_cp, NULL, planificador_corto_plazo, NULL) != 0)
    {
        LOG_ERROR(kernel_log, "Error al crear hilo para planificador de corto plazo");
        terminar_kernel(EXIT_FAILURE);
    }
    pthread_detach(hilo_planificador_cp);

    pthread_t hilo_rechazados;
    if (pthread_create(&hilo_rechazados, NULL, verificar_procesos_rechazados, NULL) != 0)
    {
        LOG_ERROR(kernel_log, "[PLANI LP] [EXIT] Error al crear hilo para verificar procesos rechazados");
        terminar_kernel(EXIT_FAILURE);
    }
    pthread_detach(hilo_rechazados);
}

// AUXILIARES

/**
 * @brief Obtains the current time in milliseconds.
 *
 * This function retrieves the current time using gettimeofday and returns
 * the time as a double representing milliseconds since the Epoch.
 *
 * @return The current time in milliseconds as a double.
 */
double get_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0;
}

t_pcb *elegir_por_fifo(t_list *cola_a_utilizar)
{
    LOG_TRACE(kernel_log, "ELIGIENDO POR FIFO");

    if (list_is_empty(cola_a_utilizar))
    {
        LOG_TRACE(kernel_log, "[FIFO] cola_a_utilizar vacía");
        return NULL;
    }

    LOG_TRACE(kernel_log, "[FIFO] seleccionando el primer PCB de la cola");
    return (t_pcb *)list_get(cola_a_utilizar, 0);
}