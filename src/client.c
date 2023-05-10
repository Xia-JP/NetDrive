#include "user_interface.h"

int main()
{
    init_user_interface();
    char* p;
    p = get_user_input();
    printf("%s", p);
    free(p);
    
    return 0;
}