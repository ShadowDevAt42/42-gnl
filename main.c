#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    int     fd;
    char    *line;
    int     test_num = 1;

    // Test 1: Fichier normal
    printf("\n=== Test %d: Lecture fichier normal ===\n", test_num++);
    fd = open("test_normal.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return (1);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);

    // Test 2: Fichier vide
    printf("\n=== Test %d: Fichier vide ===\n", test_num++);
    fd = open("test_empty.txt", O_RDONLY);
    if (fd != -1)
    {
        line = get_next_line(fd);
        if (line)
        {
            printf("Contenu: %s\n", line);
            free(line);
        }
        else
            printf("Fichier vide (NULL retourné)\n");
        close(fd);
    }

    // Test 3: Fichier avec une seule ligne sans \n
    printf("\n=== Test %d: Une ligne sans \\n ===\n", test_num++);
    fd = open("test_single_line.txt", O_RDONLY);
    if (fd != -1)
    {
        line = get_next_line(fd);
        if (line)
        {
            printf("%s", line);
            free(line);
        }
        close(fd);
    }

    // Test 4: FD invalide
    printf("\n=== Test %d: FD invalide ===\n", test_num++);
    line = get_next_line(-1);
    if (!line)
        printf("Test FD invalide OK (NULL retourné)\n");
    
    return (0);
}