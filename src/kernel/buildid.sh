COMMIT=$(git --no-pager log -1 --pretty=format:%h)
BRANCH=$(git rev-parse --abbrev-ref HEAD)

echo "char *kernel_buildid=\"$BRANCH/$COMMIT\";" > buildid.c