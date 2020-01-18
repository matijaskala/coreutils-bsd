#include <signal.h>
#include <stddef.h>

#ifdef __UCLIBC__
const char * sys_sigabbrev[NSIG];
#endif

void sys_sigabbrev_init() {
#ifdef __UCLIBC__
sys_sigabbrev[0] = "Signal 0";
#ifdef SIGHUP
    if (sys_sigabbrev[SIGHUP] == NULL)
	sys_sigabbrev[SIGHUP] = "HUP";
#endif
#ifdef SIGINT
    if (sys_sigabbrev[SIGINT] == NULL)
	sys_sigabbrev[SIGINT] = "INT";
#endif
#ifdef SIGQUIT
    if (sys_sigabbrev[SIGQUIT] == NULL)
	sys_sigabbrev[SIGQUIT] = "QUIT";
#endif
#ifdef SIGILL
    if (sys_sigabbrev[SIGILL] == NULL)
	sys_sigabbrev[SIGILL] = "ILL";
#endif
#ifdef SIGTRAP
    if (sys_sigabbrev[SIGTRAP] == NULL)
	sys_sigabbrev[SIGTRAP] = "TRAP";
#endif
#ifdef SIGABRT
    if (sys_sigabbrev[SIGABRT] == NULL)
	sys_sigabbrev[SIGABRT] = "ABRT";
#endif
#ifdef SIGIOT
    if (sys_sigabbrev[SIGIOT] == NULL)
	sys_sigabbrev[SIGIOT] = "IOT";
#endif
#ifdef SIGEMT
    if (sys_sigabbrev[SIGEMT] == NULL)
	sys_sigabbrev[SIGEMT] = "EMT";
#endif
#ifdef SIGFPE
    if (sys_sigabbrev[SIGFPE] == NULL)
	sys_sigabbrev[SIGFPE] = "FPE";
#endif
#ifdef SIGKILL
    if (sys_sigabbrev[SIGKILL] == NULL)
	sys_sigabbrev[SIGKILL] = "KILL";
#endif
#ifdef SIGUNUSED
    if (sys_sigabbrev[SIGUNUSED] == NULL)
	sys_sigabbrev[SIGUNUSED] = "UNUSED";
#endif
#ifdef SIGBUS
    if (sys_sigabbrev[SIGBUS] == NULL)
	sys_sigabbrev[SIGBUS] = "BUS";
#endif
#ifdef SIGSEGV
    if (sys_sigabbrev[SIGSEGV] == NULL)
	sys_sigabbrev[SIGSEGV] = "SEGV";
#endif
#ifdef SIGSYS
    if (sys_sigabbrev[SIGSYS] == NULL)
	sys_sigabbrev[SIGSYS] = "SYS";
#endif
#ifdef SIGPIPE
    if (sys_sigabbrev[SIGPIPE] == NULL)
	sys_sigabbrev[SIGPIPE] = "PIPE";
#endif
#ifdef SIGALRM
    if (sys_sigabbrev[SIGALRM] == NULL)
	sys_sigabbrev[SIGALRM] = "ALRM";
#endif
#ifdef SIGTERM
    if (sys_sigabbrev[SIGTERM] == NULL)
	sys_sigabbrev[SIGTERM] = "TERM";
#endif
#ifdef SIGSTKFLT
    if (sys_sigabbrev[SIGSTKFLT] == NULL)
	sys_sigabbrev[SIGSTKFLT] = "STKFLT";
#endif
#ifdef SIGIO
    if (sys_sigabbrev[SIGIO] == NULL)
	sys_sigabbrev[SIGIO] = "IO";
#endif
#ifdef SIGXCPU
    if (sys_sigabbrev[SIGXCPU] == NULL)
	sys_sigabbrev[SIGXCPU] = "XCPU";
#endif
#ifdef SIGXFSZ
    if (sys_sigabbrev[SIGXFSZ] == NULL)
	sys_sigabbrev[SIGXFSZ] = "XFSZ";
#endif
#ifdef SIGVTALRM
    if (sys_sigabbrev[SIGVTALRM] == NULL)
	sys_sigabbrev[SIGVTALRM] = "VTALRM";
#endif
#ifdef SIGPROF
    if (sys_sigabbrev[SIGPROF] == NULL)
	sys_sigabbrev[SIGPROF] = "PROF";
#endif
#ifdef SIGWINCH
    if (sys_sigabbrev[SIGWINCH] == NULL)
	sys_sigabbrev[SIGWINCH] = "WINCH";
#endif
#ifdef SIGLOST
    if (sys_sigabbrev[SIGLOST] == NULL)
	sys_sigabbrev[SIGLOST] = "LOST";
#endif
#ifdef SIGUSR1
    if (sys_sigabbrev[SIGUSR1] == NULL)
	sys_sigabbrev[SIGUSR1] = "USR1";
#endif
#ifdef SIGUSR2
    if (sys_sigabbrev[SIGUSR2] == NULL)
	sys_sigabbrev[SIGUSR2] = "USR2";
#endif
#ifdef SIGPWR
    if (sys_sigabbrev[SIGPWR] == NULL)
	sys_sigabbrev[SIGPWR] = "PWR";
#endif
#ifdef SIGPOLL
    if (sys_sigabbrev[SIGPOLL] == NULL)
	sys_sigabbrev[SIGPOLL] = "POLL";
#endif
#ifdef SIGSTOP
    if (sys_sigabbrev[SIGSTOP] == NULL)
	sys_sigabbrev[SIGSTOP] = "STOP";
#endif
#ifdef SIGTSTP
    if (sys_sigabbrev[SIGTSTP] == NULL)
	sys_sigabbrev[SIGTSTP] = "TSTP";
#endif
#ifdef SIGCONT
    if (sys_sigabbrev[SIGCONT] == NULL)
	sys_sigabbrev[SIGCONT] = "CONT";
#endif
#ifdef SIGCHLD
    if (sys_sigabbrev[SIGCHLD] == NULL)
	sys_sigabbrev[SIGCHLD] = "CHLD";
#endif
#ifdef SIGCLD
    if (sys_sigabbrev[SIGCLD] == NULL)
	sys_sigabbrev[SIGCLD] = "CLD";
#endif
#ifdef SIGTTIN
    if (sys_sigabbrev[SIGTTIN] == NULL)
	sys_sigabbrev[SIGTTIN] = "TTIN";
#endif
#ifdef SIGTTOU
    if (sys_sigabbrev[SIGTTOU] == NULL)
	sys_sigabbrev[SIGTTOU] = "TTOU";
#endif
#ifdef SIGINFO
    if (sys_sigabbrev[SIGINFO] == NULL)
	sys_sigabbrev[SIGINFO] = "INFO";
#endif
#ifdef SIGURG
    if (sys_sigabbrev[SIGURG] == NULL)
	sys_sigabbrev[SIGURG] = "URG";
#endif
#ifdef SIGWAITING
    if (sys_sigabbrev[SIGWAITING] == NULL)
	sys_sigabbrev[SIGWAITING] = "WAITING";
#endif
#ifdef SIGLWP
    if (sys_sigabbrev[SIGLWP] == NULL)
	sys_sigabbrev[SIGLWP] = "LWP";
#endif
#ifdef SIGFREEZE
    if (sys_sigabbrev[SIGFREEZE] == NULL)
	sys_sigabbrev[SIGFREEZE] = "FREEZE";
#endif
#ifdef SIGTHAW
    if (sys_sigabbrev[SIGTHAW] == NULL)
	sys_sigabbrev[SIGTHAW] = "THAW";
#endif
#ifdef SIGCANCEL
    if (sys_sigabbrev[SIGCANCEL] == NULL)
	sys_sigabbrev[SIGCANCEL] = "CANCEL";
#endif
#endif
}
