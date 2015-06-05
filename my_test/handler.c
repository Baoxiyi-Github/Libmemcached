#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <libmemcached/memcached.h>

int main(void)
{
    memcached_st *memc = NULL;
    memcached_return rc;
    memcached_server_st *server  = NULL;// = memcached_servers_parse(NULL);

    /*
     *char *key = "Baocf";
     *int key_len = strlen("Baocf");
     *char *value = "Baochenfei";
     *int value_len = strlen("Baochenfei");
     */


    memc = memcached_create(NULL);
    server = memcached_server_list_append(NULL, "192.168.159.129", 11212, &rc);
    rc = memcached_server_push(memc, server);
    /*memcached_server_list_free(server);*/

    //set method
    /*rc = memcached_set(memc, key, key_len, value, value_len, (time_t)0, (uint32_t)0);*/
    
    //get method
    /*char *str = memcached_get(memc,key, key_len, &value_len, (uint32_t)0, &rc);*/
    
    /*
     *rc = memcached_replace(memc, key, key_len, "Baoxiiiy", strlen("Baoxiiiy"), (time_t)0, (uint32_t)0);
     *assert(rc == MEMCACHED_SUCCESS);
     *printf("key: %s\n", key);
     *
     */
    char *key= "豆瓣";
    char *value="我们在炎热抑郁的夏天无法停止豆瓣";
    char *value2;
    size_t length;
    uint32_t flags;

    rc= memcached_set(memc, key, strlen(key),
            value, strlen(value),
            (time_t)0, 0);

    assert(rc == MEMCACHED_SUCCESS);

    value2= memcached_get(memc, key, strlen(key),
            &length, &flags, &rc);

    assert(length==strlen(value));
    assert(rc == MEMCACHED_SUCCESS);
    assert(memcmp(value, value2, length)==0);
    free(value2);

    memcached_free(memc);
    return 0;
}
