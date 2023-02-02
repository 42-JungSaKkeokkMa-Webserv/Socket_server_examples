#include "../includes/libft.hpp"

using namespace std;

void strerr_exit(const char *msg) {
    cerr << msg << endl;
    exit(1);
}

string getAbsolutePath(const char* relativePath) {
    char *currentPath = getcwd(NULL, 0);
    return string(currentPath) + string(relativePath);
}