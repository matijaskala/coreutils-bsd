#include <signal.h>

static const char* signalnamestr(int sig) {
#if defined __GLIBC__ && !defined __UCLIBC__
    extern const char *const sys_sigabbrev[];
    return sys_sigabbrev[sig];
#else
#ifdef SIGHUP
    if (sig == SIGHUP) return "HUP";
#endif
#ifdef SIGINT
    if (sig == SIGINT) return "INT";
#endif
#ifdef SIGQUIT
    if (sig == SIGQUIT) return "QUIT";
#endif
#ifdef SIGILL
    if (sig == SIGILL) return "ILL";
#endif
#ifdef SIGTRAP
    if (sig == SIGTRAP) return "TRAP";
#endif
#ifdef SIGABRT
    if (sig == SIGABRT) return "ABRT";
#endif
#ifdef SIGIOT
    if (sig == SIGIOT) return "IOT";
#endif
#ifdef SIGEMT
    if (sig == SIGEMT) return "EMT";
#endif
#ifdef SIGFPE
    if (sig == SIGFPE) return "FPE";
#endif
#ifdef SIGKILL
    if (sig == SIGKILL) return "KILL";
#endif
#ifdef SIGUNUSED
    if (sig == SIGUNUSED) return "UNUSED";
#endif
#ifdef SIGBUS
    if (sig == SIGBUS) return "BUS";
#endif
#ifdef SIGSEGV
    if (sig == SIGSEGV) return "SEGV";
#endif
#ifdef SIGSYS
    if (sig == SIGSYS) return "SYS";
#endif
#ifdef SIGPIPE
    if (sig == SIGPIPE) return "PIPE";
#endif
#ifdef SIGALRM
    if (sig == SIGALRM) return "ALRM";
#endif
#ifdef SIGTERM
    if (sig == SIGTERM) return "TERM";
#endif
#ifdef SIGSTKFLT
    if (sig == SIGSTKFLT) return "STKFLT";
#endif
#ifdef SIGIO
    if (sig == SIGIO) return "IO";
#endif
#ifdef SIGXCPU
    if (sig == SIGXCPU) return "XCPU";
#endif
#ifdef SIGXFSZ
    if (sig == SIGXFSZ) return "XFSZ";
#endif
#ifdef SIGVTALRM
    if (sig == SIGVTALRM) return "VTALRM";
#endif
#ifdef SIGPROF
    if (sig == SIGPROF) return "PROF";
#endif
#ifdef SIGWINCH
    if (sig == SIGWINCH) return "WINCH";
#endif
#ifdef SIGLOST
    if (sig == SIGLOST) return "LOST";
#endif
#ifdef SIGUSR1
    if (sig == SIGUSR1) return "USR1";
#endif
#ifdef SIGUSR2
    if (sig == SIGUSR2) return "USR2";
#endif
#ifdef SIGPWR
    if (sig == SIGPWR) return "PWR";
#endif
#ifdef SIGPOLL
    if (sig == SIGPOLL) return "POLL";
#endif
#ifdef SIGSTOP
    if (sig == SIGSTOP) return "STOP";
#endif
#ifdef SIGTSTP
    if (sig == SIGTSTP) return "TSTP";
#endif
#ifdef SIGCONT
    if (sig == SIGCONT) return "CONT";
#endif
#ifdef SIGCHLD
    if (sig == SIGCHLD) return "CHLD";
#endif
#ifdef SIGCLD
    if (sig == SIGCLD) return "CLD";
#endif
#ifdef SIGTTIN
    if (sig == SIGTTIN) return "TTIN";
#endif
#ifdef SIGTTOU
    if (sig == SIGTTOU) return "TTOU";
#endif
#ifdef SIGINFO
    if (sig == SIGINFO) return "INFO";
#endif
#ifdef SIGURG
    if (sig == SIGURG) return "URG";
#endif
#ifdef SIGWAITING
    if (sig == SIGWAITING) return "WAITING";
#endif
#ifdef SIGLWP
    if (sig == SIGLWP) return "LWP";
#endif
#ifdef SIGFREEZE
    if (sig == SIGFREEZE) return "FREEZE";
#endif
#ifdef SIGTHAW
    if (sig == SIGTHAW) return "THAW";
#endif
#ifdef SIGCANCEL
    if (sig == SIGCANCEL) return "CANCEL";
#endif
    return "Signal 0";
#endif
}
