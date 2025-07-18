#ifndef CPU_H
#define CPU_H

/////////////////////////////// Includes ///////////////////////////////

#include "sockets.h"

/////////////////////////////// Declaracion de variables globales ///////////////////////////////

extern t_log* cpu_log;
extern t_config* cpu_config;
extern int numero_cpu;

extern int fd_memoria;
extern int fd_kernel_dispatch;
extern int fd_kernel_interrupt;

extern char* IP_MEMORIA;
extern char* PUERTO_MEMORIA;
extern char* IP_KERNEL;
extern char* PUERTO_KERNEL_DISPATCH;
extern char* PUERTO_KERNEL_INTERRUPT;
extern char* ENTRADAS_TLB;
extern char* REEMPLAZO_TLB;
extern char* ENTRADAS_CACHE;
extern char* REEMPLAZO_CACHE;
extern char* RETARDO_CACHE;
extern char* LOG_LEVEL;

/////////////////////////////// Prototipos ///////////////////////////////

void leer_config_cpu(const char *path_cfg);
void iniciar_logger_cpu(void);
void* conectar_kernel_dispatch(void);
void* conectar_kernel_interrupt(void);
void* conectar_cpu_memoria(void);

#endif /* CPU_H */
