// shader_path_res.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#include <stddef.h>


#ifdef _WIN32

#include <windows.h>
#include <string.h>

ssize_t readlink_win(const char *path, char *buf, size_t bufsize) {
    // Special case for /proc/self/exe
    if (strcmp(path, "/proc/self/exe") == 0) {
        DWORD len = GetModuleFileNameA(NULL, buf, (DWORD)bufsize);
        if (len == 0 || len >= bufsize) {
            fprintf(stderr, "GetModuleFileNameA failed: %ld\n", GetLastError());
            return -1;
        }
        // Normalize backslashes to forward slashes for consistency
        for (DWORD i = 0; i < len; i++) {
            if (buf[i] == '\\') buf[i] = '/';
        }
        buf[len] = '\0';
        return (ssize_t)len;
    }

    // Handle actual symlinks
    HANDLE hFile = CreateFileA(
        path, 0, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT, NULL
    );
    if (hFile == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "CreateFileA failed: %ld\n", GetLastError());
        return -1;
    }
    DWORD len = GetFinalPathNameByHandleA(hFile, buf, (DWORD)bufsize, FILE_NAME_NORMALIZED);
    CloseHandle(hFile);
    if (len == 0 || len > bufsize) {
        fprintf(stderr, "GetFinalPathNameByHandleA failed: %ld\n", GetLastError());
        return -1;
    }
    if (len > 4 && strncmp(buf, "\\\\?\\", 4) == 0) {
        memmove(buf, buf + 4, len - 4);
        len -= 4;
    }
    for (DWORD i = 0; i < len; i++) {
        if (buf[i] == '\\') buf[i] = '/';
    }
    buf[len] = '\0';
    return (ssize_t)len;
}
#define readlink readlink_win // Map readlink to readlink_win on Windows

#else

#include <unistd.h> // For standard readlink on Unix-like systems

#endif



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