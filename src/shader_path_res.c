// shader_path_res.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>

#define MAX_PATH 1024

// Gets the directory containing the executable
char* _get_executable_dir() {
    // Buffer for executable path
    char path[MAX_PATH];
    char *result = NULL;
    // Read symbolic link to executable path (Linux-specific)
    ssize_t count = readlink("/proc/self/exe", path, MAX_PATH - 1);
    if (count != -1) {
        path[count] = '\0';
        // Extract directory from path
        result = dirname(path);  // Extract the directory part
        // Return duplicated string (dirname may modify path)
        return strdup(result);
    }
    return NULL;
}

// Constructs the full path to a shader file
char* get_shader_path(const char *shader_name) {
    // Get executable directory
    char *exe_dir = _get_executable_dir();
    if (!exe_dir) {
        return NULL;
    }

    // Calculate required path length
    size_t path_len = strlen(exe_dir) + strlen("/../shaders/") + strlen(shader_name) + 1;
    // Allocate memory for shader path
    char *shader_path = (char*)malloc(path_len);
    if (!shader_path) {
        free(exe_dir);
        return NULL;
    }

    // Build path: <exe_dir>/../shaders/<shader_name>
    snprintf(shader_path, path_len, "%s/../shaders/%s", exe_dir, shader_name);

    // Free executable directory string
    free(exe_dir);  // Clean up
    return shader_path;
}