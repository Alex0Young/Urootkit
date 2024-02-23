#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>

#define MAX_HIDDEN_COUNT 10

struct Config {
    const char* hidden[MAX_HIDDEN_COUNT];
    const char* backdoor;
    int hidden_count; 
};

void parse_config(const char* filename, struct Config* config) {
    config_t cfg;
    config_init(&cfg);

    // 读取配置文件
    if (!config_read_file(&cfg, filename)) {
        fprintf(stderr, "Error reading config file: %s\n", config_error_text(&cfg));
        config_destroy(&cfg);
        exit(EXIT_FAILURE);
    }

    // 读取 backdoor
    const char* backdoor;
    if (config_lookup_string(&cfg, "backdoor", &backdoor)) {
        config->backdoor = backdoor;
    } else {
        fprintf(stderr, "backdoor 未设置\n");
        config_destroy(&cfg);
        exit(EXIT_FAILURE);
    }
    printf("backdoor %s\n", backdoor);
    printf("backdoor2: %s\n", config->backdoor);

    // 读取 hidden
    config_setting_t* hidden = config_lookup(&cfg, "hidden");
    if (hidden != NULL) {
        int count = config_setting_length(hidden);
        if (count > MAX_HIDDEN_COUNT) {
            fprintf(stderr, "hidden 数量超过最大限制\n");
            config_destroy(&cfg);
            exit(EXIT_FAILURE);
        }
        config->hidden_count = count;
        for (int i = 0; i < count; ++i) {
            config_setting_t* path = config_setting_get_elem(hidden, i);
            const char* path_str = config_setting_get_string(path);
            config->hidden[i] = path_str;
            printf("path_str %s\n", path_str);
        }
    } else {
        fprintf(stderr, "hidden 未设置\n");
        config_destroy(&cfg);
        exit(EXIT_FAILURE);
    }

    // 释放资源
    config_destroy(&cfg);
}

int main() {
    struct Config config;
    parse_config("uroot.cfg", &config);

    printf("backdoor: %s\n", config.backdoor);
    printf("hidden_count: %d\n", config.hidden_count);
    printf("hidden:\n");
    for (int i = 0; i < config.hidden_count; ++i) {
        printf("  %s\n", config.hidden[i]);
    }

    return 0;
}
