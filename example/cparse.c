#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>
 
/* This example reads the configuration file 'example.cfg' and displays
 * some of its contents.
 */
 
int main(int argc, char **argv)
{
  config_t cfg;
  config_setting_t *setting;
  const char *backdoor;
 
  config_init(&cfg);
 
  /* Read the file. If there is an error, report it and exit. */
  if(! config_read_file(&cfg, "uroot.cfg"))
  {
    fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
            config_error_line(&cfg), config_error_text(&cfg));
    config_destroy(&cfg);
    return(EXIT_FAILURE);
  }
 
  /* Get the store name. 读取配置文件中的“Basic store information:”信息 */
  if(config_lookup_string(&cfg, "backdoor", &backdoor))
    printf("Store name: %s\n\n", backdoor);
  else
    fprintf(stderr, "No 'name' setting in configuration file.\n");
 
//   if(config_lookup_string(&cfg, "hours", &str))
//     printf("Store hours: %s\n\n", str);
//   else
//     fprintf(stderr, "No 'hours' setting in configuration file.\n");
 
 
  /* Output a list of all books in the inventory. */
  setting = config_lookup(&cfg, "hidden");
  if(setting != NULL)
  {
    int count = config_setting_length(setting);
    int i;
 
    // printf("%-30s  %-30s   %-6s  %s\n", "TITLE", "AUTHOR", "PRICE", "QTY");
 
    for(i = 0; i < count; ++i)
    {
      config_setting_t *book = config_setting_get_elem(setting, i);
 
      /* Only output the record if all of the expected fields are present. */
      const char *path, *author;
      double price;
      int qty;
 
      if(!(config_setting_lookup_string(book, "path", &path)))
        continue;
 
      printf("path: %s\n", path);
    }
    putchar('\n');
  }
 
  /* Output a list of all movies in the inventory. */
//   setting = config_lookup(&cfg, "inventory.movies");
//   if(setting != NULL)
//   {
//     unsigned int count = config_setting_length(setting);
//     unsigned int i;
 
//     printf("%-30s  %-10s   %-6s  %s\n", "TITLE", "MEDIA", "PRICE", "QTY");
//     for(i = 0; i < count; ++i)
//     {
//       config_setting_t *movie = config_setting_get_elem(setting, i);
 
//       /* Only output the record if all of the expected fields are present. */
//       const char *title, *media;
//       double price;
//       int qty;
 
//       if(!(config_setting_lookup_string(movie, "title", &title)
//            && config_setting_lookup_string(movie, "media", &media)
//            && config_setting_lookup_float(movie, "price", &price)
//            && config_setting_lookup_int(movie, "qty", &qty)))
//         continue;
 
//       printf("%-30s  %-10s  $%6.2f  %3d\n", title, media, price, qty);
//     }
//     putchar('\n');
//   }
 
  config_destroy(&cfg);
  return(EXIT_SUCCESS);
}
 
/* eof */