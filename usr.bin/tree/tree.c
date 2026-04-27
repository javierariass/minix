#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>
#include<unistd.h>

void print_tree(const char *path, int level){
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    char full_path[1024];

    if(dir = opendir(path)){
        while((entry = readdir(dir)) != NULL){
            if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") ==0){
                continue;
            }
            snprintf(full_path, sizeof(path), "%s/%s", path, entry->d_name);

            if(lstat(full_path, &statbuf) == -1){
                continue;
            }

            for(int i =0; i < level; i++){
                printf("    ");
            }
            printf("%s\n",entry->d_name);

            if(S_ISDIR(statbuf.st_mode) && !S_ISLNK(statbuf.st_mode)){
                print_tree(full_path, level + 1);
            }
        }       
        closedir(dir);
    }
}

int main(int argc, char *argv[]){
    const char *path = ".";
    if(argc > 1){
        path = argv[1];
    }

    print_tree(path,0);
    return 0;
}