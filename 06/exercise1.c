// Peter Koll, Jonas Wagner
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <omp.h>
#include <sys/sysmacros.h>
#include <limits.h>


char *concatinate(const char *string1, const char *string2){
    char *result = malloc(strlen(string1) + strlen(string2) + 2);
    strcpy(result, string1);
    strcat(result, "/");
    strcat(result, string2);
    return result;
}


long calculateSize(char *directory_path){
    struct stat statbuffer;
    long long byte = 0;

    DIR *directory = opendir(directory_path);
    struct dirent *directory_pt;

    while((directory_pt = readdir(directory)) != NULL){
        if(strcmp((*directory_pt).d_name, ".") == 0 || strcmp((*directory_pt).d_name, "..") == 0){
            continue;
        }

        char *file_path = concatinate(directory_path, (*directory_pt).d_name);
        lstat(file_path, &statbuffer);
        switch (statbuffer.st_mode & S_IFMT){
            case S_IFDIR:
                #pragma omp task shared(byte)
                {
                    byte += calculateSize(file_path);
                }
                byte += statbuffer.st_size;
                break;
            default:
                byte += statbuffer.st_size;
                break;
            }
    }

    closedir(directory);
    #pragma omp taskwait
    return byte;
}


int main(int argc, char **argv){
    if(argc != 3){
        printf("Call should look like: ./ex1 <threads> <path>\n");
        return EXIT_FAILURE;
    }

    long long size;
    int threads = atoi(argv[1]);

    struct stat statbuffer;
    lstat(argv[2], &statbuffer);

    double start, end;
    start = omp_get_wtime();
    #pragma omp parallel num_threads(threads)
    #pragma omp single
    size = calculateSize(argv[2]);
    end = omp_get_wtime();

    printf("Size: %ld\n", size + statbuffer.st_size);
    printf("Time: %f\n", end - start);
    return EXIT_SUCCESS;
}