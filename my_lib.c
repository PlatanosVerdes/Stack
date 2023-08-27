//Luis Barca Pons, Joan Martorell Ferriol, Jorge González Pascual

#include <stdio.h>
#include "my_lib.h"

/*
Esta función calcula el nº de bytes de la cadena apuntada por str, 
sin incluir el carácter nulo de terminación ‘\0’.

Devuelve la longitud de la cadena apuntada por str. No devuelve error.
*/
size_t my_strlen(const char *str)
{
    size_t len = 0;
    //Recorrido hasta el final de la cadena
    for (len = 0; len < str[len]; len++)
        ;
    return len;
}

/*
Esta función compara las cadenas apuntadas por str1 y str2.
Devuelve un entero:
    < 0 indica que str1 < str2.
    > 0 indica que str2 < str1.
    = 0 indica que str1 = str2.
No se basa en la longitud sino en los códigos ASCII. Cuando encuentra uno 
diferente reporta el resultado calculado como la resta de los códigos ASCII 
de los caracteres diferentes.
*/
int my_strcmp(const char *str1, const char *str2)
{
    int i = 0;
    int cmp = 0;

    while (str1[i] && (str1[i] != str2[i]))
    {
        if (str1[i] != str2[i])
        {
            //Realizamos la diferencia correspondiente a los caracteres ASCII
            //como hace srtcmp()
            cmp = *(const unsigned char *)str1 - *(const unsigned char *)str2;
        }
        i++;
    }

    return cmp;
}

/*
La función strcpy() copia la cadena apuntada por src (con el carácter de terminación ‘\0’) 
en la memoria apuntada por dest.

Devuelve el puntero dest. No devuelve error.
*/
char *my_strcpy(char *dest, const char *src)
{
    int c = 0;
    for (int i = 0; src[i]; i++, c++)
    {
        dest[c] = src[c];
    }
    dest[c] = '\0';
    return dest;
}

/*
La función strncpy() copia n caracteres de la cadena apuntada por src (con el carácter de terminación ‘\0’) 
en la memoria apuntada por dest. 

Devuelve el puntero dest. No devuelve error.
En caso de que strlen(src) < n, el resto de la cadena apuntada por dest ha de ser rellenado con 0s. 
*/
char *my_strncpy(char *dest, const char *src, size_t n)
{
    char *paux = dest;
    int len = my_strlen(src);
    if (n <= len)
    { //Copiamos n caracteres sin '\0'
        while (n)
        {
            *paux = *src;
            paux++;
            src++;
            n--;
        }
    }
    else
    { //Copiamos todos los carácteres y rellenamos con '\0'
        int resto = n - (len + 1);
        while (len)
        {
            *paux = *src;
            paux++;
            src++;
            len--;
        }
        //Una vez copiados los carácteres añadimos '\0'
        *paux = '\0';
        while (resto)
        {
            paux++;
            resto--;
            *paux = '\0';
        }
    }
    return dest;
}

/*
La función strcat() añade la cadena apuntada por src (terminada con el carácter nulo) 
a la cadena apuntada por dest (también terminada con el carácter nulo).
El primer carácter de src sobreescribe el carácter nulo de dest. 

Devuelve el puntero dest. No devuelve error.
*/
char *my_strcat(char *dest, const char *src)
{
    char *new_dest = dest;

    //Nos movemos al final de dest
    while (*dest)
    {
        dest++;
    }

    //Concatenamos 'dest' con 'src'
    while (*src)
    {
        *dest++ = *src++;
    }

    //Añadimos el null a dest
    *dest = '\0';
    return new_dest;
}

/*
Reserva espacio para una variable de tipo struct my_stack, que contendrá el puntero al nodo 
superior de la pila y el tamaño de los datos, e inicializa esos valores con NULL, como valor 
del puntero al nodo superior de la pila, y con el tamaño de datos que nos pasan como parámetro.

Devuelve un puntero a la pila inicializada.
*/
struct my_stack *my_stack_init(int size)
{
    struct my_stack *stack = malloc(sizeof(struct my_stack));
    if (stack == NULL)
    { //Control de errores
        fprintf(stderr, "No hay espacio en memoria dinámica disponible en este momento.\n");
        return NULL;
    }
    stack->top = NULL;
    stack->size = size;
    return stack;
}

/*
Inserta un nuevo nodo en los elementos de la pila (hay que reservar espacio de memoria para él).
El puntero a los datos de ese nodo nos lo pasan como parámetro.
*/
int my_stack_push(struct my_stack *stack, void *data)
{
    //Valor de retorno del método
    int e = -1;
    //Miramos si la pila esta inicializada
    if (stack)
    {
        if (stack->size > 0)
        {
            //Creamos un nuevo nodo con los datos de los parámetros
            //Y "actualizamos" el nuevo top de la pila.
            struct my_stack_node *new_node = malloc(sizeof(new_node));
            if (new_node == NULL)
            {
                fprintf(stderr, "No hay espacio en memoria dinámica disponible en este momento.\n");
                return e;
            }
            new_node->data = data;
            new_node->next = stack->top;

            stack->top = new_node;
            e = 0;
        }
    }
    return e;
}

/*
Elimina el nodo superior de los elementos de la pila (y libera la memoria que ocupaba ese nodo!).
Devuelve el puntero a los datos del elemento eliminado. 

Si no existe nodo superior (pila vacía), retorna NULL.
*/
void *my_stack_pop(struct my_stack *stack)
{
    if (stack->top)
    {
        //Creamos un nodo temporal
        struct my_stack_node *temp_node = stack->top;

        //Copiamos los datos que a continuación se eliminarán
        void *datos = temp_node->data;

        //Asignamos el nuevo "top" del stack y así "borramos" el primer nodo
        stack->top = temp_node->next;

        free(temp_node);
        return datos;
    }
    else
    {
        return NULL;
    }
}

/*
Recorre la pila y retorna el número de nodos totales que hay en los elementos de la pila.
*/
int my_stack_len(struct my_stack *stack)
{
    //Contador de nodos
    int i = 0;
    struct my_stack_node *temp_node = stack->top;

    //Recorrido hasta el final de la pila y aumentamos el i
    while (temp_node)
    {
        temp_node = temp_node->next;
        i++;
    }
    return i;
}

/*
Recorre la pila liberando la memoria que habíamos reservado para cada uno de los datos 
(data) y la de cada nodo. Finalmente libera también la memoria que ocupa la pila. Es decir, 
toda la memoria que se reservó con malloc() en algún momento, se libera con la función free(). 

Devuelve el número de bytes liberados.
*/
int my_stack_purge(struct my_stack *stack)
{
    int bytes = sizeof(struct my_stack); //Bytes de la pila

    //Recorrido por toda la pila
    while (stack->top)
    {
        bytes += sizeof(struct my_stack_node); //Bytes de cada nodo
        bytes += stack->size;                  //Bytes de los datos
        free(my_stack_pop(stack));             //my_stack_pop retorna la posición de los datos
                                               //que eliminamos de la pila
    }

    free(stack); //Liberamos toda la pila
    return bytes;
}

/*
Función auxiliar del write
*/
int aux_my_stack_write(struct my_stack_node *node, int fichero, int size)
{
    // Inicializa a 0 i mira si no es el último nodo
    int bytes = 0;
    if (node->next)
    {
        // Llama de nuevo a la funcion con el nodo como entrada
        bytes = aux_my_stack_write(node->next, fichero, size);
    }

    // Escribe el nodo en el fichero y devuelve los bytes escritos
    return write(fichero, node->data, size) + bytes;
}

/*
Almacena los datos de la pila en el fichero indicado por "filename"
*/
int my_stack_write(struct my_stack *stack, char *filename)
{
    int bytes = -1;
    // Creamos el enlace al fichero
    int fichero = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    //Control de error de open
    if (fichero < 0)
    {
        fprintf(stderr, "Error al abrir el fichero\n");
        return bytes;
    }

    bytes = write(fichero, &stack->size, sizeof(stack->size)); //write(fichero, dato a escribir, tamaño del tado)
                                                               //y nos devuelve los bytes escritos
    bytes = aux_my_stack_write(stack->top, fichero, stack->size);

    // Cerramos el enlace al fichero y devolvemos el número de datos escritos, con control de errores
    if (close(fichero) == -1)
    {
        fprintf(stderr, "Error al cerrar el fichero\n");
        return -1;
    }
    //Control de errores al escribir
    if (bytes == -1)
    {
        fprintf(stderr, "Error al escribir en el archivo\n");
        return bytes;
    }
    else
    {
        return bytes / stack->size;
    }
}

/*
Lee los datos de la pila almacenados en el fichero indicado por "filename"
*/
struct my_stack *my_stack_read(char *filename)
{
    int size;
    struct my_stack *stack;
    void *data;

    // Creamos el enlace al fichero
    int fichero = open(filename, O_RDONLY);

    // Control de errores
    if (fichero < 0)
    {
        fprintf(stderr, "Error al abrir el fichero\n");
        return NULL;
    }

    // Cogemos el tamaño del data del fichero
    read(fichero, &size, sizeof(int));

    // Inicializamos el stack (usando init) y reservamos tamaño para el data
    stack = my_stack_init(size);
    data = malloc(size);
    if (data == NULL)
    {
        fprintf(stderr, "No hay espacio en memoria dinámica disponible en este momento.\n");
        return NULL;
    }

    //Bucle para restaurar los nodos
    while (read(fichero, data, size) > 0)
    {
        //Reservamos memoria para el data
        my_stack_push(stack, data);
        data = malloc(size);
        if (data == NULL)
        {
            fprintf(stderr, "No hay espacio en memoria dinámica disponible en este momento.\n");
            return NULL;
        }
    }
    //Cerramos el enlace con el fichero
    if (close(fichero) < 0)
    {
        fprintf(stderr, "Error al cerrar el fichero\n");
    }

    free(data);
    return stack;
}
