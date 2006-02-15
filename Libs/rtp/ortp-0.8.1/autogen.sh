set -x
rm -rf config.cache autom4te.cache
aclocal
autoheader
automake --force-missing --add-missing --copy
libtoolize --copy --force
autoconf
