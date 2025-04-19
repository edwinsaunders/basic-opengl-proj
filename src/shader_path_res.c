#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>

#define MAX_PATH 1024

/* Get the directory containing the executable */
char* _get_executable_dir() {
    char path[MAX_PATH];
    char *result = NULL;
    ssize_t count = readlink("/proc/self/exe", path, MAX_PATH - 1);
    if (count != -1) {
        path[count] = '\0';
        result = dirname(path);  // Extract the directory part
        // dirname may modify path, so we duplicate the result
        return strdup(result);
    }
    return NULL;
}

/* Construct the path to a shader file */
char* get_shader_path(const char *shader_name) {
    char *exe_dir = _get_executable_dir();
    if (!exe_dir) {
        return NULL;
    }

    // Allocate enough space for the full path: exe_dir + "/../shaders/" + shader_name + null terminator
    size_t path_len = strlen(exe_dir) + strlen("/../shaders/") + strlen(shader_name) + 1;
    char *shader_path = (char*)malloc(path_len);
    if (!shader_path) {
        free(exe_dir);
        return NULL;
    }

    // Build the path: <exe_dir>/../shaders/<shader_name>
    snprintf(shader_path, path_len, "%s/../shaders/%s", exe_dir, shader_name);

    free(exe_dir);  // Clean up
    return shader_path;
}