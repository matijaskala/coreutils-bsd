#include <signal.h>

static const char* signalnamestr(int sig) {
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

#ifdef SIGBREAK
    if (sig == SIGBREAK) return "BREAK";
#endif
#ifdef SIGCKPT
    if (sig == SIGCKPT) return "CKPT";
#endif
#ifdef SIGCPUFAIL
    if (sig == SIGCPUFAIL) return "CPUFAIL";
#endif
#ifdef SIGDANGER
    if (sig == SIGDANGER) return "DANGER";
#endif
#ifdef SIGKAP
    if (sig == SIGKAP) return "KAP";
#endif
#ifdef SIGKILLTHR
    if (sig == SIGKILLTHR) return "KILLTHR";
#endif
#ifdef SIGKMEM
    if (sig == SIGKMEM) return "KMEM";
#endif
#ifdef SIGKMESS
    if (sig == SIGKMESS) return "KMESS";
#endif
#ifdef SIGKSIG
    if (sig == SIGKSIG) return "KSIG";
#endif
#ifdef SIGKSIGM
    if (sig == SIGKSIGSM) return "KSIGSM";
#endif
#ifdef SIGLIBRT
    if (sig == SIGLIBRT) return "LIBRT";
#endif
#ifdef SIGMIGRATE
    if (sig == SIGMIGRATE) return "MIGRATE";
#endif
#ifdef SIGMSG
    if (sig == SIGMSG) return "MSG";
#endif
#ifdef SIGPRE
    if (sig == SIGPRE) return "PRE";
#endif
#ifdef SIGPTINTR
    if (sig == SIGPTINTR) return "PTINTR";
#endif
#ifdef SIGPTRESCHED
    if (sig == SIGPTRESCHED) return "PTRESCHED";
#endif
#ifdef SIGRECONFIG
    if (sig == SIGRECONFIG) return "RECONFIG";
#endif
#ifdef SIGRECOVERY
    if (sig == SIGRECOVERY) return "RECOVERY";
#endif
#ifdef SIGRESTART
    if (sig == SIGRESTART) return "RESTART";
#endif
#ifdef SIGRETRACT
    if (sig == SIGRETRACT) return "RETRACT";
#endif
#ifdef SIGSAK
    if (sig == SIGSAK) return "SAK";
#endif
#ifdef SIGSNDELAY
    if (sig == SIGSNDELAY) return "SNDELAY";
#endif
#ifdef SIGSOUND
    if (sig == SIGSOUND) return "SOUND";
#endif
#ifdef SIGSYSERROR
    if (sig == SIGSYSERROR) return "SYSERROR";
#endif
#ifdef SIGTALRM
    if (sig == SIGTALRM) return "TALRM";
#endif
#ifdef SIGTHR
    if (sig == SIGTHR) return "THR";
#endif
#ifdef SIGUME
    if (sig == SIGUME) return "UME";
#endif
#ifdef SIGVIRT
    if (sig == SIGVIRT) return "VIRT";
#endif

    return "Signal 0";
}
