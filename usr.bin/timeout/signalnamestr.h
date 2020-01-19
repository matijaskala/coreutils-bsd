#include <signal.h>

static const char* signalnamestr(int sig) {
#if defined __GLIBC__ && !defined __UCLIBC__
    extern const char *const sys_sigabbrev[];
    return sys_sigabbrev[sig];
#else
    switch (sig) {
#ifdef SIGHUP
    case SIGHUP: return "HUP";
#endif
#ifdef SIGINT
    case SIGINT: return "INT";
#endif
#ifdef SIGQUIT
    case SIGQUIT: return "QUIT";
#endif
#ifdef SIGILL
    case SIGILL: return "ILL";
#endif
#ifdef SIGTRAP
    case SIGTRAP: return "TRAP";
#endif
#ifdef SIGABRT
    case SIGABRT: return "ABRT";
#endif
#ifdef SIGIOT
    case SIGIOT: return "IOT";
#endif
#ifdef SIGEMT
    case SIGEMT: return "EMT";
#endif
#ifdef SIGFPE
    case SIGFPE: return "FPE";
#endif
#ifdef SIGKILL
    case SIGKILL: return "KILL";
#endif
#ifdef SIGUNUSED
    case SIGUNUSED: return "UNUSED";
#endif
#ifdef SIGBUS
    case SIGBUS: return "BUS";
#endif
#ifdef SIGSEGV
    case SIGSEGV: return "SEGV";
#endif
#ifdef SIGSYS
    case SIGSYS: return "SYS";
#endif
#ifdef SIGPIPE
    case SIGPIPE: return "PIPE";
#endif
#ifdef SIGALRM
    case SIGALRM: return "ALRM";
#endif
#ifdef SIGTERM
    case SIGTERM: return "TERM";
#endif
#ifdef SIGSTKFLT
    case SIGSTKFLT: return "STKFLT";
#endif
#ifdef SIGIO
    case SIGIO: return "IO";
#endif
#ifdef SIGXCPU
    case SIGXCPU: return "XCPU";
#endif
#ifdef SIGXFSZ
    case SIGXFSZ: return "XFSZ";
#endif
#ifdef SIGVTALRM
    case SIGVTALRM: return "VTALRM";
#endif
#ifdef SIGPROF
    case SIGPROF: return "PROF";
#endif
#ifdef SIGWINCH
    case SIGWINCH: return "WINCH";
#endif
#ifdef SIGLOST
    case SIGLOST: return "LOST";
#endif
#ifdef SIGUSR1
    case SIGUSR1: return "USR1";
#endif
#ifdef SIGUSR2
    case SIGUSR2: return "USR2";
#endif
#ifdef SIGPWR
    case SIGPWR: return "PWR";
#endif
#ifdef SIGPOLL
    case SIGPOLL: return "POLL";
#endif
#ifdef SIGSTOP
    case SIGSTOP: return "STOP";
#endif
#ifdef SIGTSTP
    case SIGTSTP: return "TSTP";
#endif
#ifdef SIGCONT
    case SIGCONT: return "CONT";
#endif
#ifdef SIGCHLD
    case SIGCHLD: return "CHLD";
#endif
#ifdef SIGCLD
    case SIGCLD: return "CLD";
#endif
#ifdef SIGTTIN
    case SIGTTIN: return "TTIN";
#endif
#ifdef SIGTTOU
    case SIGTTOU: return "TTOU";
#endif
#ifdef SIGINFO
    case SIGINFO: return "INFO";
#endif
#ifdef SIGURG
    case SIGURG: return "URG";
#endif
#ifdef SIGWAITING
    case SIGWAITING: return "WAITING";
#endif
#ifdef SIGLWP
    case SIGLWP: return "LWP";
#endif
#ifdef SIGFREEZE
    case SIGFREEZE: return "FREEZE";
#endif
#ifdef SIGTHAW
    case SIGTHAW: return "THAW";
#endif
#ifdef SIGCANCEL
    case SIGCANCEL: return "CANCEL";
#endif
    }
    return "Signal 0";
#endif
}
