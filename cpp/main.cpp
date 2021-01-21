#include <stdio.h>

//definire CLIENT globalmente

#include "erpc_mbf_setup.h"
#include "erpc_transport_setup.h"

#ifdef CLIENT
#include "erpc_client_setup.h"
#include "pippo.h"
#else // SERVER
#include "erpc_server_setup.h"
#include "pippo_server.h"

uint32_t var=0;

extern "C" bool scrivi(uint32_t val)
{
	var=val;
	return true;
}

extern "C" uint32_t leggi(void)
{
	return var;
}

#endif


int main(void)
{
    erpc_mbf_t mbf = erpc_mbf_dynamic_init() ;
    erpc_transport_t trans = erpc_transport_serial_init("com12", 115200) ;
#ifdef CLIENT
    erpc_client_init(trans, mbf) ;

    while (true) {
        printf("leggo ...\r\n") ;
        uint32_t val = leggi() ;
        printf("\tletto %d\r\n", val) ;

        val += 1 ;
        printf("scrivo: %s", scrivi(val) ? "OK" : "ERR") ;
    }

    erpc_client_deinit() ;
#else
    printf("server\r\n") ;

    (void) erpc_server_init(trans, mbf);

    erpc_add_service_to_server(create_pluto_service());

    erpc_server_run();

    erpc_server_deinit();
    destroy_pluto_service();
#endif
    return 0 ;
}
