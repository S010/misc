#!/bin/sh

os=`uname -s | tr A-Z a-z`

err() {
    exitcode=$1
    shift
    echo "$0: error: $@" 2>&1
    exit $exitcode
}

case "$os" in
*linux*)
    case "$1" in
    +)
        amixer sset Master 3%+
        ;;
    -)
        amixer sset Master 3%-
        ;;
    mute)
        amixer sset Master toggle
        ;;
    *)
        err 1 unknown command
        ;;
    esac
    ;;
*openbsd*)
    case "$1" in
    +)
        mixerctl -q outputs.hp=+10
        ;;
    -)
        mixerctl -q outputs.hp=-10
        ;;
    *)
        err 1 unknown command
        ;;
    esac
    ;;
*freebsd*)
    case "$1" in
    +)
	mixer -s vol +2
	;;
    -)
	mixer -s vol -2
	;;
    *)
	err 1 unknown command
	;;
    esac
    ;;
*)
    err 1 unknown os
    ;;
esac

