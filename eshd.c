#define BUFFER 8192
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <mpv/client.h>

static inline void check_error(int status)
{
  if (status < 0) {
    printf("mpv API error: %s\n", mpv_error_string(status));
    exit(1);
  }
}

int main(int argc, char *argv[])
{
  int i;
  int64_t wid;
  
  if (argv[1] == "/c") {
    exit(0);
  }

  if (argv[2]) {
    puts("preview2");
    puts(argv[2]);
    wid = argv[2];
    puts(wid);
  }
    
  for(i=1;i<argc-1;i++) {
    puts(argv[i]);
  }

  char installpath[255];
  char installpathcp[255];
  char m3u[255];
  char mpvinputconf[255];
  DWORD BufferSize = BUFFER;
  RegGetValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Electric Sheep HD\\Settings", "InstallPath", RRF_RT_ANY, NULL, (PVOID)&installpath, &BufferSize);
  puts(installpath);
  FILE *file;
  strcpy(installpathcp, installpath);
  file = fopen(strcat(installpathcp, "\\.active-season"), "r");
  if (file == NULL) {
    printf("fopen failed: %s \n", installpath);
    exit(1);
  }

  char season[100];
  fgets(season, 100, file);
  fclose(file);
  //char m3u[] = "C:\\Program Files (x86)\\Electric Sheep HD\\branches\\G244_W1920_H1080_Q1024_K1C1DF3M\\movies\\eshd.m3u";
  puts(installpath);
  //puts(season);
  //puts(strcat(strcat(installpath, "\\branches\\"), strcat(season, "\\movies\\eshd.m3u")));
  strcpy(m3u, installpath);
  strcat(m3u, "\\branches\\");
  strcat(m3u, season);
  strcat(m3u, "\\movies\\eshd.m3u");
  puts(m3u);

  mpv_handle *ctx = mpv_create();
  if (!ctx) {
    printf("failed creating context\n");
    return 1;
  }

  strcpy(mpvinputconf, installpath);
  strcat(mpvinputconf, "\\mpv-input.conf");
  
  check_error(mpv_set_option_string(ctx, "fullscreen", "yes"));
  check_error(mpv_set_option_string(ctx, "panscan", "1"));
  check_error(mpv_set_option_string(ctx, "stop-screensaver", "no"));
  check_error(mpv_set_option_string(ctx, "osc", "no"));
  check_error(mpv_set_option_string(ctx, "input-default-bindings", "no"));
  check_error(mpv_set_option_string(ctx, "input-vo-keyboard", "yes"));
  check_error(mpv_set_option_string(ctx, "input-conf", mpvinputconf));
  check_error(mpv_set_option(ctx, "wid", MPV_FORMAT_INT64, &wid));

  int val = 1;


  // Done setting up options.
  check_error(mpv_initialize(ctx));

  // Play this file.
  const char *cmd[] = {"loadfile", m3u, NULL};
  check_error(mpv_command(ctx, cmd));

  // Let it play, and wait until the user quits.
  while (1) {
    mpv_event *event = mpv_wait_event(ctx, 10000);
    printf("event: %s\n", mpv_event_name(event->event_id));
    if (event->event_id == MPV_EVENT_SHUTDOWN)
      break;
  }

  mpv_terminate_destroy(ctx);
  return 0;
}
