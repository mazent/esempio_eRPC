# Per compilare occorre:
#	1) creare una cartella (sorella di quella col codice, p.e. compila)
#	2) entrarci con msys2
#	3) cmake -G "Unix Makefiles" ../srv/
#	4) compilare: make
# ? Per il compilation database: cmake -G -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ../prova/ ?


cmake_minimum_required(VERSION 3.6)

option(VERS_DEBUG
	"Compilo in debug"
	OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(ERPC ${CMAKE_SOURCE_DIR}/../erpc_c)

include_directories(
	${ERPC}/config
	${ERPC}/infra
	${ERPC}/port
	${ERPC}/setup
	${ERPC}/transports
	${CMAKE_SOURCE_DIR}/../prog
)

project(srv VERSION 0.1)


set(CODICE
	${CMAKE_SOURCE_DIR}/../main.cpp	
	
	${CMAKE_SOURCE_DIR}/../prog/pippo_server.cpp
	
	${ERPC}/infra/erpc_basic_codec.cpp
	${ERPC}/infra/erpc_client_manager.cpp
	${ERPC}/infra/erpc_crc16.cpp
	${ERPC}/infra/erpc_framed_transport.cpp
	${ERPC}/infra/erpc_message_buffer.cpp
	${ERPC}/infra/erpc_pre_post_action.cpp
	${ERPC}/infra/erpc_server.cpp
	${ERPC}/infra/erpc_simple_server.cpp
	
	${ERPC}/port/erpc_port_stdlib.cpp
	${ERPC}/port/erpc_serial.cpp
	${ERPC}/port/erpc_threading_win32.cpp

	${ERPC}/setup/erpc_client_setup.cpp
	${ERPC}/setup/erpc_server_setup.cpp
	${ERPC}/setup/erpc_setup_mbf_dynamic.cpp
	${ERPC}/setup/erpc_setup_serial.cpp

	${ERPC}/transports/erpc_serial_transport.cpp
)

add_executable(srv ${CODICE})




#find_program(CLANG_TIDY_COMMAND NAMES clang-tidy)
#if(CLANG_TIDY_COMMAND)
#    # --fix modifica i file
#    #set(CMAKE_C_CLANG_TIDY "${CLANG_TIDY_COMMAND};--header-filter=.;--checks=-*,bugprone-*,-bugprone-macro-parentheses")
#	#set(CMAKE_C_CLANG_TIDY "${CLANG_TIDY_COMMAND};--checks=-*,readability-*,-readability-magic-numbers")
#	#set(CMAKE_C_CLANG_TIDY "${CLANG_TIDY_COMMAND};--checks=-*,cert-*")
#	#set(CMAKE_C_CLANG_TIDY "${CLANG_TIDY_COMMAND};--checks=-*,performance-*")
#    # analisi statica
#    set(CMAKE_C_CLANG_TIDY "${CLANG_TIDY_COMMAND};--header-filter=.;--checks=-*,clang-analyzer-*,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling")
#endif()


#####################################################################
# Opzioni comuni a c e c++
set(gcc_flags "-Wall -Wextra")
if (VERS_DEBUG)
	set(gcc_flags "${gcc_flags} -g3 -O0 -Werror")
	add_definitions(-DDEBUG)
else ()
	set(gcc_flags "${gcc_flags} -O3")
	add_definitions(-DNDEBUG)
endif ()
# Altre regole utili
set(gcc_flags
	"${gcc_flags} -fstrict-aliasing -Wshadow")
set(gcc_flags
	"${gcc_flags} -Wendif-labels -Wpointer-arith -Wcast-align")


# Non si sa mai
set(gcc_flags
	"${gcc_flags} -Wno-unknown-pragmas")


#####################################################################
# Ai compilatori
set(CMAKE_C_FLAGS
	"${CMAKE_C_FLAGS} ${gcc_flags} ${gcc_c_flags}")
set(CMAKE_CXX_FLAGS
	"${CMAKE_CXX_FLAGS} ${gcc_flags} ${gcc_cpp_flags}")

#####################################################################
