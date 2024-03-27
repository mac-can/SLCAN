//
//  Trial Program
//  Lawicel SLCAN Protocol
//  Bart Simpson didn't do it
//
#ifdef _MSC_VER
//no Microsoft extensions please!
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 1
#endif
#endif
#include "serial.h"
#include "slcan.h"

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#if !defined(_WIN32) && !defined(_WIN64)
 #include <unistd.h>
#else
 #include <windows.h>
#endif

#include <inttypes.h>
#include "debug.h"

#if !defined(_WIN32) && !defined(_WIN64)
#if defined(__APPLE__)
#define SERIAL_PORT  "/dev/tty.usbserial-LW4KOZQW"
#elif !defined(__CYGWIN__)
#define SERIAL_PORT  "/dev/ttyUSB0"
#else
#define SERIAL_PORT  "/dev/ttyS3"
#endif
#else
#define SERIAL_PORT  "\\\\.\\COM4"
#endif
#define LOG_FILE  "./slcan.log"

#if defined(_WIN32) || defined(_WIN64)
 static void usleep(unsigned int usec);
 /* useconds_t: to be compatible with macOS */
 typedef unsigned int  useconds_t;
#endif
static void sigterm(int signo);

static volatile int running = 1;

#if (OPTION_COMPILE_SERIAL != 0)
static int main_serial(int argc, char *argv[]) {
    sio_port_t port = NULL;
    uint8_t cmd_open[2] = {'O','\r'};
    uint8_t cmd_close[2] = {'C','\r'};
    int rc = 0;
    (void)argc;
    (void)argv;

    port = sio_create(NULL, NULL);
    if (!port) {
        fprintf(stderr, "+++ error: sio_create returnd NULL (%i)\n", errno);
        return -1;
    }
    rc = sio_connect(port, SERIAL_PORT, NULL);
    if (rc < 0) {
        fprintf(stderr, "+++ error: sio_connect returnd %i (%i)\n", rc, errno);
        goto end;
    }
    rc = sio_transmit(port, cmd_close, 2);
    if (rc < 0) {
        fprintf(stderr, "+++ error: sio_transmit (close) returnd %i (%i)\n", rc, errno);
        goto teardown;
    }
    rc = sio_transmit(port, cmd_open, 2);
    if (rc < 0) {
        fprintf(stderr, "+++ error: sio_transmit (open) returnd %i (%i)\n", rc, errno);
        goto teardown;
    }
    while (running) {
        usleep(10);
    }
    rc = sio_transmit(port, cmd_close, 2);
    if (rc < 0) {
        fprintf(stderr, "+++ error: sio_transmit (close) returnd %i (%i)\n", rc, errno);
        goto teardown;
    }
teardown:
    rc = sio_disconnect(port);
    if (rc < 0) {
        fprintf(stderr, "+++ error: sio_disconnect returnd %i (%i)\n", rc, errno);
        goto end;
    }
end:
    rc = sio_destroy(port);
    if (rc < 0) {
        fprintf(stderr, "+++ error: sio_destroy returnd %i (%i)\n", rc, errno);
    }
    return rc;
}
#else

static int main_slcan(int argc, char *argv[]) {
    slcan_port_t port = NULL;
    int rc = 0;
    (void)argc;
    (void)argv;

    fprintf(stderr, "!!! %s\n", slcan_api_version(NULL, NULL, NULL));

    port = slcan_create(8U);
    if (!port) {
        fprintf(stderr, "+++ error: slcan_create returnd NULL (%i)\n", errno);
        return -1;
    }
    rc = slcan_connect(port, SERIAL_PORT, NULL);
    if (rc < 0) {
        fprintf(stderr, "+++ error: slcan_connect returnd %i (%i)\n", rc, errno);
        goto end;
    }
    rc = slcan_setup_bitrate(port, CAN_250K);
    if (rc < 0) {
        fprintf(stderr, "+++ error: slcan_setup_bitrate returnd %i (%i)\n", rc, errno);
        goto teardown;
    }
    rc = slcan_open_channel(port);
    if (rc < 0) {
        fprintf(stderr, "+++ error: slcan_open_channel returnd %i (%i)\n", rc, errno);
        goto teardown;
    }
    while (running) {
        usleep(10);
    }
    rc = slcan_close_channel(port);
    if (rc < 0) {
        fprintf(stderr, "+++ error: slcan_close_channel returnd %i (%i)\n", rc, errno);
        goto teardown;
    }
teardown:
    rc = slcan_disconnect(port);
    if (rc < 0) {
        fprintf(stderr, "+++ error: slcan_disconnect returnd %i (%i)\n", rc, errno);
        goto end;
    }
end:
    rc = slcan_destroy(port);
    if (rc < 0) {
        fprintf(stderr, "+++ error: slcan_destroy returnd %i (%i)\n", rc, errno);
    }
    return rc;
}
#endif

int main(int argc, char *argv[]) {
    int rc = 0;

    if((signal(SIGINT, sigterm) == SIG_ERR) ||
#if !defined(_WIN32) && !defined(_WIN64)
       (signal(SIGHUP, sigterm) == SIG_ERR) ||
#endif
       (signal(SIGTERM, sigterm) == SIG_ERR)) {
        perror("+++ error");
        return errno;
    }
    LOGGER_INIT(LOG_FILE);
    fprintf(stdout, "!!! %s %s %s\n",__FILE__,__DATE__,__TIME__);
#if (OPTION_COMPILE_SERIAL != 0)
    rc = main_serial(argc, argv);
#else
    rc = main_slcan(argc, argv);
#endif
    fprintf(stdout, "!!! Cheers!\n");
    LOGGER_EXIT();
    return rc;
}

#if defined(_WIN32) || defined(_WIN64)
 /* usleep(3) - Linux man page
  *
  * Notes
  * The type useconds_t is an unsigned integer type capable of holding integers in the range [0,1000000].
  * Programs will be more portable if they never mention this type explicitly. Use
  *
  *    #include <unistd.h>
  *    ...
  *        unsigned int usecs;
  *    ...
  *        usleep(usecs);
  */
 static void usleep(unsigned int usec) {
    HANDLE timer;
    LARGE_INTEGER ft;

    ft.QuadPart = -(10 * (LONGLONG)usec); // Convert to 100 nanosecond interval, negative value indicates relative time
    if (usec >= 100) {
        if ((timer = CreateWaitableTimer(NULL, TRUE, NULL)) != NULL) {
            SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
            WaitForSingleObject(timer, INFINITE);
            CloseHandle(timer);
        }
    }
    else {
        Sleep(0);
    }
 }
#endif

static void sigterm(int signo) {
    //fprintf(stderr, "%s: got signal %d\n", __FILE__, signo);
    // TODO: signal waiting objects
    running = 0;
    (void)signo;
}
