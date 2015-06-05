#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libmemcached/memcached.h>

int main(int argc, char **argv)
{
    memcached_st *memc;
    memcached_return_t rc;
    memcached_server_st *server;
    /*char value[8192];*/

    //connect multi server
    memc = memcached_create(NULL);
    /*memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_SORT_HOSTS, 1);*/
    
    memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_DISTRIBUTION, MEMCACHED_DISTRIBUTION_CONSISTENT);

    server = memcached_server_list_append(NULL, "192.168.159.129", 11211, &rc);
    /*server = memcached_server_list_append(server, "192.168.159.129",21201, &rc);*/
    /*server = memcached_server_list_append(server, "192.168.159.129",12012, &rc);*/
    rc = memcached_server_push(memc, server);
  
    int count = memcached_server_list_count(server);
    /*int count2 = memcached_server_count(memc);*/
     
    fprintf(stdout, "server count is %d\n", memc->number_of_hosts);
    memcached_server_free(server);

    size_t i;
    const char const *keys[] = {"key1", "key2", "key3", "key4"};
    const size_t key_length[] = {4,4,4,4};
    
    char *values[]={"this is first value", "this is second value", "this is third value", "this is fourth value"};
    size_t values_len[] = {strlen("this is first value"), strlen("this is second value"), strlen("this is third value"), strlen("this is fourth value")};


    //set multi data
    for(i = 0; i < 4; i++){
        memcached_set(memc, keys[i], key_length[i], values[i], values_len[i], (time_t)0, (uint32_t)0);
        assert(rc == MEMCACHED_SUCCESS);
        printf("Save key:%s data: %s\n", keys[i], values[i]);
    }


    //fetch multi data
    
    char return_key[MEMCACHED_MAX_KEY];
    size_t return_key_length;
    char *return_values;
    size_t return_values_len;
    uint32_t flags;

    rc = memcached_mget(memc, keys, key_length,4);

    while((return_values = memcached_fetch(memc, return_key, &return_key_length,&return_values_len, &flags, &rc))){
        assert(rc == MEMCACHED_SUCCESS);
        printf("Fetch key:%s\ndata: %s\n", return_key, return_values);
    }

    memcached_free(memc);
    return 0;
}
