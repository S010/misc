#!/bin/sh

progname=${0##*/}
screenshotdir="$HOME/screenshots"
screenshotext="png"

error() {
    echo "$progname: $@" 1>&2
    exit 1
}

usage() {
    echo "usage: $progname [-f]"
    echo "Take a screenshot and put it into $screenshotdir."
    echo " -f -- take a fullscreen screenshot"
}

if ! which import > /dev/null; then
    error "import command not found, nothing to take screenshot with"
fi

mkdir -p "$screenshotdir" || error "failed to create $screenshotdir directory"

fullscreen=0

while [ $# -gt 0 ]; do
    case "$1" in
    -f)
        fullscreen=1
        ;;
    -h|--help)
        usage
        exit 0
        ;;
    *)
        usage
        exit 1
        ;;
    esac
    shift
done

n_images=`ls "$screenshotdir"/*$screenshotext | wc -l`
n_images=$(($n_images+1))
file_no=`printf %04d $n_images`
filename="$screenshotdir/screenshot_$file_no.png"

if [ $fullscreen -eq 1 ]; then
    import -window root "$filename"
else
    import "$filename"
fi

