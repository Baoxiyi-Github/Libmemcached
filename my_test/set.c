//#include <iostream>
#include <stdio.h>
#include <string.h>
#include <libmemcached/memcached.h>

//using namespace std;
int main(void)
{
    memcached_st *mems;
    memcached_st *clon;
    memcached_return_t mr;
    memcached_server_st *server;
    time_t exp;
    uint32_t flags;

    mems = memcached_create(NULL);
    /*clon = memcached_clone(NULL, NULL);*/
    server = memcached_server_list_append(NULL, "192.168.159.129",11211, &mr);
    mr = memcached_server_push(mems, server);
    int cout = memcached_server_count(mems);

    printf("count = %d\n", mems->number_of_hosts);
    memcached_server_list_free(server);
    /*
     *string key = "baochenfei";
     *string value = "Baoxiyi";
     */
    
    char key[] = "BF";
    char value[] = "BXY_Yang";
    int key_len = strlen(key);
    int value_len = strlen(value);
    
    /*mr = memcached_set(mems, key.c_str(), key.length(), value.c_str(), value.length(), exp, flags);*/
    mr = memcached_set(mems, key, strlen(key), value, strlen(value), exp, flags);

    if(mr == MEMCACHED_SUCCESS)
    {
        //cout << "set data ok! key = " << key.c_str() << "value = "<< value.c_str() << endl;
        printf("key = %s, value = %s\n", key, value);
    }


    memcached_free(mems);
    return 0;
}
