#ifndef TYPES_H
#define TYPES_H

#include "../../utils/headers/sockets.h"
#include "../../memoria/headers/estructuras.h"

typedef struct PCB
{
    int PID;
    int PC;
    int ME[7];
    int MT[7];
    int Estado;
    double tiempo_inicio_exec;
    double estimacion_rafaga;
    char *path;
    int tamanio_memoria;
    double tiempo_inicio_blocked;
    bool *timer_flag;
    pthread_mutex_t mutex;
} t_pcb;

typedef enum Estados
{
    NEW,
    READY,
    EXEC,
    BLOCKED,
    SUSP_READY,
    SUSP_BLOCKED,
    EXIT_ESTADO,
    INIT
} Estados;

typedef struct
{
    t_pcb *pcb;
    t_temporal *cronometro;
} t_pcb_temporal;

typedef enum
{
    CPU_DISPATCH,
    CPU_INTERRUPT
} tipo_conexion_cpu;

typedef struct CPU
{
    int fd;
    int id;
    int pid;
    tipo_conexion_cpu tipo_conexion;
    op_code instruccion_actual;
} cpu;

typedef enum
{
    IO_DISPONIBLE,
    IO_OCUPADO
} estado_io;

typedef struct
{
    int fd;
    char *nombre;
    estado_io estado;
    t_pcb *proceso_actual;
} io;

typedef struct PCB_IO
{
    t_pcb *pcb;
    io *io;
    int tiempo_a_usar;
} t_pcb_io;

typedef struct PCB_DUMP_MEMORY
{
    t_pcb *pcb;
    int timestamp;
} t_pcb_dump_memory;

typedef struct
{
    cpu *cpu_a_desalojar;
} t_interrupcion;

typedef struct
{
    t_pcb *pcb;
    bool *vigente;
    int pid;
} t_timer_arg;

#endif /* TYPES_H */