#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <libmemcached/memcached.h>

int main(void)
{
    char *key = "fool";
    char *value;
    size_t value_len = 8192;
    unsigned int x;
    memcached_return_t rc;
    memcached_st *memc;
    memcached_server_st *server;

    memc = memcached_clone(NULL, NULL);
    server = memcached_server_list_append(NULL,"192.168.159.129", 11211, &rc);
    rc = memcached_server_push(memc, server);
    memcached_server_free(server);

    value = (char *)malloc(value_len);
    assert(value);

    srandom(time(NULL));
    for(x = 0; x <7; x++){
      value[x] = "ABCDEFG"[x];
      printf("%c\n", value[x]);
    }

    for(x = 0; x <1; x++)
    {
        rc = memcached_set(memc, key, strlen(key), value, value_len, (time_t)0, (uint32_t)0);
    
        assert(rc == MEMCACHED_SUCCESS);
        printf("value = %s\n", value);
    }

    memcached_free(memc);

    return 0;
}
