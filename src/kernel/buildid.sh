COMMIT=$(git --no-pager log -1 --pretty=format:%h)

echo "char *kernel_buildid=\"$COMMIT\";" > buildid.c