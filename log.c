#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "log.h"

int debug_file(char* str){
  if(DEBUG){
    printf("[UROOT-DEBUG] %s\n", str);
    return 0;
  }
  return 1;
}

// int debug_file(char* str){
//     if(DEBUG){
//         FILE *file = fopen("log.txt", "a");
//         if (file == NULL) {
//             printf("无法打开文件。\n");
//             return 1;
//         }

//         // 写入内容
//         fprintf(file, "[uroot-DEBUG] :");
//         fprintf(file, str);
//         fprintf(file, "\n");

//         // 关闭文件
//         fclose(file);

//         printf("已写入内容到 log.txt 文件中。\n");
//     }    
//     return 0;
// }