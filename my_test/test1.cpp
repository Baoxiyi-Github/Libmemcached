#include <iostream>
#include <string>
#include <libmemcached/memcached.h>

using namespace std;

int main(int argc, char **argv)
{
    memcached_st *memc;
    memcached_return rc;
    memcached_server_st *server;
    time_t exp;
    uint32_t flags;

    memc = memcached_create(NULL);
    server = memcached_server_list_append(NULL, "192.168.159.129",11211, &rc);
    rc = memcached_server_push(memc, server);
    memcached_server_list_free(server);


    string key = "key";
    string value = "value";
    size_t value_length = value.length();
    size_t key_length = key.length();


    rc = memcached_set(memc, key.c_str(), key.length(), value.c_str(),value.length(), exp, flags);

    if(rc == MEMCACHED_SUCCESS)
    {
        cout << "Save data: " << value << " sussessful!" <<endl;
    }

    char *str=memcached_get(memc, key.c_str(), key_length, &value_length, &flags, &rc);
    if(rc == MEMCACHED_SUCCESS)
    {
    
        cout <<"Get data: " << str << "successful!\n";
    }

    rc = memcached_delete(memc, key.c_str(),key_length, exp);

    if(rc == MEMCACHED_SUCCESS)
    {
        cout <<"Delete data: " << value << " successful!\n"; 
    }
    memcached_free(memc);
    return 0;
}
